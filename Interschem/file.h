#pragma once
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include "blocks.h"
#include "lines.h"
OPENFILENAMEA ofn = { 0 }, ofn2 = { 0 };
char szFile[300], filePathOpen[300] , szFile2[300], filePathSave[300];
FILE *fptr, *fptr2;
bool fileWasOpened = false;

void openFile(){
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.lpstrFilter = "Scheme (*.sch)\0*.sch\0";
    ofn.nMaxFile = sizeof(szFile);
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    if (GetOpenFileNameA(&ofn))
    {
        std::cout << ofn.lpstrFile << '\n';
        strcpy(filePathOpen, ofn.lpstrFile);
        fileWasOpened = true;
        fptr = fopen(filePathOpen, "r");
        fscanf(fptr, "%d\n", &drawnObjects);
        std::cout << drawnObjects << " blocks imported.\n";
        for (int i = 0; i < drawnObjects; i++)
        {
            fscanf(fptr, "%d %d %d %d %d %d\n", &drawnBlocks[i].xtopleft, &drawnBlocks[i].ytopleft, &drawnBlocks[i].xbotright, &drawnBlocks[i].ybotright, &drawnBlocks[i].xmiddle, &drawnBlocks[i].ymiddle);
            fscanf(fptr, "%d %d\n", &drawnBlocks[i].textHeight, &drawnBlocks[i].textWidth);
            fscanf(fptr, "%d %d %d %d %d %d %d %d\n", &drawnBlocks[i].xtopleftC1, &drawnBlocks[i].ytopleftC1, &drawnBlocks[i].xbotrightC1, &drawnBlocks[i].ybotrightC1, &drawnBlocks[i].xtopleftC2, &drawnBlocks[i].ytopleftC2, &drawnBlocks[i].xbotrightC2, &drawnBlocks[i].ybotrightC2);
            fscanf(fptr, "%d %d %d %d %d %d %d %d\n", &drawnBlocks[i].xtopleftC3, &drawnBlocks[i].ytopleftC3, &drawnBlocks[i].xbotrightC3, &drawnBlocks[i].ybotrightC3, &drawnBlocks[i].xtopleftC4, &drawnBlocks[i].ytopleftC4, &drawnBlocks[i].xbotrightC4, &drawnBlocks[i].ybotrightC4);
            fscanf(fptr, "%d\n", &drawnBlocks[i].movable);
            fscanf(fptr, "%d %d %d %d %d %d\n", &drawnBlocks[i].isStart, &drawnBlocks[i].isStop, &drawnBlocks[i].isVariable, &drawnBlocks[i].isOutput, &drawnBlocks[i].isIfCond, &drawnBlocks[i].isExpression);
            fscanf(fptr, "%s\n", &drawnBlocks[i].text);
            std::cout << drawnBlocks[i].text << '\n';
        }
        fscanf(fptr, "%d\n", &linesIndex);
        for (int i = 0; i < linesIndex; i++)
        {
            fscanf(fptr, "%d %d\n", &lines[i].indexBlock1, &lines[i].indexBlock2);
            fscanf(fptr, "%d %d %d %d\n", &lines[i].x1, &lines[i].y1, &lines[i].x2, &lines[i].y2);
        }
        fclose(fptr);

        fptr = fopen(filePathOpen, "r");
        fscanf(fptr, "%d\n", &drawnObjectsCopy);
        for (int i = 0; i < drawnObjects; i++)
        {
            fscanf(fptr, "%d %d %d %d %d %d\n", &drawnBlocksCopy[i].xtopleft, &drawnBlocksCopy[i].ytopleft, &drawnBlocksCopy[i].xbotright, &drawnBlocksCopy[i].ybotright, &drawnBlocksCopy[i].xmiddle, &drawnBlocksCopy[i].ymiddle);
            fscanf(fptr, "%d %d\n", &drawnBlocksCopy[i].textHeight, &drawnBlocksCopy[i].textWidth);
            fscanf(fptr, "%d %d %d %d %d %d %d %d\n", &drawnBlocksCopy[i].xtopleftC1, &drawnBlocksCopy[i].ytopleftC1, &drawnBlocksCopy[i].xbotrightC1, &drawnBlocksCopy[i].ybotrightC1, &drawnBlocksCopy[i].xtopleftC2, &drawnBlocksCopy[i].ytopleftC2, &drawnBlocksCopy[i].xbotrightC2, &drawnBlocksCopy[i].ybotrightC2);
            fscanf(fptr, "%d %d %d %d %d %d %d %d\n", &drawnBlocksCopy[i].xtopleftC3, &drawnBlocksCopy[i].ytopleftC3, &drawnBlocksCopy[i].xbotrightC3, &drawnBlocksCopy[i].ybotrightC3, &drawnBlocksCopy[i].xtopleftC4, &drawnBlocksCopy[i].ytopleftC4, &drawnBlocksCopy[i].xbotrightC4, &drawnBlocksCopy[i].ybotrightC4);
            fscanf(fptr, "%d\n", &drawnBlocks[i].movable);
            fscanf(fptr, "%d %d %d %d %d %d\n", &drawnBlocksCopy[i].isStart, &drawnBlocksCopy[i].isStop, &drawnBlocksCopy[i].isVariable, &drawnBlocksCopy[i].isOutput, &drawnBlocksCopy[i].isIfCond, &drawnBlocksCopy[i].isExpression);
            fscanf(fptr, "%s\n", &drawnBlocksCopy[i].text);
        }
        fscanf(fptr, "%d\n", &linesIndexCopy);
        for (int i = 0; i < linesIndex; i++)
        {
            fscanf(fptr, "%d %d\n", &linesCopy[i].indexBlock1, &linesCopy[i].indexBlock2);
            fscanf(fptr, "%d %d %d %d\n", &linesCopy[i].x1, &linesCopy[i].y1, &linesCopy[i].x2, &linesCopy[i].y2);
        }
        fclose(fptr);
    }
}

