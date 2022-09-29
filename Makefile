
NAME = sdl_test

_SRC = main.c 


_OBJ = $(_SRC:.c=.o)


_EXLIB =
_IDIR = ./

SDIR = 
ODIR =


EXLIBD = 

IFLAG = -I

SRC = $(patsubst %, $(SDIR)%, $(_SRC))
OBJ = $(patsubst %, $(ODIR)%, $(_OBJ))


EXLIB = $(patsubst %, $(EXLIBD)%, $(_EXLIB))
INC = $(patsubst %, $(IFLAG)%, $(_IDIR))

CC = gcc

FLAGS = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)



$(NAME): $(OBJ) $(OBJ2)
	$(CC) $(FLAGS) $(INC) $(OBJ)  $(EXLIB) -o $(NAME) -lSDL2main -lSDL

$(ODIR)%.o : $(SDIR)%.c 
	$(CC) $(FLAGS) $(INC) -c  $< -o $@


clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all