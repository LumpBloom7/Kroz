#ifndef STORYLINE_H
#define STORYLINE_H
int main();
namespace systemFS { // Experimental gameplay mechanic to simulate an actually file system that will be used within the
                     // game.
  enum fileTypes { text = 0, executable = 1, audio = 2, image = 3, video = 4 };
  struct File {
    // Virtual file for the terminal, will be stored in an std::vector located in the class Directory.
  public:
    static std::shared_ptr<File> makeFile();
    void changeDetails( std::string name );
    void changeDetails( int FileType );
    void changeDetails( bool isHidden );
    void changeDetails( std::string name, int FileType );
    void changeDetails( bool isHidden, int FileType );
    void changeDetails( std::string name, bool isHidden );
    void changeDetails( std::string name, bool isHidden, int FileType );
    void changeContents( std::string fileContent );
    std::string getFileName();
    bool getHiddenStatus();

  private:
    bool hidden{};
    std::string content{};
    std::string fileName{};
    int fileType = fileTypes::text;
  };
  struct Directory { // Virtual directory for the terminal
  public:
    std::string fullPath;
    std::string getName();
    bool isHidden();
    void changeDetails( std::string newName );
    void changeDetails( bool isHidden );
    void changeDetails( std::string newName, bool isHidden );
    std::vector<std::shared_ptr<Directory>> getSubDirectories();
    std::string getFolderName();
    void createDirectory( std::string directoryName );
    void createDirectory( std::string directoryName, bool isHidden );
    void createFile( std::string fileName );
    void createFile( std::string fileName, int fileType );
    void createFile( std::string fileName, bool isHidden );
    void createFile( std::string fileName, int fileType, bool isHidden );
    void createFile( std::string fileName, std::string content );
    void createFile( std::string fileName, int fileType, std::string content );
    void createFile( std::string fileName, bool isHidden, std::string content );
    void createFile( std::string fileName, int fileType, bool isHidden, std::string content );
    void sortDir(); // Sorts subDirectories and files. Should have a worst time complexity of O((s^2) + (f^2)), best is
                    // O(s + f). Need to use merge sort, which is much faster, but this would do for now.
    void dir();

  private:
    std::string name;
    bool hidden{};

    std::vector<std::shared_ptr<Directory>> subDirectories{};
    std::vector<std::shared_ptr<File>> files{};
    bool getHiddenStatus{};
  };
}

auto Computer = std::make_shared<systemFS::Directory>();
namespace chapter1 {

  int story(); // Storyline
  int actions(); // Lets the player interact with his virtual computer
  int terminal(); // Experimental terminal functionality
  int programsList(); // A list of shortcuts to usefull tools within the game
  void bootupCinematics(); // Self explanatory
};
#endif
