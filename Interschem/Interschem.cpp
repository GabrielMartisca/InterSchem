#include "interface.h"
#include "menu.h"

int main()
{
	generateMenus();
	drawWindow();
	drawMenu();
	active();
	
	getch();
	closegraph();
	return 0;
}