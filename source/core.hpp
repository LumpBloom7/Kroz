#ifndef CORE_H
#define CORE_H

#if defined(_WIN32) || defined(_WIN64)
#   define Windows
#elif defined(__APPLE__)
#   define MacOS
#elif defined(__unix__) || defined(__unix)
#   define Linux
#else
#   error unsupported platform
#endif

namespace core {
    void clear()
    {
#if defined(Windows)
        COORD topLeft  = { 0, 0 };
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO screen;
        DWORD written;

        GetConsoleScreenBufferInfo(console, &screen);
        FillConsoleOutputCharacterA(
            console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
        );
        FillConsoleOutputAttribute(
            console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
            screen.dwSize.X * screen.dwSize.Y, topLeft, &written
        );
        SetConsoleCursorPosition(console, topLeft);
#elif defined(Linux)
        std::cout << "\x1B[2J\x1B[HL";
#endif
    }
};

#endif // CORE_H
