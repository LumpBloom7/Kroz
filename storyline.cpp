#include "storyline.hpp"

#include <chrono>
#include <thread>
#include <algorithm>

namespace systemFS { // Experimental gameplay mechanic to simulate an actually file system that will be used within the
                     // game.
  void File::changeDetails( std::string name ) { fileName = name; }
  void File::changeDetails( int FileType ) { fileType = FileType; }
  void File::changeDetails( bool isHidden ) { hidden = isHidden; }
  void File::changeDetails( std::string name, int FileType ) {
    fileName = name;
    fileType = FileType;
  }
  void File::changeDetails( bool isHidden, int FileType ) {
    hidden = isHidden;
    fileType = FileType;
  }
  void File::changeDetails( std::string name, bool isHidden ) {
    fileName = name;
    hidden = isHidden;
  }
  void File::changeDetails( std::string name, bool isHidden, int FileType ) {
    fileName = name;
    hidden = isHidden;
    fileType = FileType;
  }
  void File::changeContents( std::string fileContent ) { content = fileContent; }
  std::string File::getFileName() { return fileName; }
  bool File::getHiddenStatus() { return hidden; }

  std::string Directory::getName() { return name; }
  bool Directory::isHidden() { return hidden; }
  void Directory::changeDetails( std::string newName ) { name = newName; }
  void Directory::changeDetails( bool isHidden ) { hidden = isHidden; }
  void Directory::changeDetails( std::string newName, bool isHidden ) {
    name = newName;
    hidden = isHidden;
  }
  std::vector<std::shared_ptr<Directory>> Directory::getSubDirectories() { return subDirectories; }
  std::string Directory::getFolderName() { return name; }
  void Directory::createDirectory( std::string directoryName ) {
    auto a = std::make_shared<Directory>();
    a->changeDetails( directoryName );
    a->fullPath = fullPath + a->name + " > ";
    subDirectories.push_back( a );
  }
  void Directory::createDirectory( std::string directoryName, bool isHidden ) {
    auto a = std::make_shared<Directory>();

    a->changeDetails( directoryName );
    a->fullPath = fullPath + a->name + " > ";
    a->changeDetails( isHidden );
    subDirectories.push_back( a );
  }
  void Directory::createFile( std::string fileName ) {
    auto a = std::make_shared<File>();
    a->changeDetails( fileName );
    a->changeContents( "" );
  }
  void Directory::createFile( std::string fileName, int fileType ) {
    auto a = std::make_shared<File>();
    a->changeDetails( fileName, fileType );
    a->changeContents( "" );
  }
  void Directory::createFile( std::string fileName, bool isHidden ) {
    auto a = std::make_shared<File>();
    a->changeDetails( fileName );
    a->changeDetails( isHidden );
    a->changeContents( "" );
  }
  void Directory::createFile( std::string fileName, int fileType, bool isHidden ) {
    auto a = std::make_shared<File>();
    a->changeDetails( fileName, isHidden, fileType );
    a->changeContents( "" );
  }
  void Directory::createFile( std::string fileName, std::string content ) {
    auto a = std::make_shared<File>();
    a->changeDetails( fileName );
    a->changeContents( content );
  }
  void Directory::createFile( std::string fileName, int fileType, std::string content ) {
    auto a = std::make_shared<File>();
    a->changeDetails( fileName );
    a->changeContents( content );
  }
  void Directory::createFile( std::string fileName, bool isHidden, std::string content ) {
    auto a = std::make_shared<File>();
    a->changeDetails( fileName, isHidden );
    a->changeContents( content );
  }
  void Directory::createFile( std::string fileName, int fileType, bool isHidden, std::string content ) {
    auto a = std::make_shared<File>();
    a->changeDetails( fileName, isHidden, fileType );
    a->changeContents( content );
  }
  void Directory::sortDir() // Sorts subDirectories and files. Should have a worst time complexity of O((s^2) + (f^2)),
                            // best is O(s + f). Need to use merge sort, which is much faster, but this would do for
                            // now.
  {
    bool again = false;
    while ( !again ) { // Sort subDirectories
      for ( int a = 0; a < subDirectories.size(); a++ ) {
        if ( a < subDirectories.size() - 1 ) {
          if ( subDirectories[ a ]->getFolderName().compare( subDirectories[ a + 1 ]->getFolderName() ) > 0 ) {
            std::iter_swap( subDirectories.begin() + a, subDirectories.begin() + a + 1 );
            again = true;
          }
        }
      }
      if ( again ) {
        again = false;
      } else {
        break;
      }
    }
    while ( !again ) { // Sort files
      for ( int a = 0; a < files.size(); a++ ) {
        if ( a < files.size() - 1 ) {
          if ( files[ a ]->getFileName().compare( files[ a + 1 ]->getFileName() ) > 0 ) {
            std::iter_swap( files.begin() + a, files.begin() + a + 1 );
            again = true;
          }
        }
      }
      if ( again ) {
        again = false;
      } else {
        break;
      }
    }
  }
  void Directory::dir() {
    for ( int a = 0; a < subDirectories.size(); a++ ) {
      std::cout << subDirectories[ a ]->getFolderName() << std::endl;
    }
    for ( int a = 0; a < files.size(); a++ ) { std::cout << files[ a ]->getFileName() << std::endl; }
  }
}

// auto Computer = std::make_shared<systemFS::Directory>();
namespace chapter1 {

  int terminal(), actions(), programsList();
  void bootupCinematics();

