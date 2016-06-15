#include "shell.h"

/*
** This file return pointer to tokens list defined in parser.h
** Tokens are structures with strings, codes and function pointer.
*/

t_token	*token_list(void)
{
	return (t_token *)g_tokens;
}
