#ifndef LIST_HEAD_H
# define LIST_HEAD_H

# include "list.h"
# include "types.h"

# include <unistd.h>

# include <wchar.h>

/*
** -- List head structure --
*/
typedef struct		s_list_head
{
	t_list	list;
	size_t	offset;
	size_t	size;
}					t_list_head;

/*
** list head insert
*/
void				list_head__insert(t_list_head *head,
						size_t offset, t_list *new);

/*
** list head del
*/
void				list_head__del(t_list_head *head, t_list *entry);

/*
** list head init
*/
void				list_head__init(t_list_head *head);

/*
** list head slice
*/
void				list_head__slice(t_list_head *new,
					t_list_head *head, size_t start, size_t len);

/*
** -- Command line node structure --
*/

/*
** Character size max
*/
# define CHARACTER_SIZE_MAX		(size_t)sizeof (wchar_t)

typedef struct		s_node_cmd
{
	t_list	list;
	size_t	character_size;
	char	character[CHARACTER_SIZE_MAX];
}					t_node_cmd;

/*
** command add
*/
int					command_add(const size_t character_size,
												const char *character,
												t_list_head *command);

/*
** command clear
*/
void				command_clear(t_list_head *command);

/*
** command clear
*/
void				command_del(t_list *entry);

/*
** list head command line dup
*/
t_list_head			*command_dup(t_list_head *dst,
								t_list_head *src);

/*
** list head command line destroy
*/
void				command_clear(t_list_head *head);

/*
** list head command line to buffer
*/
int					command_to_buffer(const t_list_head *head,
			const size_t buffer_size_max, size_t *buffer_size, char *buffer);

/*
** -- History node structure --
*/
typedef struct		s_node_history
{
	t_list		list;
	t_buffer	command;
	int			is_modified;
}					t_node_history;

/*
** add history
*/
t_node_history		*history_add(const char *str, t_list_head *history);

/*
** clear history
*/
void				history_clear(t_list_head *history);

/*
** history search
*/
int					history_search(t_list_head *history,
									const char *str,
									const size_t size,
									int direction);

/*
** history search prefix
*/
int					history_search_prefix(t_list_head *history,
											const char *str,
											const size_t size,
											int direction);

/*
** history get
*/
int					history_get(t_list_head *history, const int index,
								t_buffer *out_history_elem);

/*
** history remove
*/
void				history_remove(t_list_head *history, const int index);

/*
** history load
*/

int					history_load(char *filename, t_list_head *history, size_t *from);

/*
** history write
*/

int					history_write(t_list_head *history, char *filename, int append);

#endif
