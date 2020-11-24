


MODULE_SRC= mlx_image.swift mlx_window.swift mlx_init.swift
MODULE_OBJ=$(MODULE_SRC:.swift=.swiftmodule)

SRC= interface.swift $(MODULE_SRC)
OBJ=$(SRC:.swift=.o)

C_SRC= mlx_xpm.c mlx_png.c mlx_string_put.c
C_OBJ=$(C_SRC:.c=.o)
CFLAGS=-O3

NAME=libmlx.dylib

INC=-I.
#OPTI=-Ounchecked

all: $(NAME)

$(NAME): $(MODULE_OBJ) $(OBJ) $(C_OBJ)
	@swiftc $(OPTI) $(INC) -o $(NAME) -emit-library $(OBJ) $(C_OBJ) -lz
# Command added to change install name of libmlx for proper loading
	@install_name_tool -id @executable_path/mlx/$(NAME) $(NAME)
	@echo "\033[90m[\033[32mSuccess\033[90m]\033[32m Successfully \
	compiled miniLibX\033[0m"

%.o: %.swift
	@swiftc $(OPTI) $(INC) -parse-as-library -c $< -o $@

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

%.swiftmodule: %.swift
	@swiftc $(OPTI) $(INC) -parse-as-library -c $< -o $@ -emit-module -module-name $(patsubst %.swift,%,$<) -module-link-name $(patsubst %.swift,%,$<)

clean:
	@rm -f $(OBJ) $(MODULE_OBJ) $(C_OBJ) *.swiftdoc *~
	@echo "\033[90m[\033[91mDeleting\033[90m]\033[31m Object and temp \
	files for miniLibX were deleted\033[0m"
# Rule created to allow cleaning without deleting library
fclean: clean
	@rm -f $(NAME)
