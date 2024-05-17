#include "graphics.h"
#include <math.h>
#include "interface.h"
#include <iostream>
#pragma comment (lib,"graphics.lib")
#pragma once

int drawnObjects = 0, drawnObjectsCopy = 0; // object counter
bool changeText = false;

struct blocks {
    int xtopleft=0, ytopleft=0, xbotright=0, ybotright=0, xmiddle=0,ymiddle=0;
    int textHeight = 0, textWidth = 0;
    int xtopleftC1 = 0, ytopleftC1 = 0, xbotrightC1 = 0, ybotrightC1 = 0, xtopleftC2 = 0, xbotrightC2 = 0, ytopleftC2 = 0, ybotrightC2 = 0;
    int xtopleftC3 = 0, ytopleftC3 = 0, xbotrightC3 = 0, ybotrightC3 = 0, xtopleftC4 = 0, xbotrightC4 = 0, ytopleftC4 = 0, ybotrightC4 = 0;
    int movable = -1, linecounter = 0;
    int isStart = false, isStop = false, isVariable = false, isOutput = false, isIfCond = false, isExpression = false;
    char text[256]= "";
}drawnBlocks[15], drawnBlocksCopy[15];

void updateStart(int xmiddle, int ymiddle, int index)
{

    drawnBlocks[index].xmiddle = xmiddle;
    drawnBlocks[index].ymiddle = ymiddle;
    strcpy(drawnBlocks[index].text, "START");
    drawnBlocks[index].xtopleft = xmiddle - 25;
    drawnBlocks[index].ytopleft = ymiddle -25;
    drawnBlocks[index].xbotright = xmiddle + 25;
    drawnBlocks[index].ybotright = ymiddle + 25;
    //rectangle coords for circle below
    drawnBlocks[index].xtopleftC2 = xmiddle - 5;
    drawnBlocks[index].ytopleftC2 = ymiddle + 20;
    drawnBlocks[index].xbotrightC2 = xmiddle + 5;
    drawnBlocks[index].ybotrightC2 = ymiddle + 30;
    
    drawnBlocks[index].isStart = true;
}

void updateStop(int xmiddle, int ymiddle, int index)
{
    drawnBlocks[index].xmiddle = xmiddle;
    drawnBlocks[index].ymiddle = ymiddle;
    strcpy(drawnBlocks[index].text, "STOP");
    drawnBlocks[index].xtopleft = xmiddle - 25;
    drawnBlocks[index].ytopleft = ymiddle - 25;
    drawnBlocks[index].xbotright = xmiddle + 25;
    drawnBlocks[index].ybotright = ymiddle + 25;
    //rectangle coords for circle above
    drawnBlocks[index].xtopleftC1 = xmiddle - 5;
    drawnBlocks[index].ytopleftC1 = ymiddle - 20;
    drawnBlocks[index].xbotrightC1 = xmiddle + 5;
    drawnBlocks[index].ybotrightC1 = ymiddle - 10;

    drawnBlocks[index].isStop = true;
}


void updateIfCond(int xmiddle, int ymiddle, int index)
{
    drawnBlocks[index].xmiddle = xmiddle;
    drawnBlocks[index].ymiddle = ymiddle;
    if (changeText)
    {
    char ifCond[30];
    std::cout << "Enter if condition(max 30): ";
    std::cin.getline(ifCond, 30);
    strcpy(drawnBlocks[index].text, ifCond);
    drawnBlocks[index].textWidth = textwidth(ifCond);
    drawnBlocks[index].textHeight = textheight(ifCond);
    }

    drawnBlocks[index].xtopleft = xmiddle - drawnBlocks[index].textWidth;
    drawnBlocks[index].ytopleft = ymiddle - drawnBlocks[index].textHeight;
    drawnBlocks[index].xbotright = xmiddle + drawnBlocks[index].textWidth;
    drawnBlocks[index].ybotright = ymiddle + drawnBlocks[index].textHeight;

    //rectangle coords for T circle
    drawnBlocks[index].xtopleftC4 = xmiddle - drawnBlocks[index].textWidth - 5;
    drawnBlocks[index].ytopleftC4 = ymiddle - 5;
    drawnBlocks[index].xbotrightC4 = xmiddle - drawnBlocks[index].textWidth + 5;
    drawnBlocks[index].ybotrightC4 = ymiddle + 5;
    //rectangle coords for F circle
    drawnBlocks[index].xtopleftC3 = xmiddle + drawnBlocks[index].textWidth - 5;
    drawnBlocks[index].ytopleftC3 = ymiddle - 5;
    drawnBlocks[index].xbotrightC3 = xmiddle + drawnBlocks[index].textWidth + 5;
    drawnBlocks[index].ybotrightC3 = ymiddle + 5;
    //rectangle coords for circle above
    drawnBlocks[index].xtopleftC1 = xmiddle - 5;
    drawnBlocks[index].ytopleftC1 = ymiddle - drawnBlocks[index].textHeight / 2 - 30;
    drawnBlocks[index].xbotrightC1 = xmiddle + 5;
    drawnBlocks[index].ybotrightC1 = ymiddle - drawnBlocks[index].textHeight / 2 - 20;

    drawnBlocks[index].isIfCond = true;
}

