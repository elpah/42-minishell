/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:44:43 by fmaurer           #+#    #+#             */
/*   Updated: 2024/11/21 22:22:37 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"

/* For ??? */
# include <signal.h>

/* For ???? */
# include <stdio.h>

# define PROMPT "$"

/* Define termios type for easier reference. */
typedef struct termios	t_termios;

/*********** Datatypes for tokenization. ***********/

/* The highest Token Number. Useful for iterating over Tokens, maybe?! */
# define TOKEN_MAX 18

/* Token types... are these really all? */
typedef enum e_toktype
{
	TOK_CMD			= 0,
	TOK_ARG			= 1,
	TOK_PIP			= 2,
	TOK_ROUT		= 3,
	TOK_RIN			= 4,
	TOK_OF			= 5,
	TOK_IF			= 6,
	TOK_ROUTA		= 7,
	TOK_HERE		= 8,
	TOK_HERE_DLIM	= 9,
	TOK_SQUOT		= 10,
	TOK_DQUOT		= 11,
	TOK_SQUOT_TXT	= 12,
	TOK_DQUOT_TXT	= 13,
	TOK_VAR_SYM		= 14,
	TOK_VAR_NAME	= 15,
	TOK_BLTIN		= 16,
	TOK_BLTIN_ARG	= 17,
	TOK_EOF			= 18
}	t_toktype;

/* Token structure */
typedef struct s_token
{
	t_toktype	type;
	char		*value;
}	t_token;

/* Inputstream structure */
typedef struct s_cmdline
{
	char	*input;
	int		position;
	int		length;
}	t_cmdline;

typedef struct s_tokenlist
{
	t_token				*token;
	struct s_tokenlist	*next;
}	t_tokenlist;

/*********** Datatypes for parsing. ***********/

/* Command structure for parsing. */
typedef struct s_cmdlst
{
	char			*executable;
	char			**args;
	int				arg_count;
	char			*output_file;
	char			*input_file;
	struct s_cmdlst	*next;
}	t_cmdlst;

/*********** Signal and terminal setup. ***********/

void		signal_handler(int signum);
void		signal_setup(void (*sig_handler)(int));
void		term_setup(struct termios *old_settings);

/*********** Utils ***********/

void		nullcheck(void *p, char *msg);
void		error_exit(char *msg);
int			ft_isspace(char c);

/*********** Tokenization. ***********/

t_tokenlist	*toklst_new(t_token *tok);
t_tokenlist	*toklst_last(t_tokenlist *head);
void		toklst_add_back(t_tokenlist **head, t_tokenlist *newend);
void		toklst_clear(t_tokenlist **lst);
int			toklst_size(t_tokenlist *lst);
t_tokenlist	*tokenize(char *input);
void		print_tokentype(t_token *token);

/*********** Parsing. ***********/

t_cmdlst	*new_command(char *executable);
t_cmdlst	*parse_tokenlist(t_tokenlist *toklst);
void		print_cmdlst(t_cmdlst *cmd);
t_cmdline	*init_cmdline(char *input);
t_token		*get_next_token(t_cmdline	*lexer);

t_cmdlst	*cmdlst_new(char *exec);
t_cmdlst	*cmdlst_last(t_cmdlst *head);
void		cmdlst_add_back(t_cmdlst **head, t_cmdlst *newend);
int			cmdlst_size(t_cmdlst *lst);
void		cmdlst_clear(t_cmdlst **lst);

#endif
