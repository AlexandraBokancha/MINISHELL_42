/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:32:45 by eschussl          #+#    #+#             */
/*   Updated: 2024/06/10 19:48:06 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*##################################*/
/*                                  */
/*            LIBRARIES            	*/
/*                                  */
/*##################################*/

# include "libft.h"
# include <aio.h>
# include <dirent.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

/*##################################*/
/*                                  */
/*             DEFINES              */
/*                                  */
/*##################################*/

# define MS_HERE_DOC_FILE ".hd"
# define MS_ERROR_CODE 1
# define MS_SYNTAX_ERROR 2
# define MS_ERROR_DQUOTES 34
# define MS_ERROR_SQUOTES 35
# define MS_PERMISSION 1
# define MS_FORK_ERROR 23
# define MS_EXECVE_ERROR -1
# define MS_CMD_NOT_FOUND 127
# define MS_DIRECTORY_ERROR 127
# define MS_MISSING_DIR 1
# define MS_DUP_ERROR 1
# define MS_DIRECTORY_ON 126

/*##################################*/
/*                                  */
/*            STRUCTURES            */
/*                                  */
/*##################################*/

typedef struct s_exec
{
	int						*pid;
	int						**pipefd;
	char					**cmdtab;
	char					**envptab;
	char					*cmdpath;
	char					**path;
}							t_exec;

typedef enum s_tokens
{
	input = 1,
	here_doc,
	output,
	append,
	space,
	word,
	squote,
	dquote,
	other
}							t_tokens;

typedef struct s_nodred		t_nodred;

// nodes correspondant a chaque input ou output contenues
// dans un pipe, mod modifie input en here_doc et output en append

struct						s_nodred
{
	char					*word;
	t_nodred				*next;
	bool					mod;
};

typedef struct s_nodargs	t_nodargs;

struct						s_nodargs
{
	char					*var;
	int						index;
	t_nodargs				*next;
};

// nodes separees par chaque pipes.

typedef struct s_nodpars	t_nodpars;

struct						s_nodpars
{
	char					*cmd;
	char					*builtin;
	int						size;
	int						index;
	t_nodred				*input;
	t_nodred				*output;
	t_nodargs				*flags;
	t_nodargs				*args;
	t_nodpars				*next;
};

// structure de reference / de controle

typedef struct s_parser
{
	t_nodpars				*head;
	int						size;
}							t_parser;

typedef struct s_nodlex		t_nodlex;
typedef struct s_piplex		t_piplex;

struct						s_nodlex
{
	int						index;
	char					*word;
	t_tokens				type;
	t_nodlex				*next;
};

// grande liste separee par les pipes

struct						s_piplex
{
	int						index;
	t_nodlex				*head;
	int						size;
	t_piplex				*next;
};

// structure de reference / de controle

typedef struct s_lexer
{
	t_piplex				*head;
	int						size;
}							t_lexer;

// Liste contenant chaque variable d'environemment et ses valeurs;

typedef struct s_nodenv		t_nodenv;

struct						s_nodenv
{
	char					*name;
	char					*value;
	bool					exp;
	t_nodenv				*next;
};

// structure de reference des variables d'environnement

typedef struct s_envp
{
	t_nodenv				*head;
	int						size;
}							t_envp;

typedef struct s_main
{
	t_envp					envp;
	t_lexer					lexer;
	t_parser				parser;
	t_exec					exec;
	int						sig;
	int						status;
	int						ilex;
	int						exitcode;
	bool					activepipe;
	bool					nofork;
}							t_main;

/*##################################*/
/*                                  */
/*            FUNCTIONS             */
/*                                  */
/*##################################*/

void						ms_routine(t_main *main);

// lexer

t_nodlex					*ms_new_nodlex(t_main *main, t_nodlex *prev,
								t_piplex *current);
t_piplex					*ms_new_piplex(t_main *main, int index);
t_nodlex					*ms_space(t_main *main, char *str, t_nodlex *prev,
								t_piplex *current);
t_nodlex					*ms_string(t_main *main, char *str, t_nodlex *prev,
								t_piplex *current);
t_nodlex					*ms_onechar(t_main *main, char *str, t_nodlex *prev,
								t_piplex *current);
t_nodlex					*ms_twochar(t_main *main, char *str, t_nodlex *prev,
								t_piplex *current);
void						ms_lexer(t_main *main, char *str);
void						ms_nodefill(t_main *main, t_piplex *node,
								char *str);
int							ms_str_size(char *str);
int							ms_stop_str(char c);
void						ms_envp(t_main *main, char **envp);
void						ms_envp_tab(t_main *main);
char						*ms_envp_name(char *str, int *i);

// parsing

