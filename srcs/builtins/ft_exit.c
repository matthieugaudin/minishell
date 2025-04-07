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
	while (str[i])
	{
		if (!ft_isdigit(*str) && !(*str == '-' && *(str + 1)))
			return (false);
		i++;
	}
	if (is_overflow(str))
		return (false);
	return (true);
}

void	ft_exit(char **args)
{
	if (!args[0])
	{
		ft_putendl_fd("exit", 1);
		exit(exit_code(0, false));
	}
	else if (!is_numeric(args[0]))
	{
		ft_putendl_fd("exit", 1);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(2);
	}
	else if (args[1])
	{
		ft_putendl_fd("exit", 1);
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		exit_code(1, true);
	}
	else
	{
		ft_putendl_fd("exit", 1);
		exit(ft_atoi(args[0]));
	}
}
