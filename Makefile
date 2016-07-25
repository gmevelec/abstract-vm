#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/02 10:34:11 by gmevelec          #+#    #+#              #
#    Updated: 2015/11/10 15:44:40 by gmevelec         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = avm

SRC = main.cpp Parser.class.cpp Exception.class.cpp Vm.class.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	clang++ -o $@ $^

%.o: %.cpp
	clang++ -o $@ -c $^ -Wall -Werror -Wextra

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
