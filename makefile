run:
	g++ ./src/*.cpp ./src/*.c -o bin/main -ldl -lglfw && cd bin && ./main
