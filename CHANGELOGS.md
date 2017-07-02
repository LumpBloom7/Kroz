Kroz changelogs
===============

#### 02/07/2017
 * [+] Redone code formatting to closely match LLVM style
 * [+] Fixed minor code styling issues

#### 03/04/2017(Final update)
 * [+] Optimizations

#### 17/03/2017
 * [-] The console functionality has totally been removed as it just had no serious use in the game.
 * [+] Started using the modularity approach in making the headers. They now only contain the declarations while the .cpp files contain the implementation. 

#### 27/02/2017
 * [+] The virtual directory system now can sort itself and display itself. This function can be called by ```sortDir()``` and ```dir()``` respectively. The ```sortDir()``` sorts the directories in a somewhat odd manner, where anything that is in upper case is guaranteed to be on the top, followed by the lower case directory names. Will hopefully be ironed out in the next commit.
 * [-] Clean out some unused includes and funtions. ```People.hpp``` still exist but is not being used by the program at its current state.


#### 12/02/2017
 * [+]<***EXPERIMENTAL***> A virtual computer with its own virtual file system, you can create new files, create subdirectories, etc. All of these are located in the namespace ```systemFS```
 * [+] The menus now works with RETURN and ESCAPE keys. Still no Linux support though.

#### 31/12/2016
 **Last day of 2016 update**
 * [+] Made all menus use ```switch()```
 * [+] Started Mac development
 * [+] Open-sourced!!!

#### 28/12/2016
 * [+] Revamped all menus. Uses ARROW_UP and ARROW_DOWN for vertical navigation, ARROW_LEFT to go back, ARROW_RIGHT to select.(Does not work on linux yet.) Located in ```core::createMenu(std::string title, std::vector<std::string> content, bool backEnabled)```
 * [-] Linux version does not work now thanks to the above update.

#### 19/12/2016
 * [+] Started working on the storyline.
 * [+] Unlocked chapter 1 and added some cinematics to it.

#### 19/10/2016
 * [+] Somewhat working console functionality(to control game variables)
 * [+] Improved variable declaration

#### 24/06/2016
 * [+] Replaced all raw pointers with smart pointers(```std::shared_ptr<Person>```) to prevent possible memory leaks.
 * [-] Removed relationships mechanic for a major revision.

#### 21/06/2016
 * [+] Added saving and loading functions into ```people``` classes.
 * [+] Added saving and loading into debug screen.
 * [+] Added [cereal](http://uscilab.github.io/cereal/index.html "cereal documentation") into the include folder(for serialization and deserialization).

#### 16/06/2016
 * [+] Debug mode now accessible through main menu by typing '2001' as a response. Currently it only debugs people factory and relationships.
 * [+] Added ```newGame()``` function, accessible with corresponding number. Others will just reload ```main()```
 * [+] Merged ```addRelationship()``` and ```removeRelationship()``` into ```changeRelationship()```accessible through an extra argument.
 * [+] implemented removing and changing relationship code.

#### 14/06/2016
 * [+] Re-added non-functioning main menu.
 * [+] A slight change in ``` checkRelationship()``` function and the ```relationStr()``` string array. Now it outputs strings about the relationship status between two people that makes more sense.
 * [-] Commented out the relationships debugging code in main.cpp(They are still implemented in people.hpp)

#### 13/06/2016
 * [+] Added working relationships mechanic.
 * [+] Added relationships test code in main.cpp

#### 04/06/2016
 * [+] Working people factory added to people.hpp
 * [-] Main menu is commented to test people factory

#### 03/06/2016
 * [+] Main menu added
 * [+] Cross-platform clear console function implemented
