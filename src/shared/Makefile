##
## EPITECH PROJECT, 2021
## ubuntu [Container ubuntu:latest (/hungry_bose)]
## File description:
## Makefile
##

CFLAGS		=	-Wall -Wextra -Werror -W -g3 fPIC

CXXFLAGS	+= "-std=c++17"

CPPFLAGS	=	-I./

LDLIBS		=	-lgtest -lgtest_main -lpthread --coverage

LD			=	g++



SRC			=	Color.cpp

# TESTSRC	=	

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

# tests_run:
# 	rm -f *.gc*
# 	$(LD) -o unit_test $(SRC) $(TESTSRC) $(CFLAGS) $(LDFLAGS) $(LDLIBS)
# 	./unit_test

debug:
	$(LD) -g -o $(NAME) $(SRC) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS)

.PHONY: all clean fclean re 