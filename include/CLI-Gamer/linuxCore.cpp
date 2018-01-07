#include <sys/ioctl.h>
#include <termios.h>
#include <cstdlib>
#include <unistd.h>

namespace cligCore {
  namespace console {
    int getConsoleWidth() // Used to get the current Width of the console window
    {
      struct winsize max;
      ioctl( 0, TIOCGWINSZ, &max );
      return max.ws_col;
    }

    int getConsoleHeight() // Used to get the current Height of the console window
    {
      struct winsize max;
      ioctl( 0, TIOCGWINSZ, &max );
      return max.ws.col
    }
    void toggleEcho( const bool &enable ) // Stops the console from printing anything if disabled.
    {
      struct termios tty;
      tcgetattr( STDIN_FILENO, &tty );
      if ( not enable ) {
        tty.c_lflag &= ~ECHO;
      } else {
        tty.c_lflag |= ECHO;
      }

      (void)tcsetattr( STDIN_FILENO, TCSANOW, &tty );
    }
    std::string
    getPassword( const char *prompt ) // Used to get the password of the user without exposing what they typed.
    {
      std::string password = getpass( prompt );
      return password;
    }
    void executeCommand( const char &command ) {
      // system(command);
    }
  }
  void clear() // This is used to clear the screen and reset any formatting changes.
  {
    std::cout << "\x1B[2J\x1B[H";
    std::cout << termcolor::reset;
  }
  Keys getArrowInput() {
    int input;
    input = getch();
    switch ( input ) // lets just waste the value
    {
    case 0:
    case 224:
      switch ( getch() ) // Here the actual code for the key is got
      {
      case 72: return Keys::up;
      case 75: return Keys::left;
      case 77: return Keys::right;
      case 80: return Keys::down;
      default: return Keys::extended;
      }
    }
  }
  Keys getArrowInput( bool delayed ) {
    int input;
    input = getch();
    switch ( input ) // lets just waste the value
    {
    case 0:
    case 224:
      switch ( getch() ) // Here the actual code for the key is got
      {
      case 72: return Keys::up;
      case 75: return Keys::left;
      case 77: return Keys::right;
      case 80: return Keys::down;
      default: return Keys::extended;
      }
    }
  }

  int createMenu( const std::string &title, const std::vector<std::string> &menuContent,
                  const bool &backEnabled ) // Creates a menu without using the nCurses library, not likely to be
  // efficient. Still needs linux code.
  {
    cligCore::clear();
    int numberOfOptions = menuContent.size() - 1;
    int pointerCoord = 0;
    cligCore::clear();
    std::cout << termcolor::bold << termcolor::underline << title << termcolor::reset << std::endl;

    for ( int a = 0; a < menuContent.size(); a++ ) {
      if ( pointerCoord == a ) { std::cout << termcolor::on_grey; }
      std::cout << menuContent[ a ] << termcolor::reset << std::endl;
    }
    bool failcheck{};
    while ( true ) {
      switch ( getArrowInput() ) {
      case Keys::up: {
        pointerCoord--;
        if ( pointerCoord < 0 ) { pointerCoord = numberOfOptions; }
        cligCore::clear();
        std::cout << termcolor::bold << termcolor::underline << title << termcolor::reset << std::endl;
        for ( int a = 0; a < menuContent.size(); a++ ) {
          if ( pointerCoord == a ) { std::cout << termcolor::on_grey; }
          std::cout << menuContent[ a ] << termcolor::reset << std::endl;
        }
        break;
      }
      case Keys::down: {
        pointerCoord++;
        if ( pointerCoord > numberOfOptions ) { pointerCoord = 0; }
        cligCore::clear();
        std::cout << termcolor::bold << termcolor::underline << title << termcolor::reset << std::endl;
        for ( int a = 0; a < menuContent.size(); a++ ) {
          if ( pointerCoord == a ) { std::cout << termcolor::on_grey; }
          std::cout << menuContent[ a ] << termcolor::reset << std::endl;
        }
        break;
      }
      case Keys::enter: {
        return pointerCoord;
      }
      case Keys::escape: {
        if ( backEnabled ) { return -1 };
      }
      }
    }
    return -1;
  }
}
