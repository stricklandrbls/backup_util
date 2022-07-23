C=g++
LIB=-lsimpleLogger -lpthread
O=build/main.o build/Content.o build/ConfigData.o build/Config.o build/Compressor.o

clean:
	@rm -rf build

setup:
	@mkdir build

objects: src/main.cpp src/Content.cpp src/ConfigData.cpp src/Config.cpp src/Compressor.cpp
	$(C) -c src/main.cpp -o build/main.o
	$(C) -c src/Content.cpp -o build/Content.o
	$(C) -c src/ConfigData.cpp -o build/ConfigData.o
	$(C) -c src/Config.cpp -o build/Config.o
	$(C) -c src/Compressor.cpp -o build/Compressor.o
	
all: clean setup objects
	$(C) $(O) $(LIB) -o build/backup-util
