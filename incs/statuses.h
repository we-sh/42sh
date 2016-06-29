/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statuses.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	ST_CLOSE,
	ST_READ,
	ST_FORK,
	ST_PIPE,
	ST_TTYNAME,
	ST_MALLOC,
	ST_TCSETPGRP,
	ST_TCSETATTR,
	ST_SIGCONT,
	ST_LEXER,
	ST_BUFFER,
	ST_PARSER,
	ST_PARSER_TOKEN,
	ST_EXIT,
	ST_CANCEL,
	ST_BREAK,
	ST_NOT_A_BUILTIN,
	ST_CHDIR,
	ST_ENOENT,
	ST_EINVAL,
	ST_E2BIG,
	ST_E2SMALL,
	ST_EISDIR,
	ST_ISLNK,
	ST_ELOOP,
	ST_ENOTDIR,
	ST_READLINK,
	ST_GETCWD,
	ST_NAN,
	ST_BLTIN_BG,
	ST_BLTIN_BG_ERR_ALREADYBG,
	ST_BLTIN_BG_ERR_JOBNOTFOUND,
	ST_BLTIN_CD,
	ST_BLTIN_CD_ERR_MISSINGHOME,
	ST_BLTIN_CD_ERR_MISSINGOLDPWD,
	ST_BLTIN_CD_OPT_P2,
	ST_BLTIN_EXIT,
	ST_BLTIN_HELP,
	ST_BLTIN_FG,
	ST_BLTIN_FG_ERR_JOBNOTFOUND,
	ST_BLTIN_JOBS,
	ST_BLTIN_JOBS_OPT_L,
	ST_BLTIN_JOBS_OPT_P,
	ST_BLTIN_JOBS_ERR_NOSUCHJOB,
	ST_BLTIN_ENV,
	ST_BLTIN_ENV_OPT_I,
	ST_BLTIN_LANGUAGE,
	ST_BLTIN_LANGUAGE_OK,
	ST_BLTIN_LANGUAGE_ERR_NOTFOUND,
	ST_BLTIN_TERMCAPS,
	ST_BLTIN_UNSETENV,
	ST_BLTIN_SETENV,
	ST_BLTIN_SETENV_TMANY_ARGV,
	ST_BLTIN_SETENV_ALPHA_NUM,
	ST_BLTIN_SETENV_FIRST_CHAR,
	ST_OPTION_C,
	ST_OPTION_HELP,
	ST_CMD_NOT_FOUND,
	ST_EACCES,
	ST_EXECVE,
	ST_DONE,
	ST_RUNNING,
	ST_STOPPED,
	ST_TERMINATED,
	ST_USAGE,
	ST_OPTIONS,
	ST_TERMCAPS_INIT,
	ST_TERMCAPS_FINALIZE,
	ST_UNEXPECTED_TOKEN,
	ST_SIGNAL,
	ST_SIGNAL_SIGHUP,
	ST_SIGNAL_SIGINT,
	ST_SIGNAL_SIGQUIT,
	ST_SIGNAL_SIGILL,
	ST_SIGNAL_SIGTRAP,
	ST_SIGNAL_SIGABRT,
	ST_SIGNAL_SIGEMT,
	ST_SIGNAL_SIGFPE,
	ST_SIGNAL_SIGKILL,
	ST_SIGNAL_SIGBUS,
	ST_SIGNAL_SIGSEGV,
	ST_SIGNAL_SIGSYS,
	ST_SIGNAL_SIGPIPE,
	ST_SIGNAL_SIGALRM,
	ST_SIGNAL_SIGTERM,
	ST_SIGNAL_SIGURG,
	ST_SIGNAL_SIGSTOP,
	ST_SIGNAL_SIGTSTP,
	ST_SIGNAL_SIGCONT,
	ST_SIGNAL_SIGCHLD,
	ST_SIGNAL_SIGTTIN,
	ST_SIGNAL_SIGTTOU,
	ST_SIGNAL_SIGIO,
	ST_SIGNAL_SIGXCPU,
	ST_SIGNAL_SIGFSZ,
	ST_SIGNAL_SIGVTALRM,
	ST_SIGNAL_SIGPROF,
	ST_SIGNAL_SIGWINCH,
	ST_SIGNAL_SIGINFO,
	ST_SIGNAL_SIGUSR1,
	ST_SIGNAL_SIGUSR2,
	ST_SIGNAL_TOTAL,
	ST_TOTAL
}				t_st;

#endif
