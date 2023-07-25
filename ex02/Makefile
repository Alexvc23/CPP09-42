RESULT	= PmergeMe
SRCS	= $(shell find srcs/ -maxdepth 1 -iname *.cpp) 
OBJS	= $(SRCS:.cpp=.o)
HEADER	= $(shell find includes/ -maxdepth 1 -iname *.hpp)

CC 		= c++
CFLAGS	= -std=c++98 -Wall -Werror -Wextra -g

all: $(RESULT)

$(RESULT): $(OBJS)
	$(CC) -Iincludes $(CFLAGS) $(OBJS) -o $@

%.o: %.cpp $(HEADER) Makefile
	$(CC) -Iincludes $(CFLAGS) -c $< -o $@

clean:
	@ echo "Removing objects"
	@rm -rf srcs/*.o

fclean: clean
	@ echo "Removing executable"
	@rm -rf $(RESULT)

re: fclean all
	@ echo "Recreating project"

.PHONY: all clean fclean re
