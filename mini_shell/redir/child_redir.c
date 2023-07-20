#include "../mini_shell.h"

// void	child_red_1(char **env, t_shell *shell)
// {
// 	pid_t	pid;
// 	char	*led;

// 	pid = fork();
// 	if (!pid)
// 	{
// 		dup2(shell->fd_red[1], 1);
// 		if (shell->infile > 0)
// 			dup2(shell->infile, 0);
// 		led = get_next_line(shell->infile);
// 		while (led)
// 		{
// 			write(shell->fd_red[1], led, ft_strlen(led));
// 			led = get_next_line(shell->infile);
// 		}
// 		exit(0);
// 	}
// 	if (shell->infile > 0)
// 		close(shell->infile);
// 	close(shell->fd_red[1]);
// }

// void	child_red_2(char **env, t_shell *shell)
// {
// 	char	**l;
// 	char	*cont;
// 	pid_t pid;

// 	cont = ft_concat(shell->cmd1->cmd, shell->cmd1->cmd_arg);
// 	l = ft_split(cont, ' ');
// 	pid = fork();
// 	if (!pid)
// 	{
// 		dup2(shell->fd_red[0], 0);
// 		if (shell->outfile != 1)
// 			dup2(shell->outfile, 1);
// 		if (shell->cmd1->cmd && ft_patht(shell->cmd1->cmd, env))
// 		{
// 			if (execve(ft_patht(shell->cmd1->cmd, env), l, env) < 0)
// 				perror("error");
// 		}
// 		else
// 			write(2, "command not found", 17);
// 	}
// 	close(shell->fd_red[0]);
// 	if (shell->outfile != 1)
// 		close(shell->outfile);
// 	waitpid(0, NULL, 0);
// 	waitpid(0, NULL, 0);
// }

void	child_red_3(char **env, t_shell *shell)
{
	char	**l;
	char	*cont;
	pid_t pid;

	cont = ft_concat(shell->cmd1->cmd, shell->cmd1->cmd_arg);
	l = ft_split(cont, ' ');
	pid = fork();
	if (!pid)
	{
		if (shell->infile > 0)
			dup2(shell->infile, 0);
		if (shell->outfile != 1)
			dup2(shell->outfile, 1);
		if (shell->cmd1->cmd && ft_patht(shell->cmd1->cmd, env))
		{
			if (execve(ft_patht(shell->cmd1->cmd, env), l, env) < 0)
				perror("error");
		}
		else
			write(2, "command not found", 17);
	}
	if (shell->outfile != 1)
		close(shell->outfile);
	if (shell->infile > 0)
		close(shell->infile);
	waitpid(0, NULL, 0);
	waitpid(0, NULL, 0);
}

void	creat_red_pipe(t_shell *shell)
{
	int fd[2];

	if (pipe(fd) < 0)
		write(2, "Error\n", 6);
	shell->fd_red[0] = fd[0];
	shell->fd_red[1] = fd[1];
}

void	redir(t_shell *shell, char **env)
{
	
	file_red_her(shell);
	creat_red_pipe(shell);
	child_red_3(env, shell);
	// child_red_1(env, shell);
	// child_red_2(env, shell);
}