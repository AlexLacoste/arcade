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

# tests_run:
# 	$(CFLAGS) solver tests_run
# 	$(CFLAGS) generator tests_run

fclean:
	$(CFLAGS) src/shared fclean
	$(CFLAGS) src/graphics fclean
	$(CFLAGS) src/arcade fclean
	rm -f lib/*.so

re:	fclean all

.PHONY: all fclean re