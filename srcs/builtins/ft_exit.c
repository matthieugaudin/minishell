#include "../../includes/builtins.h"

static bool	threshold_exceeded(char *str, long long res, int sign, int i)
{
	if (((-res == (LLONG_MIN / 10) && str[i] > '8')
			|| (-res < (LLONG_MIN / 10) && str[i]))
		|| (sign != -1 && ((res == (LLONG_MAX / 10)
					&& str[i] > '7') || (res > (LLONG_MAX / 10) && str[i]))))
		return (true);
	else
		return (false);
}

static bool	is_overflow(char *str)
{
	int			i;
	long long	res;
	int			sign;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == 32 || (9 <= str[i] && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		if (threshold_exceeded(str, res, sign, i))
			return (true);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (false);
}

static bool	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (isspace(str[i]))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !((str[i] == '+' || str[i] == '-') && isdigit(str[i + 1])))
			return (false);
		i++;
	}
	if (is_overflow(str))
		return (false);
	return (true);
}

void	ft_exit(t_data* data, char **args, int stdin, int stdout, bool to_exit)
{
	int code;

	if (stdin != -1)
	{
		close(stdin);
		close(stdout);
	}
	if (!args[0])
	{
		if (!to_exit)
			ft_putendl_fd("exit", 1);
		free_all(data);
		exit(exit_code(0, false));
	}
	else if (!is_numeric(args[0]))
	{
		if (!to_exit)
			ft_putendl_fd("exit", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putendl_fd(": numeric argument required", 2 );
		free_all(data);
		exit(2);
	}
	else if (args[1])
	{
		if (!to_exit)
			ft_putendl_fd("exit", 2);
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		if (to_exit)
		{
			free_all(data);
			exit(1);
		}
		exit_code(1, true);
	}
	else
	{
		code = ft_atoi(args[0]);
		if (!to_exit)
			ft_putendl_fd("exit", 1);
		free_all(data);
		exit(code);
	}
}

/*
exit > "./outfiles/outfile"
*/