# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mleconte <mleconte@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/30 13:39:33 by anouvel           #+#    #+#              #
#    Updated: 2016/05/26 17:36:10 by mleconte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------------------------------------- #
# PROJECT DATA
# ---------------------------------------------------------------------------- #

NAME		=	42sh

# ---------------------------------------------------------------------------- #

SRCS		=	\
				main.c							\
				builtins/cd/builtin_cd.c		\
				builtins/help/builtin_help.c	\
				builtins/jobs/builtin_jobs.c	\
				builtins/builtin_callback.c		\
				log_status/log_status.c			\
				i18n/i18n_translate.c			\
				init/shell_init.c				\
				init/shell_language.c			\
				stdin_loop.c					\
				parse.c							\
				job/job_alloc.c					\
				job/job_available_id.c			\
				job/job_foreground.c			\
				job/job_is_completed.c			\
				job/job_is_stopped.c			\
				job/job_kill.c					\
				job/job_launch.c				\
				job/job_wait.c					\
				job/proc_find.c					\
				job/proc_launch.c				\
				job/proc_update_status.c		\
				list/list_node__proc_alloc.c	\
				options/option_is_set.c			\
				options/list_node__option_alloc.c\
				options/option_parse.c			\
				signal/signal_sigchld.c			\
				signal/signal_to_default.c		\
				signal/signal_to_ignore.c		\
				lexer/lexer.c					\
				lexer/token_list.c				\
				lexer/tokenize.c				\
				termcaps/termcaps_init.c		\
				termcaps/termcaps_read_input.c					\
				termcaps/termcaps_get_character_bytes_count.c	\
				termcaps/termcaps_string_to_command_line.c		\
				termcaps/termcaps_character_to_command_line.c	\
				termcaps/termcaps_display_command_line.c		\
				termcaps/termcaps_isunicode.c					\
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
				termcaps/key__share.c							\
				termcaps/key__share_words.c						\

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
				-lncurses						\

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
	@git submodule foreach git pull origin master

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
		$(CC) -MM $(s) $(CPPFLAGS)								>> Makefile	&& \
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

