# ---------------------------------------------------------------------------- #
# PROJECT DATA
# ---------------------------------------------------------------------------- #

NAME		=	42sh

# ---------------------------------------------------------------------------- #

SRCS		=	\
				main.c							\
				parser/parser.c										\
				parser/alloc/parser_new.c							\
				parser/build/parser_build_list_unstack_lexer.c		\
				parser/build/parser_build_list_unstack_lexer_none.c	\
				parser/build/parser_build_list_unstack_lexer_job.c	\
				parser/build/parser_build_list_unstack_lexer_proc.c	\
				parser/build/parser_build_list_unstack_lexer_globing.c\
				parser/expand/expand.c								\
				parser/lexer/lexer_bufferize.c						\
				parser/lexer/lexer_token_add.c						\
				parser/lexer/lexer_tokens_alloc.c					\
				parser/lexer/lexer_tokens_realloc.c					\
				parser/lexer/lexer_buffer_dump.c					\
				parser/lexer/lexer.c								\
				parser/lexer/lexer_tokenize.c						\
				parser/lexer/lexer_token_recognizer.c				\
				parser/token/token_globing_parse_none.c				\
				parser/token/token_globing_parse_inhib.c			\
				parser/token/token_parse_none.c						\
				parser/token/token_parse_and.c						\
				parser/token/token_parse_andgreat.c					\
				parser/token/token_parse_greatand.c					\
				parser/token/token_parse_lessand.c					\
				parser/token/token_parse_semi.c						\
				parser/token/token_parse_and_if.c					\
				parser/token/token_parse_or_if.c					\
				parser/token/token_parse_pipe.c						\
				parser/token/token_parse_less.c						\
				parser/token/token_parse_great.c					\
				parser/token/token_parse_dless.c					\
				parser/token/token_parse_dgreat.c					\
				parser/token/token_parse_inhib.c					\
				parser/token/token_parse_separator.c				\
				parser/token/utils/token_parse_utils_get_full_word.c\
				parser/token/utils/token_parse_utils_get_word_and_inhib.c\
				parser/token/utils/token_parse_utils_open_new_fd.c	\
				parser/token/utils/token_parse_utils_push_command.c	\
				parser/token/utils/token_parse_utils_set_proc_fds.c	\
				parser/token/utils/token_parse_utils_skip_separators.c\
				parser/token/utils/token_parse_utils_check_char_to_fd.c	\
				parser/token/utils/token_parse_utils_gen_token_after_dash.c\
				parser/token/utils/token_parse_utils_heredoc.c		\
				parser/token/utils/token_globing_parse_utils_push_str.c\
				builtins/bg/builtin_bg.c		\
				builtins/cd/builtin_cd.c		\
				builtins/cd/builtin_cd_chk_path.c\
				builtins/cd/builtin_cd_readlink.c\
				builtins/cd/builtin_cd_rm_dotdot.c\
				builtins/echo/builtin_echo.c	\
				builtins/echo/builtin_echo_escape.c	\
				builtins/exit/builtin_exit.c	\
				builtins/fg/builtin_fg.c		\
				builtins/help/builtin_help.c	\
				builtins/jobs/builtin_jobs.c	\
				builtins/env/builtin_env.c		\
				builtins/language/builtin_language.c\
				builtins/setenv/builtin_setenv.c\
				builtins/setenv/builtin_setenv_argv_is_valid.c\
				builtins/termcaps/builtin_termcaps.c\
				builtins/unsetenv/builtin_unsetenv.c\
				builtins/builtin_callback.c		\
				builtins/builtin_usage.c		\
				env/env_get.c					\
				env/env_get_path.c				\
				env/env_get_user.c				\
				env/env_get_home.c				\
				env/env_get_term.c				\
				env/env_set.c					\
				env/env_unset.c					\
				env/env_index_value.c			\
				env/env_update_from_cmd_line.c	\
				display/display_status.c		\
				i18n/i18n_translate.c			\
				init/shell_init.c				\
				init/shell_language.c			\
				init/shell_environment.c		\
				init/shell_set_prompt.c			\
				job/job_alloc.c					\
				job/proc_alloc.c				\
				job/job_available_id.c			\
				job/job_background.c			\
				job/job_background_nth.c		\
				job/job_background_update_status.c\
				job/job_by_id.c					\
				job/job_by_name.c				\
				job/job_display_status.c		\
				job/job_foreground.c			\
				job/job_free.c					\
				job/job_is_completed.c			\
				job/job_is_signaled.c			\
				job/job_is_stopped.c			\
				job/job_kill.c					\
				job/job_launch.c				\
				job/job_list_clean.c			\
				job/job_set_stopped.c			\
				job/job_wait.c					\
				job/proc_find.c					\
				job/proc_free.c					\
				job/proc_launch.c				\
				job/proc_update_status.c		\
				job/redir_alloc.c				\
				job/redir_free.c				\
				job/redir_list_free.c			\
				loop/loop_main.c				\
				options/option_get_value.c		\
				options/option_is_set.c			\
				options/list_node__option_alloc.c\
				options/option_free.c			\
				options/option_parse.c			\
				path/path_init_hasht.c			\
				path/path_free_hasht.c			\
				path/path_get_new_cmd.c			\
				path/path_fnv_a_str.c			\
				path/path_hash_finder.c			\
				path/path_add_folder_content_to_hasht.c	\
				path/path_commande_not_found_in_hasht.c\
				quoting/quoting_new_context.c\
				signal/signal_to_default.c		\
				signal/signal_to_ignore.c		\
				signal/signal_to_pgid.c			\
				termcaps/termcaps_initialize.c		\
				termcaps/termcaps_finalize.c		\
				termcaps/termcaps_line_print.c				\
				termcaps/termcaps_line_erase.c				\
				termcaps/termcaps_read_input.c					\
				termcaps/termcaps_read_loop.c					\
				termcaps/termcaps_get_character_bytes_count.c	\
				termcaps/termcaps_string_to_command_line.c		\
				termcaps/termcaps_character_to_command_line.c	\
				termcaps/termcaps_display_command_line.c		\
				termcaps/termcaps_isunicode.c					\
				termcaps/termcaps_identify_input.c				\
				termcaps/list_head.c							\
				termcaps/list_head_command.c					\
				termcaps/list_head_history.c					\
				termcaps/key__backspace.c						\
				termcaps/key__copy.c							\
				termcaps/key__cursor_to_begin_of_line.c			\
				termcaps/key__cursor_to_end_of_line.c			\
				termcaps/key__cursor_to_next_character.c		\
				termcaps/key__cursor_to_next_command.c			\
				termcaps/key__cursor_to_next_line.c				\
				termcaps/key__cursor_to_next_word.c				\
				termcaps/key__cursor_to_prev_character.c		\
				termcaps/key__cursor_to_prev_command.c			\
				termcaps/key__cursor_to_prev_line.c				\
				termcaps/key__cursor_to_prev_word.c				\
				termcaps/key__cut.c								\
				termcaps/key__cut_to_end_of_line.c				\
				termcaps/key__delete_command_line.c				\
				termcaps/key__delete_under_cursor.c				\
				termcaps/key__paste.c							\
				termcaps/key__select.c							\
				termcaps/key__send.c							\
				termcaps/key__share__command_line_to_history.c	\
				termcaps/key__share__copy_build_copy.c			\
				termcaps/key__share__cut_build_copy.c			\
				termcaps/key__share__selection_get.c			\
				termcaps/key__share_words.c						\
				termcaps/key__completion.c						\
				termcaps/key__completion_s.c					\
				termcaps/key__completion_list_dir.c				\
				termcaps/key__ctrl_c.c							\
				termcaps/key__clear.c							\
				termcaps/key__search_history.c					\
				termcaps/termcaps_history_search.c				\
				termcaps/termcaps_write.c						\
				conf/conf_check_color_mode.c					\
				conf/conf_file_init.c							\

# ---------------------------------------------------------------------------- #
# PROJECT CONFIGURATION
# ---------------------------------------------------------------------------- #

CFLAGS		=	\
				-g 								\
				-Wall -Wextra -Werror			\

# >>> REQUIRED FOR LIBRARIES >>> THINK ABOUT CHANGING THE *LIBS rules

CPPFLAGS	=	\
				-I $(DIRINC)					\
				-I $(DIRINCCAPS)				\
				-I $(DIRINCBLTIN)				\
				-I $(DIRLIB)libft/$(DIRINC)		\
				-I $(DIRLIB)logger/$(DIRINC)	\
				-I $(DIRLIB)libcaps/$(DIRINC)	\

LDFLAGS		=	\
				-L $(DIRLIB)logger				\
				-L $(DIRLIB)libcaps				\
				-L $(DIRLIB)libft				\

LDLIBS		=	\
				-llogger						\
				-lcaps							\
				-lft							\
				-ltermcap						\

# GLOBAL SETUP
AR			=	ar
CC			=	clang
RM			=	rm
MKDIR		=	mkdir
MAKE		=	make

