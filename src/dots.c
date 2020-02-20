#include "filler.h"


t_dot	*init_dot(int i, int j)
{
	t_dot *dot;

	dot = (t_dot*)malloc(sizeof(t_dot));
	dot->i = i;
	dot->j = j;
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
}

t_dot	*check_dots(t_dot *dot, int i, int j)
{
	t_dot *tmp;

	tmp = dot;
	while (tmp)
	{
		if (tmp->i == i && tmp->j == j)
		{
			tmp->free_b = 0;
			tmp->free_t = 0;
			tmp->free_r = 0;
			tmp->free_l = 0;
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	get_free_space(t_map *map, int i, int j, t_piece *p)
{
	t_dot	*dot;
	int 	isNew;

	isNew = 0;
	if ((dot = check_dots(map->dots, i, j)) == NULL)
	{
		isNew = 1;
		dot = init_dot(i, j);
	}
	while (--i >= 0 && (dot->i - i) < p->width)
		dot->free_l = map->map[j][i] == '.' ? 1 : 0;
	i = dot->i;
	while (++i < map->width && (i - dot->i) < p->width)
		dot->free_r = map->map[j][i] == '.' ? 1 : 0;
	i = dot->i;
	while (--j >= 0 && (dot->j - j) < p->height)
		dot->free_t = map->map[j][i] == '.' ? 1 : 0;
	j = dot->j;
	while (++j < map->height && (j - dot->j) < p->height)
		dot->free_b = map->map[j][i] == '.' ? 1 : 0;
	if (isNew && (dot->free_l + dot->free_b + dot->free_r + dot->free_t) != 0)
		add_last_dot(&map->dots, dot);
	else if (isNew)
		delete_dot(dot);
}
