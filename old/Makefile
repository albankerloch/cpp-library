NAME	= containers
SRCS	= main.cpp
SRCS	+= List/TestList.cpp
SRCS	+= List/TestListIterator.cpp
SRCS	+= Map/TestMap.cpp
SRCS	+= Map/TestMapIterator.cpp
SRCS	+= Vector/TestVector.cpp
SRCS	+= Vector/TestVectorIterator.cpp
SRCS	+= Stack/TestStack.cpp
SRCS	+= Queue/TestQueue.cpp

CFLAGS	= -Wall -Wextra -Werror -std=c++98
CC		= clang++

OBJDIR	= .objs
OBJS	=	$(addprefix $(OBJDIR)/, $(SRCS:.cpp=.o))

$(NAME): $(OBJS)
		${CC} ${CFLAGS} $(OBJS) -o $(NAME)

all:		$(NAME)

$(OBJS): | $(OBJDIR)

$(OBJDIR):
		@mkdir $(OBJDIR)
		@mkdir $(OBJDIR)/List
		@mkdir $(OBJDIR)/Vector
		@mkdir $(OBJDIR)/Map
		@mkdir $(OBJDIR)/Iterators
		@mkdir $(OBJDIR)/Stack
		@mkdir $(OBJDIR)/Queue

${OBJDIR}/%.o: %.cpp
		${CC} ${CFLAGS} -c $< -o $@

clean:
			rm -rf $(OBJDIR)

fclean:	clean
			rm -f $(NAME)

re:		fclean all

.PHONY: all clean fclean re
