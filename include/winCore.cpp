#include "windows.h"
#include <limits.h>

namespace core {
  namespace console {

    int getConsoleWidth() // Used to get the current Width of the console window
    {
      CONSOLE_SCREEN_BUFFER_INFO csbi;
      int columns;
      GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
      columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

      return columns;
    }

    int getConsoleHeight() // Used to get the current Height of the console window
    {
      CONSOLE_SCREEN_BUFFER_INFO csbi;
      int rows;
      GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
      rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
      return rows;
    }
    void toggleEcho( const bool &enable ) // Stops the console from printing anything if disabled.
    {
      HANDLE hStdin = GetStdHandle( STD_INPUT_HANDLE );
      DWORD mode;
      GetConsoleMode( hStdin, &mode );

      if ( not enable ) {
        mode &= ~ENABLE_ECHO_INPUT;
      } else {
        mode |= ENABLE_ECHO_INPUT;
      }

      SetConsoleMode( hStdin, mode );
    }
    std::string
    getPassword( const char *prompt ) // Used to get the password of the user without exposing what they typed.
    {
      std::cout << prompt << std::flush;
      std::string password;
      toggleEcho( false );
      std::cin >> password;
      toggleEcho( true );
      return password;
    }
  }

  void clear() // This is used to clear the screen and reset any formatting changes.
  {
    COORD topLeft{0, 0};
    HANDLE console = GetStdHandle( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo( console, &screen );
    FillConsoleOutputCharacterA( console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written );
    FillConsoleOutputAttribute( console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
                                screen.dwSize.X * screen.dwSize.Y, topLeft, &written );
    SetConsoleCursorPosition( console, topLeft );
    std::cout << termcolor::reset;
  }
  ArrowKeys getArrowInput() {
    if ( GetAsyncKeyState( VK_DOWN ) & SHRT_MAX ) {
      return ArrowKeys::down;
    } else if ( GetAsyncKeyState( VK_UP ) & SHRT_MAX ) {
      return ArrowKeys::up;
    } else if ( GetAsyncKeyState( VK_LEFT ) & SHRT_MAX ) {
      return ArrowKeys::left;
    } else if ( GetAsyncKeyState( VK_RIGHT ) & SHRT_MAX ) {
      return ArrowKeys::right;
    } else if ( GetAsyncKeyState( VK_RETURN ) & SHRT_MAX ) {
      return ArrowKeys::enter;
    } else if ( GetAsyncKeyState( VK_ESCAPE ) & SHRT_MAX ) {
      return ArrowKeys::escape;
    } else {
      return ArrowKeys::extended;
    }
  }
  ArrowKeys getArrowInput( bool delayed ) {
    if ( delayed ) {
      GetAsyncKeyState( VK_DOWN );
      GetAsyncKeyState( VK_UP );
      GetAsyncKeyState( VK_LEFT );
      GetAsyncKeyState( VK_RIGHT );
      GetAsyncKeyState( VK_RETURN );
      GetAsyncKeyState( VK_ESCAPE );
    }
    if ( GetAsyncKeyState( VK_DOWN ) & SHRT_MAX ) {
      return ArrowKeys::down;
    } else if ( GetAsyncKeyState( VK_UP ) & SHRT_MAX ) {
      return ArrowKeys::up;
    } else if ( GetAsyncKeyState( VK_LEFT ) & SHRT_MAX ) {
      return ArrowKeys::left;
    } else if ( GetAsyncKeyState( VK_RIGHT ) & SHRT_MAX ) {
      return ArrowKeys::right;
    } else if ( GetAsyncKeyState( VK_RETURN ) & SHRT_MAX ) {
      return ArrowKeys::enter;
    } else if ( GetAsyncKeyState( VK_ESCAPE ) & SHRT_MAX ) {
      return ArrowKeys::escape;
    } else {
      return ArrowKeys::extended;
    }
  }
  int createMenu( const std::string &title, const std::vector<std::string> &menuContent, const bool &backEnabled ) {
    core::clear();
    int numberOfOptions = menuContent.size() - 1;
    int pointerCoord = 0;
    core::clear();
    std::cout << title << termcolor::reset << std::endl;

    for ( int a = 0; a < menuContent.size(); a++ ) {
      if ( pointerCoord == a ) { std::cout << termcolor::green << "> "; }
      std::cout << menuContent[ a ] << termcolor::reset << std::endl;
    }
    bool failcheck{};
    while ( true ) {
      ArrowKeys input = getArrowInput();
      if ( input == ArrowKeys::up && failcheck ) {
        pointerCoord--;
        if ( pointerCoord < 0 ) { pointerCoord = numberOfOptions; }
        core::clear();
        std::cout << title << termcolor::reset << std::endl;
        for ( int a = 0; a < menuContent.size(); a++ ) {
          if ( pointerCoord == a ) { std::cout << termcolor::green << "> "; }
          std::cout << menuContent[ a ] << termcolor::reset << std::endl;
        }

      } else if ( input == ArrowKeys::down && failcheck ) {
        pointerCoord++;
        if ( pointerCoord > numberOfOptions ) { pointerCoord = 0; }
        core::clear();
        std::cout << title << termcolor::reset << std::endl;
        for ( int a = 0; a < menuContent.size(); a++ ) {
          if ( pointerCoord == a ) { std::cout << termcolor::green << "> "; }
          std::cout << menuContent[ a ] << termcolor::reset << std::endl;
        }
      } else if ( input == ArrowKeys::enter && failcheck ) {
        std::cin.ignore();
        return pointerCoord;
      } else if ( ( backEnabled == true ) && ( input == ArrowKeys::escape && failcheck ) ) {
        std::cin.ignore();
        return -1;
      }
      failcheck = true;
    }
    return -1;
  }
}
