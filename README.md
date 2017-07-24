Kroz
====
**Announcement: Project Kroz has been put on hold. There is just not much going on here. I spent 2.5 years on this lone-project with little degrees of progress, and I have other ideas I want to work on. I'll move the framework into a new repo and update the framework. But this game itself will not be with it. I may come back in the future to finish up when I feel like it. I learnt a lot from this project, and it will help me a lot in my future works.**


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

#### 24/07/2017
 * [+] ```core::createMenu()``` now uses switch cases to get key input and do the appropriate stuff.
 * [+] ```getArrowInput()``` had now been renamed to ```getKeyInput()``` to accurately match its actual function.
 * [+] The ```ArrowKeys``` enumerator has been renamed to ```Keys``` because it does not only contain arrowKeys.

#### 21/07/2017
 * [+] Tidied up core.cpp. All OS specific calls are now in their own independent code files and is appropriately called during compilation.
 * [+] Menus should now work on Linux since the Linux code to get arrow key input is implemented.
 * [+] Arrow key input is now handled by ```core::getArrowInput()```.

More changes can be found in CHANGELOGS.md
