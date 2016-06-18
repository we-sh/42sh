#ifndef LIST_HEAD_H
# define LIST_HEAD_H

# include "list.h"
# include "types.h"

# include <unistd.h>

/*
** -- List head structure --
*/
typedef struct	s_list_head
{
	t_list	list;
	size_t	size;
	size_t	offset;
}				t_list_head;

/*
** list head insert
*/
void	list_head__insert(t_list_head *head, size_t offset, t_list *new);

/*
** list head del
*/
void	list_head__del(t_list_head *head, t_list *entry);

/*
** list head init
*/
void	list_head__init(t_list_head *head);

/*
** list head slice
*/
void	list_head__slice(t_list_head *new, t_list_head *head, size_t start, size_t len);

/*
** -- Command line node structure --
*/

# include <wchar.h>

/*
** Character size max
*/
# define CHARACTER_SIZE_MAX		(size_t)sizeof (wchar_t)

typedef struct	s_list_node_cmd
{
	t_list	list;
	size_t	character_size;
	char	character[CHARACTER_SIZE_MAX];
}				t_list_node_cmd;

/*
** list node cmd_line create
*/
t_list_node_cmd	*list_node__command_line_create(const size_t character_size, const char *character);

/*
** list node command line destroy
*/
void			list_node__command_line_destroy(t_list *entry);

/*
** list head command line dup
*/
t_list_head		*list_head__command_line_dup(t_list_head *dst, t_list_head *src);

/*
** list head command line destroy
*/
void			list_head__command_line_destroy(t_list_head *head);

/*
** list head command line to buffer
*/
int				list_head__command_line_to_buffer(const t_list_head *head, const size_t buffer_size_max, size_t *buffer_size, char *buffer);

/*
** list head command line match
*/
int				list_head__command_line_match(const t_list_head *head, const t_list_head *match);

/*
** -- History node structure --
*/
typedef struct	s_list_node_history
{
	t_list		list;
	t_list_head	command_line;
}				t_list_node_history;

/*
** list node history create
*/
t_list_node_history	*list_node__history_create(t_list_head *cmd_line);

/*
** list head history destroy
*/
void			list_head__history_destroy(t_list_head *head);

#endif
