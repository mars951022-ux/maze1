#pragma once
#include <windows.h>
#include <conio.h>
#include <iostream>

namespace rlutil {

enum Color {
    BLACK = 0,
    DARKGREY = 8,
    GREY = 7,
    WHITE = 7,
    YELLOW = 14,
    LIGHTGREEN = 10,
    CYAN = 11
};

static WORD rl_default_attr = 7;

inline void saveDefaultColor() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    rl_default_attr = csbi.wAttributes;
}
inline void resetColor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), rl_default_attr);
}
inline void setColor(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)c);
}

inline void cls() { system("cls"); }
inline void locate(int x, int y) {
    COORD coord;
    coord.X = (SHORT)(x - 1);
    coord.Y = (SHORT)(y - 1);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

inline void hidecursor() {
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}
inline void showcursor() {
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    info.bVisible = TRUE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

inline void anykey() {
    _getch();
}

inline void msleep(int ms) { Sleep(ms); }

// Arrow keys codes returned by getkey()
const int KEY_UP = 72;
const int KEY_DOWN = 80;
const int KEY_LEFT = 75;
const int KEY_RIGHT = 77;
const int KEY_ESCAPE = 27;

// Read keyboard for special keys: return arrow codes or ASCII
inline int getkey() {
    int c = _getch();
    if (c == 0 || c == 224) {
        int c2 = _getch();
        return c2; // return scan code like 72,80,75,77
    }
    return c;
}

inline bool kbhit() { return _kbhit(); }

} // namespace rlutil

// Provide a global kbhit() because original code calls it without namespace
inline bool kbhit() { return rlutil::kbhit(); }
