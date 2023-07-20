/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hez-zahi <hez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:10:34 by hez-zahi          #+#    #+#             */
/*   Updated: 2023/03/18 01:33:46 by hez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# define ERR_ARG "nombre d'argumet invalude"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_cmd
{
	char			*cmd;
	char			*cmd_arg;
	struct s_cmd	*next_cmd;
}t_cmd;

typedef struct s_limit
{
	char			*limit;
	int				index_limit;
	struct s_limit	*next_limit;	
}t_limit;

typedef struct s_shell
{
	char			**arg;
	t_cmd			*cmd1;
	t_limit			*limit;
	int				permi;
	int				infile;
	int				outfile;
	int				fd_red[2];
	int				fd_pipe[2];
	struct s_pip_bo	*next;
}t_shell;

char		**ft_split(char const *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s1);
size_t		ft_strlen1(const char *s);
char		*ft_concat(char const *s1, char const *s2);

char		*patht(char *cmd, char **env);
char		*ft_patht(char *cmd, char **env);
t_limit		*creat_linkdlist(t_limit	*head, char *limit, int index);
t_cmd		*creat_cmd(t_cmd	*head, char *cmd, char *arg_cmd, int index_cmd);

char		*get_next_line(int fd);
char		*ft_strjoin1(char const *s1, char const *s2);
char		*ft_strchr(const char *s, int c);
char		*copy(char *txt, char *save, int i);
char		*conc(char *stash, char *buf);

void		init_arg(t_shell *shell, int ac, char **av);
void		init_limit(t_shell *shell);
char		*last_limit(t_shell *shell);
void		child_1(char **env, t_shell *shell);
void		child_2(char **env, t_shell *shell);
void		affich(t_shell *shell, char **env);
void		creat_pipe(t_shell *shell);
void		file_redric(t_shell *shell);
void		file_red_her(t_shell *shell);

void		redir(t_shell *shell, char **env);
void		herdoc(t_shell *shell, int ac , char **av, char **env);

int			ft_check_cmd_arg(char *str);
int			check_herdoc(char **arg);
void		pipe_redir(t_shell *shell);
#endif
