##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

CFLAGS	=	-Wall -Wextra -Werror -W -g3

CXXFLAGS += "-std=c++17"

CPPFLAGS	=	-I./include/

LDLIBS	=	-lgtest -lgtest_main -lpthread --coverage

LD		=	g++

NAME	=	nanotekspice

MAIN	=	src/main.cpp

SRC		=	

TESTSRC	=	

OBJ		=	$(SRC:.cpp=.o) $(MAIN:.cpp=.o)

all:	$(NAME)

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

re:	fclean all

tests_run:
	rm -f *.gc*
	$(LD) -o unit_test $(SRC) $(TESTSRC) $(CFLAGS) $(LDFLAGS) $(LDLIBS)
	./unit_test

debug:
	$(LD) -g -o $(NAME) $(MAIN) $(SRC) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS)

.PHONY: all clean fclean re tests_run
