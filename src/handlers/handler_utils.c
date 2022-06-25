/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vantonie <vantonie@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 13:29:26 by vantonie          #+#    #+#             */
/*   Updated: 2022/06/25 21:02:04 by vantonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	add_token(t_ms *ms, char *token)
{
	char	*tmp;

	tmp = ms->handlers;
	ms->handlers = ft_formatf("%s%s", ms->handlers, token);
	free(tmp);
}

char	*verify_token(t_ms *ms, char *s_tmp, char a)
{
	if (*s_tmp == a)
	{
		if (*s_tmp == '|')
			add_token(ms, "o");
		else if (*s_tmp == '>')
			add_token(ms, "t");
		else if (*s_tmp == '<')
			add_token(ms, "h");
		return (s_tmp + 1);
	}
	else if (*s_tmp == '|' || *s_tmp == '>' || *s_tmp == '<' || *s_tmp == '&')
		ms->err = -2;
	if (a == '|')
		add_token(ms, "p");
	if (a == '>')
		add_token(ms, ">");
	if (a == '<')
		add_token(ms, "<");
	return (s_tmp);
}

int	verify_error(char *handlers, int len, int err)
{
	if (handlers[len - 1] != 'c' && handlers[len - 1] != 'f' && err == 0)
	{
		if (handlers[len - 1] == 'p'
			|| handlers[len - 1] == 'a' || handlers[len - 1] == 'o' )
			return (1);
		return (-2);
	}
	return (err);
}

void	verify_cmd(t_ms *ms, char *str)
{
	int	strlen;

	strlen = ft_strlen(ms->handlers);
	if (*str == 0)
		return ;
	else if (strlen > 0 && (ms->handlers[strlen - 1] == '>'
			|| ms->handlers[strlen - 1] == '<'
			|| ms->handlers[strlen - 1] == 't'))
		add_token(ms, "f");
	else
	{
		ms->cmd_number ++;
		add_token(ms, "c");
	}
}
