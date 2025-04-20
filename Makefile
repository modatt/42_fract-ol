CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = mandlebrot.c julia.c burning_ship.c main.c utils.c events.c mlx_utils.c render.c
OBJS = $(SRCS:.c=.o)

FRACTOL = fractol

# MLX setup
MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_MAKE = make -C $(MLX_DIR)

INCLUDES = -I$(MLX_DIR)
MLX_LDFLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

# Build everything
all: $(MLX_LIB) $(FRACTOL)

$(MLX_LIB):
	$(MLX_MAKE)

$(FRACTOL): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(MLX_LDFLAGS) -o $(FRACTOL)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJS)
	$(MLX_MAKE) clean

fclean: clean
	rm -rf $(FRACTOL)

re: fclean all

.PHONY: all clean fclean re
