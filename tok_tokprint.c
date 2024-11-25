/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_tokprint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:31:43 by fmaurer           #+#    #+#             */
/*   Updated: 2024/11/24 22:34:04 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_tokentype1(t_token *token)
{
	int	ret;

	ret = 0;
	if (token->type == TOK_CMD)
		ret = ft_printf("TOK_CMD");
	else if (token->type == TOK_ARG)
		ret = ft_printf("TOK_ARG");
	else if (token->type == TOK_PIP)
		ret = ft_printf("TOK_PIP");
	else if (token->type == TOK_ROUT)
		ret = ft_printf("TOK_ROUT");
	else if (token->type == TOK_RIN)
		ret = ft_printf("TOK_RIN");
	else if (token->type == TOK_OF)
		ret = ft_printf("TOK_OF");
	else if (token->type == TOK_IF)
		ret = ft_printf("TOK_IF");
	else if (token->type == TOK_ROUTA)
		ret = ft_printf("TOK_ROUTA");
	else if (token->type == TOK_HERE)
		ret = ft_printf("TOK_HERE");
	else if (token->type == TOK_HERE_DLIM)
		ret = ft_printf("TOK_HERE_DLIM");
	return (ret);
}

static int	print_tokentype2(t_token *token)
{
	int	ret;

	ret = 0;
	if (token->type == TOK_SQUOT)
		ret = ft_printf("TOK_SQUOT");
	else if (token->type == TOK_DQUOT)
		ret = ft_printf("TOK_DQUOT");
	else if (token->type == TOK_SQUOT_TXT)
		ret = ft_printf("TOK_SQUOT_TXT");
	else if (token->type == TOK_DQUOT_TXT)
		ret = ft_printf("TOK_DQUOT_TXT");
	else if (token->type == TOK_VAR_SYM)
		ret = ft_printf("TOK_VAR_SYM");
	else if (token->type == TOK_VAR_NAME)
		ret = ft_printf("TOK_VAR_NAME");
	else if (token->type == TOK_BLTIN)
		ret = ft_printf("TOK_BLTIN");
	else if (token->type == TOK_BLTIN_ARG)
		ret = ft_printf("TOK_BLTIN_ARG");
	else if (token->type == TOK_EOF)
		ret = ft_printf("TOK_EOF");
	else if (token->type == TOK_WORD)
		ret = ft_printf("TOK_WORD");
	return (ret);
}

void	print_tokentype(t_token *token)
{
	if (print_tokentype1(token))
		return ;
	else
		print_tokentype2(token);
}