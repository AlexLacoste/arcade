##
## EPITECH PROJECT, 2021
## ubuntu [Container ubuntu:latest (/hungry_bose)]
## File description:
## Makefile
##

CFLAGS		=	-Wall -Wextra -Werror -W

CXXFLAGS	+= "-std=c++17"

CPPFLAGS	=	-I./ -I./DLLoader -g3

LDLIBS		=	-ldl

LD			=	g++

NAME		=	arcade

SRC			=	main.cpp				\
				Arcade.cpp				\
				Menu.cpp

OBJ			=	$(SRC:.cpp=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	$(LD) -o $(NAME) ../shared/*.o $(OBJ) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)
	mv arcade ../../

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
	rm -f ../../arcade

re:	fclean all

debug:
	$(LD) -g -o $(NAME) $(MAIN) $(SRC) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS)

.PHONY: all clean fclean re 