/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:56:01 by krwongwa          #+#    #+#             */
/*   Updated: 2024/04/18 17:34:21 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	freelist(t_p *list)
{
	close(list->pipe[0]);
	close(list->pipe[1]);
	if (list->infile > -1)
		close(list->infile);
	list->count = 0;
	free(list->process_pid);
	list->argc = 0;
	free(list);
}

char	**free2darr(char **str)
{
	size_t	i;
	char	*temp;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			temp = str[i];
			free(temp);
			i++;
		}
		free(str);
	}
	return (NULL);
}
