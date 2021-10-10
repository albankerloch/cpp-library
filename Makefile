#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akerloc- <akerloc-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/12 17:40:07 by akerloc-          #+#    #+#              #
#    Updated: 2020/01/26 13:14:04 by akerloc-         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SRCS =	main.cpp \
        Test_Map.cpp
OBJS = ${SRCS:.cpp=.o}
NAME = containers
CXX = clang++
RM = rm -rf
CXXFLAGS = -g -Wall -Wextra -Werror -std=c++98 -I.

all : ${NAME}

clean : 
		$(RM) ${OBJS} 

fclean : clean
		$(RM) ${NAME}

$(NAME) : ${OBJS} 
		${CXX} -o ${NAME} ${OBJS} ${CXXFLAGS}

re : fclean all

.PHONY : all clean re fclean