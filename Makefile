all: compile link
all-clean: compile link clean

compile: 
	g++ -c src/*.cpp -Wall -I include 

link:
	g++ *.o -o bin/main -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm *.o