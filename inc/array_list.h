#ifndef ARRAY_LIST_H
# define ARRAY_LIST_H
# include "ft_printf.h"
# include <errno.h>
# include <stdio.h>


typedef struct t_alist
{
	int size;
	int maxSize;
	int *array;
	
	int (*add)(struct t_alist *self, int n);
	int (*get)(struct t_alist *self, int index);
//	int (*removeLast)();
//	int (*get_index)(int n);
	
}				alist;

int				add(alist *self, int n);
alist			*init_alist(void);

#endif
