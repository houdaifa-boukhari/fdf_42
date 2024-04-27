/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:12:05 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/04/27 15:09:53 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

bool	creat_list(char *cmd, t_map **head)
{
	t_map	*cmds;
	t_map	*ptr;

	if (!cmd || !head)
		return (false);
	cmds = malloc(sizeof(t_map));
	if (!cmds)
		return (false);
	cmds->map = new_split(cmd);
	cmds->next = NULL;
	free(cmd);
	if (!*head)
	{
		*head = cmds;
		return (true);
	}
	ptr = *head;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = cmds;
	return (true);
}

void	*free_list(t_map **head)
{
	t_map	*ptr;

	ptr = *head;
	if (!head)
		return (NULL);
	while (*head)
	{
		ptr = (*head)->next;
		free_arrays((*head)->map);
		(*head)->map = NULL;
		free(*head);
		*head = ptr;
	}
	*head = NULL;
	return (NULL);
}

void	free_arrays(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	else
	{
		while (str[i])
		{
			free(str[i]);
			str[i] = NULL;
			i++;
		}
		free(str);
		str = NULL;
	}
}
