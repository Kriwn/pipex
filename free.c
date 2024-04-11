/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:56:01 by krwongwa          #+#    #+#             */
/*   Updated: 2024/04/11 15:56:03 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void freelist(p_p *list)
{
        close(list->pipe[0]);
        close(list->pipe[1]);
        list->argc = 0;
        if (list->processPid[0])
                free(list->processPid[0]);
        if (list->processPid[1])
                free(list->processPid[1]);
        list->status = 0;
        if (list->infile > -1)
                close(list->infile)
        list->count = 0;
}

void free2darr(char **str)
{
        size_t  i;
        char    *temp;

        i = 0;
        if (str)
        {
                while(str[i])
                {
                        temp = str[i];
                        free(temp);
                        i++;
                }
                free(str);
        }        
}