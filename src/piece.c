#include "filler.h"

t_piece	*init_piece()
{
	t_piece *new;

	new = (t_piece*)malloc(sizeof(t_piece));
	new->width = 0;
	new->height = 0;
	new->m_top = 0;
	new->m_bottom = 0;
	new->m_left = 0;
	new->m_right = 0;
	new->pos = 0;
	new->pos_bottom = 0;
	new->map = NULL;
	get_piece(new);
	get_pieces_params(new);
	return (new);
}

int		get_piece(t_piece *p)
{
	char	*line;
	int		lines;

	get_next_line(0, &line);
	p->width = p->width ? p->width : ft_atoi(ft_strrchr(line, ' '));
	p->height = p->height ? p->height : ft_atoi(ft_strchr(line, ' '));
	free(line);
	lines = -1;
	p->map = (char**)malloc(sizeof(char*) * p->height + 1);
	while (++lines < p->height)
	{
		if (get_next_line(0, &line) == -1)
			return set_errno(EIO);
		p->map[lines] = line;
	}
	p->map[lines] = NULL;
	return (0);
}

void	get_pieces_params(t_piece *p)
{
	int i;
	int found;
	int found_end;
	int seen_star;

	i = -1;
	seen_star = 0;
	p->m_right = p->width;
	p->m_left = p->width;
	while (++i < p->height)
	{
		found = ft_strchrn(p->map[i], '*');
		found_end = ft_strrchrn(p->map[i], '*');
		if (found == -1 && seen_star == 0)
			p->m_top++;
		else if (found != -1 && found < p->m_left)
		{
			p->m_left = found;
			seen_star = 1;
		}
		if (found_end != -1 && p->width - found_end - 1 < p->m_right)
			p->m_right = p->width - found_end - 1;
	}
	while (--i >= 0 && ft_strchrn(p->map[i], '*') == -1)
		p->m_bottom++;
}

void	delete_piece(t_piece *p)
{
	int i;

	if (!p)
		return ;
	i = -1;
	while (p->map && ++i)
		free(p->map[i]);
	free(p);
}
