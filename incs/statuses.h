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
	ST_TCSETATTR,
	ST_SIGNAL,
	ST_SIGCONT,
	ST_LEXER,
	ST_BUFFER,
	ST_EXIT,
	ST_NOT_A_BUILTIN,
	ST_CHDIR,
	ST_ENOENT,
	ST_EINVAL,
	ST_E2BIG,
	ST_E2SMALL,
	ST_NAN,
	ST_BLTIN_CD,
	ST_BLTIN_CD_OPT_P2,
	ST_BLTIN_EXIT,
	ST_BLTIN_HELP,
	ST_BLTIN_JOBS,
	ST_BLTIN_JOBS_OPT_L,
	ST_BLTIN_JOBS_OPT_P,
	ST_BLTIN_SETENV,
	ST_BLTIN_UNSETENV,
	ST_BLTIN_SETENV_TMANY_ARGV,
	ST_BLTIN_SETENV_ALPHA_NUM,
	ST_BLTIN_SETENV_FIRST_CHAR,
	ST_OPTION_C,
	ST_OPTION_HELP,
	ST_DONE,
	ST_RUNNING,
	ST_USAGE,
	ST_OPTIONS,
	ST_TOTAL
}				t_st;

#endif
