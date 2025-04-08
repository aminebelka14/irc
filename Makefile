NAME = ircserv

CC	= clang++

CFLAGES = -g3 -Wall -Wextra -std=c++98 -fsanitize=address


IFLAGES =  -I./inc -I./inc/cmd

SRCS := ./main.cpp \
		./srcs/Socket.cpp \
		./srcs/Utils.cpp \
		./srcs/Server.cpp \
		./srcs/User.cpp \
		./srcs/Invoker.cpp \
		./srcs/Channel.cpp \
		./srcs/cmd/Join.cpp \
		./srcs/cmd/Invite.cpp \
		./srcs/cmd/Kick.cpp \
		./srcs/cmd/Mode.cpp \
		./srcs/cmd/Privmsg.cpp \
		./srcs/cmd/Quit.cpp \
		./srcs/cmd/Ping.cpp \
		./srcs/cmd/Part.cpp \
		./srcs/cmd/Notice.cpp \
		./srcs/Server_utils.cpp



OBJS := $(SRCS:%.cpp=%.o)

$(NAME): $(OBJS)
		@$(CC) $(CFLAGES) $(OBJS) -o $@ 

all: $(NAME)

clean:
		@rm -rf $(OBJS) 
		@echo "Delete"

fclean:clean
		@rm -rf $(NAME)
		@echo "Delete all"

%.o: %.cpp
		@$(CC) $(CFLAGES) $(IFLAGES) -c $< -o $@
		
re: fclean all

.PHONY: all clean fclean re
	
