#ifndef CLIGCORE_H
#define CLIGCORE_H

namespace cligCore {
  namespace filesystem {                            // Functions used to read and modify the file system of the user.
    bool fileExists( const std::string &fileName ); // Used to check if a certain file exists with a certain directory
  }
  namespace console {
    int getConsoleWidth();                 // Used to get the current Width of the console window
    int getConsoleHeight();                // Used to get the current Height of the console window
    void toggleEcho( const bool &enable ); // Stops the console from printing anything if disabled.
    std::string
    getPassword( const char *prompt ); // Used to get the password of the user without exposing what they typed.
  }
  enum Keys { up = 0, down = 1, left = 2, right = 3, enter = 4, escape = 5, extended = 6 };
  Keys getKeyInput();
  Keys getKeyInput( bool delayed );
  void save();  // Serialize namespace player
  int load();   // Deserialize namespace player
  void clear(); // This is used to clear the screen and reset any formatting changes.
  int createMenu( const std::string &title, const std::vector<std::string> &menuContent,
                  const bool &backEnabled ); // Creates a menu without using the nCurses library, not likely to be
                                             // efficient. Still needs linux code.
}

#endif // CORE_H
