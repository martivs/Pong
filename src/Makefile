WWW = -Wall -Werror -Wextra

all: pong pong_dinamic

pong:
	gcc $(WWW) pong.c -o ../build/pong.out

pong_dinamic:
	gcc $(WWW) pong_dinamic.c -lncurses -o ../build/pong_dinamic.out

clean: 
	rm -rf ../build/*.out