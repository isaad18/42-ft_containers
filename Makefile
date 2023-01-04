SRCS		= main.cpp

OBJS		= $(SRCS:.cpp=.o)

CXX			= c++

$(RM)		= rm -f

CXXFLAGS		= -Wall -Werror -Wextra -std=c++98 -g

NAME		= out

all:		$(NAME)

$(NAME):	$(OBJS)
				$(CXX) $(CXXFLAGS) $(SRCS) -o $(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
				$(RM) $(NAME)

re:			fclean all