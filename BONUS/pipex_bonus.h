/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:35:59 by krwongwa          #+#    #+#             */
/*   Updated: 2024/04/15 19:51:35 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/resource.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct p_pipe
{
	int	pipe[2];
	int	argc;
	int	*process_pid;
	int	infile;
	int	count;
	int	here_doc;
}	t_p;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# define FD_MAX 1024

//          free.c
void	freelist(t_p *list);
void	free2darr(char **str);

//          ft_split.c
size_t	count(char const *s, char c);
int		makearray(char **ptr, char const *s, char c);
char	**ft_split(char const *s, char c);

//          handleError.c
void	ft_putstr_fd(char *s, int fd);
void	ft_puterror(char *s, int errnum, t_p *list);
int		ft_puterrorcmd(char *s, int errnum, t_p *list);

//          path.c
int		find_slash(char *command);
int		check(char *env, char *path);
char	**find_path(char **env);
char	*cmd_path(char *command, char **path);
void	run_cmd(char *command, char **env, int infile, t_p *list);

//          pipe.c
void	parent_process(t_p *list);
void	child_process(char **argv, char **env, t_p *list);
int		wait_all_process(t_p *list);

//          pipeUtils.c
void	init(t_p *list, int argc);
void	open_in_file(char *argv, t_p *list);
void	open_out_file(char *argv, t_p *list, int flag);
void	pipe_write(t_p *list);

//          utils.c
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

//			here_doc.c
int		do_here_doc(char *str, t_p *list);

//			get_next_line.c
char	*clearline(char **file, size_t pos);
char	*ft_readline(char *file, char *buffer, int fd);
char	*makebuff(char **file, int fd);
char	*get_next_line(int fd);

//			get_next_line_utils.c
char	*ft_linejoin(char *s1, char const *s2);
char	*ft_strdup(const char *s);
char	*ft_strrchr(const char *s, int c);
#endif
