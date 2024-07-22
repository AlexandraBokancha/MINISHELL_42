# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/01 13:32:31 by eschussl          #+#    #+#              #
#    Updated: 2024/06/10 19:31:40 by albokanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME			=	minishell

CC				=	cc
CFLAGS			=	-Wall -Wextra -g3 -Werror
LFLAGS			=	-lreadline -lhistory

LIBS_PATH		=	libs/
LIBFT_PATH		=	$(addprefix $(LIBS_PATH),libft/)
LIBFT			=	$(addprefix $(LIBFT_PATH),libft.a)

SRCS_PATH		=	src/
SIGN_PATH       =   signals/
PARS_PATH		=	parser/
WORDS_PATH		=	words/
LEXER_PATH		=	lexer/
EXEC_PATH		=	executor/
BUILTIN_PATH    =   builtin/
PIPE_PATH		=	pipe/
NO_PIPE_PATH	=	no_pipe/
ERR_PATH		=   error/
ENVP_PATH		=	envp/
SRCS			=	main.c\
					$(addprefix $(ENVP_PATH), ms_envp.c)\
					$(addprefix $(LEXER_PATH), ms_lexer.c ms_nodefill.c ms_lexer_utils.c)\
					$(addprefix $(PARS_PATH), ms_parser_utils.c ms_parser_utils2.c ms_build_utils.c ms_parser.c ms_parsing_env.c ms_parsing_quotes.c ms_parsing_spaces.c ms_parsingdquotes.c\
						$(addprefix $(WORDS_PATH), ms_here_doc.c ms_input_set.c ms_args.c ms_cmd_set.c ms_output_set.c ms_parsing_words.c))\
					$(addprefix $(EXEC_PATH), ms_exec_utils.c ms_executor.c ms_dup.c ms_red.c\
						$(addprefix $(PIPE_PATH), ms_child.c ms_child_utils.c ms_fork.c ms_path.c ms_pip.c)\
						$(addprefix $(NO_PIPE_PATH), ms_no_pipe.c ms_no_pipe_utils.c ms_path.c)\
						$(addprefix $(BUILTIN_PATH), ms_builtin.c ms_export_utils.c ms_cd.c ms_echo.c ms_env.c ms_export.c ms_pwd.c ms_exit.c ms_unset.c))\
					$(addprefix $(ERR_PATH), ms_error.c ms_free.c ms_free_env.c)\
					$(addprefix $(SIGN_PATH), ms_signal_trap.c)\
					
					
OBJS_PATH		=	obj/
OBJS			=	$(addprefix $(OBJS_PATH),$(SRCS:.c=.o))
INC_PATH		=	inc/

$(NAME): $(OBJS)
	make -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBFT) -I$(LIBFT_PATH)$(INC_PATH) -I$(INC_PATH) $(LFLAGS) 

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c $(INC_PATH)minishell.h
	@mkdir -p $(OBJS_PATH)
	@mkdir -p $(OBJS_PATH)$(PARS_PATH)
	@mkdir -p $(OBJS_PATH)$(PARS_PATH)$(WORDS_PATH)
	@mkdir -p $(OBJS_PATH)$(LEXER_PATH)
	@mkdir -p $(OBJS_PATH)$(EXEC_PATH)$(BUILTIN_PATH)
	@mkdir -p $(OBJS_PATH)$(EXEC_PATH)$(PIPE_PATH)
	@mkdir -p $(OBJS_PATH)$(EXEC_PATH)$(NO_PIPE_PATH)
	@mkdir -p $(OBJS_PATH)$(ERR_PATH)
	@mkdir -p $(OBJS_PATH)$(ENVP_PATH)
	@mkdir -p $(OBJS_PATH)$(SIGN_PATH)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_PATH) -I $(LIBFT_PATH)$(INC_PATH)

all	:$(NAME) libs

libft :
	make -C $(LIBFT_PATH)

clean :
	make -C $(LIBFT_PATH) clean
	rm -rf $(OBJS_PATH)

fclean : clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re : fclean all

.PHONY : all libft clean fclean re