int							ms_parser(t_main *main);
void						ms_parsing_env(t_main *main, t_piplex *current);
int							ms_parsing_quotes(t_main *main, t_piplex *current);
void						ms_parsing_spaces(t_main *main, t_piplex *current);
int							ms_parsing_words(t_main *main, t_piplex *curlex,
								t_nodpars *curpars);
int							ms_input_set(t_main *main, t_piplex *curlex,
								t_nodpars *curpars);
int							ms_here_doc(t_main *main, t_nodlex *tmp,
								t_nodpars *curpars);
void						ms_here_doc_write(t_main *main, char *lim);
void						ms_write_to_here_doc(t_main *main, char *lim,
								int filetmp);
void						ms_build_input_node(t_main *main,
								t_nodpars *current, char *word, bool value);
void						ms_build(t_main *main, t_nodlex *current);
int							ms_output_set(t_main *main, t_piplex *curlex,
								t_nodpars *curpars);
void						ms_cmd_set(t_main *main, t_piplex *curlex,
								t_nodpars *curpars);
void						ms_args(t_main *main, t_nodlex *current,
								t_nodpars *curpars);
void						ms_parsingdquotes(t_main *main, t_piplex *current);
void						ms_parsing_var_env(t_nodlex *tmp, t_nodlex *tmp2,
								t_piplex *current);
void						ms_parsing_word_env(t_nodlex *tmp, t_main *main);
void						ms_parsing_exitcode_env(t_nodlex *tmp,
								t_main *main);
void						ms_iter_index(t_nodlex *first, t_piplex *current,
								int value);
void						ms_last_node(t_main *main, t_nodlex *previous,
								t_piplex *current);
void						ms_last_word(t_main *main, t_nodlex *ref,
								t_nodlex *current, int size);
void						ms_edit_first_word(t_main *main, t_nodlex *current,
								int size);
void						ms_destroy_node(t_nodlex *previous,
								t_nodlex *actual, t_piplex *current);
void						ms_size_words(char *str, int *sfirst, int *slast);
void						ms_new_space_nodlex(t_main *main,
								t_nodlex *previous, t_piplex *current);

// execution

void						ms_executor(t_main *main);
void						ms_builtin(t_main *main, t_nodpars *current,
								int *input, int *output);
void						ms_pip_init(t_main *main);
int							ms_check_mod(t_nodred *first);
char						**ms_cmdtab(char *cmd, t_nodpars *current,
								t_main *main);
char						*ms_cmdpath(char *path, char *cmd);
void						ms_path_init(t_main *main);
void						ms_fork(t_main *main);
void						ms_child(t_main *main, int *input,
								t_nodpars *current, int *output);
void						ms_pip_close(t_main *main);
int							ms_input(t_nodpars *current, int *input);
int							ms_output(t_nodpars *current, int *output);
void						ms_dup(t_main *main, int *input, int *output);
void						ms_no_pipe(t_main *main);
int							ms_no_pipe_frompath(t_main *main,
								t_nodpars *current);
int							ms_no_pipe_nopath(t_main *main, t_nodpars *current);
int							ms_fake_flag(char *var);
void						ms_check_dir(t_main *main, char *cmd);
int							ms_check_input(t_nodpars *current, int *input);
int							ms_check_output(t_nodpars *current, int *output);
char						*ms_cmd_on(t_main *main, char *cmd);
void						ms_waiting(t_main *main, pid_t pid);
void						ms_fork_ending(t_main *main);
void						ms_execute_no_pipe(t_main *main, int *red);
void						ms_check_access(t_main *main, int *red);
void						ms_simple_cmd(t_main *main, int *red);

// builtin

int							ms_pwd(t_nodpars *current);
int							ms_env(t_main *main, t_nodpars *current);
int							ms_echo(t_nodpars *current);
int							ms_cd(t_main *main, t_nodpars *current);
int							ms_export(t_main *main, t_nodpars *current);
int							ms_exit_b(t_main *main, t_nodpars *current);
int							ms_unset(t_main *main, t_nodpars *current);
char						*ms_env_elem(t_main *main, char *elem);
t_nodenv					*ms_check_node(t_main *main, char *var);
int							ms_special_c(char c);
int							ms_name_format(char *str);
int							ms_no_equal(char *cmd);

// signals

void						ms_signal_trap(void);
void						ms_sig_handler(int signal);
void						ms_sig_handler_fork(int signal);
void						ms_sig_handler_hd(int signal);

// error handling

int							ms_printerror(char *str, char *str1, char *str2,
								int nbreturn);
void						ms_error(t_main *main, int errorcode);
void						ms_exit(t_main *main, int exit_code);

// free functions

void						ms_here_doc_del(void);
void						ms_free_exec(t_main *main);
void						ms_free_parser(t_main *main);
void						ms_free_lexer(t_main *main);
void						ms_free_envp(t_main *main);
void						ms_exit_child(t_main *main, int exit_code);
void						ms_free_var(t_nodargs *head);

#endif