void updateVariable(int xmiddle, int ymiddle, int index)
{
    drawnBlocks[index].xmiddle = xmiddle;
    drawnBlocks[index].ymiddle = ymiddle;

    if (changeText)
    {
    char variables[30];
    std::cout << "Enter variables(max 30 char): ";
    std::cin.getline(variables, 30);
    strcpy(drawnBlocks[index].text, variables);
    drawnBlocks[index].textWidth = textwidth(variables);
    drawnBlocks[index].textHeight = textheight(variables);
    }

    drawnBlocks[index].xtopleft = xmiddle - drawnBlocks[index].textWidth;
    drawnBlocks[index].ytopleft = ymiddle - drawnBlocks[index].textHeight;
    drawnBlocks[index].xbotright = xmiddle + drawnBlocks[index].textWidth;
    drawnBlocks[index].ybotright = ymiddle + drawnBlocks[index].textHeight;

    //rectangle coords for circle above
    drawnBlocks[index].xtopleftC1 = xmiddle - 5;
    drawnBlocks[index].ytopleftC1 = ymiddle - drawnBlocks[index].textHeight / 2 - 20;
    drawnBlocks[index].xbotrightC1 = xmiddle + 5;
    drawnBlocks[index].ybotrightC1 = ymiddle - drawnBlocks[index].textHeight / 2 - 10;
    //rectangle coords for circle below
    drawnBlocks[index].xtopleftC2 = xmiddle - 5;
    drawnBlocks[index].ytopleftC2 = ymiddle + drawnBlocks[index].textHeight / 2 + 20;
    drawnBlocks[index].xbotrightC2 = xmiddle + 5;
    drawnBlocks[index].ybotrightC2 = ymiddle + drawnBlocks[index].textHeight / 2 + 30;
    drawnBlocks[index].isVariable = true;

    
}

void updateOutput(int xmiddle, int ymiddle,int index)
{
    drawnBlocks[index].xmiddle = xmiddle;
    drawnBlocks[index].ymiddle = ymiddle;
    if (changeText)
    {
    char output[30];
    std::cout << "Enter output(max 30 char): ";
    std::cin.getline(output, 30);
    strcpy(drawnBlocks[index].text, output);
    drawnBlocks[index].textWidth = textwidth(output);
    drawnBlocks[index].textHeight = textheight(output);
    }

    drawnBlocks[index].xtopleft = xmiddle - drawnBlocks[index].textWidth;
    drawnBlocks[index].ytopleft = ymiddle - drawnBlocks[index].textHeight;
    drawnBlocks[index].xbotright = xmiddle + drawnBlocks[index].textWidth;
    drawnBlocks[index].ybotright = ymiddle + drawnBlocks[index].textHeight;

    //rectangle coords for circle above
    drawnBlocks[index].xtopleftC1 = xmiddle - 5;
    drawnBlocks[index].ytopleftC1 = ymiddle - drawnBlocks[index].textHeight / 2 - 20;
    drawnBlocks[index].xbotrightC1 = xmiddle + 5;
    drawnBlocks[index].ybotrightC1 = ymiddle - drawnBlocks[index].textHeight / 2 - 10;
    //rectangle coords for circle below
    drawnBlocks[index].xtopleftC2 = xmiddle - 5;
    drawnBlocks[index].ytopleftC2 = ymiddle + drawnBlocks[index].textHeight / 2 + 20;
    drawnBlocks[index].xbotrightC2 = xmiddle + 5;
    drawnBlocks[index].ybotrightC2 = ymiddle + drawnBlocks[index].textHeight / 2 + 30;

    drawnBlocks[index].isOutput = true;
}

void updateExp(int xmiddle, int ymiddle, int index)
{
    drawnBlocks[index].xmiddle = xmiddle;
    drawnBlocks[index].ymiddle = ymiddle;
    if (changeText)
    {
    char expression[30];
    std::cout << "Enter expression(max 30): ";
    std::cin.getline(expression, 30);
    strcpy(drawnBlocks[index].text, expression);
    drawnBlocks[index].textWidth = textwidth(expression);
    drawnBlocks[index].textHeight = textheight(expression);
    }

    drawnBlocks[index].xtopleft = xmiddle - drawnBlocks[index].textWidth;
    drawnBlocks[index].ytopleft = ymiddle - drawnBlocks[index].textHeight;
    drawnBlocks[index].xbotright = xmiddle + drawnBlocks[index].textWidth;
    drawnBlocks[index].ybotright = ymiddle + drawnBlocks[index].textHeight;
    //rectangle coords for circle above
    drawnBlocks[index].xtopleftC1 = xmiddle - 5;
    drawnBlocks[index].ytopleftC1 = ymiddle - drawnBlocks[index].textHeight / 2 - 30;
    drawnBlocks[index].xbotrightC1 = xmiddle + 5;
    drawnBlocks[index].ybotrightC1 = ymiddle - drawnBlocks[index].textHeight / 2 - 20;
    //rectangle coords for circle below
    drawnBlocks[index].xtopleftC2 = xmiddle - 5;
    drawnBlocks[index].ytopleftC2 = ymiddle + drawnBlocks[index].textHeight / 2 + 20;
    drawnBlocks[index].xbotrightC2 = xmiddle + 5;
    drawnBlocks[index].ybotrightC2 = ymiddle + drawnBlocks[index].textHeight / 2 + 30;

    drawnBlocks[index].isExpression = true;
}

