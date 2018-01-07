#include "windows.h"
#include <limits.h>

namespace cligCore {
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
  Keys getKeyInput() {
    if ( GetAsyncKeyState( VK_DOWN ) & SHRT_MAX ) {
      return Keys::down;
    } else if ( GetAsyncKeyState( VK_UP ) & SHRT_MAX ) {
      return Keys::up;
    } else if ( GetAsyncKeyState( VK_LEFT ) & SHRT_MAX ) {
      return Keys::left;
    } else if ( GetAsyncKeyState( VK_RIGHT ) & SHRT_MAX ) {
      return Keys::right;
    } else if ( GetAsyncKeyState( VK_RETURN ) & SHRT_MAX ) {
      return Keys::enter;
    } else if ( GetAsyncKeyState( VK_ESCAPE ) & SHRT_MAX ) {
      return Keys::escape;
    } else {
      return Keys::extended;
    }
  }
  Keys getKeyInput( bool delayed ) {
    if ( delayed ) {
      GetAsyncKeyState( VK_DOWN );
      GetAsyncKeyState( VK_UP );
      GetAsyncKeyState( VK_LEFT );
      GetAsyncKeyState( VK_RIGHT );
      GetAsyncKeyState( VK_RETURN );
      GetAsyncKeyState( VK_ESCAPE );
    }
    if ( GetAsyncKeyState( VK_DOWN ) & SHRT_MAX ) {
      return Keys::down;
    } else if ( GetAsyncKeyState( VK_UP ) & SHRT_MAX ) {
      return Keys::up;
    } else if ( GetAsyncKeyState( VK_LEFT ) & SHRT_MAX ) {
      return Keys::left;
    } else if ( GetAsyncKeyState( VK_RIGHT ) & SHRT_MAX ) {
      return Keys::right;
    } else if ( GetAsyncKeyState( VK_RETURN ) & SHRT_MAX ) {
      return Keys::enter;
    } else if ( GetAsyncKeyState( VK_ESCAPE ) & SHRT_MAX ) {
      return Keys::escape;
    } else {
      return Keys::extended;
    }
  }
  int createMenu( const std::string &title, const std::vector<std::string> &menuContent, const bool &backEnabled ) {
    cligCore::clear();
    int numberOfOptions = menuContent.size() - 1;
    int pointerCoord = 0;
    cligCore::clear();
    std::cout << title << termcolor::reset << std::endl;

    for ( int a = 0; a < menuContent.size(); a++ ) {
      if ( pointerCoord == a ) { std::cout << termcolor::green << "> "; }
      std::cout << menuContent[ a ] << termcolor::reset << std::endl;
    }
    bool failcheck{};
    while ( true ) {
      if ( not failcheck ) {
        GetAsyncKeyState( VK_DOWN );
        GetAsyncKeyState( VK_UP );
        GetAsyncKeyState( VK_LEFT );
        GetAsyncKeyState( VK_RIGHT );
        GetAsyncKeyState( VK_RETURN );
        GetAsyncKeyState( VK_ESCAPE );
        failcheck = true;
      }
      switch ( getKeyInput() ) {
      case Keys::up: {
        pointerCoord--;
        if ( pointerCoord < 0 ) { pointerCoord = numberOfOptions; }
        cligCore::clear();
        std::cout << title << termcolor::reset << std::endl;
        for ( int a = 0; a < menuContent.size(); a++ ) {
          if ( pointerCoord == a ) { std::cout << termcolor::green << "> "; }
          std::cout << menuContent[ a ] << termcolor::reset << std::endl;
        }
        break;
      }
      case Keys::down: {
        pointerCoord++;
        if ( pointerCoord > numberOfOptions ) { pointerCoord = 0; }
        cligCore::clear();
        std::cout << title << termcolor::reset << std::endl;
        for ( int a = 0; a < menuContent.size(); a++ ) {
          if ( pointerCoord == a ) { std::cout << termcolor::green << "> "; }
          std::cout << menuContent[ a ] << termcolor::reset << std::endl;
        }
        break;
      }
      case Keys::enter: {
        return pointerCoord;
      }
      case Keys::escape: {
        if ( backEnabled ) { return -1; }
      }
      }
    }
    return -1;
  }
}
