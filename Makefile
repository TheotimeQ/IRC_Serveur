.PHONY:		fclean, all, clear, re

NAME					=	ircserv

CMP						=	c++
FLG						=	-Wall -Wextra -Werror -std=c++98 -fsanitize=address
RM						=	rm -rf
BUILD_DIR				= 	build/

OBJ_DIR					=	Object
MANAGER_DIR				=	Manager

OBJ_FILE				=   Server Client Channel A_Command Commands
MANAGER_FILE			=   Command_Manager ChannelManager Client_Manager

INC_DIR					=	incs
INC_FILE				=	$(OBJ_INC) $(MANAGER_INC) Irc utils

MANAGER_INC				=  	$(addprefix $(MANAGER_DIR)/, $(MANAGER_FILE))
OBJ_INC					=  	$(addprefix $(OBJ_DIR)/, $(OBJ_FILE))
INC						= 	$(addsuffix .hpp, $(addprefix $(INC_DIR)/, $(INC_FILE)))

SRCS_DIR				=	srcs
SRCS_FILE				=	$(OBJ_SRC) $(MANAGER_SRC) main utils Object/Commands_Channel_Operation Object/Commands_Registration Object/Commands_Message

MANAGER_SRC				=  	$(addprefix $(MANAGER_DIR)/, $(MANAGER_FILE))
OBJ_SRC					=  	$(addprefix $(OBJ_DIR)/, $(OBJ_FILE))
SRCS					=  	$(addsuffix .cpp, $(addprefix $(SRCS_DIR)/, $(SRCS_FILE)))

OBJS			    	= 	$(SRCS:%.cpp=$(BUILD_DIR)%.o)

$(BUILD_DIR)%.o:		%.cpp $(INC)
						@echo -n .
						@mkdir -p $(@D)
						@$(CMP) $(FLG) -I$(INC_DIR) -c $< -o $@

all:		clear $(NAME)

clear:
			clear

$(NAME):	$(INC) $(OBJS)
			@$(CMP) $(FLG) $(OBJS) -I$(INC_DIR) -o $(NAME)
			@echo "\033[32m\n-- Done compiling $(NAME)--\033[0m"

fclean:
			$(RM) $(NAME)
			$(RM) $(BUILD_DIR)

re:			fclean all


