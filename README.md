Kroz
====

This is a text based ~~adventure game(like Zork)~~. 

After 2 months of thinking what should be in an adventure game, I decided to changed the game to be a hacker simulator kind of game(Like watchdogs, but with less bullshit and graphics). Code or mechanics related to the old idea will be gradually removed, they will be placed in a different file so the engine can be releases with those functionality.

### Currently implemented:
 * Main Menu
 * Clear console function
 * People factory
 * Cross-platform compatibility(Confirmed on Linux & Windows)
 * Partial savegame system for NPC's
 * Somewhat working console functionality(to control game variables)
 * Game cinematics

### Next up:
 * Revamped relationships mechanic
 * Cross-platform make directory function(for savegames)
 * Working vocabulary system

### Changelogs:

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
