all: mq.o game

mq.o: mq.c 
	gcc -Wall -Werror -std=c11 -c mq.c
 
game: game.c
	gcc -Wall -Werror -std=c11 -g -o game game.c mq.o
 
clean:
	rm mq.o
	rm game

