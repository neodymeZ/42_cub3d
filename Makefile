# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: larosale <larosale@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/04 11:31:09 by larosale          #+#    #+#              #
#    Updated: 2020/08/28 16:47:02 by larosale         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= cub3d
CFLAGS			= -Wall -Werror -Wextra
NODEPS			= clean fclean re
LIBS			= -L $(LIBFT_FLDR) -L $(MLX_FLDR) -lft -lmlx
INCLUDES		= -I $(LIBFT_FLDR) -I $(MLX_FLDR) -I $(HDRS_FLDR)
SRCS_FLDR		= ./srcs
HDRS_FLDR		= ./includes
LIBFT_FLDR		= ./libft
MLX_FLDR		= ./mlx
SRCS_LIST		= engine.c cast_ray.c render_walls.c render_floor_and_ceil.c \
				render_skybox.c define_structs.c render_sprites.c \
				clear_structs.c handle_events.c handle_errors.c \
				read_cub_file.c parse_cub_specs.c parse_cub_map.c \
				cleanup.c destroy_structs.c destroy_structs_2.c \
				player_actions.c save_bmp.c engine_utils.c main.c
HDRS_LIST		= engine.h window.h events.h files.h rendering.h errors.h
SRCS			= $(addprefix $(SRCS_FLDR)/,$(SRCS_LIST))
OBJS			= $(SRCS:.c=.o)
HDRS			= $(addprefix $(HDRS_FLDR)/,$(HDRS_LIST))
DEPS			= $(SRCS:.c=.d)
LIBFT			= $(LIBFT_FLDR)/libft.a
MLX				= $(MLX_FLDR)/libmlx.dylib

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@$(CC) $(CFLAGS) $(LIBS) $(OBJS) -o $(NAME)
	@echo "\033[90m[\033[32mSuccess\033[90m]\033[32m Successfully \
	compiled Cub3D\033[0m"

# Include all .d dependency files to the Makefile.
# Including dependencies is conditional - it shall not work when cleaning.

ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
-include $(DEPS)
endif

# Generate a dependency file for each source file

%.d: %.c $(HDRS)
	@$(CC) $(CFLAGS) $(INCLUDES) $< -MM -MF $@; \
	(/bin/echo -n srcs/ && cat $@) > temp && mv temp $@

# Dependencies for .o files are automatically merged with the dependencies from
# .d file for each object

%.o: %.c 
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "\033[90m[\033[32mOK\033[90m]\033[34m Compiling $<\033[0m"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_FLDR)

$(MLX):
	@$(MAKE) -C $(MLX_FLDR)

.PHONY: bonus
bonus: all

.PHONY: clean
clean:
	@$(MAKE) -C $(LIBFT_FLDR) clean
	@$(MAKE) -C $(MLX_FLDR) clean
	@rm -f $(OBJS) $(DEPS)
	@echo "\033[90m[\033[91mDeleting\033[90m]\033[31m Object and temp files \
	for Cub3D were deleted\033[0m"

.PHONY: fclean
fclean: clean
	@rm -f $(LIBFT)
	@rm -f $(MLX)
	@rm -f $(NAME)
	@echo "\033[90m[\033[91mDeleting\033[90m]\033[31m All compiled \
	items were deleted.\033[0m"

.PHONY: re
re: fclean all
