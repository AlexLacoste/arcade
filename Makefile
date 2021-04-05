##
## EPITECH PROJECT, 2021
## ubuntu [Container ubuntu:latest (/hungry_bose)]
## File description:
## Makefile
##

CFLAGS = make -C

all:
	$(CFLAGS) src/shared
	$(CFLAGS) src/graphics
	$(CFLAGS) src/arcade

games:
	$(CFLAGS) src/shared
	$(CFLAGS) src/games

graphicals:
	$(CFLAGS) src/shared
	$(CFLAGS) src/graphics

core:
	$(CFLAGS) src/arcade

clean:
	$(CFLAGS) src/shared clean
	$(CFLAGS) src/graphics clean
	$(CFLAGS) src/arcade clean

fclean:
	$(CFLAGS) src/shared fclean
	$(CFLAGS) src/graphics fclean
	$(CFLAGS) src/arcade fclean
	rm -f lib/*.so
	rm -f vgcore.*

re:	fclean all

.PHONY: all fclean re