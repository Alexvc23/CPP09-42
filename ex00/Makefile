
RESULT	= btc
SRCS	+= $(shell find srcs -maxdepth 1 -iname *.cpp)
OBJS	= $(SRCS:.cpp=.o)
HEADER	+= $(shell find includes/ -maxdepth 1 -iname *.hpp)

CC		= c++
CFLAGS	= -std=c++98 -g -Wall -Werror -Wextra


all: $(RESULT)

$(RESULT) : $(OBJS)
	$(CC) -Iincludes $(CFLAGS) $(OBJS) -o $@

%.o:	%.cpp $(HEADER) Makefile
	$(CC) -Iincludes $(CFLAGS) -c $< -o $@ 


clean :
	@rm -rf $(OBJS)/*.o

fclean : clean
	@rm -rf $(RESULT)

re : fclean all

.PHONY: all clean fclean re