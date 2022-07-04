/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:51:40 by vantonie          #+#    #+#             */
/*   Updated: 2022/07/03 21:04:43 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static void	free_command_export(char *text, char **splitted)
{
	free_ptr((void **)&text);
	free_ptr((void **)&splitted[0]);
	free_ptr((void **)&splitted[1]);
	free_ptr((void **)&splitted);
}

char	*verify_text(char *text)
{
	char	*tmp2;

	tmp2 = verify_quotes(text, 0);
	if (tmp2 == NULL)
		return (NULL);
	return (tmp2);
}

void	command_export(t_ms *ms)
{
	char	**splitted;
	char	*text;
	int		i;

	i = 1;
	while (ms->cmd[ms->cmd_now]->argv[i] != NULL)
	{
		if (ft_strchr(ms->cmd[ms->cmd_now]->argv[i], '='))
		{
			text = verify_text(ms->cmd[ms->cmd_now]->argv[i]);
			if (text == NULL)
				printf("minishell: export: close your quotes\n");
			splitted = ft_split(text, '=');
			if (ft_strchr(ms->cmd[ms->cmd_now]->argv[i], '=') == ms->cmd
				[ms->cmd_now]->argv[i] || ft_strchr(splitted[0], ' ') != NULL)
				custom_perror(ms, 1,"minishell: export: `=': not a valid identifier\n");
			else if (splitted[1] == NULL)
				set_env(splitted[0], "");
			else
				set_env(splitted[0], splitted[1]);
			free_command_export(text, splitted);
		}
		else
			custom_perror(ms, 1, " not a valid identifier");
		i++;
	}
}
