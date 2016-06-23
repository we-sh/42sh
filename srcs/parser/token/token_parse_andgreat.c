#include "parser.h"

/*
** Operator: &>
** Type:     TT_REDIR
** Code:     TC_ANDGREAT
*/

int	token_parse_andgreat(void *target, t_parser *parser, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s '&>'", "TT_REDIR");

	int	ret;
	int	fd;

	// setup
	lexer->tokens[*i].is_redir_checked = 1;
	ret = ST_OK;

	// skip token if necessary
	if (TOKEN_CODE(*i) != TC_ANDGREAT)
		return (lexer->tokens[*i].parse(target, parser, lexer, i));

	// if jobs : just join the command
	// else, if '-' without space, close all, else, skip space, open the next TT_NONE
	if (parser->mode == F_PARSING_JOBS)
	{
		if (token_parse_utils_push_command(TOKEN_CONTENT(*i), &((t_job *)target)->command) != ST_OK)
			return (ST_MALLOC);
	}
	else if (parser->mode == F_PARSING_PROCS)
	{
		(*i)++;
		if (ft_strcmp(TOKEN_CONTENT(*i), "-") == 0)
			fd = -1;
		else
		{
			token_parse_utils_skip_separators(lexer, i, NULL);
			// FIXME from @anouvel to @jgigault : ??? (case of 'ls &> ;')
			// doesnt work because the ';' is escape
			if (TOKEN_CODE(*i) != TT_NONE)
			{
				log_error("unexpected token `%s'", TOKEN_CONTENT(*i));
				return (ST_PARSER);
			}
			ret = token_parse_utils_open_new_fd((t_proc *)target,
					TOKEN_CONTENT(*i), &fd, O_WRONLY | O_CREAT | O_APPEND);
		}
		// set the fds
		token_parse_utils_set_proc_fds(target, STDOUT_FILENO, STDERR_FILENO);
		token_parse_utils_set_proc_fds(target, STDERR_FILENO, fd);
	}
	// epilogue
	(*i)++;
	return (ST_OK);
}
