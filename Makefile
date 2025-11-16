build_all: utf-8 build_Game build_World build_Randomizers build_Grid build_AVLNode build_AVLTree build_HashEntry build_HashTable build_WeightNode build_WeightTree build_Person build_main link 

utf-8:
	chcp 65001

build_World:
	g++ -I./src -I./src/EntityManager -I./src/HashLP -c ./src/EntityManager/World.cpp -o ./bin/World.o

build_Randomizers:
	g++ -I./src -I./src/SupportFunctions -c ./src/SupportFunctions/Randomizers.cpp -o ./bin/Randomizers.o

build_Grid:
	g++ -I./src -I./src/Grid -c ./src/Grid/Grid.cpp -o ./bin/Grid.o

build_AVLNode:
	g++ -I./src -I./src/AVL -c ./src/AVL/AVLNode.cpp -o ./bin/AVLNode.o

build_AVLTree:
	g++ -I./src -I./src/AVL -c ./src/AVL/AVLTree.cpp -o ./bin/AVLTree.o

build_HashEntry:
	g++ -I./src -I./src/HashLP -c ./src/HashLP/HashEntry.cpp -o ./bin/HashEntry.o

build_HashTable:
	g++ -I./src -I./src/HashLP -c ./src/HashLP/HashTable.cpp -o ./bin/HashTable.o

build_WeightNode:
	g++ -I./src -I./src/WeightTree -c ./src/WeightTree/WeightNode.cpp -o ./bin/WeightNode.o

build_WeightTree:
	g++ -I./src -I./src/WeightTree -c ./src/WeightTree/WeightTree.cpp -o ./bin/WeightTree.o

build_Person:
	g++ -I./src -I./src/Person -c ./src/Person/Person.cpp -o ./bin/Person.o

build_Game:
	g++ -c ./src/Game.cpp -I./src -I./src/EntityManager -Iexternal/spdlog/include -Iexternal/SDL3/include -Iexternal/SDL3_image/include -Iexternal/nlohmann_json/include -Iexternal/SDL3_ttf/include -o ./bin/Game.o

build_main:
	g++ -I./src -c ./src/main.cpp -Iexternal/spdlog/include -Iexternal/SDL3/include -Iexternal/SDL3_image/include -Iexternal/nlohmann_json/include -Iexternal/SDL3_ttf/include -o ./bin/main.o

link: ./bin/Game.o ./bin/World.o ./bin/Grid.o ./bin/WeightNode.o ./bin/WeightTree.o ./bin/HashEntry.o ./bin/HashTable.o ./bin/AVLNode.o ./bin/AVLTree.o ./bin/Person.o ./bin/main.o ./bin/Randomizers.o
	g++ ./bin/Game.o ./bin/World.o ./bin/Grid.o ./bin/WeightNode.o ./bin/WeightTree.o ./bin/HashEntry.o ./bin/HashTable.o ./bin/AVLNode.o ./bin/AVLTree.o ./bin/Person.o ./bin/main.o ./bin/Randomizers.o \
	-Lexternal/spdlog -lspdlog \
	-Lexternal/SDL3/lib -lSDL3 \
	-Lexternal/SDL3_image/lib -lSDL3_image \
	-Lexternal/SDL3_ttf/lib -lSDL3_ttf \
	-lwinmm -limm32 -lversion -lole32 -loleaut32 \
	-lsetupapi -lshell32 -luser32 -lgdi32 -luuid \
	-o ./bin/main.exe
run:
	./bin/main.exe

clean:
	del /Q ./bin/*.o
	del /Q ./bin/*.exe