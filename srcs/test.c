# include <stdio.h>
# include <linux/limits.h>
 #include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
int main(int argc, char **argv, char **envp)
{
	char **args = malloc(sizeof(char *) * 1);
	*args = NULL;
	(void)argc;
	(void)argv;
	if (execve("fdqwefhsdahf", args, envp) == -1)
	{
		perror("execve");
	}
	
	return (0);
}
