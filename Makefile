PP = g++
FLAGS = -Wall
SRCS = src/main.cpp src/Config.cpp
OUT = bin/backup_util

all: main

main:
	$(PP) $(FLAGS) $(SRCS) -o $(OUT)