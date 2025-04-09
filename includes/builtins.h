/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:33:24 by mgaudin           #+#    #+#             */
/*   Updated: 2025/04/09 18:36:07 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <linux/limits.h>
# include <limits.h>
# include "execution.h"

void	ft_exit(t_data *data, char **args, bool to_exit);
int		ft_pwd(t_data *data, bool exit);
int		ft_echo(t_data *data, char **args, bool exit);
int		value(t_data *data, int status, bool to_exit);
int		ft_env(t_data *data, t_env *env, char **args, bool exit);
int		ft_unset(t_data *data, char **args, bool exit);
int		ft_cd(t_data *data, char **args, bool exit);
int		ft_export(t_data *data, char **args, bool exit);
int		ft_cd_error_path(char *curpath);
int		ft_cd_too_many_args(void);
void	print_export_error(char *str);
bool	threshold_exceeded(char *str, long long res, int sign, int i);

#endif /* BUILTINS_H */
