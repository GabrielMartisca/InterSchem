#pragma once
#include "graphics.h"
#include "interface.h"
#include "blocks.h"
#include "file.h"
#include "lines.h"
#include <string.h>
#include "run.h"
bool isInputClicked = false;
int mx, my; // mouse coords
bool uniqueStart = true, uniqueStop = true;
int page = 0;

void insert()
{
	if (!isInputClicked)
		drawInsertMenu();
	else delInsertMenu();
}

void drawLines()
{
	for (int i = 0; i < linesIndex; i++)
	{
		line(lines[i].x1, lines[i].y1, lines[i].x1, (lines[i].y1+lines[i].y2)/2);
		line(lines[i].x1, (lines[i].y1 + lines[i].y2) / 2, lines[i].x2, (lines[i].y1 + lines[i].y2) / 2);
		line(lines[i].x2, (lines[i].y1 + lines[i].y2) / 2, lines[i].x2, lines[i].y2);
	}
}
void redrawObj() //REDRAW BLOCKS
{
	setactivepage(page);
	cleardevice();
	drawMenu();
	if (isInputClicked)
		drawInsertMenu();
	else {
		setbkcolor(WHITE);
		setcolor(BLACK);
		setfillstyle(1, WHITE);
	}
	for (int i = 0; i < drawnObjects; i++)
		if (drawnBlocks[i].isStart)
			desenStart(drawnBlocks[i].xmiddle, drawnBlocks[i].ymiddle);
		else if (drawnBlocks[i].isStop)
			desenStop(drawnBlocks[i].xmiddle, drawnBlocks[i].ymiddle);
		else if (drawnBlocks[i].isIfCond)
			desenIF(drawnBlocks[i].xmiddle, drawnBlocks[i].ymiddle, drawnBlocks[i].text);
		else if (drawnBlocks[i].isVariable)
			desenCitire(drawnBlocks[i].xmiddle, drawnBlocks[i].ymiddle, drawnBlocks[i].text);
		else if (drawnBlocks[i].isOutput)
			desenScriere(drawnBlocks[i].xmiddle, drawnBlocks[i].ymiddle, drawnBlocks[i].text);
		else if (drawnBlocks[i].isExpression)
			desenExpresie(drawnBlocks[i].xmiddle, drawnBlocks[i].ymiddle, drawnBlocks[i].text);
	drawLines();
	setvisualpage(page);
	page = 1 - page;
}
//
void active()
{
	while (1)
	{
		//menu buttons
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, mx, my);
			if (mx >= menuButtons[0].xtopleft && mx <= menuButtons[0].xbotright and my >= menuButtons[0].ytopleft && my <= menuButtons[0].ybotright)
			{
				insert();
				if (isInputClicked)
					isInputClicked = false;
				else isInputClicked = true;
			}
			if (mx >= menuButtons[1].xtopleft && mx <= menuButtons[1].xbotright and my >= menuButtons[1].ytopleft && my <= menuButtons[1].ybotright)
			{
				redrawObj();
				delay(500);
				run();
			}
			if (mx >= menuButtons[2].xtopleft && mx <= menuButtons[2].xbotright and my >= menuButtons[2].ytopleft && my <= menuButtons[2].ybotright)
			{
				delLines();
				redrawObj();
			}
			if (mx >= menuButtons[3].xtopleft && mx <= menuButtons[3].xbotright and my >= menuButtons[3].ytopleft && my <= menuButtons[3].ybotright)
			{
				openFile();
				if (fileWasOpened)
					if (drawnObjects)
					{
						redrawObj(); // quick fix for page being white if no blocks are moved before pressing load
						redrawObj();
					}
					else std::cout << "Empty Scheme.\n";
			}
			if (mx >= menuButtons[4].xtopleft && mx <= menuButtons[4].xbotright and my >= menuButtons[4].ytopleft && my <= menuButtons[4].ybotright)
				saveFile();
			if (mx >= menuButtons[5].xtopleft && mx <= menuButtons[5].xbotright and my >= menuButtons[5].ytopleft && my <= menuButtons[5].ybotright)
			{
				loadFile();
				if (fileWasOpened)
				{
					redrawObj(); // quick fix for page being white if no blocks are moved before pressing load
					redrawObj();
				}
			}
	//input menu
			if (isInputClicked)
			{
				//DRAW START BLOCK
				if (mx >= insertMenu[0].xtopleft && mx <= insertMenu[0].xbotright and my >= insertMenu[0].ytopleft && my <= insertMenu[0].ybotright)
				{
					for (int i = 0; i < drawnObjects; i++)
						if (drawnBlocks[i].isStart == true)
							uniqueStart = false;
					if (uniqueStart)
					{
						drawnBlocks[drawnObjects].xmiddle = 500;
						drawnBlocks[drawnObjects].ymiddle = 200;
						changeText = true;
						updateStart(drawnBlocks[drawnObjects].xmiddle, drawnBlocks[drawnObjects].ymiddle, drawnObjects);
						changeText = false;
						desenStart(drawnBlocks[drawnObjects].xmiddle, drawnBlocks[drawnObjects].ymiddle);
						drawnObjects++;
					}
					else std::cout << "There can only be one START block.\n";
				}
				//DRAW STOP BLOCK
				if (mx >= insertMenu[1].xtopleft && mx <= insertMenu[1].xbotright and my >= insertMenu[1].ytopleft && my <= insertMenu[1].ybotright)
				{
					for (int i = 0; i < drawnObjects; i++)
						if (drawnBlocks[i].isStop == true)
							uniqueStop = false;
					if (uniqueStop)
					{
						drawnBlocks[drawnObjects].xmiddle = 500;
						drawnBlocks[drawnObjects].ymiddle = 300;
						changeText = true;
						updateStop(drawnBlocks[drawnObjects].xmiddle, drawnBlocks[drawnObjects].ymiddle, drawnObjects);
						changeText = false;
						desenStop(drawnBlocks[drawnObjects].xmiddle, drawnBlocks[drawnObjects].ymiddle);
						drawnObjects++;
					}
					else std::cout << "There can only be one STOP block.\n";
				}
				//DRAW IF CONDITION BLOCK
				if (mx >= insertMenu[2].xtopleft && mx <= insertMenu[2].xbotright and my >= insertMenu[2].ytopleft && my <= insertMenu[2].ybotright)
				{
					drawnBlocks[drawnObjects].xmiddle = 500;
					drawnBlocks[drawnObjects].ymiddle = 400;
					changeText = true;
					updateIfCond(drawnBlocks[drawnObjects].xmiddle, drawnBlocks[drawnObjects].ymiddle, drawnObjects);
					changeText = false;
					desenIF(drawnBlocks[drawnObjects].xmiddle, drawnBlocks[drawnObjects].ymiddle, drawnBlocks[drawnObjects].text);
					drawnObjects++;
				}
				//DRAW INPUT BLOCK
				if (mx >= insertMenu[3].xtopleft && mx <= insertMenu[3].xbotright and my >= insertMenu[3].ytopleft && my <= insertMenu[3].ybotright)
				{
					drawnBlocks[drawnObjects].xmiddle = 500;
					drawnBlocks[drawnObjects].ymiddle = 500;
					changeText = true;
					updateVariable(drawnBlocks[drawnObjects].xmiddle, drawnBlocks[drawnObjects].ymiddle, drawnObjects);
					changeText = false;
					desenCitire(drawnBlocks[drawnObjects].xmiddle, drawnBlocks[drawnObjects].ymiddle, drawnBlocks[drawnObjects].text);
					drawnObjects++;
				}
				//DRAW OUTPUT BLOCK
				if (mx >= insertMenu[4].xtopleft && mx <= insertMenu[4].xbotright and my >= insertMenu[4].ytopleft && my <= insertMenu[4].ybotright)
				{
					drawnBlocks[drawnObjects].xmiddle = 500;
					drawnBlocks[drawnObjects].ymiddle = 600;
					changeText = true;
					updateOutput(drawnBlocks[drawnObjects].xmiddle, drawnBlocks[drawnObjects].ymiddle, drawnObjects);
					changeText = false;
					desenScriere(drawnBlocks[drawnObjects].xmiddle, drawnBlocks[drawnObjects].ymiddle, drawnBlocks[drawnObjects].text);
					drawnObjects++;
				}
				//DRAW EXPRESSION BLOCK
				if (mx >= insertMenu[5].xtopleft && mx <= insertMenu[5].xbotright and my >= insertMenu[5].ytopleft && my <= insertMenu[5].ybotright)
				{
					drawnBlocks[drawnObjects].xmiddle = 500;
					drawnBlocks[drawnObjects].ymiddle = 700;
					changeText = true;
					updateExp(drawnBlocks[drawnObjects].xmiddle, drawnBlocks[drawnObjects].ymiddle, drawnObjects);
					changeText = false;
					desenExpresie(drawnBlocks[drawnObjects].xmiddle, drawnBlocks[drawnObjects].ymiddle, drawnBlocks[drawnObjects].text);
					drawnObjects++;
				}
			}
		}
		//edit block text
		if (ismouseclick(WM_LBUTTONDBLCLK))
		{
			getmouseclick(WM_LBUTTONDBLCLK, mx, my);
			for(int i = 0; i<drawnObjects; i++)
				if (mx >= drawnBlocks[i].xtopleft && mx <= drawnBlocks[i].xbotright and my >= drawnBlocks[i].ytopleft && my <= drawnBlocks[i].ybotright)
				{
					changeText = true;
					if (drawnBlocks[i].isStart == false and drawnBlocks[i].isStop == false)
					{
						if (drawnBlocks[i].isExpression)
						{
							updateExp(drawnBlocks[i].xmiddle, drawnBlocks[i].ymiddle, i);
							redrawObj();
						}
						if (drawnBlocks[i].isOutput)
						{
							updateOutput(drawnBlocks[i].xmiddle, drawnBlocks[i].ymiddle, i);
							redrawObj();
						}
						if (drawnBlocks[i].isVariable)
						{
							updateVariable(drawnBlocks[i].xmiddle, drawnBlocks[i].ymiddle, i);
							redrawObj();
						}
						if (drawnBlocks[i].isIfCond)
						{
							updateIfCond(drawnBlocks[i].xmiddle, drawnBlocks[i].ymiddle, i);
							redrawObj();
						}
					}
					changeText = false;
				}
		}
		//move block
		if (ismouseclick(WM_RBUTTONDOWN))
		{
			getmouseclick(WM_RBUTTONDOWN, mx, my);
			for (int i = 0; i < drawnObjects; i++)
				if (mx >= drawnBlocks[i].xtopleft && mx <= drawnBlocks[i].xbotright and my >= drawnBlocks[i].ytopleft && my <= drawnBlocks[i].ybotright)
				{	
					if (drawnBlocks[i].movable == -1) 
					{
						if (ismouseclick(WM_RBUTTONUP))
							clearmouseclick(WM_RBUTTONUP);
						while (!ismouseclick(WM_RBUTTONUP))
						{
							if (ismouseclick(WM_MOUSEMOVE))
								getmouseclick(WM_MOUSEMOVE, mx, my);
						
							//x axis bound
							if (mx < xmin)
								drawnBlocks[i].xmiddle = xmin+50;
							else if (mx > xmax)
								drawnBlocks[i].xmiddle = xmax-50;
							else drawnBlocks[i].xmiddle = mx;
							//y axis bound
							if (my < ymin)
								drawnBlocks[i].ymiddle = ymin+50;
							else if(my>ymax)
								drawnBlocks[i].ymiddle = ymax-50;
							else drawnBlocks[i].ymiddle = my;


							if (drawnBlocks[i].isStart)
								updateStart(drawnBlocks[i].xmiddle, drawnBlocks[i].ymiddle, i);
							else if (drawnBlocks[i].isStop)
								updateStop(drawnBlocks[i].xmiddle, drawnBlocks[i].ymiddle, i);
							else if (drawnBlocks[i].isExpression)
								updateExp(drawnBlocks[i].xmiddle, drawnBlocks[i].ymiddle, i);
							else if (drawnBlocks[i].isOutput)
								updateOutput(drawnBlocks[i].xmiddle, drawnBlocks[i].ymiddle, i);
							else if (drawnBlocks[i].isVariable)
								updateVariable(drawnBlocks[i].xmiddle, drawnBlocks[i].ymiddle, i);
							else if (drawnBlocks[i].isIfCond)
								updateIfCond(drawnBlocks[i].xmiddle, drawnBlocks[i].ymiddle, i);
							redrawObj();
							delay(10);
						}
					}
				}
		}
		
		//create line
		if (ismouseclick(WM_MBUTTONDOWN))
		{
			getmouseclick(WM_MBUTTONDOWN, mx, my);
			for (int i = 0; i < drawnObjects; i++)
			{
				bool drawLine = false;
				if (mx >= drawnBlocks[i].xtopleftC1 && mx <= drawnBlocks[i].xbotrightC1 and my >= drawnBlocks[i].ytopleftC1 && my <= drawnBlocks[i].ybotrightC1)
				{
					std::cout << "clicked circle1\n";
					drawLine = true;
					while (drawLine)
					{
						if (ismouseclick(WM_MBUTTONDOWN))
						{
							getmouseclick(WM_MBUTTONDOWN, mx, my);
							for(int j = 0; j<drawnObjects && drawLine; j++)
								if (i != j)
								{
									if (mx >= drawnBlocks[j].xtopleftC1 && mx <= drawnBlocks[j].xbotrightC1 and my >= drawnBlocks[j].ytopleftC1 && my <= drawnBlocks[j].ybotrightC1)
									{
										lines[linesIndex].x1 = (drawnBlocks[i].xtopleftC1 + drawnBlocks[i].xbotrightC1) / 2;
										lines[linesIndex].x2 = (drawnBlocks[j].xtopleftC1 + drawnBlocks[j].xbotrightC1) / 2;
										lines[linesIndex].y1 = (drawnBlocks[i].ytopleftC1 + drawnBlocks[i].ybotrightC1) / 2;
										lines[linesIndex].y2 = (drawnBlocks[j].ytopleftC1 + drawnBlocks[j].ybotrightC1) / 2;
										lines[linesIndex].indexBlock1 = i;
										lines[linesIndex].indexBlock2 = j;
										linesIndex++;
										drawnBlocks[i].movable = drawnBlocks[j].movable = 0; 
										drawnBlocks[i].linecounter++;
										drawLine = false;
										drawLines();
									}
									else if (mx >= drawnBlocks[j].xtopleftC2 && mx <= drawnBlocks[j].xbotrightC2 and my >= drawnBlocks[j].ytopleftC2 && my <= drawnBlocks[j].ybotrightC2)
									{
										lines[linesIndex].x1 = (drawnBlocks[i].xtopleftC1 + drawnBlocks[i].xbotrightC1) / 2;
										lines[linesIndex].x2 = (drawnBlocks[j].xtopleftC2 + drawnBlocks[j].xbotrightC2) / 2;
										lines[linesIndex].y1 = (drawnBlocks[i].ytopleftC1 + drawnBlocks[i].ybotrightC1) / 2;
										lines[linesIndex].y2 = (drawnBlocks[j].ytopleftC2 + drawnBlocks[j].ybotrightC2) / 2;
										lines[linesIndex].indexBlock1 = i;
										lines[linesIndex].indexBlock2 = j;
										linesIndex++;
										drawnBlocks[i].movable = drawnBlocks[j].movable = 0; 
										drawnBlocks[i].linecounter++;
										drawLine = false;
										drawLines();
									}
									else if (mx >= drawnBlocks[j].xtopleftC3 && mx <= drawnBlocks[j].xbotrightC3 and my >= drawnBlocks[j].ytopleftC3 && my <= drawnBlocks[j].ybotrightC3)
									{
										lines[linesIndex].x1 = (drawnBlocks[i].xtopleftC1 + drawnBlocks[i].xbotrightC1) / 2;
										lines[linesIndex].x2 = (drawnBlocks[j].xtopleftC3 + drawnBlocks[j].xbotrightC3) / 2;
										lines[linesIndex].y1 = (drawnBlocks[i].ytopleftC1 + drawnBlocks[i].ybotrightC1) / 2;
										lines[linesIndex].y2 = (drawnBlocks[j].ytopleftC3 + drawnBlocks[j].ybotrightC3) / 2;
										lines[linesIndex].indexBlock1 = i;
										lines[linesIndex].indexBlock2 = j;
										linesIndex++;
										drawnBlocks[i].movable = drawnBlocks[j].movable = 0; 
										drawnBlocks[i].linecounter++;
										drawLine = false;
										drawLines();
									}
									else if (mx >= drawnBlocks[j].xtopleftC4 && mx <= drawnBlocks[j].xbotrightC4 and my >= drawnBlocks[j].ytopleftC4 && my <= drawnBlocks[j].ybotrightC4)
									{
										lines[linesIndex].x1 = (drawnBlocks[i].xtopleftC1 + drawnBlocks[i].xbotrightC1) / 2;
										lines[linesIndex].x2 = (drawnBlocks[j].xtopleftC4 + drawnBlocks[j].xbotrightC4) / 2;
										lines[linesIndex].y1 = (drawnBlocks[i].ytopleftC1 + drawnBlocks[i].ybotrightC1) / 2;
										lines[linesIndex].y2 = (drawnBlocks[j].ytopleftC4 + drawnBlocks[j].ybotrightC4) / 2;
										lines[linesIndex].indexBlock1 = i;
										lines[linesIndex].indexBlock2 = j;
										linesIndex++;
										drawnBlocks[i].movable = drawnBlocks[j].movable = 0; 
										drawnBlocks[i].linecounter++;
										drawLine = false;
										drawLines();
									}
								}
							drawLine = false;
						}
					}
				}
				else if (mx >= drawnBlocks[i].xtopleftC2 && mx <= drawnBlocks[i].xbotrightC2 and my >= drawnBlocks[i].ytopleftC2 && my <= drawnBlocks[i].ybotrightC2)
				{
					std::cout << "clicked circle2\n";
					drawLine = true;
					while (drawLine)
					{
						if (ismouseclick(WM_MBUTTONDOWN))
						{
							getmouseclick(WM_MBUTTONDOWN, mx, my);
							for (int j = 0; j < drawnObjects && drawLine; j++)
								if (i != j)
								{
									if (mx >= drawnBlocks[j].xtopleftC1 && mx <= drawnBlocks[j].xbotrightC1 and my >= drawnBlocks[j].ytopleftC1 && my <= drawnBlocks[j].ybotrightC1)
									{
										lines[linesIndex].x1 = (drawnBlocks[i].xtopleftC2 + drawnBlocks[i].xbotrightC2) / 2;
										lines[linesIndex].x2 = (drawnBlocks[j].xtopleftC1 + drawnBlocks[j].xbotrightC1) / 2;
										lines[linesIndex].y1 = (drawnBlocks[i].ytopleftC2 + drawnBlocks[i].ybotrightC2) / 2;
										lines[linesIndex].y2 = (drawnBlocks[j].ytopleftC1 + drawnBlocks[j].ybotrightC1) / 2;
										lines[linesIndex].indexBlock1 = i;
										lines[linesIndex].indexBlock2 = j;
										linesIndex++;
										drawnBlocks[i].movable = drawnBlocks[j].movable = 0; 
										drawnBlocks[i].linecounter++;
										drawLine = false;
										drawLines();
									}
									else if (mx >= drawnBlocks[j].xtopleftC2 && mx <= drawnBlocks[j].xbotrightC2 and my >= drawnBlocks[j].ytopleftC2 && my <= drawnBlocks[j].ybotrightC2)
									{
										lines[linesIndex].x1 = (drawnBlocks[i].xtopleftC2 + drawnBlocks[i].xbotrightC2) / 2;
										lines[linesIndex].x2 = (drawnBlocks[j].xtopleftC2 + drawnBlocks[j].xbotrightC2) / 2;
										lines[linesIndex].y1 = (drawnBlocks[i].ytopleftC2 + drawnBlocks[i].ybotrightC2) / 2;
										lines[linesIndex].y2 = (drawnBlocks[j].ytopleftC2 + drawnBlocks[j].ybotrightC2) / 2;
										lines[linesIndex].indexBlock1 = i;
										lines[linesIndex].indexBlock2 = j;
										linesIndex++;
										drawnBlocks[i].movable = drawnBlocks[j].movable = 0; 
										drawnBlocks[i].linecounter++;
										drawLine = false;
										drawLines();
									}
									else if (mx >= drawnBlocks[j].xtopleftC3 && mx <= drawnBlocks[j].xbotrightC3 and my >= drawnBlocks[j].ytopleftC3 && my <= drawnBlocks[j].ybotrightC3)
									{
										lines[linesIndex].x1 = (drawnBlocks[i].xtopleftC2 + drawnBlocks[i].xbotrightC2) / 2;
										lines[linesIndex].x2 = (drawnBlocks[j].xtopleftC3 + drawnBlocks[j].xbotrightC3) / 2;
										lines[linesIndex].y1 = (drawnBlocks[i].ytopleftC2 + drawnBlocks[i].ybotrightC2) / 2;
										lines[linesIndex].y2 = (drawnBlocks[j].ytopleftC3 + drawnBlocks[j].ybotrightC3) / 2;
										lines[linesIndex].indexBlock1 = i;
										lines[linesIndex].indexBlock2 = j;
										linesIndex++;
										drawnBlocks[i].movable = drawnBlocks[j].movable = 0; 
										drawnBlocks[i].linecounter++;
										drawLine = false;
										drawLines();
									}
									else if (mx >= drawnBlocks[j].xtopleftC4 && mx <= drawnBlocks[j].xbotrightC4 and my >= drawnBlocks[j].ytopleftC4 && my <= drawnBlocks[j].ybotrightC4)
									{
										lines[linesIndex].x1 = (drawnBlocks[i].xtopleftC2 + drawnBlocks[i].xbotrightC2) / 2;
										lines[linesIndex].x2 = (drawnBlocks[j].xtopleftC4 + drawnBlocks[j].xbotrightC4) / 2;
										lines[linesIndex].y1 = (drawnBlocks[i].ytopleftC2 + drawnBlocks[i].ybotrightC2) / 2;
										lines[linesIndex].y2 = (drawnBlocks[j].ytopleftC4 + drawnBlocks[j].ybotrightC4) / 2;
										lines[linesIndex].indexBlock1 = i;
										lines[linesIndex].indexBlock2 = j;
										linesIndex++;
										drawnBlocks[i].movable = drawnBlocks[j].movable = 0; 
										drawnBlocks[i].linecounter++;
										drawLine = false;
										drawLines();
									}
								}
							drawLine = false;
						}
					}
				}
				else if (mx >= drawnBlocks[i].xtopleftC3 && mx <= drawnBlocks[i].xbotrightC3 and my >= drawnBlocks[i].ytopleftC3 && my <= drawnBlocks[i].ybotrightC3)
				{
					std::cout << "clicked circle3\n";
					drawLine = true;
					while (drawLine)
					{
						if (ismouseclick(WM_MBUTTONDOWN))
						{
							getmouseclick(WM_MBUTTONDOWN, mx, my);
							for (int j = 0; j < drawnObjects && drawLine; j++)
								if (i != j)
								{
									if (mx >= drawnBlocks[j].xtopleftC1 && mx <= drawnBlocks[j].xbotrightC1 and my >= drawnBlocks[j].ytopleftC1 && my <= drawnBlocks[j].ybotrightC1)
									{
										lines[linesIndex].x1 = (drawnBlocks[i].xtopleftC3 + drawnBlocks[i].xbotrightC3) / 2;
										lines[linesIndex].x2 = (drawnBlocks[j].xtopleftC1 + drawnBlocks[j].xbotrightC1) / 2;
										lines[linesIndex].y1 = (drawnBlocks[i].ytopleftC3 + drawnBlocks[i].ybotrightC3) / 2;
										lines[linesIndex].y2 = (drawnBlocks[j].ytopleftC1 + drawnBlocks[j].ybotrightC1) / 2;
										lines[linesIndex].indexBlock1 = i;
										lines[linesIndex].indexBlock2 = j;
										linesIndex++;
										drawnBlocks[i].movable = drawnBlocks[j].movable = 0; 
										drawnBlocks[i].linecounter++;
										drawLine = false;
										drawLines();
									}
									else if (mx >= drawnBlocks[j].xtopleftC2 && mx <= drawnBlocks[j].xbotrightC2 and my >= drawnBlocks[j].ytopleftC2 && my <= drawnBlocks[j].ybotrightC2)
									{
										lines[linesIndex].x1 = (drawnBlocks[i].xtopleftC3 + drawnBlocks[i].xbotrightC3) / 2;
										lines[linesIndex].x2 = (drawnBlocks[j].xtopleftC2 + drawnBlocks[j].xbotrightC2) / 2;
										lines[linesIndex].y1 = (drawnBlocks[i].ytopleftC3 + drawnBlocks[i].ybotrightC3) / 2;
										lines[linesIndex].y2 = (drawnBlocks[j].ytopleftC2 + drawnBlocks[j].ybotrightC2) / 2;
										lines[linesIndex].indexBlock1 = i;
										lines[linesIndex].indexBlock2 = j;
										linesIndex++;
										drawnBlocks[i].movable = drawnBlocks[j].movable = 0; 
										drawnBlocks[i].linecounter++;
										drawLine = false;
										drawLines();
									}
									else if (mx >= drawnBlocks[j].xtopleftC3 && mx <= drawnBlocks[j].xbotrightC3 and my >= drawnBlocks[j].ytopleftC3 && my <= drawnBlocks[j].ybotrightC3)
									{
										lines[linesIndex].x1 = (drawnBlocks[i].xtopleftC3 + drawnBlocks[i].xbotrightC3) / 2;
										lines[linesIndex].x2 = (drawnBlocks[j].xtopleftC3 + drawnBlocks[j].xbotrightC3) / 2;
										lines[linesIndex].y1 = (drawnBlocks[i].ytopleftC3 + drawnBlocks[i].ybotrightC3) / 2;
										lines[linesIndex].y2 = (drawnBlocks[j].ytopleftC3 + drawnBlocks[j].ybotrightC3) / 2;
										lines[linesIndex].indexBlock1 = i;
										lines[linesIndex].indexBlock2 = j;
										linesIndex++;
										drawnBlocks[i].movable = drawnBlocks[j].movable = 0; 
										drawnBlocks[i].linecounter++;
										drawLine = false;
										drawLines();
									}
									else if (mx >= drawnBlocks[j].xtopleftC4 && mx <= drawnBlocks[j].xbotrightC4 and my >= drawnBlocks[j].ytopleftC4 && my <= drawnBlocks[j].ybotrightC4)
									{
										lines[linesIndex].x1 = (drawnBlocks[i].xtopleftC3 + drawnBlocks[i].xbotrightC3) / 2;
										lines[linesIndex].x2 = (drawnBlocks[j].xtopleftC4 + drawnBlocks[j].xbotrightC4) / 2;
										lines[linesIndex].y1 = (drawnBlocks[i].ytopleftC3 + drawnBlocks[i].ybotrightC3) / 2;
										lines[linesIndex].y2 = (drawnBlocks[j].ytopleftC4 + drawnBlocks[j].ybotrightC4) / 2;
										lines[linesIndex].indexBlock1 = i;
										lines[linesIndex].indexBlock2 = j;
										linesIndex++;
										drawnBlocks[i].movable = drawnBlocks[j].movable = 0; 
										drawnBlocks[i].linecounter++;
										drawLine = false;
										drawLines();
									}
								}
							drawLine = false;
						}
					}
				}
				else if (mx >= drawnBlocks[i].xtopleftC4 && mx <= drawnBlocks[i].xbotrightC4 and my >= drawnBlocks[i].ytopleftC4 && my <= drawnBlocks[i].ybotrightC4)
				{
					std::cout << "clicked circle4\n";
					drawLine = true;
					while (drawLine)
					{
						if (ismouseclick(WM_MBUTTONDOWN))
						{
							getmouseclick(WM_MBUTTONDOWN, mx, my);
							for (int j = 0; j < drawnObjects && drawLine; j++)
								if (i != j)
								{
									if (mx >= drawnBlocks[j].xtopleftC1 && mx <= drawnBlocks[j].xbotrightC1 and my >= drawnBlocks[j].ytopleftC1 && my <= drawnBlocks[j].ybotrightC1)
									{
										lines[linesIndex].x1 = (drawnBlocks[i].xtopleftC4 + drawnBlocks[i].xbotrightC4) / 2;
										lines[linesIndex].x2 = (drawnBlocks[j].xtopleftC1 + drawnBlocks[j].xbotrightC1) / 2;
										lines[linesIndex].y1 = (drawnBlocks[i].ytopleftC4 + drawnBlocks[i].ybotrightC4) / 2;
										lines[linesIndex].y2 = (drawnBlocks[j].ytopleftC1 + drawnBlocks[j].ybotrightC1) / 2;
										lines[linesIndex].indexBlock1 = i;
										lines[linesIndex].indexBlock2 = j;
										linesIndex++;
										drawnBlocks[i].movable = drawnBlocks[j].movable = 0; 
										drawnBlocks[i].linecounter++;
										drawLine = false;
										drawLines();
									}
									else if (mx >= drawnBlocks[j].xtopleftC2 && mx <= drawnBlocks[j].xbotrightC2 and my >= drawnBlocks[j].ytopleftC2 && my <= drawnBlocks[j].ybotrightC2)
									{
										lines[linesIndex].x1 = (drawnBlocks[i].xtopleftC4 + drawnBlocks[i].xbotrightC4) / 2;
										lines[linesIndex].x2 = (drawnBlocks[j].xtopleftC2 + drawnBlocks[j].xbotrightC2) / 2;
										lines[linesIndex].y1 = (drawnBlocks[i].ytopleftC4 + drawnBlocks[i].ybotrightC4) / 2;
										lines[linesIndex].y2 = (drawnBlocks[j].ytopleftC2 + drawnBlocks[j].ybotrightC2) / 2;
										lines[linesIndex].indexBlock1 = i;
										lines[linesIndex].indexBlock2 = j;
										linesIndex++;
										drawnBlocks[i].movable = drawnBlocks[j].movable = 0; 
										drawnBlocks[i].linecounter++;
										drawLine = false;
										drawLines();
									}
									else if (mx >= drawnBlocks[j].xtopleftC3 && mx <= drawnBlocks[j].xbotrightC3 and my >= drawnBlocks[j].ytopleftC3 && my <= drawnBlocks[j].ybotrightC3)
									{
										lines[linesIndex].x1 = (drawnBlocks[i].xtopleftC4 + drawnBlocks[i].xbotrightC4) / 2;
										lines[linesIndex].x2 = (drawnBlocks[j].xtopleftC3 + drawnBlocks[j].xbotrightC3) / 2;
										lines[linesIndex].y1 = (drawnBlocks[i].ytopleftC4 + drawnBlocks[i].ybotrightC4) / 2;
										lines[linesIndex].y2 = (drawnBlocks[j].ytopleftC3 + drawnBlocks[j].ybotrightC3) / 2;
										lines[linesIndex].indexBlock1 = i;
										lines[linesIndex].indexBlock2 = j;
										linesIndex++;
										drawnBlocks[i].movable = drawnBlocks[j].movable = 0; 
										drawnBlocks[i].linecounter++;
										drawLine = false;
										drawLines();
									}
									else if (mx >= drawnBlocks[j].xtopleftC4 && mx <= drawnBlocks[j].xbotrightC4 and my >= drawnBlocks[j].ytopleftC4 && my <= drawnBlocks[j].ybotrightC4)
									{
										lines[linesIndex].x1 = (drawnBlocks[i].xtopleftC4 + drawnBlocks[i].xbotrightC4) / 2;
										lines[linesIndex].x2 = (drawnBlocks[j].xtopleftC4 + drawnBlocks[j].xbotrightC4) / 2;
										lines[linesIndex].y1 = (drawnBlocks[i].ytopleftC4 + drawnBlocks[i].ybotrightC4) / 2;
										lines[linesIndex].y2 = (drawnBlocks[j].ytopleftC4 + drawnBlocks[j].ybotrightC4) / 2;
										lines[linesIndex].indexBlock1 = i;
										lines[linesIndex].indexBlock2 = j;
										linesIndex++;
										drawnBlocks[i].movable = drawnBlocks[j].movable = 0; 
										drawnBlocks[i].linecounter++;
										drawLine = false;
										drawLines();
									}
								}
							drawLine = false;
						}
					}
				}
			}
		}
		//delete block
		if (ismouseclick(WM_MBUTTONDBLCLK))
		{
			getmouseclick(WM_MBUTTONDBLCLK, mx, my);
			for (int i = 0; i < drawnObjects; i++)
				if (mx >= drawnBlocks[i].xtopleft && mx <= drawnBlocks[i].xbotright and my >= drawnBlocks[i].ytopleft && my <= drawnBlocks[i].ybotright)
				{
					//uniqueStart = true, uniqueStop = true;
					if (drawnBlocks[i].isStart)
						uniqueStart = true;
					if (drawnBlocks[i].isStop)
						uniqueStop = true;
					for (int j = i; j < drawnObjects; j++)
						drawnBlocks[j] = drawnBlocks[j + 1];
					drawnObjects--;
					redrawObj();
				}
		}
	}//WHILE(1)
}//FUNCTION END
