/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dots.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 19:45:19 by akraig            #+#    #+#             */
/*   Updated: 2020/04/18 16:25:38 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_dot	*init_dot(int i, int j, int letter)
{
	t_dot *dot;

	dot = (t_dot*)malloc(sizeof(t_dot));
	dot->i = i;
	dot->j = j;
	dot->c = letter;
	dot->heat_max = 0;
	dot->heat = 0;
	dot->free_t = 0;
	dot->free_b = 0;
	dot->free_r = 0;
	dot->free_l = 0;
	dot->next = NULL;
	dot->prev = dot;
	return (dot);
}

t_dot	*add_last_dot(t_dot **head, t_dot *new)
{
	if (head && new)
	{
		if (*head)
		{
			(*head)->prev->next = new;
			new->prev = (*head)->prev;
			(*head)->prev = new;
		}
		else
			*head = new;
		return (new);
	}
	return (NULL);
}

void	delete_dot(t_dot *dot)
{
	dot->prev->next = dot->next;
	if (dot->next)
		dot->next->prev = dot->prev;
	free(dot);
}

void	clear_dots(t_dot **head)
{
	t_dot *tmp;

	if (!head || !(*head))
		return;
	tmp = *head;
	while (tmp->next)
	{
		(*head) = tmp->next;
		(*head)->prev = NULL;
		tmp->next = NULL;
		free(tmp);
		tmp = *head;
	}
	free(tmp);
	*head = NULL;
}

t_dot	*find_dot(t_dot *head, t_dot *dot)
{
	t_dot *tmp;

	if (!head || !dot)
		return (NULL);
	tmp = head;
	while (tmp)
	{
		if (tmp->i == dot->i && tmp->j == dot->j)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
