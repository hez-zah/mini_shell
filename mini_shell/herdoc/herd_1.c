#include "../mini_shell.h"

void	init_arg(t_shell *shell, int ac, char **av)
{
	char		*led;
	char		*led_old;
	int			i;
	i = 1;
	led = ft_strdup(av[i]);
	shell->permi = 0;
	while (++i < ac)
	{
		led_old = led;
		led = ft_concat(led, av[i]);
		free(led_old);
	}
	shell->arg = ft_split(led, ' ');
}

void init_limit(t_shell *shell)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	shell->limit = NULL;
	while (shell->arg[i])
	{
		if (!ft_strncmp(shell->arg[i], "<<", 2) && shell->arg[i + 1])
		{
			shell->limit = creat_linkdlist(shell->limit, shell->arg[i + 1], j);
			j++;
		}
		i++;
	}
}

char	*last_limit(t_shell *shell)
{
	t_limit *fin;

	fin = shell->limit;
	while (fin->next_limit)
		fin = fin->next_limit;
	return(fin->limit);
}

void	child_1(char **env, t_shell *shell)
{
	pid_t pid;

	pid = fork();
	if (!pid)
	{
		if (shell->fd_red[0])
			dup2(shell->fd_red[0], 0);
		dup2(shell->outfile, 1);
		exit(0);
	}
	if (shell->fd_red[0])
		close(shell->fd_red[0]);
	close(shell->outfile);
}

void	child_2(char **env, t_shell *shell)
{
	char	**l;
	char	*cont;
	pid_t pid;

	cont = ft_concat(shell->cmd1->cmd, shell->cmd1->cmd_arg);
	l = ft_split(cont, ' ');
	pid = fork();
	if (!pid)
	{
		dup2(shell->infile, 0);
		if (shell->fd_red[1] != 1)
			dup2(shell->fd_red[1], 1);
		if (shell->cmd1->cmd && ft_patht(shell->cmd1->cmd, env))
		{
			if (execve(ft_patht(shell->cmd1->cmd, env), l, env) < 0)
				perror("error");
		}
		else
			write(2, "command not found", 17);
	}
	close(shell->infile);
	if (shell->fd_red[1])
		close(shell->fd_red[1]);
	waitpid(0, NULL, 0);
	waitpid(0, NULL, 0);
}