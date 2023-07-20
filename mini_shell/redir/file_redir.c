#include "../mini_shell.h"

int	creat_file1(char *filename, int lo_method)
{
	if (lo_method == 0)
	{
		if (access(filename, F_OK) == 0)
			return (open(filename, O_RDONLY));
		else
		{
			write(2, "zsh: No such file or directory: ", 32);
			write(2, filename, ft_strlen(filename));
			exit (1);
		}
	}
	else if (lo_method == 1)
		return (open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	else
		return (open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644));
}

void	file_red_her(t_shell *shell)
{
	int i;

	i = 0;
	while (shell->arg[++i])
	{
		if (!ft_strncmp(shell->arg[i], "<<", 2))
			continue;
		else if (!ft_strncmp(shell->arg[i], "<", 1) && shell->arg[i + 1])
			shell->infile = creat_file1(shell->arg[i + 1], 0);
		else if (!ft_strncmp(shell->arg[i], ">>", 2) && shell->arg[i + 1])
			shell->outfile = creat_file1(shell->arg[i + 1], 2);
		else if (!ft_strncmp(shell->arg[i], ">", 1) && shell->arg[i + 1])
			shell->outfile =  creat_file1(shell->arg[i + 1], 1);
	}
}

void	file_redric(t_shell *shell)
{
	int i;

	i = 0;
	while (shell->arg[++i])
	{
		if (!ft_strncmp(shell->arg[i], "<<", 2))
			continue;
		else if (!ft_strncmp(shell->arg[i], "<", 1) && shell->arg[i + 1])
			shell->fd_red[0] = creat_file1(shell->arg[i + 1], 0);
		else if (!ft_strncmp(shell->arg[i], ">>", 2) && shell->arg[i + 1])
			shell->fd_red[1] = creat_file1(shell->arg[i + 1], 2);
		else if (!ft_strncmp(shell->arg[i], ">", 1) && shell->arg[i + 1])
			shell->fd_red[1] =  creat_file1(shell->arg[i + 1], 1);
	}
}

void	herdoc(t_shell *shell, int ac , char **av, char **env)
{
	init_limit(shell);
	shell->fd_red[0] = 0;
	shell->fd_red[1] = 1;
	creat_pipe(shell);
	affich(shell, env);
	file_redric(shell);
	child_1(env, shell);
	child_2(env, shell);
}

void	pipe_redir(t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (shell->arg[i + 1])
		shell->cmd1 = creat_cmd(shell->cmd1 ,shell->arg[i], shell->arg[i + 1], j);
	else
		shell->cmd1 = creat_cmd(shell->cmd1 ,shell->arg[i], "", j);
	while (shell->arg[i])
	{
		if (!ft_strncmp(shell->arg[i], "|", 1) && shell->arg[i + 1])
		{
			if (shell->arg[i + 2])
				shell->cmd1 = creat_cmd(shell->cmd1 ,shell->arg[i + 1], shell->arg[i + 2], j);
			else
				shell->cmd1 = creat_cmd(shell->cmd1 ,shell->arg[i + 1], "", j);
			j++;
		}
		i++;
	}
}
