SRC = main.c read_file.c
OBJ = $(SRC:.c=.o)
INC = -I ./libft/includes -I .
INCS = libft.h wolf.h
LIBF = ./libft/libft.a
FLAG = gcc
NAME = wolf
MLX = -framework Opengl -framework appkit -lmlx

all: $(NAME)

$(NAME) : $(LIBF) $(OBJ)
	$(FLAG) -o $@ $(OBJ) $(LIBF) $(INC) $(MLX)

$(LIBF) :
	make -C libft

$(OBJ) : %.o:%.c
	$(FLAG) -c $< $(INC)

clean :
	rm -rf $(OBJ)
	make -C libft clean

fclean : clean
	rm -rf $(NAME)
	make -C libft fclean

re : fclean all
