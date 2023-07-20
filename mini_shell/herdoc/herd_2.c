#include "../mini_shell.h"

int	check_sort(t_shell *shell)
{
	t_limit *head;
	int i;

	i = 0;
	head = shell->limit;
	while (head)
	{
		i++;
		head = head->next_limit;
	}
	return (i);
}

int	check_entr(t_shell *shell, char *led, char **env)
{
	t_limit *head;

	head = shell->limit;
	while (head)
	{
		if (shell->permi == head->index_limit &&
				!ft_strncmp(head->limit, led, ft_strlen(led)))
					shell->permi += 1;
		head = head->next_limit;
	}
	return (shell->permi);
}

char	*befor_limit(t_shell *shell)
{
	t_limit *head;

	head = shell->limit;
	if (!shell->permi)
		return (head->limit);
	while (head->next_limit->next_limit)
		head = head->next_limit;
	return (head->limit);
}

void affich(t_shell *shell, char **env)
{
	char *led;
	char *aid_led;
	write(1, ">", 1);

	led = get_next_line(0);
	while (1)
	{
		shell->permi = check_entr(shell, led, env);
		if (shell->permi == check_sort(shell))
			break;
		if (shell->permi == check_sort(shell) - 1)
		{
			if (ft_strncmp(befor_limit(shell), led, ft_strlen(led)))
				write(shell->outfile, led, ft_strlen(led));
		}
		write(1, ">", 1);
		led = get_next_line(0);
	}
}

void	creat_pipe(t_shell *shell)
{
	int fd[2];

	if (pipe(fd) < 0)
		write(2, "Error\n", 6);
	shell->infile = fd[0];
	shell->outfile = fd[1];
}