#ifndef STATUSES_H
# define STATUSES_H

/*
** This file contains all status codes for failure and state management
** Each status must have an associated translation in i18n translations
** ST_OK must be at top of the enumeration and set to 0
** ST_TOTAL must be at bottom to represent the count of statuses
*/

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
	ST_TCSETPGRP,
	ST_SIGNAL,
	ST_LEXER,
	ST_TOTAL
}				t_st;

#endif
