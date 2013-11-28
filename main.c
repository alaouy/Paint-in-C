#include <stdio.h>
#include <stdlib.h>
#include "utility.h"

/**
    Name        : Paint in C
    Author      : Mustapha Alaouy
    Email       : alaouym@gmail.com
    Description : basic drawing program (Paint) using only the console
                  and the DOS colors
*/

int main()
{
    system("color 0a");
    system("mode con cols=160 lines=57");
    //welcomemsg();       // loading
    drawframe();        // draws the menu
    while(1)
    {
        paint();
    }
    return 0;
}
