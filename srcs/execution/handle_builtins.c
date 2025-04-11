/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:31:32 by mgaudin           #+#    #+#             */
/*   Updated: 2025/04/11 12:25:01 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static void	check_builtins(t_data *data, t_cmd *cmd,
	int stdin_tmp, int stdout_tmp)
{
	if (g_sigint_flag != 1)
	{
		if (!ft_strcmp(cmd->args[0], "export"))
			ft_export(data, &cmd->args[1], false);
		else if (!ft_strcmp(cmd->args[0], "env"))
			ft_env(data, data->env, &cmd->args[0], false);
		else if (!ft_strcmp(cmd->args[0], "cd"))
			ft_cd(data, &cmd->args[1], false);
		else if (!ft_strcmp(cmd->args[0], "pwd"))
			ft_pwd(data, false);
		else if (!ft_strcmp(cmd->args[0], "echo"))
			ft_echo(data, cmd->args, false);
		else if (!ft_strcmp(cmd->args[0], "unset"))
			ft_unset(data, cmd->args, false);
		else if (!ft_strcmp(cmd->args[0], "exit"))
		{
			if (!cmd->args[2])
			{
				close(stdin_tmp);
				close(stdout_tmp);
			}
			ft_exit(data, &cmd->args[1], false);
		}
	}
}

void	handle_builtins(t_data *data, t_cmd *cmd)
{
	int	stdin_tmp;
	int	stdout_tmp;

	stdin_tmp = s_dup(data, 0);
	stdout_tmp = s_dup(data, 1);
	open_here_doc(data, cmd);
	if (open_files(data, cmd, cmd->files, true))
	{
		redirect_fds(data, cmd);
		check_builtins(data, cmd, stdin_tmp, stdout_tmp);
	}
	s_dup2(data, stdin_tmp, 0);
	s_dup2(data, stdout_tmp, 1);
	close(stdin_tmp);
	close(stdout_tmp);
}
