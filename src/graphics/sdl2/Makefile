##
## EPITECH PROJECT, 2021
## ubuntu [Container ubuntu:latest (/hungry_bose)]
## File description:
## Makefile
##

CXXFLAGS		=	-Wall -Wextra -g3 -fPIC "-std=c++17"

CPPFLAGS	=	-I./ -I../

LDLIBS		=	-lSDL2main -lSDL2 -lSDL2_ttf

LDFLAGS		=	-shared

LD			=	g++

NAME		=	arcade_sdl2.so

SRC			=	GraphicSdl2.cpp		\
				TextSdl2.cpp		\
				SpriteSdl2.cpp

OBJ			=	$(SRC:.cpp=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	$(LD) -o $(NAME) $(OBJ) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)
	mkdir -p ../../../lib
	mv $(NAME) ../../../lib/

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
	rm -f *.o

re:	fclean all

debug:
	$(LD) -g -o $(NAME) $(MAIN) $(SRC) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS)

.PHONY: all clean fclean re 