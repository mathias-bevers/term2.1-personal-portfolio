# To intergrade with vs-code look at https://hackernoon.com/how-to-set-up-c-debugging-in-vscode-using-a-makefile

CC = g++
CFLAGS = -g -Wall

TARGET = program.out
BUILD_DIR = build/

all: reset main clean

reset: 
	rm -rf ./$(BUILD_DIR)*.out

clean:
	mv *.o $(BUILD_DIR)
	mv *.out $(BUILD_DIR)

main: main.o calculator.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o calculator.o

main.o: main.cpp 
	$(CC) $(CFLAGS) -c main.cpp

calculator.o:
	$(CC) $(CFLAGS) -c src/calculator.cpp