  int story() // Storyline
  {
    Computer->changeDetails( "Computer" );
    Computer->fullPath = "Computer > ";
    core::clear();
    std::cout << termcolor::magenta << "You are a professional hacker" << std::endl;
    std::this_thread::sleep_for( std::chrono::seconds( 3 ) );
    std::cout << "This is your story to get revenge" << std::endl;
    std::this_thread::sleep_for( std::chrono::seconds( 3 ) );
    std::cout << "Revenge on someone who stole your code.." << std::endl;
    std::this_thread::sleep_for( std::chrono::seconds( 3 ) );
    core::clear();
    std::cout << termcolor::magenta << termcolor::underline << "Monday, 18th of April 2016" << std::endl;
    bootupCinematics();
    core::clear();
    if ( player::userName == "" ) {
      std::cout << "Please register your new HackOS account..." << std::endl
                << "Enter Username(Without spaces): " << std::flush;
      std::cin >> player::userName;
      std::string password = core::console::getPassword( "Enter optional password: " );
    }
    actions();
    std::cin.get();
    std::cin.get();
    return 0;
  }
  int actions() // Lets the player interact with his virtual computer
  {
    std::vector<std::string> menu{"0. Terminal", "1. Programs", "2. E-Mail", "3. Internet", "4. ShutDown"};

    int results = core::createMenu( "What do you want to do?", menu, true );

    switch ( results ) {
    case 0: {
      // Terminal
      terminal();
      break;
    }
    case 1: {
      // Programs menu...
      programsList();
      break;
    }
    case 2: {
      // E-Mail interface
      break;
    }
    case 3: {
      // Internet browser that does not browse the web
      break;
    }
    case 4: {
      ::main();
      return 0;
    }
    default: { actions(); }
    }
    actions();
  }
  int terminal() // Experimental terminal functionality
  {
    core::clear();
    std::cin.ignore();
    while ( true ) {
      auto cd = ::Computer;
      std::string cdStr = cd->fullPath;
      std::cout << cdStr << std::flush;
      std::string command{};
      std::string arguments;
      // First get the command, the rest of the line will be arguments. If no arguments are provided, do the default
      // option.
      // Computer > dir /s /a
      //       Command^  ^Arguments
      std::cin >> command;
      // std::cin.getLine(arguments);
      std::cout << command << std::endl;
    }
  }
  int programsList() // A list of shortcuts to usefull tools within the game
  {
    std::vector<std::string> menu{"Terminal", "E-Mail"};
    if ( player::internetUnlocked ) { menu.push_back( "Internet" ); }
    if ( player::passwordCracker ) { menu.push_back( "Password Cracker" ); }
    menu.push_back( "Return" );
    int results = core::createMenu( "Programs", menu, true );
    switch ( results ) {
    case 0: {
      terminal();
    }
    case 1: {
    }
    case 2: {
    }
    case 3: {
    }
    case -1: {
    }
    }
  }
  void bootupCinematics() // Self explanatory
  {
    std::this_thread::sleep_for( std::chrono::seconds( 3 ) );
    core::clear();
    for ( int x = 0; x < ( core::console::getConsoleWidth() / 2 ) - 10; x++ ) { std::cout << "=" << std::flush; }
    std::cout << "HackOS v0.59.32 Beta" << std::flush;
    for ( int x = 0; x < ( core::console::getConsoleWidth() / 2 ) - 10; x++ ) { std::cout << "=" << std::flush; }
    std::cout << "Kernel loaded." << std::endl;
    std::this_thread::sleep_for( std::chrono::milliseconds( 300 ) );
    std::cout << termcolor::reset << "Loading core system files..." << std::endl;
    std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
    std::cout << "Computer > System > processManager.sys started." << std::endl;
    std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );
    std::cout << "Computer > System > powerManager.sys started." << std::endl;
    std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
    std::cout << "Computer > System > overClocker.sys started." << std::endl;
    std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );
    std::cout << "Computer > System > Drivers > genericDisplay.dri started." << std::endl;
    std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );
    std::cout << "Computer > System > Drivers > inputDrivers.dri started." << std::endl;
    std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );
    std::cout << "Computer > System > Drivers > networkCard.dri started." << std::endl;
    std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );
    std::cout << "Computer > System > Drivers > audioCard.dri failed to start due to lack of audio card." << std::endl;
    std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );
    std::cout << "Computer > System > Drivers > piChipset.dri started." << std::endl;
    std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );
    std::cout << "Computer > System > Network > networkInterface.sys started." << std::endl;
    std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
    std::cout << "Computer > System > Network > rotVPN.paf started." << std::endl;
    std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
    std::cout << "Computer > System > Network > wifiInterface.sys started." << std::endl;
    std::this_thread::sleep_for( std::chrono::milliseconds( 300 ) );
    std::cout << "Computer > System > Network > macAddressChanger.paf started." << std::endl;
    std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
    std::cout << "Computer > System > Network > remoteAccess.sys started" << std::endl;
    std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
    std::cout << "Computer > System > HackServices > MITMService.paf started." << std::endl;
    std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
    std::cout << "Computer > System > HackServices > EMP.paf started." << std::endl;
    std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
    std::cout << "Computer > System > HackServices > denialOfService.paf started." << std::endl;
    std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
    std::cout << "Computer > System > Applications > ApplicationsService.sys started." << std::endl;
    std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
    std::cout << "Computer > System > stdUserInterface.sys started" << std::endl;
    std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
    std::cout << termcolor::green << "Core systems file sucessfully loaded." << std::endl;

    for ( int x = 0; x < core::console::getConsoleHeight(); x++ ) {
      std::cout << std::endl;
      std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );
    }
  }
};