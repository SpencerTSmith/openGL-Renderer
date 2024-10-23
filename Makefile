build:
	g++ -g -Wall -std=c++20 ./src/*.cpp -lGL -lglfw -lGLEW -lm -o renderer
run:
	./renderer
clean:
	rm renderer
