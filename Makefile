# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mku <mku@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/09 10:00:00 by student           #+#    #+#              #
#    Updated: 2025/04/26 16:51:58 by mku              ###   ########.fr        #
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
PARSER =	parser/parse_colors.c\
			parser/parse_colors2.c\
			parser/parse_map.c\
			parser/parse_map2.c\
			parser/parse_map3.c\
			parser/parse_textures.c\
			parser/parse_textures2.c\
			parser/validate_map.c\
			parser/validate2_map.c
PLAYER =	player/move.c\
			player/move_utils.c\
			player/rotate.c
RENDERING =	rendering/draw.c\
			rendering/ray.c\
			rendering/raycasting.c\
			rendering/render.c\
			rendering/textures.c
UTILS =		utils/error.c\
			utils/math_utils.c\
			utils/memory.c\
			utils/string_utils.c\
			utils/split.c
EVENTS =	events/exit_handler.c\
			events/key_handler.c
MLX =		mlx/mlx_wrapper.c

SRCS = main.c init.c init2.c \
	   $(PARSER)\
	   $(PLAYER)\
	   $(RENDERING)\
	   $(UTILS)\
	   $(EVENTS)\
	   $(MLX)

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
