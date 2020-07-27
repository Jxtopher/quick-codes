#
# @Author: Jxtopher
# @Date: 2017
#

CC = g++
CFLAGS = -std=c++2a -Wall
OFLAGS = -Os # Optimization flags
GFLAGS = -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused # -Wshadow
DFLAGS = -DDEBUG
FLAGS = $(CFLAGS) $(OFLAGS) $(GFLAGS) $(DFLAGS)
EXEC_NAME = wordGenerator


all : wordGenerator.cpp
	$(CC) $(FLAGS) $< -o $(EXEC_NAME)

run:
	./$(EXEC_NAME)

packages-debain:
	apt-get install g++ build-essential

.PHONY: clean

clean:
	rm $(EXEC_NAME)

mrproper:
	rm $(EXEC_NAME) *.o