$(DIROBJ)main.o: srcs/main.c incs/shell.h libs/libft/./incs/libft.h \
  libs/libft/./incs/list.h libs/logger/./incs/logger.h \
  libs/logger/./incs/logger_utils.h incs/statuses.h incs/option.h \
  incs/job.h incs/termcaps/termcaps.h incs/termcaps/list_head.h \
  libs/libcaps/./incs/types.h incs/termcaps/log.h \
  incs/termcaps/termcaps_struct.h incs/termcaps/key.h \
  libs/libcaps/./incs/caps.h libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/main.c\n"
		@$(CC) -c ./srcs/main.c -o ./.objs/main.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)builtin_cd.o: srcs/builtins/cd/builtin_cd.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/builtins/cd/builtin_cd.c\n"
		@$(CC) -c ./srcs/builtins/cd/builtin_cd.c -o ./.objs/builtin_cd.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)builtin_help.o: srcs/builtins/help/builtin_help.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h \
  incs/builtins/builtin_struct.h incs/builtins/builtin_cd.h \
  incs/builtins/builtin_help.h incs/builtins/builtin_jobs.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/builtins/help/builtin_help.c\n"
		@$(CC) -c ./srcs/builtins/help/builtin_help.c -o ./.objs/builtin_help.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)builtin_jobs.o: srcs/builtins/jobs/builtin_jobs.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/builtins/jobs/builtin_jobs.c\n"
		@$(CC) -c ./srcs/builtins/jobs/builtin_jobs.c -o ./.objs/builtin_jobs.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)builtin_callback.o: srcs/builtins/builtin_callback.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h \
  incs/builtins/builtin_struct.h incs/builtins/builtin_cd.h \
  incs/builtins/builtin_help.h incs/builtins/builtin_jobs.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/builtins/builtin_callback.c\n"
		@$(CC) -c ./srcs/builtins/builtin_callback.c -o ./.objs/builtin_callback.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)log_status.o: srcs/log_status/log_status.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/log_status/log_status.c\n"
		@$(CC) -c ./srcs/log_status/log_status.c -o ./.objs/log_status.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)i18n_translate.o: srcs/i18n/i18n_translate.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/i18n/i18n_translate.c\n"
		@$(CC) -c ./srcs/i18n/i18n_translate.c -o ./.objs/i18n_translate.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)shell_init.o: srcs/init/shell_init.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/init/shell_init.c\n"
		@$(CC) -c ./srcs/init/shell_init.c -o ./.objs/shell_init.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)shell_language.o: srcs/init/shell_language.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/init/shell_language.c\n"
		@$(CC) -c ./srcs/init/shell_language.c -o ./.objs/shell_language.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)stdin_loop.o: srcs/stdin_loop.c incs/shell.h libs/libft/./incs/libft.h \
  libs/libft/./incs/list.h libs/logger/./incs/logger.h \
  libs/logger/./incs/logger_utils.h incs/statuses.h incs/option.h \
  incs/job.h incs/termcaps/termcaps.h incs/termcaps/list_head.h \
  libs/libcaps/./incs/types.h incs/termcaps/log.h \
  incs/termcaps/termcaps_struct.h incs/termcaps/key.h \
  libs/libcaps/./incs/caps.h libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/stdin_loop.c\n"
		@$(CC) -c ./srcs/stdin_loop.c -o ./.objs/stdin_loop.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)parse.o: srcs/parse.c incs/shell.h libs/libft/./incs/libft.h \
  libs/libft/./incs/list.h libs/logger/./incs/logger.h \
  libs/logger/./incs/logger_utils.h incs/statuses.h incs/option.h \
  incs/job.h incs/termcaps/termcaps.h incs/termcaps/list_head.h \
  libs/libcaps/./incs/types.h incs/termcaps/log.h \
  incs/termcaps/termcaps_struct.h incs/termcaps/key.h \
  libs/libcaps/./incs/caps.h libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parse.c\n"
		@$(CC) -c ./srcs/parse.c -o ./.objs/parse.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)job_alloc.o: srcs/job/job_alloc.c incs/shell.h libs/libft/./incs/libft.h \
  libs/libft/./incs/list.h libs/logger/./incs/logger.h \
  libs/logger/./incs/logger_utils.h incs/statuses.h incs/option.h \
  incs/job.h incs/termcaps/termcaps.h incs/termcaps/list_head.h \
  libs/libcaps/./incs/types.h incs/termcaps/log.h \
  incs/termcaps/termcaps_struct.h incs/termcaps/key.h \
  libs/libcaps/./incs/caps.h libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/job_alloc.c\n"
		@$(CC) -c ./srcs/job/job_alloc.c -o ./.objs/job_alloc.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)job_available_id.o: srcs/job/job_available_id.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/job_available_id.c\n"
		@$(CC) -c ./srcs/job/job_available_id.c -o ./.objs/job_available_id.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)job_foreground.o: srcs/job/job_foreground.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/job_foreground.c\n"
		@$(CC) -c ./srcs/job/job_foreground.c -o ./.objs/job_foreground.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)job_is_completed.o: srcs/job/job_is_completed.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/job_is_completed.c\n"
		@$(CC) -c ./srcs/job/job_is_completed.c -o ./.objs/job_is_completed.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)job_is_stopped.o: srcs/job/job_is_stopped.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/job_is_stopped.c\n"
		@$(CC) -c ./srcs/job/job_is_stopped.c -o ./.objs/job_is_stopped.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)job_kill.o: srcs/job/job_kill.c incs/shell.h libs/libft/./incs/libft.h \
  libs/libft/./incs/list.h libs/logger/./incs/logger.h \
  libs/logger/./incs/logger_utils.h incs/statuses.h incs/option.h \
  incs/job.h incs/termcaps/termcaps.h incs/termcaps/list_head.h \
  libs/libcaps/./incs/types.h incs/termcaps/log.h \
  incs/termcaps/termcaps_struct.h incs/termcaps/key.h \
  libs/libcaps/./incs/caps.h libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/job_kill.c\n"
		@$(CC) -c ./srcs/job/job_kill.c -o ./.objs/job_kill.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)job_launch.o: srcs/job/job_launch.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/job_launch.c\n"
		@$(CC) -c ./srcs/job/job_launch.c -o ./.objs/job_launch.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)job_wait.o: srcs/job/job_wait.c incs/shell.h libs/libft/./incs/libft.h \
  libs/libft/./incs/list.h libs/logger/./incs/logger.h \
  libs/logger/./incs/logger_utils.h incs/statuses.h incs/option.h \
  incs/job.h incs/termcaps/termcaps.h incs/termcaps/list_head.h \
  libs/libcaps/./incs/types.h incs/termcaps/log.h \
  incs/termcaps/termcaps_struct.h incs/termcaps/key.h \
  libs/libcaps/./incs/caps.h libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/job_wait.c\n"
		@$(CC) -c ./srcs/job/job_wait.c -o ./.objs/job_wait.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)proc_find.o: srcs/job/proc_find.c incs/shell.h libs/libft/./incs/libft.h \
  libs/libft/./incs/list.h libs/logger/./incs/logger.h \
  libs/logger/./incs/logger_utils.h incs/statuses.h incs/option.h \
  incs/job.h incs/termcaps/termcaps.h incs/termcaps/list_head.h \
  libs/libcaps/./incs/types.h incs/termcaps/log.h \
  incs/termcaps/termcaps_struct.h incs/termcaps/key.h \
  libs/libcaps/./incs/caps.h libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/proc_find.c\n"
		@$(CC) -c ./srcs/job/proc_find.c -o ./.objs/proc_find.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)proc_launch.o: srcs/job/proc_launch.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/proc_launch.c\n"
		@$(CC) -c ./srcs/job/proc_launch.c -o ./.objs/proc_launch.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)proc_update_status.o: srcs/job/proc_update_status.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/proc_update_status.c\n"
		@$(CC) -c ./srcs/job/proc_update_status.c -o ./.objs/proc_update_status.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)list_node__proc_alloc.o: srcs/list/list_node__proc_alloc.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/list/list_node__proc_alloc.c\n"
		@$(CC) -c ./srcs/list/list_node__proc_alloc.c -o ./.objs/list_node__proc_alloc.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)option_is_set.o: srcs/options/option_is_set.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/options/option_is_set.c\n"
		@$(CC) -c ./srcs/options/option_is_set.c -o ./.objs/option_is_set.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)list_node__option_alloc.o: srcs/options/list_node__option_alloc.c \
  incs/shell.h libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/options/list_node__option_alloc.c\n"
		@$(CC) -c ./srcs/options/list_node__option_alloc.c -o ./.objs/list_node__option_alloc.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)option_parse.o: srcs/options/option_parse.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/options/option_parse.c\n"
		@$(CC) -c ./srcs/options/option_parse.c -o ./.objs/option_parse.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)signal_sigchld.o: srcs/signal/signal_sigchld.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/signal/signal_sigchld.c\n"
		@$(CC) -c ./srcs/signal/signal_sigchld.c -o ./.objs/signal_sigchld.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)signal_to_default.o: srcs/signal/signal_to_default.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/signal/signal_to_default.c\n"
		@$(CC) -c ./srcs/signal/signal_to_default.c -o ./.objs/signal_to_default.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)signal_to_ignore.o: srcs/signal/signal_to_ignore.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/signal/signal_to_ignore.c\n"
		@$(CC) -c ./srcs/signal/signal_to_ignore.c -o ./.objs/signal_to_ignore.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)lexer.o: srcs/lexer/lexer.c incs/shell.h libs/libft/./incs/libft.h \
  libs/libft/./incs/list.h libs/logger/./incs/logger.h \
  libs/logger/./incs/logger_utils.h incs/statuses.h incs/option.h \
  incs/job.h incs/termcaps/termcaps.h incs/termcaps/list_head.h \
  libs/libcaps/./incs/types.h incs/termcaps/log.h \
  incs/termcaps/termcaps_struct.h incs/termcaps/key.h \
  libs/libcaps/./incs/caps.h libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/lexer/lexer.c\n"
		@$(CC) -c ./srcs/lexer/lexer.c -o ./.objs/lexer.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)token_list.o: srcs/lexer/token_list.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/lexer/token_list.c\n"
		@$(CC) -c ./srcs/lexer/token_list.c -o ./.objs/token_list.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)tokenize.o: srcs/lexer/tokenize.c incs/shell.h libs/libft/./incs/libft.h \
  libs/libft/./incs/list.h libs/logger/./incs/logger.h \
  libs/logger/./incs/logger_utils.h incs/statuses.h incs/option.h \
  incs/job.h incs/termcaps/termcaps.h incs/termcaps/list_head.h \
  libs/libcaps/./incs/types.h incs/termcaps/log.h \
  incs/termcaps/termcaps_struct.h incs/termcaps/key.h \
  libs/libcaps/./incs/caps.h libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/lexer/tokenize.c\n"
		@$(CC) -c ./srcs/lexer/tokenize.c -o ./.objs/tokenize.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)termcaps_init.o: srcs/termcaps/termcaps_init.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/termcaps_init.c\n"
		@$(CC) -c ./srcs/termcaps/termcaps_init.c -o ./.objs/termcaps_init.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)termcaps_read_input.o: srcs/termcaps/termcaps_read_input.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/termcaps_read_input.c\n"
		@$(CC) -c ./srcs/termcaps/termcaps_read_input.c -o ./.objs/termcaps_read_input.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)termcaps_get_character_bytes_count.o: \
  srcs/termcaps/termcaps_get_character_bytes_count.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/termcaps_get_character_bytes_count.c\n"
		@$(CC) -c ./srcs/termcaps/termcaps_get_character_bytes_count.c -o ./.objs/termcaps_get_character_bytes_count.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)termcaps_string_to_command_line.o: \
  srcs/termcaps/termcaps_string_to_command_line.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/termcaps_string_to_command_line.c\n"
		@$(CC) -c ./srcs/termcaps/termcaps_string_to_command_line.c -o ./.objs/termcaps_string_to_command_line.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)termcaps_character_to_command_line.o: \
  srcs/termcaps/termcaps_character_to_command_line.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/termcaps_character_to_command_line.c\n"
		@$(CC) -c ./srcs/termcaps/termcaps_character_to_command_line.c -o ./.objs/termcaps_character_to_command_line.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)termcaps_display_command_line.o: \
  srcs/termcaps/termcaps_display_command_line.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/termcaps_display_command_line.c\n"
		@$(CC) -c ./srcs/termcaps/termcaps_display_command_line.c -o ./.objs/termcaps_display_command_line.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)termcaps_isunicode.o: srcs/termcaps/termcaps_isunicode.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/termcaps_isunicode.c\n"
		@$(CC) -c ./srcs/termcaps/termcaps_isunicode.c -o ./.objs/termcaps_isunicode.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)list_head.o: srcs/termcaps/list_head.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/list_head.c\n"
		@$(CC) -c ./srcs/termcaps/list_head.c -o ./.objs/list_head.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)list_head_command.o: srcs/termcaps/list_head_command.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/list_head_command.c\n"
		@$(CC) -c ./srcs/termcaps/list_head_command.c -o ./.objs/list_head_command.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)list_head_history.o: srcs/termcaps/list_head_history.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/list_head_history.c\n"
		@$(CC) -c ./srcs/termcaps/list_head_history.c -o ./.objs/list_head_history.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__backspace.o: srcs/termcaps/key__backspace.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__backspace.c\n"
		@$(CC) -c ./srcs/termcaps/key__backspace.c -o ./.objs/key__backspace.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__copy.o: srcs/termcaps/key__copy.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__copy.c\n"
		@$(CC) -c ./srcs/termcaps/key__copy.c -o ./.objs/key__copy.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__cursor_to_begin_of_line.o: \
  srcs/termcaps/key__cursor_to_begin_of_line.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__cursor_to_begin_of_line.c\n"
		@$(CC) -c ./srcs/termcaps/key__cursor_to_begin_of_line.c -o ./.objs/key__cursor_to_begin_of_line.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__cursor_to_end_of_line.o: srcs/termcaps/key__cursor_to_end_of_line.c \
  incs/shell.h libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__cursor_to_end_of_line.c\n"
		@$(CC) -c ./srcs/termcaps/key__cursor_to_end_of_line.c -o ./.objs/key__cursor_to_end_of_line.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__cursor_to_next_character.o: \
  srcs/termcaps/key__cursor_to_next_character.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__cursor_to_next_character.c\n"
		@$(CC) -c ./srcs/termcaps/key__cursor_to_next_character.c -o ./.objs/key__cursor_to_next_character.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__cursor_to_next_command.o: \
  srcs/termcaps/key__cursor_to_next_command.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__cursor_to_next_command.c\n"
		@$(CC) -c ./srcs/termcaps/key__cursor_to_next_command.c -o ./.objs/key__cursor_to_next_command.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__cursor_to_next_line.o: srcs/termcaps/key__cursor_to_next_line.c \
  incs/shell.h libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__cursor_to_next_line.c\n"
		@$(CC) -c ./srcs/termcaps/key__cursor_to_next_line.c -o ./.objs/key__cursor_to_next_line.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__cursor_to_next_word.o: srcs/termcaps/key__cursor_to_next_word.c \
  incs/shell.h libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__cursor_to_next_word.c\n"
		@$(CC) -c ./srcs/termcaps/key__cursor_to_next_word.c -o ./.objs/key__cursor_to_next_word.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__cursor_to_prev_character.o: \
  srcs/termcaps/key__cursor_to_prev_character.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__cursor_to_prev_character.c\n"
		@$(CC) -c ./srcs/termcaps/key__cursor_to_prev_character.c -o ./.objs/key__cursor_to_prev_character.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__cursor_to_prev_command.o: \
  srcs/termcaps/key__cursor_to_prev_command.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__cursor_to_prev_command.c\n"
		@$(CC) -c ./srcs/termcaps/key__cursor_to_prev_command.c -o ./.objs/key__cursor_to_prev_command.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__cursor_to_prev_line.o: srcs/termcaps/key__cursor_to_prev_line.c \
  incs/shell.h libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__cursor_to_prev_line.c\n"
		@$(CC) -c ./srcs/termcaps/key__cursor_to_prev_line.c -o ./.objs/key__cursor_to_prev_line.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__cursor_to_prev_word.o: srcs/termcaps/key__cursor_to_prev_word.c \
  incs/shell.h libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__cursor_to_prev_word.c\n"
		@$(CC) -c ./srcs/termcaps/key__cursor_to_prev_word.c -o ./.objs/key__cursor_to_prev_word.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__cut.o: srcs/termcaps/key__cut.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__cut.c\n"
		@$(CC) -c ./srcs/termcaps/key__cut.c -o ./.objs/key__cut.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__cut_to_end_of_line.o: srcs/termcaps/key__cut_to_end_of_line.c \
  incs/shell.h libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__cut_to_end_of_line.c\n"
		@$(CC) -c ./srcs/termcaps/key__cut_to_end_of_line.c -o ./.objs/key__cut_to_end_of_line.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__delete_command_line.o: srcs/termcaps/key__delete_command_line.c \
  incs/shell.h libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__delete_command_line.c\n"
		@$(CC) -c ./srcs/termcaps/key__delete_command_line.c -o ./.objs/key__delete_command_line.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__delete_under_cursor.o: srcs/termcaps/key__delete_under_cursor.c \
  incs/shell.h libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__delete_under_cursor.c\n"
		@$(CC) -c ./srcs/termcaps/key__delete_under_cursor.c -o ./.objs/key__delete_under_cursor.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__paste.o: srcs/termcaps/key__paste.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__paste.c\n"
		@$(CC) -c ./srcs/termcaps/key__paste.c -o ./.objs/key__paste.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__select.o: srcs/termcaps/key__select.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__select.c\n"
		@$(CC) -c ./srcs/termcaps/key__select.c -o ./.objs/key__select.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__send.o: srcs/termcaps/key__send.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__send.c\n"
		@$(CC) -c ./srcs/termcaps/key__send.c -o ./.objs/key__send.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__share.o: srcs/termcaps/key__share.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__share.c\n"
		@$(CC) -c ./srcs/termcaps/key__share.c -o ./.objs/key__share.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)key__share_words.o: srcs/termcaps/key__share_words.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/statuses.h incs/option.h incs/job.h incs/termcaps/termcaps.h \
  incs/termcaps/list_head.h libs/libcaps/./incs/types.h \
  incs/termcaps/log.h incs/termcaps/termcaps_struct.h \
  incs/termcaps/key.h libs/libcaps/./incs/caps.h \
  libs/libcaps/./incs/logger.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h incs/builtins/builtin.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/termcaps/key__share_words.c\n"
		@$(CC) -c ./srcs/termcaps/key__share_words.c -o ./.objs/key__share_words.o $(CPPFLAGS) $(CFLAGS) 


#end
