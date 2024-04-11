/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:01:20 by krwongwa          #+#    #+#             */
/*   Updated: 2024/04/11 16:28:55 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void parentProcess(p_p *list)
{
    if (list->infile  > -1)
        close(list->infile);
    close(list->pipe[0]);
    list->infile = dup(list->pipe[0]);
    list->count += 1;
    close(list->pipe[1]);
}

void childProcess(char **argv, char **env, p_p *list)
{
    if (list->count == 0)
        openInFile(argv[1], list);
    // need new condition to do this function 
    else if (list->count == list->argc -1)
        openOutFile(argv[list->argc -1], list);
    else
        pipeWrite(list);    
    runcmd(argv[list->count + 2], env, list->infile, list);
}

int wait_all_process(p_p *list)
{
    size_t  i;
    
    i = 0;
    while(i < list->argc - 3)
    {
        if (list->processPid[i] > -1)
            waitpid(list->processPid[i], &list->status, WUNTRACED);
        i++;
    }
    freelist(list);
    return (WEXITSTATUS(list->status));
}

int main(int argc, char **argv,char **env)
{
    p_p     *list;
    
    list = malloc(sizeof(p_p));
    if (argc != 5)
    {
        ft_puterror("Input wrong argument", 22, list);
    }
    init(list, argc);
    while(list->count < argc - 3)
    {
        if (pipe(list->pipe) == -1)
            ft_puterror("Pipe error", errno, list); 
        list->processPid[list->count] = fork();
        if (list->processPid[list->count] == -1)
            ft_puterror("Fork error", errno, list);
        if (list->processPid[list->count] == 0)
            childProcess(argv, env, list);
        else if (list->processPid[list->count] > 0)
            parentProcess(list);
    }
    return (wait_all_process(list));
}