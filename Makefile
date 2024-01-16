NAME		:= webserv

INC			:= -I ./srcs/server/
SRCS_DIR	:= ./srcs
SRCS		:= $(wildcard $(SRCS_DIR)/*.cpp) $(wildcard $(SRCS_DIR)/*/*.cpp)
OBJS_DIR	:= ./objs
OBJS		:= $(subst $(SRCS_DIR), $(OBJS_DIR), $(SRCS:.cpp=.o))
DEPS		:= $(subst $(SRCS_DIR), $(OBJS_DIR), $(SRCS:.cpp=.d))

CXX			:= c++
CXXFLAGS	:= -Wall -Wextra -Werror -std=c++98 $(INC) -MMD -MP

# Debug
ifeq ($(MAKECMDGOALS), debug)
	CFLAGS += -DDEBUG
endif

# Color
CHECK		= \033[32m[✔]\033[0m
REMOVE		= \033[31m[✘]\033[0m
GENERATE	= \033[33m[➤]\033[0m
BLUE		= \033[1;34m
YELLOW		= \033[1;33m
RESET		= \033[0m

# Progress bar
TOTAL_FILES := $(shell echo $(words $(SRCS)))
CURRENT_FILE = 1

define progress
    @printf "$(GENERATE) $(YELLOW)Webserv obj file gen Progress: %3d%% (%d/%d)$(RESET)\r" $$(($(CURRENT_FILE)*100/$(TOTAL_FILES))) $(CURRENT_FILE) $(TOTAL_FILES)
    @$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))
    @if [ $(CURRENT_FILE) -gt $(TOTAL_FILES) ]; then \
        printf "$(GENERATE) $(YELLOW)Finish Generating WEBSERV Object files !%-50.50s\n$(RESET)"; \
    fi
endef

all			: $(NAME)

$(NAME)	: $(OBJS)
	@$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: srcs/%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -o $@ -c $<
	$(call progress)

clean		:
	rm -rf $(OBJS_DIR)

fclean		: clean
	$(RM) $(NAME)

re			: fclean all

debug		: re

.PHONY		: all clean fclean re debug

-include $(DEPS)