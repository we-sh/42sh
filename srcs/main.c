#include "shell.h"

int	main(int ac, const char *av[])
{
	logger_init(D_FATAL, "out.log");
	(void)av;
	(void)ac;
	logger_close();
	return (0);
}
