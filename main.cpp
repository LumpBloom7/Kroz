#include <iostream> // For IO functionality
#include <vector>   // For Vector functionality
#include <memory>   // For memory management, includes std::shared_ptr and std::unique_ptr
#include <string>   // For string variable

#include "termcolor.hpp" // This header contains the functionality of adding colors to 'std::cout'.
#include "player.hpp"    // This header contains the namespace used to store player data and progress.

// This provides some basic functions to ease game development.
#include "core.cpp"
// #include "people.cpp" // This header contains the people factory and personality system.
#include "storyline.cpp" // This contains the storyboard data for the game.

void newGame(), continueGame(), chapterSelect(), userSelect(), quit();
int main() {

  core::clear(); // Clear the console of anything before loading the main menu.
  std::vector<std::string> menu{"New game", "Continue", "Select chapter", "Select user", "Debug", "Quit"};
  // Prints main menu, duh...
  int playerReply = core::createMenu( "Welcome to Kroz. What would you like to do?", menu, false );
  switch ( playerReply ) {
  case 0: {
    newGame();
    break;
  }
  case 1: {
    continueGame();
    break;
  }
  case 2: {
    chapterSelect();
    break;
  }
  case 4: {
    std::cout << termcolor::yellow << "DEBUG -- Testing password input." << std::endl;
    std::cout << std::endl << core::console::getPassword( "passwordTest: " ) << std::endl << std::endl;

    std::cout << termcolor::yellow << "DEBUG -- Testing File Save functionality." << std::endl;
    player::userName = "Byte";
    player::password = "lolbit";
    player::experience = 25.36;
    core::save();
    core::load();
    std::cout << player::userName << std::endl
              << player::password << std::endl
              << player::experience << std::endl
              << std::endl;

    std::cout << termcolor::yellow << "DEBUG -- Testing Directory system." << std::endl;
    Computer->changeDetails( "Computer" );
    Computer->createDirectory( "System" );
    Computer->createDirectory( "lols" );
    Computer->createDirectory( "hello" );
    Computer->createDirectory( "bullshit" );
    Computer->createDirectory( "wtf" );
    Computer->createDirectory( "halo" );
    Computer->createDirectory( "Heil Hitler" );
    std::cout << Computer->getSubDirectories()[ 0 ]->getFolderName() << std::endl;
    Computer->getSubDirectories()[ 0 ]->createDirectory( "Networking" );
    Computer->getSubDirectories()[ 0 ]->getSubDirectories()[ 0 ]->createDirectory( "Wireless" );
    std::cout << Computer->getSubDirectories()[ 0 ]->getSubDirectories()[ 0 ]->getSubDirectories()[ 0 ]->getFolderName()
              << std::endl
              << std::endl;

    std::cout << termcolor::yellow << "DEBUG -- Testing directory sorting algorithm." << std::endl;
    Computer->dir();
    Computer->sortDir();
    std::cout << std::endl;
    Computer->dir();

    system( "pause" );
    main();
    break;
  }
  case 5: {
    exit( 0 );
  }
  default: {
    main();
    break;
  }
  }
  return 0;
}
void newGame() {
  core::clear();
  std::cout << termcolor::red << termcolor::blink << "WARNING: All saved games will be deleted." << std::endl
            << termcolor::reset << termcolor::red << "Are you sure you want to start a new game?" << std::endl
            << termcolor::green << "Please enter your choice(y/N): " << std::flush;

  std::string playerReply{};
  std::cin >> playerReply;

  if ( playerReply == "N" || playerReply == "n" )
    main();
  else if ( playerReply == "Y" || playerReply == "y" ) {
    int result = chapter1::story();
    if ( result == -1 ) main();
  } else {
    std::cout << termcolor::red << "ERROR: Invalid response." << std::endl
              << termcolor::reset << "Press any key to continue..." << std::endl;

    std::cin.get();
    std::cin.get();

    newGame();
  }
}
void continueGame() {
  core::clear();
  int lastPlayedChapter{};
  switch ( lastPlayedChapter ) {
  /*case 1:
   int result = chapter1::story();
   if(result == -1)
            main();
   break;
  case 2:
   chapter2();
   break;
  case 3:
   chapter3();
   break;
  case 4:
   chapter4();
   break;*/
  default:
    std::cout << termcolor::red << "ERROR: No previous game session detected on this computer" << std::endl
              << termcolor::reset << "Please select \"New Game\" to start a new adventure" << std::endl
              << termcolor::reset << "Press any key to continue..." << std::endl;
    std::cin.get();
    std::cin.get();
    main();
    break;
  }
}
void chapterSelect() {
  core::clear();
  bool chapter3Unlocked{}, chapter4Unlocked{};
  std::vector<std::string> menu{"0. Prologue", "1. Terminal"};
  if ( chapter3Unlocked )
    menu.push_back( "2. Superuser" );
  else
    menu.push_back( "2. <LOCKED>" );

  if ( chapter4Unlocked )
    menu.push_back( "3. Bootloader" );
  else
    menu.push_back( "3. <LOCKED>" );

  int playerReply = core::createMenu( "Chapter select", menu, true );

  switch ( playerReply ) {
  case 0: {
    std::cout << "0. Prologue" << std::endl;
    break;
  }
  case 1: {
    int result = chapter1::story();
    if ( result == -1 ) main();
    break;
  }
  case 2: {
    std::cout << "2. Superuser" << std::endl;
    break;
  }
  case 3: {
    std::cout << "3. Bootloader" << std::endl;
    break;
  }
  case -1: {
    main();
    break;
  }
  default: {
    chapterSelect();
    break;
  }
  }
}
