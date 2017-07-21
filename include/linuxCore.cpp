#include <sys/ioctl.h>
#include <termios.h>
#include <cstdlib>
#include <unistd.h>

namespace core {
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
  void save() // Serialize namespace player, you can change this to another namespace or object
  {
    std::string password;
    std::ofstream os( ( "saveData/" + player::userName + ".json" ) );
    cereal::JSONOutputArchive archive( os );

    archive( CEREAL_NVP( player::userName ), CEREAL_NVP( player::password ),
             CEREAL_NVP( player::experience ) ); // Names the output the same as the variable name
  }

  void clear() // This is used to clear the screen and reset any formatting changes.
  {
    std::cout << "\x1B[2J\x1B[H";
    std::cout << termcolor::reset;
  }
  ArrowKeys getArrowInput() {
    int input;
    input = getch();
    switch ( input ) // lets just waste the value
    {
    case 0:
    case 224:
      switch ( getch() ) // Here the actual code for the key is got
      {
      case 72: return ArrowKeys::up;
      case 75: return ArrowKeys::left;
      case 77: return ArrowKeys::right;
      case 80: return ArrowKeys::down;
      default: return ArrowKeys::extended;
      }
    }
  }
  ArrowKeys getArrowInput( bool delayed ) {
    int input;
    input = getch();
    switch ( input ) // lets just waste the value
    {
    case 0:
    case 224:
      switch ( getch() ) // Here the actual code for the key is got
      {
      case 72: return ArrowKeys::up;
      case 75: return ArrowKeys::left;
      case 77: return ArrowKeys::right;
      case 80: return ArrowKeys::down;
      default: return ArrowKeys::extended;
      }
    }
  }

  int createMenu( const std::string &title, const std::vector<std::string> &menuContent,
                  const bool &backEnabled ) // Creates a menu without using the nCurses library, not likely to be
  // efficient. Still needs linux code.
  {
    core::clear();
    int numberOfOptions = menuContent.size() - 1;
    int pointerCoord = 0;
    core::clear();
    std::cout << termcolor::bold << termcolor::underline << title << termcolor::reset << std::endl;

    for ( int a = 0; a < menuContent.size(); a++ ) {
      if ( pointerCoord == a ) { std::cout << termcolor::on_grey; }
      std::cout << menuContent[ a ] << termcolor::reset << std::endl;
    }
    bool failcheck{};
    while ( true ) {
      if ( getArrowInput() == ArrowKeys::up && failcheck ) {
        pointerCoord--;
        if ( pointerCoord < 0 ) { pointerCoord = numberOfOptions; }
        core::clear();
        std::cout << termcolor::bold << termcolor::underline << title << termcolor::reset << std::endl;
        for ( int a = 0; a < menuContent.size(); a++ ) {
          if ( pointerCoord == a ) { std::cout << termcolor::on_grey; }
          std::cout << menuContent[ a ] << termcolor::reset << std::endl;
        }

      } else if ( getArrowInput() == ArrowKeys::down && failcheck ) {
        pointerCoord++;
        if ( pointerCoord > numberOfOptions ) { pointerCoord = 0; }
        core::clear();
        std::cout << termcolor::bold << termcolor::underline << title << termcolor::reset << std::endl;
        for ( int a = 0; a < menuContent.size(); a++ ) {
          if ( pointerCoord == a ) { std::cout << termcolor::on_grey; }
          std::cout << menuContent[ a ] << termcolor::reset << std::endl;
        }
      } else if ( getArrowInput() == ArrowKeys::enter && failcheck ) { // Fix Later
        std::cin.ignore();
        return pointerCoord;
      } else if ( ( backEnabled == true ) && ( getArrowInput() == ArrowKeys::escape && failcheck ) ) { // Fix Later
        std::cin.ignore();
        return -1;
      }
      failcheck = true;
    }
    return -1;
  }
}
