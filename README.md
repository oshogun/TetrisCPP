# TetrisCPP
Tetris implemented in C++17, for Linux. This is still in very early development, and core mechanics like Game Over aren't implemented yet, but the game is playable.

# Installing dependencies

This game has the following dependencies:

  - SFML 2.5.0 or higher
  - gcc 8.2.0 or higher (with C++ support installed)
  - GNU Make (any version should work, I use version 4.2.1)
  
**On Arch Linux:**

All dependencies are available on the distribution's repositories,
and may be installed with Pacman. The first step is optional, but recommended,
in order to update your repositories and packages: 

    # pacman -Syu
    # pacman -S sfml gcc
    
**On other Linux distributions:**
 
 All distros I tested, including Fedora, have outdated versions of SFML that
 will not work with this project, so you will need to build SFML yourself. Instructions
 for that are available in https://www.sfml-dev.org/tutorials/2.5/start-linux.php
 
 # Building the game
 
 The build process is very straightforward. 
 
  - To clean up the binary, run
      
      $  make clean
      
  - To compile the game, run
      
      $  make
      
  The game will be available as 
      
      ./Tetris
