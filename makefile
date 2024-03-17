build:
	g++ ./src/*.cpp ./src/*.c -o bin/main -ldl -lglfw
run:
	cd ./bin && ./main
