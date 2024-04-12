/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:59:09 by krwongwa          #+#    #+#             */
/*   Updated: 2024/04/12 16:07:46 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int     findslash(char *command)
{
    size_t i = 0;

    while(command[i])
    {

        if (command[i] == '/')
            return (1);
        i++;
    }
    return (0);    
}

int		check(char *env, char *path)
{

		if (*env != *path)
			return (0);
		else
		{
			while(*path)
			{
				if (*path != *env)
					return (0);
				path++;
				env++;
			}
			return (1);
		}
}

char **findPath(char **env)
{
    size_t  i;
    char    **ans;
    i = 0;
    if (env == NULL)
        return (NULL);
    while(env)
    {
        if (check(*env,"PATH="))
            break;
        env++;
    }
    ans = ft_split((*env) + 5, ':');
    return (ans);
}

char *cmdPath(char *command,char **path)
{
    char *temp;
    size_t  i;

    if (!command)
        return (NULL);
    if (path == NULL)
        if (access(command, X_OK) == 0)
            return (command);
    i = 0;
    while(path != NULL && path[i])
    {
        temp = ft_strjoin(path[i], "/");
        temp = ft_strjoin(temp, command);
        if (access(temp, X_OK) == 0)
            return (temp);
        free(temp);
        i++;
    }
    return (NULL);
}

void runcmd(char *command, char **env,int infile ,p_p *list)
{
    char    **args;
    char    **path;
    char    *cmd;
    
    path = NULL;
    args = ft_split(command, ' '); // "ls -la"
    if (!findslash(command))
        path = findPath(env);
    cmd = cmdPath(args[0], path);
    dup2(infile , 0);
    close(infile);
    if (execve(cmd, args,env) == -1)
    {
        freelist(list);
        if (!args)
            free(args);
        if (!path)
            free(path);
    }
}