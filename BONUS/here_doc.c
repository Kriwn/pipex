/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 13:45:52 by krwongwa          #+#    #+#             */
/*   Updated: 2024/04/15 15:47:31 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	do_here_doc(char *str, t_p *list)
{
	char	*getline;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_puterror("Pipe error", errno, list);
	while (1)
	{
		write(1, "> ", 2);
		getline = get_next_line(0);
		if (getline == NULL || check(getline, str))
		{
			if (getline)
				free(getline);
			break ;
		}
		write(fd[1], getline, ft_strlen(getline));
		if (getline)
			free(getline);
	}
	list->count += 1;
	list->infile = dup(fd[0]);
	close(fd[0]);
	close(fd[1]);
	return (1);
}
