/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:35:59 by krwongwa          #+#    #+#             */
/*   Updated: 2024/04/11 01:07:13 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/resource.h>
# include <string.h>
# include <errno.h>

typedef struct p_pipe{
    int pipe[2];
    int argc;
    int *processPid;   // processId
    int status;        // for waitpid
    int infile;        // fd input file
    int count;   
}  p_p;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif


//          free.c
void freelist(p_p *list);
void free2darr(char **str);

//          ft_split.c
size_t	count(char const *s, char c);
int	    makearray(char **ptr, char const *s, char c);
char**  ft_split(char const *s, char c);


//          handleError.c
void	ft_putstr_fd(char *s, int fd);
void    ft_puterror(char *s,int errnum,p_p *list);


//          path.c
int     findslash(char *command);
int		check(char *env, char *path);
char**  findPath(char **env);
char*   cmdPath(char *command,char **path);
void    runcmd(char *command, char **env,int infile ,p_p *list);


//          pipe.c
void    parentProcess(p_p *list);
void    childProcess(char **argv, char **env, p_p *list);
int wait_all_process(p_p *list)


//          pipeUtils.c
void    init(p_p *list,int argc);
void openInFile(char **argv,p_p *list);
void openOutFile(char *argv, p_p *list);
void    pipeWrite(p_p *list);

#endif