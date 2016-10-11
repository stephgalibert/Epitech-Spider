##
## Makefile for server in /home/galibe_s/project/SpiderServer/lib
## 
## Made by stephane galibert
## Login   <galibe_s@epitech.net>
## 
## Started on  Fri Aug 19 19:44:38 2016 stephane galibert
## Last update Fri Aug 19 20:17:52 2016 stephane galibert
##

NAME		=	./bin/libplugin.a

CXX		=	g++

RM		=	rm -f

SRCS		+=	./src/PluginRegister.cpp

OBJS		=	$(SRCS:.cpp=.o)

CXXFLAGS	+=	-g
CXXFLAGS        +=      -fPIC -shared
CXXFLAGS	+=	-std=c++11
CXXFLAGS	+=	-Wall -Wextra -Werror

CXXFLAGS	+=	-I./include/

LDFLAGS		+=	-lboost_system


all:		$(NAME)

$(NAME):	$(OBJS)
		ar rc $(NAME) $(OBJS)
		ranlib $(NAME)

re:		fclean all

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)