void cercConec(int x, int y)
{
    circle(x, y, 7);
}
void desenStart(int x, int y)
{
    setbkcolor(maincolor);
    setcolor(BLACK);
    char ch[256] = "START";
    arc(x - 15, y - 5, 90, 180, 10);
    line(x - 15, y - 15, x + 15, y - 15);
    arc(x + 15, y - 5, 0, 90, 10);
    line(x + 25, y - 5, x + 25, y + 15);
    arc(x + 15, y + 15, 270, 0, 10);
    line(x - 15, y + 25, x + 15, y + 25);
    arc(x - 15, y + 15, 180, 270, 10);
    line(x - 25, y - 5, x - 25, y + 15);
    outtextxy(x - 20, y - 10, ch);
    cercConec(x, y + 25);
}
void desenStop(int x, int y)
{
    setbkcolor(maincolor);
    setcolor(BLACK);
    char ch[256] = "STOP";
    arc(x - 15, y - 5, 90, 180, 10);
    line(x - 15, y - 15, x + 15, y - 15);
    arc(x + 15, y - 5, 0, 90, 10);
    line(x + 25, y - 5, x + 25, y + 15);
    arc(x + 15, y + 15, 270, 0, 10);
    line(x - 15, y + 25, x + 15, y + 25);
    arc(x - 15, y + 15, 180, 270, 10);
    line(x - 25, y - 5, x - 25, y + 15);
    outtextxy(x - 18, y - 5, ch);
    cercConec(x, y - 15);
}
void desenCitire(int x, int y, char m[])
{
    setbkcolor(maincolor);
    setcolor(BLACK);
    int h, w;
    h = textheight(m);
    w = textwidth(m);
    line(x - 25 - w / 2, y - 15 - h / 2, x + 25 + w / 2, y - 15 - h / 2);
    line(x - 5 - w / 2, y + 25 + h / 2, x + 5 + w / 2, y + 25 + h / 2);
    line(x + 5 + w / 2, y + 25 + h / 2, x + 25 + w / 2, y - 15 - h / 2);
    line(x - 25 - w / 2, y - 15 - h / 2, x - 5 - w / 2, y + 25 + h / 2);
    outtextxy(x - w / 2, y - h, m);
    cercConec(x, y + 25 + h / 2);
    cercConec(x, y - 15 - h / 2);
}
void desenScriere(int x, int y, char m[])
{
    setbkcolor(maincolor);
    setcolor(BLACK);
    int h, w;
    h = textheight(m);
    w = textwidth(m);
    line(x - 25 - w / 2, y + 25 + h / 2, x + 25 + w / 2, y + 25 + h / 2);
    line(x - 5 - w / 2, y - 15 - h / 2, x + 5 + w / 2, y - 15 - h / 2);
    line(x - 25 - w / 2, y + 25 + h / 2, x - 5 - w / 2, y - 15 - h / 2);
    line(x + 25 + w / 2, y + 25 + h / 2, x + 5 + w / 2, y - 15 - h / 2);
    outtextxy(x - w / 2, y - h, m);
    cercConec(x, y + 25 + h / 2);
    cercConec(x, y - 30 + h / 2);
}
void desenIF(int x, int y, char m[])
{
    setbkcolor(maincolor);
    setcolor(BLACK);
    int h, w;
    char T[10] = "T";
    char F[10] = "F";
    h = textheight(m);
    w = textwidth(m);
    outtextxy(x - w / 2, y - h / 2, m);
    int xa, ya, xb, yb;
    xa = x - w;
    xb = x;
    yb = y - 2 * h;
    ya = y;
    line(xa, ya, xb, yb);
    cercConec(xa, ya);
    outtextxy(xa - 3, y - 25, T);
    yb = y + 2 * h;
    line(xa, ya, xb, yb);
    xa = x + w;
    line(xa, ya, xb, yb);
    yb = y - 2 * h;
    line(xa, ya, xb, yb);
    cercConec(xa, ya);
    outtextxy(xa - 3, y - 25, F);
    cercConec(x, y - 25 - h / 2);
}

void desenExpresie(int x, int y, char m[])
{
    setbkcolor(maincolor);
    setcolor(BLACK);
    int h, w;
    h = textheight(m);
    w = textwidth(m);
    outtextxy(x - w / 2, y - h, m);
    rectangle(x - w / 1.5, y - 2 * h, x + w / 1.5, y + 2 * h);
    cercConec(x, y - 25 - h / 2);
    cercConec(x, y + 25 + h / 2);
}