NAME		:= ircserv
PORT		:= 6667
PSWD		:= password
INC			:= $(shell find srcs -type d | sed 's/^/-I /')
SRCS_DIR	:= ./srcs
SRCS	    := $(shell find srcs -name "*.cpp"| sed 's/^/.\//')
OBJS_DIR	:= ./objs
OBJS		:= $(subst $(SRCS_DIR), $(OBJS_DIR), $(SRCS:.cpp=.o))
DEPS		:= $(subst $(SRCS_DIR), $(OBJS_DIR), $(SRCS:.cpp=.d))

CXX			:= c++
CXXFLAGS	:= -Wall -Wextra -Werror -std=c++98 $(INC) -MMD -MP -g -fsanitize=address

# Debug
ifeq ($(MAKECMDGOALS), debug)
	CXXFLAGS += -DDEBUG
endif

all			: $(NAME)

$(NAME)	: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: srcs/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean		:
	rm -rf $(OBJS_DIR) $(shell find . -name '*.o')

fclean		: clean
	$(RM) $(NAME)

re			: fclean all

debug		: re

run			: all
	./$(NAME) $(PORT) $(PSWD)

# ./client が存在したら./clientを削除してから./clientをコンパイルする
client		:
	$(RM) client
	$(CXX) -o client.o client.cpp
	./client.o

help		: Makefile
	@echo "Usage: make [target]"
	@echo ""
	@echo "Targets:"
	@echo "  all		- build $(NAME)"
	@echo "  clean		- remove object files"
	@echo "  fclean	- remove object files and $(NAME)"
	@echo "  re		- remove object files and $(NAME) then build"
	@echo "  debug		- build $(NAME) with debug flag"
	@echo "  run		- run $(NAME) with $(PORT) and '$(PSWD)'"
	@echo "  client	- run client with $(PORT) run server first"
	@echo "  help		- show this help"

.PHONY		: all clean fclean re debug help run

-include $(DEPS)