NAME		:= MyContainers.exe
NAME_STL	:= STLContainers.exe

CC			:= c++
CFLAGS		:= -Wall -Wextra -Werror -std=c++98
DEP_FLAGS	:= -MP -MMD

SRCS_DIR	:= sources
HDRS_DIR	:= headers
vpath %.cpp	$(SRCS_DIR)
vpath %.hpp	$(HDRS_DIR)
INCLUDES	:= -I$(HDRS_DIR)

SRCS		:=	main.cpp \
				vector.test.cpp

OBJS_DIR	:= .objects
OBJ_PREFIX	:= ft_
OBJS_FT		:= $(SRCS:%.cpp=$(OBJS_DIR)/$(OBJ_PREFIX)%.o)

DEPS		:= $(SRCS:%.cpp=$(OBJS_DIR)/%.d)

all:
					@echo "$(BOLD)Creating/updating $(WHITE_B)'$(NAME)'$(BOLD):$(DEF)"
					@$(MAKE) --no-print-directory $(NAME)
					@$(MAKE) --no-print-directory NAME=$(NAME_STL) CFLAGS+=" -D STL_TEST" OBJ_PREFIX="stl_" $(NAME_STL)

$(NAME):			$(OBJS_FT)
					@echo "$(BOLD)Linking files...$(DEF)"
					@$(CC) $(OBJS_FT) $(CFLAGS) $(INCLUDES) -o $@
					@echo "$(WHITE_B)'$(NAME)'$(BOLD) has been created/updated.$(DEF)"

$(OBJS_DIR)/$(OBJ_PREFIX)%.o:	%.cpp | $(OBJS_DIR)
								@echo "Assembling $<..."
								@$(CC) $(CFLAGS) $(DEP_FLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR):
					@mkdir -p $@
					@echo "$(BOLD)Directory '$(OBJS_DIR)' has been created.$(DEF)"

clean:
					@rm -rf $(OBJS_FT) $(DEPS) $(OBJS_DIR)
					@echo "$(WHITE)$(NAME): $(BOLD)Object files have been cleaned.$(DEF)"
					@echo "$(WHITE)$(NAME_STL): $(BOLD)Object files have been cleaned.$(DEF)"

fclean:				clean
					@rm -rf $(NAME) $(NAME_STL)
					@echo "$(WHITE)'$(NAME)'$(BOLD) has been cleaned.$(DEF)"
					@echo "$(WHITE)'$(NAME_STL)'$(BOLD) has been cleaned.$(DEF)"

re:					fclean all

.PHONY:				all clean fclean re

-include $(DEPS)

BOLD	:= \033[0;1m
WHITE_B	:= \033[1;37m
WHITE	:= \033[37m
DEF		:= \033[0;39m
