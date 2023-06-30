build:
	g++ ./src/*.cpp -Wall -std=c++17 -o bin/sfmlgame -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network 

run:
	./bin/sfmlgame

clean:
	rm bin/sfmlgame