void loadFile()
{
    if (fileWasOpened)
    {
        std::cout << "Drawing scheme from " << filePathOpen << '\n';
        drawnObjects = drawnObjectsCopy;
        for (int i = 0; i < drawnObjects; i++)
            drawnBlocks[i] = drawnBlocksCopy[i];
        linesIndex = linesIndexCopy;
        for (int i = 0; i < linesIndexCopy; i++)
            lines[i] = linesCopy[i];
    }
    else std::cout << "No file has been imported.\n";
}

void saveFile() {
    ZeroMemory(&ofn, sizeof(ofn2));
    ofn2.lStructSize = sizeof(ofn2);
    ofn2.lpstrFile = szFile2;
    ofn2.lpstrFile[0] = '\0';
    ofn2.lpstrFilter = "Scheme (*.sch)\0*.sch\0";
    ofn2.nMaxFile = sizeof(szFile2);
    ofn2.lpstrDefExt = "sch";
    ofn2.Flags = OFN_PATHMUSTEXIST;
    if (GetSaveFileNameA(&ofn2))
    {
        strcpy(filePathSave, ofn2.lpstrFile);
        fptr2 = fopen(filePathSave, "w");
        fprintf(fptr2, "%d\n", drawnObjects);
        for (int i = 0; i < drawnObjects; i++)
        {
            fprintf(fptr2, "%d %d %d %d %d %d\n", drawnBlocks[i].xtopleft, drawnBlocks[i].ytopleft, drawnBlocks[i].xbotright, drawnBlocks[i].ybotright, drawnBlocks[i].xmiddle, drawnBlocks[i].ymiddle);
            fprintf(fptr2, "%d %d\n", drawnBlocks[i].textHeight, drawnBlocks[i].textWidth);
            fprintf(fptr2, "%d %d %d %d %d %d %d %d\n", drawnBlocks[i].xtopleftC1, drawnBlocks[i].ytopleftC1, drawnBlocks[i].xbotrightC1, drawnBlocks[i].ybotrightC1, drawnBlocks[i].xtopleftC2, drawnBlocks[i].ytopleftC2, drawnBlocks[i].xbotrightC2, drawnBlocks[i].ybotrightC2);
            fprintf(fptr2, "%d %d %d %d %d %d %d %d\n", drawnBlocks[i].xtopleftC3, drawnBlocks[i].ytopleftC3, drawnBlocks[i].xbotrightC3, drawnBlocks[i].ybotrightC3, drawnBlocks[i].xtopleftC4, drawnBlocks[i].ytopleftC4, drawnBlocks[i].xbotrightC4, drawnBlocks[i].ybotrightC4);
            fprintf(fptr2, "%d\n", drawnBlocks[i].movable);
            fprintf(fptr2, "%d %d %d %d %d %d\n", drawnBlocks[i].isStart, drawnBlocks[i].isStop, drawnBlocks[i].isVariable, drawnBlocks[i].isOutput, drawnBlocks[i].isIfCond, drawnBlocks[i].isExpression);
            fprintf(fptr2, "%s\n", (char*)drawnBlocks[i].text);
        }
        fprintf(fptr2, "%d\n", linesIndex);
        for (int i = 0; i < linesIndex; i++)
        {
            fprintf(fptr2, "%d %d\n", lines[i].indexBlock1, lines[i].indexBlock2);
            fprintf(fptr2, "%d %d %d %d\n", lines[i].x1, lines[i].y1, lines[i].x2, lines[i].y2);
        }
        fclose(fptr2);
        std::cout << "File saved at " << filePathSave << '\n';
    }
}