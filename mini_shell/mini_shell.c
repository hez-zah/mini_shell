/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bounus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hez-zahi <hez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 23:17:32 by hez-zahi          #+#    #+#             */
/*   Updated: 2023/03/18 01:35:43 by hez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	main(int ac, char *av[], char **env)
{
	t_shell	shell;
	int		nbr;
	int		i;

	if (ac >= 1)
	{
		nbr = 1;
		init_arg(&shell, ac, av);
		pipe_redir(&shell);
		if (check_herdoc(shell.arg))
			herdoc(&shell, ac, av, env);
		else
			redir(&shell, env);
	}
	return (0);
}
