##
## Makefile for server in /home/galibe_s/project/SpiderServer/plugins/UIConsole
## 
## Made by stephane galibert
## Login   <galibe_s@epitech.net>
## 
## Started on  Mon Aug  8 20:25:54 2016 stephane galibert
## Last update Mon Aug 22 19:26:33 2016 stephane galibert
##

NAME		=	bin/ui_console.so

CXX		=	g++

RM		=	rm -f

SRCS		+=	Console.cpp
SRCS		+=	./utils/StaticTools.cpp
SRCS		+=	./utils/JSONBuilder.cpp
SRCS		+=	./utils/JSONReader.cpp

OBJS		=	$(SRCS:.cpp=.o)

CXXFLAGS	+=	-g
CXXFLAGS	+=	-fPIC -shared
CXXFLAGS	+=	-std=c++11
CXXFLAGS	+=	-Wall -Wextra -Werror

CXXFLAGS	+=	-I./
CXXFLAGS	+=	-I./lib/
CXXFLAGS	+=	-I./utils/

LDFLAGS		+=	-lpthread
LDFLAGS		+=	-L./lib/ -lplugin

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
		cp $(NAME) ../../bin/plugins/

re:		fclean all

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)
