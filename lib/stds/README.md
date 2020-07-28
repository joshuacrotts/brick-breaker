<h1 align="center">C - Standards</h1>

<p align="center">
  <img width="200" height="200" src="standards.PNG">
</p>

[![CodeFactor](https://www.codefactor.io/repository/github/joshuacrotts/C-Standards/badge)](https://www.codefactor.io/repository/github/joshuacrotts/C-Standards) ![GitHub contributors](https://img.shields.io/github/contributors/JoshuaCrotts/C-Standards) ![GitHub commit activity](https://img.shields.io/github/commit-activity/m/JoshuaCrotts/C-Standards) ![GitHub repo size](https://img.shields.io/github/repo-size/JoshuaCrotts/C-Standards)  ![](https://tokei.rs/b1/github/JoshuaCrotts/C-Standards) ![](https://tokei.rs/b1/github/JoshuaCrotts/C-Standards?category=files) [![GitHub issues open](https://img.shields.io/github/issues/JoshuaCrotts/C-Standards)]() 
[![GitHub issues closed](https://img.shields.io/github/issues-closed-raw/JoshuaCrotts/C-Standards)]()

C - Standards is the continuation of the Standards game library, originally written in Java. While not all features are implemented such as handlers, the basic necessities for creating a game are completely here. All data structures for entity-handling/updating/drawing should be drawn by the programmer, but these structures should come at a future date. SDL is the back-end graphical library for this engine.

## Dependencies

The only dependencies for this library are SDL components.

1. [SDL_2.0.12](https://www.libsdl.org/download-2.0.php)
2. [SDL_ttf 2.0.15 (Fonts)](https://www.libsdl.org/projects/SDL_ttf/)
3. [SDL_mixer 2.0.4 (Audio)](https://www.libsdl.org/projects/SDL_mixer/)
4. [SDL_image 2.0.5 (PNG/JPG Wrapper)](https://www.libsdl.org/projects/SDL_image/)

## Rebuilding C - Standards

**Windows**: To rebuild the code, clone the repository to your computer. This project is compiled with MinGW and a makefile. Depending on how you want to compile the project, you will need to alter the makefile to fit your needs and make sure you have SDL and its extensions installed correctly. Compile the code via <code>mingw32-make</code>.

**MacOS**: For MacOS, run the following commands in your terminal to get the appropriate development files for SDL:

1. <code>brew install SDL2</code>
2. <code>brew install SDL2_image</code>
3. <code>brew install SDL2_ttf</code>
4. <code>brew install SDL2_mixer</code>

Then, compile via <code>make</code>.

**Linux (Ubuntu/Debian)**: The process is similar to the former, with the exception of having to install SDL files to your system in Linux. Run the following commands (or their distro-equivalent) in your terminal:

1. <code>sudo apt-get install libsdl2-dev</code>
2. <code>sudo apt-get install libsdl2-image-dev</code>
3. <code>sudo apt-get install libsdl2-ttf-dev</code>
4. <code>sudo apt-get install libsdl2-mixer-dev</code>

Then, compile via <code>make</code>.

## Reporting Bugs

See the Issues Tab.

## Version History
The **master** branch encompasses all changes. The **development** branch has in-progress additions and updates that are not yet ready for the master branch.
