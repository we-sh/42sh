#ifndef STATUSES_H
# define STATUSES_H

typedef enum	e_st
{
	ST_OK = 0,
	ST_END_OF_INPUT,
	ST_SETPGID,
	ST_OPEN,
	ST_READ,
	ST_FORK,
	ST_PIPE,
	ST_TTYNAME,
	ST_MALLOC,
	ST_TCSETPGRP
}				t_st;

#endif