DIRSRC		=	./srcs/
DIROBJ		=	./.objs/
DIRINC		=	./incs/
DIRINCCAPS	=	./incs/termcaps/
DIRINCBLTIN	=	./incs/builtins/
DIRLIB		=	./libs/
DIRTST		=	./test/

# EXTRA COLOR
C_DFL		=	\033[0m
C_GRA		=	\033[30m
C_RED		=	\033[31m
C_GRE		=	\033[32m
C_YEL		=	\033[33m
C_BLUE		=	\033[34m
C_MAG		=	\033[35m
C_CYA		=	\033[36m
C_WHI		=	\033[37m

# ============================================================================ #

# ---------------------------------------------------------------------------- #
# SOURCES NORMALIZATION
# ---------------------------------------------------------------------------- #

SRC			=	$(addprefix $(DIRSRC), $(SRCS))
OBJ			=	$(addprefix $(DIROBJ), $(notdir $(SRC:.c=.o)))

# ---------------------------------------------------------------------------- #
# RULES
# ---------------------------------------------------------------------------- #

all			:	libs $(NAME)
	@printf "$(C_GRE)[ $(NAME) ] [ %-6s ]$(C_DFL) build completed\n" "$(MAKE)"

$(NAME)		:	$(DIROBJ) $(OBJ)
	@printf "$(C_GRE)[ $(NAME) ] [ %-6s ]$(C_DFL) linking objects\n" "$(CC)"
	@$(CC) $(OBJ) -o $(NAME) $(LDFLAGS) $(LDLIBS)

# ---------------------------------------------------------------------------- #
# CUSTOMISABLE RULES

libs		:
	@make -C $(DIRLIB)libft
	@make -C $(DIRLIB)logger
	@make -C $(DIRLIB)libcaps

fcleanlibs	:
	@make -C $(DIRLIB)libft fclean
	@make -C $(DIRLIB)logger fclean
	@make -C $(DIRLIB)libcaps fclean

test		:	re
	@cd $(DIRTST) && sh 42ShellTester.sh $$PWD/../$(NAME) --hard

submodule	:
	@git submodule init && git submodule update
	@git submodule foreach git pull --rebase origin master

norme		:
	@/usr/bin/norminette -R CheckTopCommentHeader	\
		$$(find * -name "*.[ch]" ! -path "libs/logger/*" ! -path "test/*")

# ---------------------------------------------------------------------------- #

clean		:
	@printf "$(C_GRE)[ $(NAME) ] [ %-6s ]$(C_DFL) remove objects\n" "$(RM)"
	@$(RM) -rf $(DIROBJ)

fclean		:	clean
	@printf "$(C_GRE)[ $(NAME) ] [ %-6s ]$(C_DFL) remove binaries\n" "$(RM)"
	@$(RM) -f $(NAME)

re			:	fclean all

$(DIROBJ)	:
	@$(MKDIR) -p $(DIROBJ)

depend		:
	@sed -e '/^#start/,/^end/d' Makefile > .mftmp && mv .mftmp Makefile
	@printf "#start\n\n" >> Makefile
	@$(foreach s, $(SRC),													\
		printf '$$(DIROBJ)'										>> Makefile	&& \
		printf "$(shell $(CC) -MM $(s) $(CPPFLAGS) | tr '\\' ' ')\n"	>> Makefile	&& \
																			\
		printf '\t\t@printf "$$(C_GRE)[ $(NAME) ] '				>> Makefile && \
		printf '[ %%-6s ]$$(C_DFL) " "$(CC)"\n'					>> Makefile && \
		printf '\t\t@printf "compiling $(s)\\n"\n'				>> Makefile	&& \
																			\
		printf '\t\t@$$(CC) -c $(s) -o '						>> Makefile	&& \
		printf '$(addprefix $(DIROBJ), $(notdir $(s:.c=.o))) '	>> Makefile	&& \
		printf '$$(CPPFLAGS) $$(CFLAGS) \n\n'					>> Makefile	&& \
																			\
		printf "$(C_GRE)[ $(NAME) ] [ %-6s ]$(C_DFL) " "dep"				&& \
		printf "$(s) rule generated\n"										|| \
																			\
		(sed -e '/^#start/,$$d' Makefile > .mftmp && mv .mftmp Makefile		&& \
		printf "#start\n\n"										>> Makefile	&& \
		printf "$(C_RED)[ $(NAME) ] [ %-6s ]$(C_DFL) " "dep"				&& \
		printf "$(s) rule generation failed\n"								) \
	;)
	@printf "\n#end\n" >> Makefile

.PHONY	:	 libs test


# ---------------------------------------------------------------------------- #
# AUTO-GENERATED SECTION - do not modify
# ---------------------------------------------------------------------------- #

#start

$(DIROBJ)main.o: srcs/main.c incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/statuses.h incs/htabl.h incs/fnv.h incs/fnvhead32.h     incs/termcaps/termcaps.h incs/termcaps/log.h incs/termcaps/key.h     incs/redirection.h libs/libft/./incs/libft.h     libs/libft/./incs/libftprintf.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/job.h     libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/main.c\n"
		@$(CC) -c ./srcs/main.c -o ./.objs/main.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)parser.o: srcs/parser/parser.c incs/parser.h libs/libft/./incs/libft.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/statuses.h incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/htabl.h incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libftprintf.h incs/job.h libs/libcaps/./incs/caps.h     incs/i18n.h libs/libft/./incs/get_next_line.h incs/builtins/builtin.h     incs/quoting.h incs/parser_struct.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/parser.c\n"
		@$(CC) -c ./srcs/parser/parser.c -o ./.objs/parser.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)parser_new.o: srcs/parser/alloc/parser_new.c incs/parser.h     libs/libft/./incs/libft.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/statuses.h incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/htabl.h incs/fnv.h     incs/fnvhead32.h incs/termcaps/termcaps.h incs/termcaps/log.h     incs/termcaps/key.h incs/redirection.h libs/libft/./incs/libftprintf.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/builtins/builtin.h     incs/quoting.h incs/parser_struct.h incs/parser_tokens.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/alloc/parser_new.c\n"
		@$(CC) -c ./srcs/parser/alloc/parser_new.c -o ./.objs/parser_new.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)parser_build_list_unstack_lexer.o:     srcs/parser/build/parser_build_list_unstack_lexer.c incs/parser.h     libs/libft/./incs/libft.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/statuses.h incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/htabl.h incs/fnv.h     incs/fnvhead32.h incs/termcaps/termcaps.h incs/termcaps/log.h     incs/termcaps/key.h incs/redirection.h libs/libft/./incs/libftprintf.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/builtins/builtin.h     incs/quoting.h incs/parser_struct.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/build/parser_build_list_unstack_lexer.c\n"
		@$(CC) -c ./srcs/parser/build/parser_build_list_unstack_lexer.c -o ./.objs/parser_build_list_unstack_lexer.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)parser_build_list_unstack_lexer_none.o:     srcs/parser/build/parser_build_list_unstack_lexer_none.c incs/parser.h     libs/libft/./incs/libft.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/statuses.h incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/htabl.h incs/fnv.h     incs/fnvhead32.h incs/termcaps/termcaps.h incs/termcaps/log.h     incs/termcaps/key.h incs/redirection.h libs/libft/./incs/libftprintf.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/builtins/builtin.h     incs/quoting.h incs/parser_struct.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/build/parser_build_list_unstack_lexer_none.c\n"
		@$(CC) -c ./srcs/parser/build/parser_build_list_unstack_lexer_none.c -o ./.objs/parser_build_list_unstack_lexer_none.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)parser_build_list_unstack_lexer_job.o:     srcs/parser/build/parser_build_list_unstack_lexer_job.c incs/parser.h     libs/libft/./incs/libft.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/statuses.h incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/htabl.h incs/fnv.h     incs/fnvhead32.h incs/termcaps/termcaps.h incs/termcaps/log.h     incs/termcaps/key.h incs/redirection.h libs/libft/./incs/libftprintf.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/builtins/builtin.h     incs/quoting.h incs/parser_struct.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/build/parser_build_list_unstack_lexer_job.c\n"
		@$(CC) -c ./srcs/parser/build/parser_build_list_unstack_lexer_job.c -o ./.objs/parser_build_list_unstack_lexer_job.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)parser_build_list_unstack_lexer_proc.o:     srcs/parser/build/parser_build_list_unstack_lexer_proc.c incs/parser.h     libs/libft/./incs/libft.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/statuses.h incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/htabl.h incs/fnv.h     incs/fnvhead32.h incs/termcaps/termcaps.h incs/termcaps/log.h     incs/termcaps/key.h incs/redirection.h libs/libft/./incs/libftprintf.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/builtins/builtin.h     incs/quoting.h incs/parser_struct.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/build/parser_build_list_unstack_lexer_proc.c\n"
		@$(CC) -c ./srcs/parser/build/parser_build_list_unstack_lexer_proc.c -o ./.objs/parser_build_list_unstack_lexer_proc.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)parser_build_list_unstack_lexer_globing.o:     srcs/parser/build/parser_build_list_unstack_lexer_globing.c     incs/parser.h libs/libft/./incs/libft.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/statuses.h incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/htabl.h incs/fnv.h     incs/fnvhead32.h incs/termcaps/termcaps.h incs/termcaps/log.h     incs/termcaps/key.h incs/redirection.h libs/libft/./incs/libftprintf.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/builtins/builtin.h     incs/quoting.h incs/parser_struct.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/build/parser_build_list_unstack_lexer_globing.c\n"
		@$(CC) -c ./srcs/parser/build/parser_build_list_unstack_lexer_globing.c -o ./.objs/parser_build_list_unstack_lexer_globing.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)expand.o: srcs/parser/expand/expand.c incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/statuses.h incs/htabl.h incs/fnv.h incs/fnvhead32.h     incs/termcaps/termcaps.h incs/termcaps/log.h incs/termcaps/key.h     incs/redirection.h libs/libft/./incs/libft.h     libs/libft/./incs/libftprintf.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/job.h     libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/expand/expand.c\n"
		@$(CC) -c ./srcs/parser/expand/expand.c -o ./.objs/expand.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)lexer_bufferize.o: srcs/parser/lexer/lexer_bufferize.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/lexer/lexer_bufferize.c\n"
		@$(CC) -c ./srcs/parser/lexer/lexer_bufferize.c -o ./.objs/lexer_bufferize.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)lexer_token_add.o: srcs/parser/lexer/lexer_token_add.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/lexer/lexer_token_add.c\n"
		@$(CC) -c ./srcs/parser/lexer/lexer_token_add.c -o ./.objs/lexer_token_add.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)lexer_tokens_alloc.o: srcs/parser/lexer/lexer_tokens_alloc.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/lexer/lexer_tokens_alloc.c\n"
		@$(CC) -c ./srcs/parser/lexer/lexer_tokens_alloc.c -o ./.objs/lexer_tokens_alloc.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)lexer_tokens_realloc.o: srcs/parser/lexer/lexer_tokens_realloc.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/lexer/lexer_tokens_realloc.c\n"
		@$(CC) -c ./srcs/parser/lexer/lexer_tokens_realloc.c -o ./.objs/lexer_tokens_realloc.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)lexer_buffer_dump.o: srcs/parser/lexer/lexer_buffer_dump.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/lexer/lexer_buffer_dump.c\n"
		@$(CC) -c ./srcs/parser/lexer/lexer_buffer_dump.c -o ./.objs/lexer_buffer_dump.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)lexer.o: srcs/parser/lexer/lexer.c incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/statuses.h incs/htabl.h incs/fnv.h incs/fnvhead32.h     incs/termcaps/termcaps.h incs/termcaps/log.h incs/termcaps/key.h     incs/redirection.h libs/libft/./incs/libft.h     libs/libft/./incs/libftprintf.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/job.h     libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/lexer/lexer.c\n"
		@$(CC) -c ./srcs/parser/lexer/lexer.c -o ./.objs/lexer.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)lexer_tokenize.o: srcs/parser/lexer/lexer_tokenize.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/lexer/lexer_tokenize.c\n"
		@$(CC) -c ./srcs/parser/lexer/lexer_tokenize.c -o ./.objs/lexer_tokenize.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)lexer_token_recognizer.o: srcs/parser/lexer/lexer_token_recognizer.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/lexer/lexer_token_recognizer.c\n"
		@$(CC) -c ./srcs/parser/lexer/lexer_token_recognizer.c -o ./.objs/lexer_token_recognizer.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)token_globing_parse_none.o: srcs/parser/token/token_globing_parse_none.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/token/token_globing_parse_none.c\n"
		@$(CC) -c ./srcs/parser/token/token_globing_parse_none.c -o ./.objs/token_globing_parse_none.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)token_globing_parse_inhib.o:     srcs/parser/token/token_globing_parse_inhib.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/token/token_globing_parse_inhib.c\n"
		@$(CC) -c ./srcs/parser/token/token_globing_parse_inhib.c -o ./.objs/token_globing_parse_inhib.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)token_parse_none.o: srcs/parser/token/token_parse_none.c incs/parser.h     libs/libft/./incs/libft.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/statuses.h incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/htabl.h incs/fnv.h     incs/fnvhead32.h incs/termcaps/termcaps.h incs/termcaps/log.h     incs/termcaps/key.h incs/redirection.h libs/libft/./incs/libftprintf.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/builtins/builtin.h     incs/quoting.h incs/parser_struct.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/token/token_parse_none.c\n"
		@$(CC) -c ./srcs/parser/token/token_parse_none.c -o ./.objs/token_parse_none.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)token_parse_and.o: srcs/parser/token/token_parse_and.c incs/parser.h     libs/libft/./incs/libft.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/statuses.h incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/htabl.h incs/fnv.h     incs/fnvhead32.h incs/termcaps/termcaps.h incs/termcaps/log.h     incs/termcaps/key.h incs/redirection.h libs/libft/./incs/libftprintf.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/builtins/builtin.h     incs/quoting.h incs/parser_struct.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/token/token_parse_and.c\n"
		@$(CC) -c ./srcs/parser/token/token_parse_and.c -o ./.objs/token_parse_and.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)token_parse_andgreat.o: srcs/parser/token/token_parse_andgreat.c     incs/parser.h libs/libft/./incs/libft.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/statuses.h incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/htabl.h incs/fnv.h     incs/fnvhead32.h incs/termcaps/termcaps.h incs/termcaps/log.h     incs/termcaps/key.h incs/redirection.h libs/libft/./incs/libftprintf.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/builtins/builtin.h     incs/quoting.h incs/parser_struct.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/token/token_parse_andgreat.c\n"
		@$(CC) -c ./srcs/parser/token/token_parse_andgreat.c -o ./.objs/token_parse_andgreat.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)token_parse_greatand.o: srcs/parser/token/token_parse_greatand.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/token/token_parse_greatand.c\n"
		@$(CC) -c ./srcs/parser/token/token_parse_greatand.c -o ./.objs/token_parse_greatand.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)token_parse_lessand.o: srcs/parser/token/token_parse_lessand.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/token/token_parse_lessand.c\n"
		@$(CC) -c ./srcs/parser/token/token_parse_lessand.c -o ./.objs/token_parse_lessand.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)token_parse_semi.o: srcs/parser/token/token_parse_semi.c incs/parser.h     libs/libft/./incs/libft.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/statuses.h incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/htabl.h incs/fnv.h     incs/fnvhead32.h incs/termcaps/termcaps.h incs/termcaps/log.h     incs/termcaps/key.h incs/redirection.h libs/libft/./incs/libftprintf.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/builtins/builtin.h     incs/quoting.h incs/parser_struct.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/token/token_parse_semi.c\n"
		@$(CC) -c ./srcs/parser/token/token_parse_semi.c -o ./.objs/token_parse_semi.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)token_parse_and_if.o: srcs/parser/token/token_parse_and_if.c     incs/parser.h libs/libft/./incs/libft.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/statuses.h incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/htabl.h incs/fnv.h     incs/fnvhead32.h incs/termcaps/termcaps.h incs/termcaps/log.h     incs/termcaps/key.h incs/redirection.h libs/libft/./incs/libftprintf.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/builtins/builtin.h     incs/quoting.h incs/parser_struct.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/token/token_parse_and_if.c\n"
		@$(CC) -c ./srcs/parser/token/token_parse_and_if.c -o ./.objs/token_parse_and_if.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)token_parse_or_if.o: srcs/parser/token/token_parse_or_if.c incs/parser.h     libs/libft/./incs/libft.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/statuses.h incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/htabl.h incs/fnv.h     incs/fnvhead32.h incs/termcaps/termcaps.h incs/termcaps/log.h     incs/termcaps/key.h incs/redirection.h libs/libft/./incs/libftprintf.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/builtins/builtin.h     incs/quoting.h incs/parser_struct.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/token/token_parse_or_if.c\n"
		@$(CC) -c ./srcs/parser/token/token_parse_or_if.c -o ./.objs/token_parse_or_if.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)token_parse_pipe.o: srcs/parser/token/token_parse_pipe.c incs/parser.h     libs/libft/./incs/libft.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/statuses.h incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/htabl.h incs/fnv.h     incs/fnvhead32.h incs/termcaps/termcaps.h incs/termcaps/log.h     incs/termcaps/key.h incs/redirection.h libs/libft/./incs/libftprintf.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/builtins/builtin.h     incs/quoting.h incs/parser_struct.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/token/token_parse_pipe.c\n"
		@$(CC) -c ./srcs/parser/token/token_parse_pipe.c -o ./.objs/token_parse_pipe.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)token_parse_less.o: srcs/parser/token/token_parse_less.c incs/parser.h     libs/libft/./incs/libft.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/statuses.h incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/htabl.h incs/fnv.h     incs/fnvhead32.h incs/termcaps/termcaps.h incs/termcaps/log.h     incs/termcaps/key.h incs/redirection.h libs/libft/./incs/libftprintf.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/builtins/builtin.h     incs/quoting.h incs/parser_struct.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/token/token_parse_less.c\n"
		@$(CC) -c ./srcs/parser/token/token_parse_less.c -o ./.objs/token_parse_less.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)token_parse_great.o: srcs/parser/token/token_parse_great.c incs/parser.h     libs/libft/./incs/libft.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/statuses.h incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/htabl.h incs/fnv.h     incs/fnvhead32.h incs/termcaps/termcaps.h incs/termcaps/log.h     incs/termcaps/key.h incs/redirection.h libs/libft/./incs/libftprintf.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/builtins/builtin.h     incs/quoting.h incs/parser_struct.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/token/token_parse_great.c\n"
		@$(CC) -c ./srcs/parser/token/token_parse_great.c -o ./.objs/token_parse_great.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)token_parse_dless.o: srcs/parser/token/token_parse_dless.c incs/parser.h     libs/libft/./incs/libft.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/statuses.h incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/htabl.h incs/fnv.h     incs/fnvhead32.h incs/termcaps/termcaps.h incs/termcaps/log.h     incs/termcaps/key.h incs/redirection.h libs/libft/./incs/libftprintf.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/builtins/builtin.h     incs/quoting.h incs/parser_struct.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/token/token_parse_dless.c\n"
		@$(CC) -c ./srcs/parser/token/token_parse_dless.c -o ./.objs/token_parse_dless.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)token_parse_dgreat.o: srcs/parser/token/token_parse_dgreat.c     incs/parser.h libs/libft/./incs/libft.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/statuses.h incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/htabl.h incs/fnv.h     incs/fnvhead32.h incs/termcaps/termcaps.h incs/termcaps/log.h     incs/termcaps/key.h incs/redirection.h libs/libft/./incs/libftprintf.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/builtins/builtin.h     incs/quoting.h incs/parser_struct.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/token/token_parse_dgreat.c\n"
		@$(CC) -c ./srcs/parser/token/token_parse_dgreat.c -o ./.objs/token_parse_dgreat.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)token_parse_inhib.o: srcs/parser/token/token_parse_inhib.c incs/parser.h     libs/libft/./incs/libft.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/statuses.h incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/htabl.h incs/fnv.h     incs/fnvhead32.h incs/termcaps/termcaps.h incs/termcaps/log.h     incs/termcaps/key.h incs/redirection.h libs/libft/./incs/libftprintf.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/builtins/builtin.h     incs/quoting.h incs/parser_struct.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/token/token_parse_inhib.c\n"
		@$(CC) -c ./srcs/parser/token/token_parse_inhib.c -o ./.objs/token_parse_inhib.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)token_parse_separator.o: srcs/parser/token/token_parse_separator.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/token/token_parse_separator.c\n"
		@$(CC) -c ./srcs/parser/token/token_parse_separator.c -o ./.objs/token_parse_separator.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)token_parse_utils_get_full_word.o:     srcs/parser/token/utils/token_parse_utils_get_full_word.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/token/utils/token_parse_utils_get_full_word.c\n"
		@$(CC) -c ./srcs/parser/token/utils/token_parse_utils_get_full_word.c -o ./.objs/token_parse_utils_get_full_word.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)token_parse_utils_get_word_and_inhib.o:     srcs/parser/token/utils/token_parse_utils_get_word_and_inhib.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/token/utils/token_parse_utils_get_word_and_inhib.c\n"
		@$(CC) -c ./srcs/parser/token/utils/token_parse_utils_get_word_and_inhib.c -o ./.objs/token_parse_utils_get_word_and_inhib.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)token_parse_utils_open_new_fd.o:     srcs/parser/token/utils/token_parse_utils_open_new_fd.c incs/parser.h     libs/libft/./incs/libft.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/statuses.h incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/htabl.h incs/fnv.h     incs/fnvhead32.h incs/termcaps/termcaps.h incs/termcaps/log.h     incs/termcaps/key.h incs/redirection.h libs/libft/./incs/libftprintf.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/builtins/builtin.h     incs/quoting.h incs/parser_struct.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/token/utils/token_parse_utils_open_new_fd.c\n"
		@$(CC) -c ./srcs/parser/token/utils/token_parse_utils_open_new_fd.c -o ./.objs/token_parse_utils_open_new_fd.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)token_parse_utils_push_command.o:     srcs/parser/token/utils/token_parse_utils_push_command.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/token/utils/token_parse_utils_push_command.c\n"
		@$(CC) -c ./srcs/parser/token/utils/token_parse_utils_push_command.c -o ./.objs/token_parse_utils_push_command.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)token_parse_utils_set_proc_fds.o:     srcs/parser/token/utils/token_parse_utils_set_proc_fds.c incs/parser.h     libs/libft/./incs/libft.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/statuses.h incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/htabl.h incs/fnv.h     incs/fnvhead32.h incs/termcaps/termcaps.h incs/termcaps/log.h     incs/termcaps/key.h incs/redirection.h libs/libft/./incs/libftprintf.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/builtins/builtin.h     incs/quoting.h incs/parser_struct.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/token/utils/token_parse_utils_set_proc_fds.c\n"
		@$(CC) -c ./srcs/parser/token/utils/token_parse_utils_set_proc_fds.c -o ./.objs/token_parse_utils_set_proc_fds.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)token_parse_utils_skip_separators.o:     srcs/parser/token/utils/token_parse_utils_skip_separators.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/token/utils/token_parse_utils_skip_separators.c\n"
		@$(CC) -c ./srcs/parser/token/utils/token_parse_utils_skip_separators.c -o ./.objs/token_parse_utils_skip_separators.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)token_parse_utils_check_char_to_fd.o:     srcs/parser/token/utils/token_parse_utils_check_char_to_fd.c     incs/parser.h libs/libft/./incs/libft.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/statuses.h incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/htabl.h incs/fnv.h     incs/fnvhead32.h incs/termcaps/termcaps.h incs/termcaps/log.h     incs/termcaps/key.h incs/redirection.h libs/libft/./incs/libftprintf.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/builtins/builtin.h     incs/quoting.h incs/parser_struct.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/token/utils/token_parse_utils_check_char_to_fd.c\n"
		@$(CC) -c ./srcs/parser/token/utils/token_parse_utils_check_char_to_fd.c -o ./.objs/token_parse_utils_check_char_to_fd.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)token_parse_utils_gen_token_after_dash.o:     srcs/parser/token/utils/token_parse_utils_gen_token_after_dash.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/token/utils/token_parse_utils_gen_token_after_dash.c\n"
		@$(CC) -c ./srcs/parser/token/utils/token_parse_utils_gen_token_after_dash.c -o ./.objs/token_parse_utils_gen_token_after_dash.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)token_parse_utils_heredoc.o:     srcs/parser/token/utils/token_parse_utils_heredoc.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/token/utils/token_parse_utils_heredoc.c\n"
		@$(CC) -c ./srcs/parser/token/utils/token_parse_utils_heredoc.c -o ./.objs/token_parse_utils_heredoc.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)token_globing_parse_utils_push_str.o:     srcs/parser/token/utils/token_globing_parse_utils_push_str.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parser/token/utils/token_globing_parse_utils_push_str.c\n"
		@$(CC) -c ./srcs/parser/token/utils/token_globing_parse_utils_push_str.c -o ./.objs/token_globing_parse_utils_push_str.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)builtin_bg.o: srcs/builtins/bg/builtin_bg.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/builtins/bg/builtin_bg.c\n"
		@$(CC) -c ./srcs/builtins/bg/builtin_bg.c -o ./.objs/builtin_bg.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)builtin_cd.o: srcs/builtins/cd/builtin_cd.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h incs/builtins/builtin_cd.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/builtins/cd/builtin_cd.c\n"
		@$(CC) -c ./srcs/builtins/cd/builtin_cd.c -o ./.objs/builtin_cd.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)builtin_cd_chk_path.o: srcs/builtins/cd/builtin_cd_chk_path.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h incs/builtins/builtin_cd.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/builtins/cd/builtin_cd_chk_path.c\n"
		@$(CC) -c ./srcs/builtins/cd/builtin_cd_chk_path.c -o ./.objs/builtin_cd_chk_path.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)builtin_cd_readlink.o: srcs/builtins/cd/builtin_cd_readlink.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/builtins/cd/builtin_cd_readlink.c\n"
		@$(CC) -c ./srcs/builtins/cd/builtin_cd_readlink.c -o ./.objs/builtin_cd_readlink.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)builtin_cd_rm_dotdot.o: srcs/builtins/cd/builtin_cd_rm_dotdot.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h incs/builtins/builtin_cd.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/builtins/cd/builtin_cd_rm_dotdot.c\n"
		@$(CC) -c ./srcs/builtins/cd/builtin_cd_rm_dotdot.c -o ./.objs/builtin_cd_rm_dotdot.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)builtin_echo.o: srcs/builtins/echo/builtin_echo.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h incs/builtins/builtin_echo.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/builtins/echo/builtin_echo.c\n"
		@$(CC) -c ./srcs/builtins/echo/builtin_echo.c -o ./.objs/builtin_echo.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)builtin_echo_escape.o: srcs/builtins/echo/builtin_echo_escape.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/builtins/echo/builtin_echo_escape.c\n"
		@$(CC) -c ./srcs/builtins/echo/builtin_echo_escape.c -o ./.objs/builtin_echo_escape.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)builtin_exit.o: srcs/builtins/exit/builtin_exit.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/builtins/exit/builtin_exit.c\n"
		@$(CC) -c ./srcs/builtins/exit/builtin_exit.c -o ./.objs/builtin_exit.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)builtin_fg.o: srcs/builtins/fg/builtin_fg.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/builtins/fg/builtin_fg.c\n"
		@$(CC) -c ./srcs/builtins/fg/builtin_fg.c -o ./.objs/builtin_fg.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)builtin_help.o: srcs/builtins/help/builtin_help.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h incs/builtins/builtin_struct.h     incs/builtins/builtin_bg.h incs/builtins/builtin_cd.h     incs/builtins/builtin_echo.h incs/builtins/builtin_exit.h     incs/builtins/builtin_fg.h incs/builtins/builtin_help.h     incs/builtins/builtin_jobs.h incs/builtins/builtin_env.h     incs/builtins/builtin_language.h incs/builtins/builtin_setenv.h     incs/builtins/builtin_termcaps.h incs/builtins/builtin_unsetenv.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/builtins/help/builtin_help.c\n"
		@$(CC) -c ./srcs/builtins/help/builtin_help.c -o ./.objs/builtin_help.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)builtin_jobs.o: srcs/builtins/jobs/builtin_jobs.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/builtins/jobs/builtin_jobs.c\n"
		@$(CC) -c ./srcs/builtins/jobs/builtin_jobs.c -o ./.objs/builtin_jobs.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)builtin_env.o: srcs/builtins/env/builtin_env.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/builtins/env/builtin_env.c\n"
		@$(CC) -c ./srcs/builtins/env/builtin_env.c -o ./.objs/builtin_env.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)builtin_language.o: srcs/builtins/language/builtin_language.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/builtins/language/builtin_language.c\n"
		@$(CC) -c ./srcs/builtins/language/builtin_language.c -o ./.objs/builtin_language.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)builtin_setenv.o: srcs/builtins/setenv/builtin_setenv.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/builtins/setenv/builtin_setenv.c\n"
		@$(CC) -c ./srcs/builtins/setenv/builtin_setenv.c -o ./.objs/builtin_setenv.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)builtin_setenv_argv_is_valid.o:     srcs/builtins/setenv/builtin_setenv_argv_is_valid.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/builtins/setenv/builtin_setenv_argv_is_valid.c\n"
		@$(CC) -c ./srcs/builtins/setenv/builtin_setenv_argv_is_valid.c -o ./.objs/builtin_setenv_argv_is_valid.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)builtin_termcaps.o: srcs/builtins/termcaps/builtin_termcaps.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/builtins/termcaps/builtin_termcaps.c\n"
		@$(CC) -c ./srcs/builtins/termcaps/builtin_termcaps.c -o ./.objs/builtin_termcaps.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)builtin_unsetenv.o: srcs/builtins/unsetenv/builtin_unsetenv.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/builtins/unsetenv/builtin_unsetenv.c\n"
		@$(CC) -c ./srcs/builtins/unsetenv/builtin_unsetenv.c -o ./.objs/builtin_unsetenv.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)builtin_callback.o: srcs/builtins/builtin_callback.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h incs/builtins/builtin_struct.h     incs/builtins/builtin_bg.h incs/builtins/builtin_cd.h     incs/builtins/builtin_echo.h incs/builtins/builtin_exit.h     incs/builtins/builtin_fg.h incs/builtins/builtin_help.h     incs/builtins/builtin_jobs.h incs/builtins/builtin_env.h     incs/builtins/builtin_language.h incs/builtins/builtin_setenv.h     incs/builtins/builtin_termcaps.h incs/builtins/builtin_unsetenv.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/builtins/builtin_callback.c\n"
		@$(CC) -c ./srcs/builtins/builtin_callback.c -o ./.objs/builtin_callback.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)builtin_usage.o: srcs/builtins/builtin_usage.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/builtins/builtin_usage.c\n"
		@$(CC) -c ./srcs/builtins/builtin_usage.c -o ./.objs/builtin_usage.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)env_get.o: srcs/env/env_get.c incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/statuses.h incs/htabl.h incs/fnv.h incs/fnvhead32.h     incs/termcaps/termcaps.h incs/termcaps/log.h incs/termcaps/key.h     incs/redirection.h libs/libft/./incs/libft.h     libs/libft/./incs/libftprintf.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/job.h     libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/env/env_get.c\n"
		@$(CC) -c ./srcs/env/env_get.c -o ./.objs/env_get.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)env_get_path.o: srcs/env/env_get_path.c incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/statuses.h incs/htabl.h incs/fnv.h incs/fnvhead32.h     incs/termcaps/termcaps.h incs/termcaps/log.h incs/termcaps/key.h     incs/redirection.h libs/libft/./incs/libft.h     libs/libft/./incs/libftprintf.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/job.h     libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/env/env_get_path.c\n"
		@$(CC) -c ./srcs/env/env_get_path.c -o ./.objs/env_get_path.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)env_get_user.o: srcs/env/env_get_user.c incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/statuses.h incs/htabl.h incs/fnv.h incs/fnvhead32.h     incs/termcaps/termcaps.h incs/termcaps/log.h incs/termcaps/key.h     incs/redirection.h libs/libft/./incs/libft.h     libs/libft/./incs/libftprintf.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/job.h     libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/env/env_get_user.c\n"
		@$(CC) -c ./srcs/env/env_get_user.c -o ./.objs/env_get_user.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)env_get_home.o: srcs/env/env_get_home.c incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/statuses.h incs/htabl.h incs/fnv.h incs/fnvhead32.h     incs/termcaps/termcaps.h incs/termcaps/log.h incs/termcaps/key.h     incs/redirection.h libs/libft/./incs/libft.h     libs/libft/./incs/libftprintf.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/job.h     libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/env/env_get_home.c\n"
		@$(CC) -c ./srcs/env/env_get_home.c -o ./.objs/env_get_home.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)env_get_term.o: srcs/env/env_get_term.c incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/statuses.h incs/htabl.h incs/fnv.h incs/fnvhead32.h     incs/termcaps/termcaps.h incs/termcaps/log.h incs/termcaps/key.h     incs/redirection.h libs/libft/./incs/libft.h     libs/libft/./incs/libftprintf.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/job.h     libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/env/env_get_term.c\n"
		@$(CC) -c ./srcs/env/env_get_term.c -o ./.objs/env_get_term.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)env_set.o: srcs/env/env_set.c incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/statuses.h incs/htabl.h incs/fnv.h incs/fnvhead32.h     incs/termcaps/termcaps.h incs/termcaps/log.h incs/termcaps/key.h     incs/redirection.h libs/libft/./incs/libft.h     libs/libft/./incs/libftprintf.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/job.h     libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/env/env_set.c\n"
		@$(CC) -c ./srcs/env/env_set.c -o ./.objs/env_set.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)env_unset.o: srcs/env/env_unset.c incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/statuses.h incs/htabl.h incs/fnv.h incs/fnvhead32.h     incs/termcaps/termcaps.h incs/termcaps/log.h incs/termcaps/key.h     incs/redirection.h libs/libft/./incs/libft.h     libs/libft/./incs/libftprintf.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/job.h     libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/env/env_unset.c\n"
		@$(CC) -c ./srcs/env/env_unset.c -o ./.objs/env_unset.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)env_index_value.o: srcs/env/env_index_value.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/env/env_index_value.c\n"
		@$(CC) -c ./srcs/env/env_index_value.c -o ./.objs/env_index_value.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)env_update_from_cmd_line.o: srcs/env/env_update_from_cmd_line.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/env/env_update_from_cmd_line.c\n"
		@$(CC) -c ./srcs/env/env_update_from_cmd_line.c -o ./.objs/env_update_from_cmd_line.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)display_status.o: srcs/display/display_status.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/display/display_status.c\n"
		@$(CC) -c ./srcs/display/display_status.c -o ./.objs/display_status.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)i18n_translate.o: srcs/i18n/i18n_translate.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/i18n/i18n_translate.c\n"
		@$(CC) -c ./srcs/i18n/i18n_translate.c -o ./.objs/i18n_translate.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)shell_init.o: srcs/init/shell_init.c incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/statuses.h incs/htabl.h incs/fnv.h incs/fnvhead32.h     incs/termcaps/termcaps.h incs/termcaps/log.h incs/termcaps/key.h     incs/redirection.h libs/libft/./incs/libft.h     libs/libft/./incs/libftprintf.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/job.h     libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/init/shell_init.c\n"
		@$(CC) -c ./srcs/init/shell_init.c -o ./.objs/shell_init.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)shell_language.o: srcs/init/shell_language.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/init/shell_language.c\n"
		@$(CC) -c ./srcs/init/shell_language.c -o ./.objs/shell_language.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)shell_environment.o: srcs/init/shell_environment.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/init/shell_environment.c\n"
		@$(CC) -c ./srcs/init/shell_environment.c -o ./.objs/shell_environment.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)shell_set_prompt.o: srcs/init/shell_set_prompt.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/init/shell_set_prompt.c\n"
		@$(CC) -c ./srcs/init/shell_set_prompt.c -o ./.objs/shell_set_prompt.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)job_alloc.o: srcs/job/job_alloc.c incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/statuses.h incs/htabl.h incs/fnv.h incs/fnvhead32.h     incs/termcaps/termcaps.h incs/termcaps/log.h incs/termcaps/key.h     incs/redirection.h libs/libft/./incs/libft.h     libs/libft/./incs/libftprintf.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/job.h     libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/job_alloc.c\n"
		@$(CC) -c ./srcs/job/job_alloc.c -o ./.objs/job_alloc.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)proc_alloc.o: srcs/job/proc_alloc.c incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/statuses.h incs/htabl.h incs/fnv.h incs/fnvhead32.h     incs/termcaps/termcaps.h incs/termcaps/log.h incs/termcaps/key.h     incs/redirection.h libs/libft/./incs/libft.h     libs/libft/./incs/libftprintf.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/job.h     libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/proc_alloc.c\n"
		@$(CC) -c ./srcs/job/proc_alloc.c -o ./.objs/proc_alloc.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)job_available_id.o: srcs/job/job_available_id.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/job_available_id.c\n"
		@$(CC) -c ./srcs/job/job_available_id.c -o ./.objs/job_available_id.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)job_background.o: srcs/job/job_background.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/job_background.c\n"
		@$(CC) -c ./srcs/job/job_background.c -o ./.objs/job_background.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)job_background_nth.o: srcs/job/job_background_nth.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/job_background_nth.c\n"
		@$(CC) -c ./srcs/job/job_background_nth.c -o ./.objs/job_background_nth.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)job_background_update_status.o: srcs/job/job_background_update_status.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/job_background_update_status.c\n"
		@$(CC) -c ./srcs/job/job_background_update_status.c -o ./.objs/job_background_update_status.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)job_by_id.o: srcs/job/job_by_id.c incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/statuses.h incs/htabl.h incs/fnv.h incs/fnvhead32.h     incs/termcaps/termcaps.h incs/termcaps/log.h incs/termcaps/key.h     incs/redirection.h libs/libft/./incs/libft.h     libs/libft/./incs/libftprintf.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/job.h     libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/job_by_id.c\n"
		@$(CC) -c ./srcs/job/job_by_id.c -o ./.objs/job_by_id.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)job_by_name.o: srcs/job/job_by_name.c incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/statuses.h incs/htabl.h incs/fnv.h incs/fnvhead32.h     incs/termcaps/termcaps.h incs/termcaps/log.h incs/termcaps/key.h     incs/redirection.h libs/libft/./incs/libft.h     libs/libft/./incs/libftprintf.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/job.h     libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/job_by_name.c\n"
		@$(CC) -c ./srcs/job/job_by_name.c -o ./.objs/job_by_name.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)job_display_status.o: srcs/job/job_display_status.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/job_display_status.c\n"
		@$(CC) -c ./srcs/job/job_display_status.c -o ./.objs/job_display_status.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)job_foreground.o: srcs/job/job_foreground.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/job_foreground.c\n"
		@$(CC) -c ./srcs/job/job_foreground.c -o ./.objs/job_foreground.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)job_free.o: srcs/job/job_free.c incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/statuses.h incs/htabl.h incs/fnv.h incs/fnvhead32.h     incs/termcaps/termcaps.h incs/termcaps/log.h incs/termcaps/key.h     incs/redirection.h libs/libft/./incs/libft.h     libs/libft/./incs/libftprintf.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/job.h     libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/job_free.c\n"
		@$(CC) -c ./srcs/job/job_free.c -o ./.objs/job_free.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)job_is_completed.o: srcs/job/job_is_completed.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/job_is_completed.c\n"
		@$(CC) -c ./srcs/job/job_is_completed.c -o ./.objs/job_is_completed.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)job_is_signaled.o: srcs/job/job_is_signaled.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/job_is_signaled.c\n"
		@$(CC) -c ./srcs/job/job_is_signaled.c -o ./.objs/job_is_signaled.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)job_is_stopped.o: srcs/job/job_is_stopped.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/job_is_stopped.c\n"
		@$(CC) -c ./srcs/job/job_is_stopped.c -o ./.objs/job_is_stopped.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)job_kill.o: srcs/job/job_kill.c incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/statuses.h incs/htabl.h incs/fnv.h incs/fnvhead32.h     incs/termcaps/termcaps.h incs/termcaps/log.h incs/termcaps/key.h     incs/redirection.h libs/libft/./incs/libft.h     libs/libft/./incs/libftprintf.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/job.h     libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/job_kill.c\n"
		@$(CC) -c ./srcs/job/job_kill.c -o ./.objs/job_kill.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)job_launch.o: srcs/job/job_launch.c incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/statuses.h incs/htabl.h incs/fnv.h incs/fnvhead32.h     incs/termcaps/termcaps.h incs/termcaps/log.h incs/termcaps/key.h     incs/redirection.h libs/libft/./incs/libft.h     libs/libft/./incs/libftprintf.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/job.h     libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/job_launch.c\n"
		@$(CC) -c ./srcs/job/job_launch.c -o ./.objs/job_launch.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)job_list_clean.o: srcs/job/job_list_clean.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/job_list_clean.c\n"
		@$(CC) -c ./srcs/job/job_list_clean.c -o ./.objs/job_list_clean.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)job_set_stopped.o: srcs/job/job_set_stopped.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/job_set_stopped.c\n"
		@$(CC) -c ./srcs/job/job_set_stopped.c -o ./.objs/job_set_stopped.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)job_wait.o: srcs/job/job_wait.c incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/statuses.h incs/htabl.h incs/fnv.h incs/fnvhead32.h     incs/termcaps/termcaps.h incs/termcaps/log.h incs/termcaps/key.h     incs/redirection.h libs/libft/./incs/libft.h     libs/libft/./incs/libftprintf.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/job.h     libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/job_wait.c\n"
		@$(CC) -c ./srcs/job/job_wait.c -o ./.objs/job_wait.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)proc_find.o: srcs/job/proc_find.c incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/statuses.h incs/htabl.h incs/fnv.h incs/fnvhead32.h     incs/termcaps/termcaps.h incs/termcaps/log.h incs/termcaps/key.h     incs/redirection.h libs/libft/./incs/libft.h     libs/libft/./incs/libftprintf.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/job.h     libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/proc_find.c\n"
		@$(CC) -c ./srcs/job/proc_find.c -o ./.objs/proc_find.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)proc_free.o: srcs/job/proc_free.c incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/statuses.h incs/htabl.h incs/fnv.h incs/fnvhead32.h     incs/termcaps/termcaps.h incs/termcaps/log.h incs/termcaps/key.h     incs/redirection.h libs/libft/./incs/libft.h     libs/libft/./incs/libftprintf.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/job.h     libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/proc_free.c\n"
		@$(CC) -c ./srcs/job/proc_free.c -o ./.objs/proc_free.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)proc_launch.o: srcs/job/proc_launch.c incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/statuses.h incs/htabl.h incs/fnv.h incs/fnvhead32.h     incs/termcaps/termcaps.h incs/termcaps/log.h incs/termcaps/key.h     incs/redirection.h libs/libft/./incs/libft.h     libs/libft/./incs/libftprintf.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/job.h     libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/proc_launch.c\n"
		@$(CC) -c ./srcs/job/proc_launch.c -o ./.objs/proc_launch.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)proc_update_status.o: srcs/job/proc_update_status.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/proc_update_status.c\n"
		@$(CC) -c ./srcs/job/proc_update_status.c -o ./.objs/proc_update_status.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)redir_alloc.o: srcs/job/redir_alloc.c incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/statuses.h incs/htabl.h incs/fnv.h incs/fnvhead32.h     incs/termcaps/termcaps.h incs/termcaps/log.h incs/termcaps/key.h     incs/redirection.h libs/libft/./incs/libft.h     libs/libft/./incs/libftprintf.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/job.h     libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/redir_alloc.c\n"
		@$(CC) -c ./srcs/job/redir_alloc.c -o ./.objs/redir_alloc.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)redir_free.o: srcs/job/redir_free.c incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/statuses.h incs/htabl.h incs/fnv.h incs/fnvhead32.h     incs/termcaps/termcaps.h incs/termcaps/log.h incs/termcaps/key.h     incs/redirection.h libs/libft/./incs/libft.h     libs/libft/./incs/libftprintf.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/job.h     libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/redir_free.c\n"
		@$(CC) -c ./srcs/job/redir_free.c -o ./.objs/redir_free.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)redir_list_free.o: srcs/job/redir_list_free.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/redir_list_free.c\n"
		@$(CC) -c ./srcs/job/redir_list_free.c -o ./.objs/redir_list_free.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)loop_main.o: srcs/loop/loop_main.c incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/statuses.h incs/htabl.h incs/fnv.h incs/fnvhead32.h     incs/termcaps/termcaps.h incs/termcaps/log.h incs/termcaps/key.h     incs/redirection.h libs/libft/./incs/libft.h     libs/libft/./incs/libftprintf.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/job.h     libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/loop/loop_main.c\n"
		@$(CC) -c ./srcs/loop/loop_main.c -o ./.objs/loop_main.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)option_get_value.o: srcs/options/option_get_value.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/options/option_get_value.c\n"
		@$(CC) -c ./srcs/options/option_get_value.c -o ./.objs/option_get_value.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)option_is_set.o: srcs/options/option_is_set.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/options/option_is_set.c\n"
		@$(CC) -c ./srcs/options/option_is_set.c -o ./.objs/option_is_set.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)list_node__option_alloc.o: srcs/options/list_node__option_alloc.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/options/list_node__option_alloc.c\n"
		@$(CC) -c ./srcs/options/list_node__option_alloc.c -o ./.objs/list_node__option_alloc.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)option_free.o: srcs/options/option_free.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/options/option_free.c\n"
		@$(CC) -c ./srcs/options/option_free.c -o ./.objs/option_free.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)option_parse.o: srcs/options/option_parse.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/options/option_parse.c\n"
		@$(CC) -c ./srcs/options/option_parse.c -o ./.objs/option_parse.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)path_init_hasht.o: srcs/path/path_init_hasht.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/path/path_init_hasht.c\n"
		@$(CC) -c ./srcs/path/path_init_hasht.c -o ./.objs/path_init_hasht.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)path_free_hasht.o: srcs/path/path_free_hasht.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/path/path_free_hasht.c\n"
		@$(CC) -c ./srcs/path/path_free_hasht.c -o ./.objs/path_free_hasht.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)path_get_new_cmd.o: srcs/path/path_get_new_cmd.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/path/path_get_new_cmd.c\n"
		@$(CC) -c ./srcs/path/path_get_new_cmd.c -o ./.objs/path_get_new_cmd.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)path_fnv_a_str.o: srcs/path/path_fnv_a_str.c incs/fnv.h incs/fnvhead32.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/path/path_fnv_a_str.c\n"
		@$(CC) -c ./srcs/path/path_fnv_a_str.c -o ./.objs/path_fnv_a_str.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)path_hash_finder.o: srcs/path/path_hash_finder.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/path/path_hash_finder.c\n"
		@$(CC) -c ./srcs/path/path_hash_finder.c -o ./.objs/path_hash_finder.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)path_add_folder_content_to_hasht.o:     srcs/path/path_add_folder_content_to_hasht.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/path/path_add_folder_content_to_hasht.c\n"
		@$(CC) -c ./srcs/path/path_add_folder_content_to_hasht.c -o ./.objs/path_add_folder_content_to_hasht.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)path_commande_not_found_in_hasht.o:     srcs/path/path_commande_not_found_in_hasht.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/path/path_commande_not_found_in_hasht.c\n"
		@$(CC) -c ./srcs/path/path_commande_not_found_in_hasht.c -o ./.objs/path_commande_not_found_in_hasht.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)quoting_new_context.o: srcs/quoting/quoting_new_context.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/quoting/quoting_new_context.c\n"
		@$(CC) -c ./srcs/quoting/quoting_new_context.c -o ./.objs/quoting_new_context.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)signal_to_default.o: srcs/signal/signal_to_default.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/signal/signal_to_default.c\n"
		@$(CC) -c ./srcs/signal/signal_to_default.c -o ./.objs/signal_to_default.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)signal_to_ignore.o: srcs/signal/signal_to_ignore.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/signal/signal_to_ignore.c\n"
		@$(CC) -c ./srcs/signal/signal_to_ignore.c -o ./.objs/signal_to_ignore.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)signal_to_pgid.o: srcs/signal/signal_to_pgid.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/signal/signal_to_pgid.c\n"
		@$(CC) -c ./srcs/signal/signal_to_pgid.c -o ./.objs/signal_to_pgid.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)termcaps_initialize.o: srcs/termcaps/termcaps_initialize.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/termcaps_initialize.c\n"
		@$(CC) -c ./srcs/termcaps/termcaps_initialize.c -o ./.objs/termcaps_initialize.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)termcaps_finalize.o: srcs/termcaps/termcaps_finalize.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/termcaps_finalize.c\n"
		@$(CC) -c ./srcs/termcaps/termcaps_finalize.c -o ./.objs/termcaps_finalize.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)termcaps_line_print.o: srcs/termcaps/termcaps_line_print.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/termcaps_line_print.c\n"
		@$(CC) -c ./srcs/termcaps/termcaps_line_print.c -o ./.objs/termcaps_line_print.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)termcaps_line_erase.o: srcs/termcaps/termcaps_line_erase.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/termcaps_line_erase.c\n"
		@$(CC) -c ./srcs/termcaps/termcaps_line_erase.c -o ./.objs/termcaps_line_erase.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)termcaps_read_input.o: srcs/termcaps/termcaps_read_input.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/termcaps_read_input.c\n"
		@$(CC) -c ./srcs/termcaps/termcaps_read_input.c -o ./.objs/termcaps_read_input.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)termcaps_read_loop.o: srcs/termcaps/termcaps_read_loop.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/termcaps_read_loop.c\n"
		@$(CC) -c ./srcs/termcaps/termcaps_read_loop.c -o ./.objs/termcaps_read_loop.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)termcaps_get_character_bytes_count.o:     srcs/termcaps/termcaps_get_character_bytes_count.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/termcaps_get_character_bytes_count.c\n"
		@$(CC) -c ./srcs/termcaps/termcaps_get_character_bytes_count.c -o ./.objs/termcaps_get_character_bytes_count.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)termcaps_string_to_command_line.o:     srcs/termcaps/termcaps_string_to_command_line.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/termcaps_string_to_command_line.c\n"
		@$(CC) -c ./srcs/termcaps/termcaps_string_to_command_line.c -o ./.objs/termcaps_string_to_command_line.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)termcaps_character_to_command_line.o:     srcs/termcaps/termcaps_character_to_command_line.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/termcaps_character_to_command_line.c\n"
		@$(CC) -c ./srcs/termcaps/termcaps_character_to_command_line.c -o ./.objs/termcaps_character_to_command_line.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)termcaps_display_command_line.o:     srcs/termcaps/termcaps_display_command_line.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/termcaps_display_command_line.c\n"
		@$(CC) -c ./srcs/termcaps/termcaps_display_command_line.c -o ./.objs/termcaps_display_command_line.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)termcaps_isunicode.o: srcs/termcaps/termcaps_isunicode.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/termcaps_isunicode.c\n"
		@$(CC) -c ./srcs/termcaps/termcaps_isunicode.c -o ./.objs/termcaps_isunicode.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)termcaps_identify_input.o: srcs/termcaps/termcaps_identify_input.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/termcaps_identify_input.c\n"
		@$(CC) -c ./srcs/termcaps/termcaps_identify_input.c -o ./.objs/termcaps_identify_input.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)list_head.o: srcs/termcaps/list_head.c incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/statuses.h incs/htabl.h incs/fnv.h incs/fnvhead32.h     incs/termcaps/termcaps.h incs/termcaps/log.h incs/termcaps/key.h     incs/redirection.h libs/libft/./incs/libft.h     libs/libft/./incs/libftprintf.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/job.h     libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/list_head.c\n"
		@$(CC) -c ./srcs/termcaps/list_head.c -o ./.objs/list_head.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)list_head_command.o: srcs/termcaps/list_head_command.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/list_head_command.c\n"
		@$(CC) -c ./srcs/termcaps/list_head_command.c -o ./.objs/list_head_command.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)list_head_history.o: srcs/termcaps/list_head_history.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/list_head_history.c\n"
		@$(CC) -c ./srcs/termcaps/list_head_history.c -o ./.objs/list_head_history.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__backspace.o: srcs/termcaps/key__backspace.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__backspace.c\n"
		@$(CC) -c ./srcs/termcaps/key__backspace.c -o ./.objs/key__backspace.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__copy.o: srcs/termcaps/key__copy.c incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/statuses.h incs/htabl.h incs/fnv.h incs/fnvhead32.h     incs/termcaps/termcaps.h incs/termcaps/log.h incs/termcaps/key.h     incs/redirection.h libs/libft/./incs/libft.h     libs/libft/./incs/libftprintf.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/job.h     libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__copy.c\n"
		@$(CC) -c ./srcs/termcaps/key__copy.c -o ./.objs/key__copy.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__cursor_to_begin_of_line.o:     srcs/termcaps/key__cursor_to_begin_of_line.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__cursor_to_begin_of_line.c\n"
		@$(CC) -c ./srcs/termcaps/key__cursor_to_begin_of_line.c -o ./.objs/key__cursor_to_begin_of_line.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__cursor_to_end_of_line.o: srcs/termcaps/key__cursor_to_end_of_line.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__cursor_to_end_of_line.c\n"
		@$(CC) -c ./srcs/termcaps/key__cursor_to_end_of_line.c -o ./.objs/key__cursor_to_end_of_line.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__cursor_to_next_character.o:     srcs/termcaps/key__cursor_to_next_character.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__cursor_to_next_character.c\n"
		@$(CC) -c ./srcs/termcaps/key__cursor_to_next_character.c -o ./.objs/key__cursor_to_next_character.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__cursor_to_next_command.o:     srcs/termcaps/key__cursor_to_next_command.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__cursor_to_next_command.c\n"
		@$(CC) -c ./srcs/termcaps/key__cursor_to_next_command.c -o ./.objs/key__cursor_to_next_command.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__cursor_to_next_line.o: srcs/termcaps/key__cursor_to_next_line.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__cursor_to_next_line.c\n"
		@$(CC) -c ./srcs/termcaps/key__cursor_to_next_line.c -o ./.objs/key__cursor_to_next_line.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__cursor_to_next_word.o: srcs/termcaps/key__cursor_to_next_word.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__cursor_to_next_word.c\n"
		@$(CC) -c ./srcs/termcaps/key__cursor_to_next_word.c -o ./.objs/key__cursor_to_next_word.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__cursor_to_prev_character.o:     srcs/termcaps/key__cursor_to_prev_character.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__cursor_to_prev_character.c\n"
		@$(CC) -c ./srcs/termcaps/key__cursor_to_prev_character.c -o ./.objs/key__cursor_to_prev_character.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__cursor_to_prev_command.o:     srcs/termcaps/key__cursor_to_prev_command.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__cursor_to_prev_command.c\n"
		@$(CC) -c ./srcs/termcaps/key__cursor_to_prev_command.c -o ./.objs/key__cursor_to_prev_command.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__cursor_to_prev_line.o: srcs/termcaps/key__cursor_to_prev_line.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__cursor_to_prev_line.c\n"
		@$(CC) -c ./srcs/termcaps/key__cursor_to_prev_line.c -o ./.objs/key__cursor_to_prev_line.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__cursor_to_prev_word.o: srcs/termcaps/key__cursor_to_prev_word.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__cursor_to_prev_word.c\n"
		@$(CC) -c ./srcs/termcaps/key__cursor_to_prev_word.c -o ./.objs/key__cursor_to_prev_word.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__cut.o: srcs/termcaps/key__cut.c incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/statuses.h incs/htabl.h incs/fnv.h incs/fnvhead32.h     incs/termcaps/termcaps.h incs/termcaps/log.h incs/termcaps/key.h     incs/redirection.h libs/libft/./incs/libft.h     libs/libft/./incs/libftprintf.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/job.h     libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__cut.c\n"
		@$(CC) -c ./srcs/termcaps/key__cut.c -o ./.objs/key__cut.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__cut_to_end_of_line.o: srcs/termcaps/key__cut_to_end_of_line.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__cut_to_end_of_line.c\n"
		@$(CC) -c ./srcs/termcaps/key__cut_to_end_of_line.c -o ./.objs/key__cut_to_end_of_line.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__delete_command_line.o: srcs/termcaps/key__delete_command_line.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__delete_command_line.c\n"
		@$(CC) -c ./srcs/termcaps/key__delete_command_line.c -o ./.objs/key__delete_command_line.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__delete_under_cursor.o: srcs/termcaps/key__delete_under_cursor.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__delete_under_cursor.c\n"
		@$(CC) -c ./srcs/termcaps/key__delete_under_cursor.c -o ./.objs/key__delete_under_cursor.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__paste.o: srcs/termcaps/key__paste.c incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/statuses.h incs/htabl.h incs/fnv.h incs/fnvhead32.h     incs/termcaps/termcaps.h incs/termcaps/log.h incs/termcaps/key.h     incs/redirection.h libs/libft/./incs/libft.h     libs/libft/./incs/libftprintf.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/job.h     libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__paste.c\n"
		@$(CC) -c ./srcs/termcaps/key__paste.c -o ./.objs/key__paste.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__select.o: srcs/termcaps/key__select.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__select.c\n"
		@$(CC) -c ./srcs/termcaps/key__select.c -o ./.objs/key__select.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__send.o: srcs/termcaps/key__send.c incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/statuses.h incs/htabl.h incs/fnv.h incs/fnvhead32.h     incs/termcaps/termcaps.h incs/termcaps/log.h incs/termcaps/key.h     incs/redirection.h libs/libft/./incs/libft.h     libs/libft/./incs/libftprintf.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/job.h     libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__send.c\n"
		@$(CC) -c ./srcs/termcaps/key__send.c -o ./.objs/key__send.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__share__command_line_to_history.o:     srcs/termcaps/key__share__command_line_to_history.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__share__command_line_to_history.c\n"
		@$(CC) -c ./srcs/termcaps/key__share__command_line_to_history.c -o ./.objs/key__share__command_line_to_history.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__share__copy_build_copy.o:     srcs/termcaps/key__share__copy_build_copy.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__share__copy_build_copy.c\n"
		@$(CC) -c ./srcs/termcaps/key__share__copy_build_copy.c -o ./.objs/key__share__copy_build_copy.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__share__cut_build_copy.o: srcs/termcaps/key__share__cut_build_copy.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__share__cut_build_copy.c\n"
		@$(CC) -c ./srcs/termcaps/key__share__cut_build_copy.c -o ./.objs/key__share__cut_build_copy.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__share__selection_get.o: srcs/termcaps/key__share__selection_get.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__share__selection_get.c\n"
		@$(CC) -c ./srcs/termcaps/key__share__selection_get.c -o ./.objs/key__share__selection_get.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__share_words.o: srcs/termcaps/key__share_words.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__share_words.c\n"
		@$(CC) -c ./srcs/termcaps/key__share_words.c -o ./.objs/key__share_words.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__completion.o: srcs/termcaps/key__completion.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__completion.c\n"
		@$(CC) -c ./srcs/termcaps/key__completion.c -o ./.objs/key__completion.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__completion_s.o: srcs/termcaps/key__completion_s.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__completion_s.c\n"
		@$(CC) -c ./srcs/termcaps/key__completion_s.c -o ./.objs/key__completion_s.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__completion_list_dir.o: srcs/termcaps/key__completion_list_dir.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__completion_list_dir.c\n"
		@$(CC) -c ./srcs/termcaps/key__completion_list_dir.c -o ./.objs/key__completion_list_dir.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__ctrl_c.o: srcs/termcaps/key__ctrl_c.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__ctrl_c.c\n"
		@$(CC) -c ./srcs/termcaps/key__ctrl_c.c -o ./.objs/key__ctrl_c.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__clear.o: srcs/termcaps/key__clear.c incs/shell.h incs/shell_struct.h     libs/libft/./incs/list.h incs/termcaps/termcaps_struct.h     incs/termcaps/list_head.h libs/libcaps/./incs/types.h incs/option.h     incs/statuses.h incs/htabl.h incs/fnv.h incs/fnvhead32.h     incs/termcaps/termcaps.h incs/termcaps/log.h incs/termcaps/key.h     incs/redirection.h libs/libft/./incs/libft.h     libs/libft/./incs/libftprintf.h libs/logger/./incs/logger.h     libs/logger/./incs/logger_utils.h incs/job.h     libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__clear.c\n"
		@$(CC) -c ./srcs/termcaps/key__clear.c -o ./.objs/key__clear.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__search_history.o: srcs/termcaps/key__search_history.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__search_history.c\n"
		@$(CC) -c ./srcs/termcaps/key__search_history.c -o ./.objs/key__search_history.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)termcaps_history_search.o: srcs/termcaps/termcaps_history_search.c     incs/shell.h incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/termcaps_history_search.c\n"
		@$(CC) -c ./srcs/termcaps/termcaps_history_search.c -o ./.objs/termcaps_history_search.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)termcaps_write.o: srcs/termcaps/termcaps_write.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/termcaps_write.c\n"
		@$(CC) -c ./srcs/termcaps/termcaps_write.c -o ./.objs/termcaps_write.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)conf_check_color_mode.o: srcs/conf/conf_check_color_mode.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/conf/conf_check_color_mode.c\n"
		@$(CC) -c ./srcs/conf/conf_check_color_mode.c -o ./.objs/conf_check_color_mode.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)conf_file_init.o: srcs/conf/conf_file_init.c incs/shell.h     incs/shell_struct.h libs/libft/./incs/list.h     incs/termcaps/termcaps_struct.h incs/termcaps/list_head.h     libs/libcaps/./incs/types.h incs/option.h incs/statuses.h incs/htabl.h     incs/fnv.h incs/fnvhead32.h incs/termcaps/termcaps.h     incs/termcaps/log.h incs/termcaps/key.h incs/redirection.h     libs/libft/./incs/libft.h libs/libft/./incs/libftprintf.h     libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h     incs/job.h libs/libcaps/./incs/caps.h incs/i18n.h     libs/libft/./incs/get_next_line.h incs/parser.h incs/parser_struct.h     incs/builtins/builtin.h incs/quoting.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/conf/conf_file_init.c\n"
		@$(CC) -c ./srcs/conf/conf_file_init.c -o ./.objs/conf_file_init.o $(CPPFLAGS) $(CFLAGS) 


#end
