#include "shell.h"

void	option_free(t_option **opt)
{
	if ((*opt)->has_multiple_values == 1)
		ft_memdel_tab((void ***)&(*opt)->values);
	else
		ft_memdel((void **)&(*opt)->value);
	ft_memdel((void **)&(*opt));
	*opt = NULL;
}
