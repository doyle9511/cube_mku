# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/09 10:00:00 by student           #+#    #+#              #
#    Updated: 2025/04/17 22:07:58 by donghwi2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

# 컴파일러 및 플래그
CC = cc
CFLAGS = -Wall -Wextra -Werror

# MinilibX 관련 설정
MLX_PATH = mlx
MLX_FLAGS = -lmlx -lXext -lX11 -lm
MLX_LIB = $(MLX_PATH)/libmlx.a

# 소스 디렉토리 및 파일
SRCS_DIR = srcs
SRCS = main.c init.c init2.c \
       parser/parse_map.c parser/validate_map.c parser/parse_textures.c parser/parse_colors.c \
       rendering/render.c rendering/raycasting.c rendering/textures.c rendering/draw.c \
       player/move.c player/rotate.c \
       events/key_handler.c events/exit_handler.c \
       utils/error.c utils/memory.c utils/math_utils.c utils/string_utils.c \
       mlx/mlx_wrapper.c

# 소스 파일 경로
SRCS_PATH = $(addprefix $(SRCS_DIR)/, $(SRCS))

# 오브젝트 디렉토리 및 파일
OBJS_DIR = objs
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

# 헤더 디렉토리
INCLUDES = -I./includes -I./$(MLX_PATH)

# 기본 규칙
all: $(NAME)

# 메인 타겟
$(NAME): $(MLX_LIB) $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(MLX_PATH) $(MLX_FLAGS)
	@echo "$(NAME) created!"

# MinilibX 라이브러리 컴파일
$(MLX_LIB):
	@echo "Compiling MinilibX..."
	@make -C $(MLX_PATH)

# 오브젝트 디렉토리 생성
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/parser
	@mkdir -p $(OBJS_DIR)/rendering
	@mkdir -p $(OBJS_DIR)/player
	@mkdir -p $(OBJS_DIR)/events
	@mkdir -p $(OBJS_DIR)/utils
	@mkdir -p $(OBJS_DIR)/mlx

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJS_DIR)
	@make -C $(MLX_PATH) clean

fclean: clean
	@echo "Cleaning executable..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re norm