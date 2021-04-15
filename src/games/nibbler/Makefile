##
## EPITECH PROJECT, 2021
## B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
## File description:
## Makefile
##

LD			=	g++

CXXFLAGS	=	-Wall -Wextra -g3 -fPIC "-std=c++17"

CPPFLAGS	=	-I./ -I../

LDFLAGS		=	-shared

NAME		=	arcade_nibbler.so

SRC			=	Nibbler.cpp		\
				NibblerPlayer.cpp


OBJ			=	$(SRC:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
			$(LD) -o $(NAME) ../../shared/*.o $(OBJ) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
			mv $(NAME) ../../../lib/

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY: 	all $(NAME) clean fclean re 
