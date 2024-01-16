NAME		:= webserv

INC			:= -I ./srcs/server/
SRCS		:= $(wildcard ./srcs/*.cpp)
SRCS		+= $(wildcard ./srcs/*/*.cpp)
OBJS_DIR	:= ./objs
OBJS		:= $(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))
DEPS		:= $(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.d))

CXX			:= c++
CXXFLAGS	:= -Wall -Wextra -Werror -std=c++98 $(INC) -MMD -MP


all			: $(NAME)

$(NAME)	: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

$(OBJS_DIR)/%.o:	%.cpp
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean		:
	rm -rf $(OBJS_DIR)

fclean		: clean
	$(RM) $(NAME)

re			: fclean all

debug		: clean
	$(MAKE) CXXFLAGS="$(CXXFLAGS) -D DEBUG"
	$(MAKE) clean

.PHONY		: all clean fclean re debug

-include $(DEPS)