#include <cstring>
#include "graphics.h"
#pragma once
#pragma comment (lib,"graphics.lib")
#define maincolor COLOR(20,100,90)

int xmin = 200, xmax = 750;
int ymin = 150, ymax = 750;
struct buttons {
	char name[15] = "";
	int xtopleft = 0, ytopleft = 0, xbotright = 0, ybotright = 0;
}menuButtons[6];

char buttonNames[6][7] = {
	"BLOCKS", "RUN", "RM LN", "IMPORT", "SAVE" ,"LOAD"
};

buttons insertMenu[6];

char blockNames[6][12] = {
	"START", "STOP", "IF", "INPUT", "OUTPUT", "EXPRESSION"
};

void generateMenus()
{
	for (int i = 25, j = 0; j < 6; i += 100, j++)
	{
		strcpy_s(menuButtons[j].name, buttonNames[j]);
		menuButtons[j].xtopleft = i; menuButtons[j].xbotright = i + 115;
		menuButtons[j].ytopleft = 50; menuButtons[j].ybotright = 100;
		i += 25;
	}

	for (int i = 0, j = 110; i < 6; i++, j += 50)
	{
		strcpy_s(insertMenu[i].name, blockNames[i]);
		insertMenu[i].xtopleft = 25; insertMenu[i].xbotright = 140;
		insertMenu[i].ytopleft = j; insertMenu[i].ybotright = j + 50;
		j += 10;
	}
}

void drawMenu()
{
	setbkcolor(WHITE);
	setcolor(BLACK);
	for (int i = 0; i < 6; i++)
	{
		bar(menuButtons[i].xtopleft, menuButtons[i].ytopleft, menuButtons[i].xbotright, menuButtons[i].ybotright);
		outtextxy(menuButtons[i].xtopleft + 10, menuButtons[i].ytopleft + 15, menuButtons[i].name);
	}
}

void drawWindow()
{
	initwindow(800, 800, "Interschem");
	setbkcolor(maincolor);
	cleardevice();
}

void drawInsertMenu()
{
	setbkcolor(WHITE);
	setcolor(BLACK);
	setfillstyle(1, WHITE);
	for (int i = 0; i < 6; i++)
	{
		bar(insertMenu[i].xtopleft, insertMenu[i].ytopleft, insertMenu[i].xbotright, insertMenu[i].ybotright);
		outtextxy(insertMenu[i].xtopleft + 10, insertMenu[i].ytopleft + 15, insertMenu[i].name);
	}
}

void delInsertMenu()
{
	setfillstyle(1, maincolor);
	bar(insertMenu[0].xtopleft, insertMenu[0].ytopleft, insertMenu[5].xbotright, insertMenu[5].ybotright);
}
