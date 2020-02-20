#include "filler.h"

int		set_errno(int val)
{
	errno = val;
	return (-1);
}
