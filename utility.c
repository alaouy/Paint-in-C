#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "utility.h"
#include "souris.cc"



void color(int t,int f)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,f*16+t);
}

void gotoxy(int x, int y)
{
    HANDLE hConsoleOutput;
    COORD dwCursorPosition;
    //cout.flush();
    dwCursorPosition.X = x;
    dwCursorPosition.Y = y;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}

void textAttr(char Attr) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),Attr);
}

void textBackground(char Color) {
    CONSOLE_SCREEN_BUFFER_INFO Info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&Info);
    textAttr((Color << 4)+(Info.wAttributes & 0x0F));
}

void textForeground(char Color) {
    CONSOLE_SCREEN_BUFFER_INFO Info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&Info);
    textAttr((Info.wAttributes << 4)+(Color & 0x0F));
}

void curseur()
{
    POINT pt;
    BOOL bContinue = TRUE;
    const SHORT Mask = 32768;
    while (bContinue)
    {
        if (GetKeyState(VK_ESCAPE) & Mask)
           bContinue = FALSE;
        GetCursorPos(&pt);
        if (GetKeyState(VK_UP) & Mask)
           pt.y -= 5;
        if (GetKeyState(VK_DOWN) & Mask)
           pt.y += 5;
        if (GetKeyState(VK_LEFT) & Mask)
           pt.x -= 5;
        if (GetKeyState(VK_RIGHT) & Mask)
           pt.x += 5;
        SetCursorPos(pt.x,pt.y);
        printf("%d - %d", (int)pt.x,(int)pt.y);
        //Sleep(50);
        system("cls");
    }
}

void welcomemsg()
{
    int c;
    char *ch = "Welcome To PaintIt in C \n\n\n Press Enter to Start ";
    char *ca = "Cliquer Sur le boutton AGRANDIR";
    char *ce = "Taper ENTRER pour de continuer";
    char *cc = "\t\t\t\t\t\t";
    char *t = ca;
    gotoxy(40,15);
    while(*t != '\0')
    {
        printf("%c",*t);
        t++;
        Sleep(100);
    }
    t = ce;
    gotoxy(40,18);
    while(*t != '\0')
    {
        printf("%c",*t);
        t++;
        Sleep(100);
    }

    do
    {
        c = getch();
        //printf(" c = %d", c);
    }while(c != 13);

    system("cls");
    t = cc;
    gotoxy(25,18);
    printf("Chargement :");
    gotoxy(40,18);
    color(0,14);
    while(*t != '\0')
    {
        printf("%c",*t);
        t++;
        Sleep(500);
    }
    color(10,0);
    t = ch;
    gotoxy(45,20);
    while(*t != '\0')
    {
        printf("%c",*t);
        t++;
        Sleep(100);
    }
    do
    {
        c = getch();
    }while(c != 13);
    system("cls"); // clear screen
}

void drawframe()
{
    int i=0;
    gotoxy(144,2);
    color(0,15);
    printf(" M E N U");
    color(10,0);
    gotoxy(140,3);
    printf("__________________");

    gotoxy(144,5);
    printf("Couleurs");
    gotoxy(144,6);
    printf("________");

    gotoxy(144,8);
    color(0,8);
    printf("   ");
    color(10,0);

    gotoxy(144,10);
    color(0,9);
    printf("   ");
    color(10,0);

    gotoxy(144,12);
    color(0,10);
    printf("   ");
    color(10,0);

    gotoxy(144,14);
    color(0,11);
    printf("   ");
    color(10,0);

    gotoxy(149,8);
    color(0,12);
    printf("   ");
    color(10,0);

    gotoxy(149,10);
    color(0,13);
    printf("   ");
    color(10,0);

    gotoxy(149,12);
    color(0,14);
    printf("   ");
    color(10,0);

    gotoxy(149,14);
    color(0,15);
    printf("   ");
    color(10,0);


    gotoxy(144,17);
    printf("Pinceaux");
    gotoxy(144,18);
    printf("________");

    gotoxy(144,20);
    //color(0,10);
    printf("*");
    color(10,0);

    gotoxy(149,20);
    color(0,10);
    printf("  ");
    color(10,0);

    gotoxy(144,25);
    printf("________");
    gotoxy(144,26);
    printf("\\ Gomme \\");
    gotoxy(145,27);
    printf("________");



    while(i<50)
    {
        gotoxy(140,i);
        printf("%c", 219);
        i++;
    }
}


void paint()
{
    static DMOUSE m;            // the mouse handler
    static int scolor = 10;     // the selected color
    static char schar = '*';    // the caracter to be printed

    static int y,x;
    mouse(&m);                  // exits when left button mouse clicked

    x = m.coordinates.X;        // the position of mouse click
    y = m.coordinates.Y;
    if(m.coordinates.X < 140)   // if in the drawing section
    {
        gotoxy(m.coordinates.X, m.coordinates.Y);   // move the cursor to the clicked position
        if(schar == ' ')
            color(0, scolor);
        else
            color(scolor, 0);
        printf("%c", schar);
        color(10,0);
    }
    else                    // in the color/palette section
    {
        if((x<148)&&(y == 8))   // the first color
            scolor = 8;
        if((x<148)&&(y == 10))  // the second color
            scolor = 9;
        if((x<148)&&(y == 12))
            scolor = 10;
        if((x<148)&&(y == 14))
            scolor = 11;
        if((x>148)&&(y == 8))
            scolor = 12;
        if((x>148)&&(y == 10))
            scolor = 13;
        if((x>148)&&(y == 12))
            scolor = 14;
        if((x>148)&&(y == 14))
            scolor = 15;
        if((x<148)&&(y == 20))
            schar = '*';
        if((x>148)&&(y == 20))
            schar = ' ';
        if((x>144)&&(y == 26))
            scolor = 0;
        if((x>144)&&(y == 25))
            scolor = 0;
        if((x>144)&&(y == 27))
            scolor = 0;
    }
}
