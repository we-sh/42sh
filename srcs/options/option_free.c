#include "shell.h"

void	option_free(t_option **opt)
{
	ft_memdel((void **)&(*opt)->value);
	ft_memdel((void **)&(*opt));
	*opt = NULL;
}
