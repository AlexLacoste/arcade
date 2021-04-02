##
## EPITECH PROJECT, 2021
## ubuntu [Container ubuntu:latest (/hungry_bose)]
## File description:
## Makefile
##

CFLAGS		=	-Wall -Wextra -Werror -W -g3

CXXFLAGS	+= "-std=c++17"

CPPFLAGS	=	-I./ -I./DLLoader

LDLIBS		=	-ldl

LD			=	g++

NAME		=	arcade

SRC			=	main.cpp				\
				Arcade.cpp

# TESTSRC	=	

OBJ			=	$(SRC:.cpp=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	$(LD) -o $(NAME) $(OBJ) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)
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

# tests_run:
# 	rm -f *.gc*
# 	$(LD) -o unit_test $(SRC) $(TESTSRC) $(CFLAGS) $(LDFLAGS) $(LDLIBS)
# 	./unit_test

debug:
	$(LD) -g -o $(NAME) $(MAIN) $(SRC) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS)

.PHONY: all clean fclean re 