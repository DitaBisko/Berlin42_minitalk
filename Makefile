CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = server.c client.c
OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: server client

server: server.o
	$(CC) $(CFLAGS) -o server server.o

client: client.o
	$(CC) $(CFLAGS) -o client client.o
	
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f server client

re: fclean all

.PHONY: all clean fclean re