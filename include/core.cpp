#include "core.hpp"

#include <fstream>
#include <sys/stat.h>
#include "cereal/types/vector.hpp"
#include "cereal/types/string.hpp"
#include "cereal/archives/json.hpp"

// Includes platform specific implementations
#if defined( _WIN32 ) || defined( _WIN64 )
#include "winCore.cpp"
#elif defined( __unix__ ) || defined( __unix )
#include "linuxCore.cpp"
#endif

namespace cligCore {
  namespace filesystem {                           // Functions used to read and modify the file system of the user.
    bool fileExists( const std::string &fileName ) // Used to check if a certain file exists with a certain directory
    {
      struct stat buffer;
      return ( stat( fileName.c_str(), &buffer ) == 0 );
    }
  }
  void save() // Serialize namespace player, you can change this to another namespace or object
  {/*
    std::string password;
    std::ofstream os( ( "saveData/" + player::userName + ".json" ) );
    cereal::JSONOutputArchive archive( os );

    archive( CEREAL_NVP( player::userName ), CEREAL_NVP( player::password ),
             CEREAL_NVP( player::experience ) ); // Names the output the same as the variable name
             */
  }
  int load() // Deserialize namespace player, you can change this to another namespace or object
  {
    /*
    std::string userName{};
    std::cout << "Please enter your userName: " << std::flush;
    std::cin >> userName;
    if ( core::filesystem::fileExists( "saveData/" + userName + ".json" ) ) {
      std::string password;
      std::ifstream is( "saveData/" + userName + ".json" );
      cereal::JSONInputArchive archive( is );
      archive( player::userName, player::password, player::experience );
      std::cout << player::password << std::endl;
      if ( player::password != "" ) {
        std::string tempPassword = core::console::getPassword( "Please input your password for your save file: " );
        std::cout << tempPassword << std::endl;
        if ( tempPassword != player::password ) {
          std::cout << termcolor::red << "The inputted password seems to be incorrect, please try again."
                    << termcolor::reset << std::endl;
          return -1;
        }
      }
    } else {
      std::cout << termcolor::red << "It seems like there is no save files for that userName.." << termcolor::reset
                << std::endl;
      return -1;
    }
    */
  }
}
