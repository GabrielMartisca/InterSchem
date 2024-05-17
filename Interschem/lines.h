#pragma once
#include "blocks.h"
int linesIndex = 0, linesIndexCopy = 0;

struct line {
	int indexBlock1, indexBlock2;
	int x1, y1, x2, y2;
}lines[30], linesCopy[30];

void delLines()
{
	linesIndex = 0;
	lines[29].x1 = lines[29].x2 = lines[29].y1 = lines[29].y2 = 0;
	for (int i = 29; i > 0; i--)
	{
		lines[i - 1] = lines[i];
	}
	for (int i = 0; i < drawnObjects; i++)
		drawnBlocks[i].movable = -1;
}