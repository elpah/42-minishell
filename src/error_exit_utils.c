/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:35:30 by fmaurer           #+#    #+#             */
/*   Updated: 2024/12/27 23:37:33 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(char *msg)
{
	if (msg)
		perror(msg);
	else
		perror("Error");
	exit(EXIT_FAILURE);
}

/* Perform NULL check on pointer. error_exit with msg if NULL. */
void	nullcheck(void *p, char *msg)
{
	if (!p)
		error_exit(msg);
}

/* Print errors msg with in the format "prefix: error_msg" to stderr and return
 * 3 parameter int-value. */
int	minish_errormsg(char *prefix, char *msg, int error)
{
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", prefix, msg);
		return (error);
}
