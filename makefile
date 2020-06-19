#Copyright Notice:
#The files within this zip file are copyrighted by Lazy Foo' Productions (2004-2014)
#and may not be redistributed without written permission.

#OBJS specifies which files to compile as part of the project
OBJS = lib/stds/src/init.c lib/stds/include/init.h lib/stds/src/draw.c lib/stds/include/draw.h lib/stds/include/stds.h lib/stds/include/input.h lib/stds/src/input.c lib/stds/include/structs.h lib/stds/include/stddefine.h  lib/stds/src/stds.c lib/stds/src/sound.c lib/stds/include/sound.h lib/stds/src/text.c lib/stds/include/text.h lib/stds/src/game.c lib/stds/include/game.h lib/stds/src/camera.c lib/stds/include/camera.h lib/stds/src/animation.c lib/stds/include/animation.h include/commons.h src/main.c include/main.h include/game_defs.h include/game_structs.h src/particle.c include/particle.h lib/stds/src/background.c lib/stds/include/background.h src/emitter.c include/emitter.h src/paddle.c include/paddle.h src/ball.c include/ball.h src/brick.c include/brick.h src/level.c include/level.h src/powerup.c include/powerup.h src/debris.c include/debris.h src/hud.c include/hud.h

#CC specifies which compiler we're using
CC = gcc

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -IC:\MinGW\include\SDL2

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -LC:\MinGW\lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresszzes all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -Werror -Wfloat-conversion

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = Game

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
