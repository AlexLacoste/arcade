##
## EPITECH PROJECT, 2021
## ubuntu [Container ubuntu:latest (/hungry_bose)]
## File description:
## Makefile
##

CXXFLAGS	+= -Wall -Wextra -Werror -W -g3 -fPIC "-std=c++17"

CPPFLAGS	=	-I./

LD			=	g++

SRC			=	Color.cpp			\
				Errors.cpp

OBJ			=	$(SRC:.cpp=.o)

all:	$(OBJ)

clean:
	rm -f $(OBJ)
	rm -f *.o
	rm -f *.gcda
	rm -f *.gcno
	rm -f vgcore.*
	rm -f *.report

fclean:		clean
	rm -f $(NAME)
	rm -f unit_test

re:	fclean all

.PHONY: all clean fclean re 