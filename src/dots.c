#include "filler.h"

void	get_array_of_candidates(t_map *map)
{
	int	i[2];

	i[1] = -1;
	map->candidates = (t_dot***)malloc(sizeof(t_dot**) * map->height);
	while (++i[1] < map->height)
	{
		i[0] = -1;
		map->candidates[i[1]] = (t_dot**)malloc(sizeof(t_dot*) * map->width);
		while (++i[0] < map->width)
		{
			map->candidates[i[1]][i[0]] = init_dot(i[0], i[1]);
		}
	}
}

t_dot	*init_dot(int i, int j)
{
	t_dot *dot;

	dot = (t_dot*)malloc(sizeof(t_dot));
	dot->i = i;
	dot->j = j;
	dot->heat_max = 0;
	dot->heat = 0;
	dot->is_placeable = 0;
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

	tmp = head;
	while (tmp)
	{
		if (tmp->i == dot->i && tmp->j == dot->j)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

/*
**	searches for a point with given coordinates
**	among all points in a list (map->dots)
*/

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

int		is_connectable(t_dot *dot, t_piece *p)
{
	if ((dot->free_r + dot->free_l >= p->width - 1) &&
		(dot->free_b + dot->free_t >= p->height - 1))
		return (1);
	return (0);
}

void	print_dot_heat(t_dot d)
{
	ft_printf("%5d ", d.heat - INT16_MAX);
}

void	map_dots(t_dot *dot, void f(t_dot))
{
	t_dot *tmp;

	tmp = dot;
	while (tmp)
	{
		f(*tmp);
		tmp = tmp->next;
	}
	ft_printf("\n");
}

/*
**	deciedes whether we can connect new piece to given point
**	1. first it searches for a point with given coordinates
**	among all points in a list (map->dots)
**	2. if the dot is found, we search for free space in 4 directions
**	2a. else create new dot
**	3. check if we can attach given piece to this point
**	(only one point of a piece must be connected to placed dots)
**
*/

//void	get_free_space(t_map *map, int i, int j, t_piece *p)
//{
//	t_dot	*dot;
//	int		is_new;
//
//	is_new = 0;
//	if ((dot = check_dots(map->dots, i, j)) == NULL)
//	{
//		is_new = 1;
//		dot = init_dot(i, j);
//	}
//	while (--i >= 0 && (dot->i - i) < p->width)
//		dot->free_l += map->map[j][i] == '.' ? 1 : 0;
//	i = dot->i;
//	while (++i < map->width && (i - dot->i) < p->width)
//		dot->free_r += map->map[j][i] == '.' ? 1 : 0;
//	i = dot->i;
//	while (--j >= 0 && (dot->j - j) < p->height)
//		dot->free_t += map->map[j][i] == '.' ? 1 : 0;
//	j = dot->j;
//	while (++j < map->height && (j - dot->j) < p->height)
//		dot->free_b += map->map[j][i] == '.' ? 1 : 0;
//	if (is_new && is_connectable(dot, p))
//		add_last_dot(&map->dots, dot);
//	else if (!is_connectable(dot, p))
//		delete_dot(dot);
//}
