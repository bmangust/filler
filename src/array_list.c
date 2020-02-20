#include "array_list.h"

int		add(alist *self, int n)
{
	int *arr;
	int i;

	if (self->size < self->maxSize)
		self->array[self->size++]=n;
	else
	{
		self->maxSize *= 2;
		arr = (int*)malloc( sizeof(int) * self->maxSize);
		i = -1;
		while (++i < self->maxSize)
			arr[i] = self->array[i];
		free(self->array);
		self->array = arr;
		self->array[self->size++] = n;
	}
	return (0);
}

int		get(alist *self, int index)
{
	if (index < 0 || index > self->size)
	{
		errno = EINVAL;
		return (-1);
	}
	return (self->array[index]);
}

alist	*init_alist(void)
{
	alist *list;
	
	if (!(list = (alist*)malloc(sizeof(alist))))
		return (NULL);
	list->size = 0;
	list->maxSize = 10;
	list->array = (int*) malloc(sizeof(int) * 10);
	list->add = &add;
	list->get = &get;
	return (list);
}

void	alist_test()
{
	alist *list;

	list = init_alist();
	for (int i = 0; i < 15; i++)
		list->add(list, i);
	for (int i = 0; i < 15; i++)
		ft_printf("%d\n", list->get(list, i));

	int n = list->get(list, 20);
	if (errno != 0)
		perror("index is out of range");
	else
		ft_printf("%d\n", n);
	ft_printf("MaxSize: %d\n", list->maxSize);
}