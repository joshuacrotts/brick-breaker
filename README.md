<h1 align="center">Brick Breaker</h1>

<p align="center">
  <img width="250" height="407" src="sdl-brick-breaker.gif">
</p>

[![CodeFactor](https://www.codefactor.io/repository/github/joshuacrotts/sdl-brick-breaker/badge)](https://www.codefactor.io/repository/github/joshuacrotts/Lock-out-protocol) ![GitHub commit activity](https://img.shields.io/github/commit-activity/m/JoshuaCrotts/SDL-Brick-Breaker) ![GitHub repo size](https://img.shields.io/github/repo-size/JoshuaCrotts/SDL-Brick-Breaker) ![GitHub contributors](https://img.shields.io/github/contributors/JoshuaCrotts/SDL-Brick-Breaker)

Brick Breaker is a remake of the original arcade Arkanoid, Breakout, or Brick Breaker (depending on which version that you have seen). Using my Standards library as a framework, combined with SDL, I decided to remake one of my oldest projects in C nonetheless. Everything here is written from scratch, including the data structures and algorithms. The only unoriginal parts are the sound effects/music, the bricks/balls, and the background.

## Dependencies

In the /lib/ directory is my Standards library, converted to C. This, unlike the Java version, does not have an external component (such as a .JAR file). So, the Standards files are simply copied from that project to this one.

## Rebuilding Brick Breaker

To rebuild the code, clone the repository to your computer. This project is compiled with MinGW and a makefile. The SDL .dll files are not included and will need to be downloaded separately to build from source without modifications to the makefile.

## Reporting Bugs

See the Issues Tab.

## Version History
The **master** branch encompasses all changes. A development branch is in the works.
