//
// Created by 姚文锋 on 2018/8/9.
//
#include <iostream>
#include <curses.h>
#include <stdio.h>

#define TOP_ROW		0			/* top_row */
#define BOT_ROW		LINES - 1
#define TOP_ROW1	(BOT_ROW-TOP_ROW)/3*2
#define LEFT_EDGE	0
#define RIGHT_EDGE	COLS - 1

using namespace std;

void InitChatWindow() {
    char wall = ' ';
    int i, j;
    initscr();
    cbreak();				/* put termial to CBREAK mode */
//    noecho();
//    curs_set(0);			/* set cursor invisible */

    /* display some message about title and wall */
    attrset(A_NORMAL);		/* set NORMAL first */
    attron(A_REVERSE);		/* turn on REVERSE to display the wall */
    for(i = 0; i < LINES; i++)
    {
        mvaddch(i, LEFT_EDGE, wall);
        mvaddch(i, RIGHT_EDGE, wall);
    }
    for(j = 0; j < COLS; j++)
    {
        mvaddch(TOP_ROW, j, wall);
        mvaddch(TOP_ROW1, j, wall);
        mvaddch(BOT_ROW, j, wall);
    }
    attroff(A_REVERSE);		/* turn off REVERSE */
    refresh();
}

void input() {
    move(TOP_ROW1+1,LEFT_EDGE+1);
    addstr("hello");
    refresh();
}