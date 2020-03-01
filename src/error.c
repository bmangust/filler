#include "filler.h"

int		set_errno(int val)
{
	errno = val;
	return (ERROR);
}
