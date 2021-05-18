##
## EPITECH PROJECT, 2021
## ubuntu [Container ubuntu:latest (/hungry_bose)]
## File description:
## Makefile
##

CFLAGS = make -C

all:
	make -C src/shared
	make -C src/graphics
	make -C src/games
	make -C src/arcade

games:
	make -C src/shared
	make -C src/games

graphicals:
	make -C src/shared
	make -C src/graphics

core:
	make -C src/shared
	make -C src/arcade

clean:
	make -C src/shared clean
	make -C src/graphics clean
	make -C src/games clean
	make -C src/arcade clean

fclean:
	make -C src/shared fclean
	make -C src/graphics fclean
	make -C src/games fclean
	make -C src/arcade fclean
	rm -f lib/*.so
	rm -f vgcore.*

re:	fclean all

.PHONY: all fclean re