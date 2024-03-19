build:
	g++ ./src/*.cpp ./src/*.c -o bin/main -ldl -lglfw
run:
	cd ./bin && ./main
brun:
	g++ ./src/*.cpp ./src/*.c -o bin/main -ldl -lglfw && cd ./bin && ./main
bwindows:
	g++ ./src/*.cpp ./src/*.c -o bin/main.exe -ldl -lglfw
dbg:
	g++ ./src/*.cpp ./src/*.c -o bin/main.exe -ldl -lglfw -ggdb && cd ./bin && gdb ./main

