# To intergrade with vs-code look at https://hackernoon.com/how-to-set-up-c-debugging-in-vscode-using-a-makefile

CC = g++
CFLAGS = -g -Wall
SFFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
OBJECTS = main.o game.o player.o gameObject.o settings.o scene.o sceneManager.o gameScene.o
TARGET = program.out
BUILD_DIR = build/

all: reset main move

reset:
	-rm -rf ./$(BUILD_DIR)*.out
	-rm -rf ./$(BUILD_DIR)*.log 

move:
	mv *.o $(BUILD_DIR)
	-mv *.out $(BUILD_DIR)
	cp -r assets/ build/

# To run SFML add flags '-lsfml-graphics -lsfml-window -lsfml-system'
main: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) src/tools/easylogging++.cc $(SFFLAGS)

main.o: game.o
	$(CC) $(CFLAGS) -c main.cpp

game.o: player.o sceneManager.o
	$(CC) $(CFLAGS) -c src/game.cpp

player.o: gameObject.o
	$(CC) $(CFLAGS) -c src/player.cpp

gameObject.o:
	$(CC) $(CFLAGS) -c src/core/gameObject.cpp

scene.o: gameObject.o
	$(CC) $(CFLAGS) -c src/core/scene.cpp

sceneManager.o: scene.o
	$(CC) $(CFLAGS) -c src/core/sceneManager.cpp

gameScene.o: scene.o
	$(CC) $(CFLAGS) -c src/scenes/gameScene.cpp

settings.o:
	$(CC) $(CFLAGS) -c src/tools/settings.cpp