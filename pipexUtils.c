/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexUtils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:38:34 by krwongwa          #+#    #+#             */
/*   Updated: 2024/04/11 16:55:30 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void init(p_p *list,int argc)
{
    size_t  i;
    
    i = 0;
    list->pipe[0] = -1;
    list->pipe[1] = -1;
    list->argc = argc;
    list->processPid = malloc(sizeof(int) * argc - 3); // name infile outfile
    if(list->processPid == NULL)
        ft_puterror("Malloc error", errno, list);
    list->status = -1;
    list->infile = -1;    
    list->count = 0;

    while(list->processPid[i])
    {
        list->processPid[i] = -1;
        i++;
    }
}

void openInFile(char *argv,p_p *list)
{
    list->infile = open(argv, O_RDONLY);

    if (list->infile == -1)
        ft_puterror("Cannot open file", errno, list);
}

void openOutFile(char *argv, p_p *list)
{
    int fd;

    fd = open(argv, O_RDWR| O_CREAT, 0644);

    if (fd == -1)
        ft_puterror("Cannot open file", errno, list);
    dup2(fd, 1);
    close(list->pipe[0]);
    close(list->pipe[1]);
    close(fd);
}


void    pipeWrite(p_p *list)
{
        close(list->pipe[0]);
        dup2(list->pipe[1], 1);
        close(list->pipe[1]); 
}