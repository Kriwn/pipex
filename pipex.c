/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:01:20 by krwongwa          #+#    #+#             */
/*   Updated: 2024/04/11 20:07:11 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void parentProcess(p_p *list)
{
    if (list->infile  > -1)
        close(list->infile);
    dprintf(2, "dup [%d] to next infile", list->pipe[0]);
    list->infile = dup(list->pipe[0]);
    dprintf(2, "dup to -> [%d]\n", list->infile);
    close(list->pipe[0]);
    list->count += 1;
    close(list->pipe[1]);
}

void childProcess(char **argv, char **env, p_p *list)
{
    dprintf(2,"argc is %d\n",list->count);
    //vv infile 
    if (list->count == 0)
        openInFile(argv[1], list);
    // should separate the work each else if

    // vvvv write pipe for olnly ac - 4
    if (list->count == list->argc - 4)
    {
        dprintf(2,"Open out file\n");
        openOutFile(argv[list->argc -1], list);
    }
    else
    {
        dprintf(2,"PipeWrite\n");
        pipeWrite(list); // first command shold run this
    }
    dprintf(2, "cmd -> %s\n", argv[list->count + 2]);
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
    if (argc < 4)
    {
        ft_puterror("Input wrong argument", 22, list);
    }
    init(list, argc);
    while(list->count < argc - 3)
    {
        if (pipe(list->pipe) == -1)
            ft_puterror("Pipe error", errno, list); 
        dprintf(2, "pipe [%d] [%d] \n", list->pipe[0], list->pipe[1]);
        list->processPid[list->count] = fork();
        if (list->processPid[list->count] == -1)
            ft_puterror("Fork error", errno, list);
        if (list->processPid[list->count] == 0)
            childProcess(argv, env, list);
        else if (list->processPid[list->count] > 0)
            parentProcess(list);
        dprintf(2, "--------------------------------\n");
    }
    return (wait_all_process(list));
}