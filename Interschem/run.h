#pragma once
#include <iostream>
#include <string.h>
#include "blocks.h"
#include "lines.h"
#include "evaluator.h"
int varIndex = 0;
struct var
{
	char name[15];
	int value;
}vars[30];



int getStartIndex()
{
	for (int i = 0; i < drawnObjects; i++)
		if (drawnBlocks[i].isStart == 1)
			return i;
}

int getStopIndex()
{
	for (int i = 0; i < drawnObjects; i++)
		if (drawnBlocks[i].isStop == 1)
			return i;
}

void run()
{
	//CHECK VALIDITY OF SCHEME (START SHOULD BE CONNECTED, STOP SHOULD BE CONNECTED, THERE SHOULD BE AT LEAST A PATH FROM START TO STOP)
	bool movableStart = true, movableStop = true;
	//check if start and stop block exist and are connected.
	for (int i = 0; i < drawnObjects; i++)
	{
		if (drawnBlocks[i].isStart == 1)
		{
			if (drawnBlocks[i].movable == 0)
				movableStart = false;
		}
		if (drawnBlocks[i].isStop == 1)
		{
			if (drawnBlocks[i].movable == 0)
				movableStop = false;
		}
	}

	int canExecute = 0;

	if (movableStart || movableStop)
	{
		std::cout << "Can't run in this state.\n";
		canExecute = 1;
	}

	//check for path from start to stop
	if (canExecute == 0)
	{
		int startIndex = getStartIndex();
		int stopIndex = getStopIndex();

		for (int i = 0; i < linesIndex; i++)
		{
			if (drawnBlocks[lines[i].indexBlock2].isStart == 1)
			{
				int aux = lines[i].indexBlock1;
				lines[i].indexBlock1 = lines[i].indexBlock2;
				lines[i].indexBlock2 = aux;
			}
			if (drawnBlocks[lines[i].indexBlock1].isStop == 1)
			{
				int aux = lines[i].indexBlock1;
				lines[i].indexBlock1 = lines[i].indexBlock2;
				lines[i].indexBlock2 = aux;
			}
		}

		int firstLine;//"execution" starts from this firstLine, indexBlock1 corresponds to START block
		for (int i = 0; i < linesIndex; i++)
			if (drawnBlocks[lines[i].indexBlock1].isStart == 1)
				firstLine = i;

		bool reachedStop = false;
		int traverseIndex = firstLine;
		int coordX, coordY;
		int ok;
		do
		{
			ok = 0;
			if (drawnBlocks[lines[traverseIndex].indexBlock2].isStop == 1)
				reachedStop = true;
			else if (drawnBlocks[lines[traverseIndex].indexBlock2].isVariable == 1)
			{
				coordX = (drawnBlocks[lines[traverseIndex].indexBlock2].xtopleftC2 + drawnBlocks[lines[traverseIndex].indexBlock2].xbotrightC2) / 2;
				coordY = (drawnBlocks[lines[traverseIndex].indexBlock2].ytopleftC2 + drawnBlocks[lines[traverseIndex].indexBlock2].ybotrightC2) / 2;
				for (int i = 0; i < linesIndex; i++)
					if (lines[i].x1 == coordX && lines[i].y1 == coordY)
					{
						ok = 1;
						traverseIndex = i;
					}
			}
			else if (drawnBlocks[lines[traverseIndex].indexBlock2].isOutput == 1)
			{
				coordX = (drawnBlocks[lines[traverseIndex].indexBlock2].xtopleftC2 + drawnBlocks[lines[traverseIndex].indexBlock2].xbotrightC2) / 2;
				coordY = (drawnBlocks[lines[traverseIndex].indexBlock2].ytopleftC2 + drawnBlocks[lines[traverseIndex].indexBlock2].ybotrightC2) / 2;
				for (int i = 0; i < linesIndex; i++)
					if (lines[i].x1 == coordX && lines[i].y1 == coordY)
					{
						ok = 1;
						traverseIndex = i;
					}
			}
			else if (drawnBlocks[lines[traverseIndex].indexBlock2].isExpression == 1)
			{
				coordX = (drawnBlocks[lines[traverseIndex].indexBlock2].xtopleftC2 + drawnBlocks[lines[traverseIndex].indexBlock2].xbotrightC2) / 2;
				coordY = (drawnBlocks[lines[traverseIndex].indexBlock2].ytopleftC2 + drawnBlocks[lines[traverseIndex].indexBlock2].ybotrightC2) / 2;
				for (int i = 0; i < linesIndex; i++)
					if (lines[i].x1 == coordX && lines[i].y1 == coordY)
					{
						ok = 1;
						traverseIndex = i;
					}
			}
			else if (drawnBlocks[lines[traverseIndex].indexBlock2].isIfCond == 1)
			{
				coordX = (drawnBlocks[lines[traverseIndex].indexBlock2].xtopleftC3 + drawnBlocks[lines[traverseIndex].indexBlock2].xbotrightC3) / 2;
				coordY = (drawnBlocks[lines[traverseIndex].indexBlock2].ytopleftC3 + drawnBlocks[lines[traverseIndex].indexBlock2].ybotrightC3) / 2;
				for (int i = 0; i < linesIndex; i++)
					if (lines[i].x1 == coordX && lines[i].y1 == coordY)
					{
						ok = 1;
						traverseIndex = i;
					}
			}
		} while (ok == 1 && reachedStop == false);

		if (reachedStop == false)
			std::cout << "START is not linked to STOP. Redraw lines from top to bottom.\n";
		else std::cout << "Scheme is valid. Executing..\n";

		if (reachedStop)
		{
			//EXECUTION OF START BLOCK
			traverseIndex = firstLine;
			coordX = coordY = -1;
			reachedStop = false;
			setcolor(RED);
			rectangle(drawnBlocks[lines[firstLine].indexBlock1].xtopleft, drawnBlocks[lines[firstLine].indexBlock1].ytopleft + 10, drawnBlocks[lines[firstLine].indexBlock1].xbotright, drawnBlocks[lines[firstLine].indexBlock1].ybotright);
			delay(500);
			line(lines[firstLine].x1, lines[firstLine].y1, lines[firstLine].x1, (lines[firstLine].y1 + lines[firstLine].y2) / 2);
			line(lines[firstLine].x1, (lines[firstLine].y1 + lines[firstLine].y2) / 2, lines[firstLine].x2, (lines[firstLine].y1 + lines[firstLine].y2) / 2);
			line(lines[firstLine].x2, (lines[firstLine].y1 + lines[firstLine].y2) / 2, lines[firstLine].x2, lines[firstLine].y2);

			do
			{
				//EXECUTION OF STOP BLOCK
				if (drawnBlocks[lines[traverseIndex].indexBlock2].isStop == 1)
				{
					delay(500);
					rectangle(drawnBlocks[lines[traverseIndex].indexBlock2].xtopleft, drawnBlocks[lines[traverseIndex].indexBlock2].ytopleft + 10, drawnBlocks[lines[traverseIndex].indexBlock2].xbotright, drawnBlocks[lines[traverseIndex].indexBlock2].ybotright);
					reachedStop = true;
				}
				//EXECUTION OF INPUT BLOCK
				else if (drawnBlocks[lines[traverseIndex].indexBlock2].isVariable == 1)
				{
					delay(500);
					rectangle(drawnBlocks[lines[traverseIndex].indexBlock2].xtopleft, drawnBlocks[lines[traverseIndex].indexBlock2].ytopleft - 10, drawnBlocks[lines[traverseIndex].indexBlock2].xbotright, drawnBlocks[lines[traverseIndex].indexBlock2].ybotright + 20);
					coordX = (drawnBlocks[lines[traverseIndex].indexBlock2].xtopleftC2 + drawnBlocks[lines[traverseIndex].indexBlock2].xbotrightC2) / 2;
					coordY = (drawnBlocks[lines[traverseIndex].indexBlock2].ytopleftC2 + drawnBlocks[lines[traverseIndex].indexBlock2].ybotrightC2) / 2;

					char* p = strtok(drawnBlocks[lines[traverseIndex].indexBlock2].text, " ");
					bool notDuplicate = true;
					while (p && notDuplicate)
					{
						strcpy(vars[varIndex].name, p);
						for (int i = 0; i < varIndex; i++)
							if (strcmp(p, vars[i].name) == 0)
								notDuplicate = false;
						if (notDuplicate)
						{
							std::cout << "Enter value (int) for: " << p << '\n';
							std::cin >> vars[varIndex++].value;
							p = strtok(NULL, " ");
						}
						else
						{
							for (int i = 0; i < varIndex; i++)
								if (strcmp(p, vars[i].name) == 0)
								{
									std::cout << "Enter value (int) for: " << p << '\n';
									std::cin >> vars[i].value;
									p = strtok(NULL, " ");
								}
							notDuplicate = true;
						}
					}

					for (int i = 0; i < linesIndex; i++)
						if (lines[i].x1 == coordX && lines[i].y1 == coordY)
						{
							traverseIndex = i;
							delay(500);
							line(lines[traverseIndex].x1, lines[traverseIndex].y1, lines[traverseIndex].x1, (lines[traverseIndex].y1 + lines[traverseIndex].y2) / 2);
							line(lines[traverseIndex].x1, (lines[traverseIndex].y1 + lines[traverseIndex].y2) / 2, lines[traverseIndex].x2, (lines[traverseIndex].y1 + lines[traverseIndex].y2) / 2);
							line(lines[traverseIndex].x2, (lines[traverseIndex].y1 + lines[traverseIndex].y2) / 2, lines[traverseIndex].x2, lines[traverseIndex].y2);
						}

				}
				//EXECUTION OF OUTPUT BLOCK
				else if (drawnBlocks[lines[traverseIndex].indexBlock2].isOutput == 1)
				{
					delay(500);
					rectangle(drawnBlocks[lines[traverseIndex].indexBlock2].xtopleft, drawnBlocks[lines[traverseIndex].indexBlock2].ytopleft - 10, drawnBlocks[lines[traverseIndex].indexBlock2].xbotright, drawnBlocks[lines[traverseIndex].indexBlock2].ybotright + 20);
					coordX = (drawnBlocks[lines[traverseIndex].indexBlock2].xtopleftC2 + drawnBlocks[lines[traverseIndex].indexBlock2].xbotrightC2) / 2;
					coordY = (drawnBlocks[lines[traverseIndex].indexBlock2].ytopleftC2 + drawnBlocks[lines[traverseIndex].indexBlock2].ybotrightC2) / 2;

					char* p = strtok(drawnBlocks[lines[traverseIndex].indexBlock2].text, " ");
					while (p)
					{
						bool exists = false;
						for (int i = 0; i < varIndex; i++)
							if (strcmp(p, vars[i].name) == 0)
							{
								std::cout << vars[i].name << ": " << vars[i].value << '\n';
								exists = true;
							}
						if (!exists)
							std::cout << "Variable " << p << " doesn't exist.\n";
						p = strtok(NULL, " ");
					}
					for (int i = 0; i < linesIndex; i++)
						if (lines[i].x1 == coordX && lines[i].y1 == coordY)
						{
							traverseIndex = i;
							delay(500);
							line(lines[traverseIndex].x1, lines[traverseIndex].y1, lines[traverseIndex].x1, (lines[traverseIndex].y1 + lines[traverseIndex].y2) / 2);
							line(lines[traverseIndex].x1, (lines[traverseIndex].y1 + lines[traverseIndex].y2) / 2, lines[traverseIndex].x2, (lines[traverseIndex].y1 + lines[traverseIndex].y2) / 2);
							line(lines[traverseIndex].x2, (lines[traverseIndex].y1 + lines[traverseIndex].y2) / 2, lines[traverseIndex].x2, lines[traverseIndex].y2);
						}
				}
				//EXECUTION OF EXPRESSION BLOCK
				else if (drawnBlocks[lines[traverseIndex].indexBlock2].isExpression == 1)
				{
					delay(500);
					rectangle(drawnBlocks[lines[traverseIndex].indexBlock2].xtopleft, drawnBlocks[lines[traverseIndex].indexBlock2].ytopleft - 20, drawnBlocks[lines[traverseIndex].indexBlock2].xbotright, drawnBlocks[lines[traverseIndex].indexBlock2].ybotright + 20);
					coordX = (drawnBlocks[lines[traverseIndex].indexBlock2].xtopleftC2 + drawnBlocks[lines[traverseIndex].indexBlock2].xbotrightC2) / 2;
					coordY = (drawnBlocks[lines[traverseIndex].indexBlock2].ytopleftC2 + drawnBlocks[lines[traverseIndex].indexBlock2].ybotrightC2) / 2;

					evaluateOperation(drawnBlocks[lines[traverseIndex].indexBlock2].text);

					for (int i = 0; i < linesIndex; i++)
						if (lines[i].x1 == coordX && lines[i].y1 == coordY)
						{
							traverseIndex = i;
							delay(500);
							line(lines[traverseIndex].x1, lines[traverseIndex].y1, lines[traverseIndex].x1, (lines[traverseIndex].y1 + lines[traverseIndex].y2) / 2);
							line(lines[traverseIndex].x1, (lines[traverseIndex].y1 + lines[traverseIndex].y2) / 2, lines[traverseIndex].x2, (lines[traverseIndex].y1 + lines[traverseIndex].y2) / 2);
							line(lines[traverseIndex].x2, (lines[traverseIndex].y1 + lines[traverseIndex].y2) / 2, lines[traverseIndex].x2, lines[traverseIndex].y2);
						}
				}
				//EXECUTION OF IF CONDITION BLOCK
				else if (drawnBlocks[lines[traverseIndex].indexBlock2].isIfCond == 1)
				{
					delay(500);
					rectangle(drawnBlocks[lines[traverseIndex].indexBlock2].xtopleft - 10, drawnBlocks[lines[traverseIndex].indexBlock2].ytopleft - 20, drawnBlocks[lines[traverseIndex].indexBlock2].xbotright + 10, drawnBlocks[lines[traverseIndex].indexBlock2].ybotright + 20);

					// if should have returned a boolean value...
					//bool bTruthValue = evaluateOperation(drawnBlocks[lines[traverseIndex].indexBlock2].text);
					bool bTruthValue = true;

					if (!bTruthValue)
					{
						//coord false branch
						coordX = (drawnBlocks[lines[traverseIndex].indexBlock2].xtopleftC3 + drawnBlocks[lines[traverseIndex].indexBlock2].xbotrightC3) / 2;
						coordY = (drawnBlocks[lines[traverseIndex].indexBlock2].ytopleftC3 + drawnBlocks[lines[traverseIndex].indexBlock2].ybotrightC3) / 2;
						for (int i = 0; i < linesIndex; i++)
							if (lines[i].x1 == coordX && lines[i].y1 == coordY)
							{
								traverseIndex = i;
								delay(500);
								line(lines[traverseIndex].x1, lines[traverseIndex].y1, lines[traverseIndex].x1, (lines[traverseIndex].y1 + lines[traverseIndex].y2) / 2);
								line(lines[traverseIndex].x1, (lines[traverseIndex].y1 + lines[traverseIndex].y2) / 2, lines[traverseIndex].x2, (lines[traverseIndex].y1 + lines[traverseIndex].y2) / 2);
								line(lines[traverseIndex].x2, (lines[traverseIndex].y1 + lines[traverseIndex].y2) / 2, lines[traverseIndex].x2, lines[traverseIndex].y2);
							}
					}
					else
					{
						coordX = (drawnBlocks[lines[traverseIndex].indexBlock2].xtopleftC4 + drawnBlocks[lines[traverseIndex].indexBlock2].xbotrightC4) / 2;
						coordY = (drawnBlocks[lines[traverseIndex].indexBlock2].ytopleftC4 + drawnBlocks[lines[traverseIndex].indexBlock2].ybotrightC4) / 2;
						for (int i = 0; i < linesIndex; i++)
							if (lines[i].x1 == coordX && lines[i].y1 == coordY)
							{
								traverseIndex = i;
								delay(500);
								line(lines[traverseIndex].x1, lines[traverseIndex].y1, lines[traverseIndex].x1, (lines[traverseIndex].y1 + lines[traverseIndex].y2) / 2);
								line(lines[traverseIndex].x1, (lines[traverseIndex].y1 + lines[traverseIndex].y2) / 2, lines[traverseIndex].x2, (lines[traverseIndex].y1 + lines[traverseIndex].y2) / 2);
								line(lines[traverseIndex].x2, (lines[traverseIndex].y1 + lines[traverseIndex].y2) / 2, lines[traverseIndex].x2, lines[traverseIndex].y2);
							}
					}
				}
			} while (reachedStop == false);
			std::cout << "Finished traversing scheme.\n";
		}
	}
}