Kroz
====
**Announcement: Project Kroz has been put on hold. There is just not much going on here. I spent 2.5 years on this lone-project with little degrees of progress, and I have other ideas I want to work on. I'll move the framework into a new repo and update the framework. But this game itself will not be with it. I may come back in the future to finish up when I feel like it. I learnt a lot from this project.**


Kroz is just a codename("Zork" reversed)

This is a text based ~~adventure game(like Zork)~~.

After 2 months of thinking what should be in an adventure game, I decided to changed the game to be a hacker simulator kind of game(Like watchdogs, but with less bullshit and no visuals). Code or mechanics related to the old idea will be gradually removed, they will be placed in a different file so the engine can be released with those functionalities.

Most of the code is improvised, but almost all of it works on all platforms. It is not the best way to make the game, but I'm learning as I go along. I will replace old code with better code as I gain more experience.

### Currently implemented:
 * Main Menu
 * Clear console function
 * Cross-platform compatibility(Confirmed on Linux & Windows)
 * Game cinematics
 * Virtual directory system

### Next up:
 * Cross-platform make directory function(for savegames)

### Changelogs:

#### 17/03/2017
 * [-] The console functionality has totally been removed as it just had no serious use in the game.
 * [+] Started using the modularity approach in making the headers. They now only contain the declarations while the .cpp files contain the implementation. 

#### 27/02/2017
 * [+] The virtual directory system now can sort itself and display itself. This function can be called by ```sortDir()``` and ```dir()``` respectively. The ```sortDir()``` sorts the directories in a somewhat odd manner, where anything that is in upper case is guaranteed to be on the top, followed by the lower case directory names. Will hopefully be ironed out in the next commit.
 * [+] Clean out some unused includes and funtions. ```People.hpp``` still exist but is not being used by the program at its current state.

#### 12/02/2017
 * [+]<***EXPERIMENTAL***> A virtual computer with its own virtual file system, you can create new files, create subdirectories, etc. All of these are located in the namespace ```systemFS```
 * [+] The menus now works with RETURN and ESCAPE keys. Still no Linux support though.

#### 31/12/2016
 **Last day of 2016 update**
 * [+] Made all menus use ```switch()```
 * [+] Started Mac development
 * [+] Open-sourced!!!

More changes can be found in CHANGELOGS.md