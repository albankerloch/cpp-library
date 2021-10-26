

CC = clang++
SRCS_FILES = main.cpp \
			 Test_Map.cpp \
			 Test_Vector.cpp

NAME = ft_containers
OBJS_PATH = ./OBJS_FT/
OBJS = ${addprefix ${OBJS_PATH}, ${SRCS_FILES:.cpp=.o}}
CFLAGS = -Wall -Wextra -Werror -std=c++98 -DNAMESPACE=ft

STD_NAME = std_containers
STD_OBJS_PATH = ./OBJS_STD/
STD_OBJS = ${addprefix ${STD_OBJS_PATH}, ${SRCS_FILES:.cpp=.o}}
STD_CFLAGS = -Wall -Wextra -Werror -std=c++98 -DNAMESPACE=std

all: ${NAME}

$(NAME): ${OBJS_PATH} ${OBJS} ${STD_OBJS_PATH} ${STD_OBJS}
	@${CC} ${CFLAGS} -o ${NAME} ${OBJS}
	@${CC} ${STD_CFLAGS} -o ${STD_NAME} ${STD_OBJS}

${OBJS_PATH}:
	@mkdir -p $@

${STD_OBJS_PATH}%.o: %.cpp 
	@${CC} ${STD_CFLAGS} -c $< -o $@

${STD_OBJS_PATH}:
	@mkdir -p $@

${OBJS_PATH}%.o: %.cpp 
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@rm -rf ${OBJS_PATH}
	@rm -rf $(STD_OBJS_PATH)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(STD_NAME)

re: fclean all

.PHONY: all clean fclean re
