#include <iostream>
#include <ncurses.h>
#include "LinuxTerminal.h"


LinuxTerminal::LinuxTerminal() :
    ITerminal()
{
}

LinuxTerminal::~LinuxTerminal()
{
    release();
}

bool LinuxTerminal::initialize()
{
    return true;
}

bool LinuxTerminal::release()
{
    if (term_mode_ == TM_GAME)
        endwin();

    return true;
}

bool LinuxTerminal::setMode(eTermMode term_mode)
{
    if (term_mode_ == term_mode)
        return true;

    term_mode_ = term_mode;

    switch (term_mode)
    {
    case TM_NORMAL:
        endwin();
        break;
    case TM_GAME:
        setlocale(LC_ALL, "");
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        nodelay(stdscr, TRUE);
        curs_set(0);
        break;
    }

    return true;
}

void LinuxTerminal::clearScreen() const
{
    switch (term_mode_)
    {
    case TM_NORMAL:
        std::system("clear");
        break;
    case TM_GAME:
        clear();
        break;
    }
}

void LinuxTerminal::setCursorPos(int x, int y) const
{
    if (term_mode_ == TM_NORMAL)
        return;

    move(y, x);
}

void LinuxTerminal::output(const std::ostringstream & oss, bool doFlush) const
{
    output(oss.str(), doFlush);
}

void LinuxTerminal::output(const std::string & str, bool doFlush) const
{
    switch (term_mode_)
    {
    case TM_NORMAL:
        std::cout << str;
        break;

    case TM_GAME:
        addstr(str.c_str());

        if (doFlush)
        {
            refresh();
        }
        break;
    }
}

void LinuxTerminal::doRefresh() const
{
    refresh();
}

bool LinuxTerminal::pollKeys(kb_codes_vec & kb_codes)
{
    if (term_mode_ == TM_NORMAL)
        return false;

    kb_codes.clear();

    int c;
    while ( (c = getch()) != ERR )
    {
        switch (c)
        {
        case 27:        kb_codes.push_back(KB_ESCAPE); break;
        case '\n':      kb_codes.push_back(KB_ENTER); break;
        case ' ':       kb_codes.push_back(KB_SPACE); break;
        case KEY_UP:    kb_codes.push_back(KB_UP); break;
        case KEY_LEFT:  kb_codes.push_back(KB_LEFT); break;
        case KEY_RIGHT: kb_codes.push_back(KB_RIGHT); break;
        case KEY_DOWN:  kb_codes.push_back(KB_DOWN); break;
        case 'A':
        case 'a':       kb_codes.push_back(KB_A); break;
        case 'B':
        case 'b':       kb_codes.push_back(KB_B); break;
        case 'C':
        case 'c':       kb_codes.push_back(KB_C); break;
        case 'D':
        case 'd':       kb_codes.push_back(KB_D); break;
        case 'E':
        case 'e':       kb_codes.push_back(KB_E); break;
        case 'F':
        case 'f':       kb_codes.push_back(KB_F); break;
        case 'G':
        case 'g':       kb_codes.push_back(KB_G); break;
        case 'H':
        case 'h':       kb_codes.push_back(KB_H); break;
        case 'I':
        case 'i':       kb_codes.push_back(KB_I); break;
        case 'J':
        case 'j':       kb_codes.push_back(KB_J); break;
        case 'K':
        case 'k':       kb_codes.push_back(KB_K); break;
        case 'L':
        case 'l':       kb_codes.push_back(KB_L); break;
        case 'M':
        case 'm':       kb_codes.push_back(KB_M); break;
        case 'N':
        case 'n':       kb_codes.push_back(KB_N); break;
        case 'O':
        case 'o':       kb_codes.push_back(KB_O); break;
        case 'P':
        case 'p':       kb_codes.push_back(KB_P); break;
        case 'Q':
        case 'q':       kb_codes.push_back(KB_Q); break;
        case 'R':
        case 'r':       kb_codes.push_back(KB_R); break;
        case 'S':
        case 's':       kb_codes.push_back(KB_S); break;
        case 'T':
        case 't':       kb_codes.push_back(KB_T); break;
        case 'U':
        case 'u':       kb_codes.push_back(KB_U); break;
        case 'V':
        case 'v':       kb_codes.push_back(KB_V); break;
        case 'W':
        case 'w':       kb_codes.push_back(KB_W); break;
        case 'X':
        case 'x':       kb_codes.push_back(KB_X); break;
        case 'Y':
        case 'y':       kb_codes.push_back(KB_Y); break;
        case 'Z':
        case 'z':       kb_codes.push_back(KB_Z); break;
        }
    }

    return (kb_codes.size() > 0);
}
