/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleError.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:58:41 by krwongwa          #+#    #+#             */
/*   Updated: 2024/04/11 15:58:51 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (fd < 0 || !s)
		return ;
	write(fd, s, ft_strlen(s));
}

void    ft_puterror(char *s,int errnum,p_p *list)
{
        ft_putstr_fd(strerror(errnum), 2);
        write(2," ",1);
        ft_putstr_fd(s, 2);
        write(2,"\n",1);
        if (list)
                freelist(list);
        exit(errnum);
}