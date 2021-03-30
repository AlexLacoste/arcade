##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

CFLAGS		=	-Wall -Wextra -Werror -W -g3 -ldl

CXXFLAGS 	+= "-std=c++17"

CPPFLAGS	=	-I./include -I./src

LDLIBS		=	-lgtest -lgtest_main -lpthread --coverage

LD			=	g++

NAME		=	arcade

MAIN		=	src/main.cpp

SRC			=	src/Core/Core.cpp			\
				src/DLLoader/DLLoader.cpp

TESTSRC		=	

OBJ			=	$(SRC:.cpp=.o) $(MAIN:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
			$(LD) -o $(NAME) $(OBJ) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)

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

re:			fclean all

tests_run:
			rm -f *.gc*
			$(LD) -o unit_test $(SRC) $(TESTSRC) $(CFLAGS) $(LDFLAGS) $(LDLIBS)
			./unit_test

debug:
			$(LD) -g -o $(NAME) $(MAIN) $(SRC) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS)

.PHONY: 	all $(NAME) clean fclean re tests_run
