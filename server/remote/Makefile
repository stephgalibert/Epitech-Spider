##
## Makefile for server in /home/galibe_s/project/SpiderServer/plugins/UIConsole
## 
## Made by stephane galibert
## Login   <galibe_s@epitech.net>
## 
## Started on  Mon Aug  8 20:25:54 2016 stephane galibert
## Last update Wed Nov  9 05:35:07 2016 stephane galibert
##

NAME		=	bin/console

CXX		=	g++

RM		=	rm -f

SRCS		+=	main.cpp
SRCS		+=	Console.cpp
SRCS		+=	Listen.cpp
SRCS		+=	./utils/StaticTools.cpp
SRCS		+=	./utils/JSONBuilder.cpp
SRCS		+=	./utils/JSONReader.cpp

OBJS		=	$(SRCS:.cpp=.o)

CXXFLAGS	+=	-g
CXXFLAGS	+=	-std=c++11
CXXFLAGS	+=	-Wall -Wextra -Werror

CXXFLAGS	+=	-I./
CXXFLAGS	+=	-I./lib/
CXXFLAGS	+=	-I./utils/

LDFLAGS		+=	-lpthread -lboost_thread -lboost_system
LDFLAGS		+=	-lssl -lcrypto

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

re:		fclean all

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)
