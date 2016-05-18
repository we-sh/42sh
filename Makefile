# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anouvel <adrien.nouvel@outlook.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/30 13:39:33 by anouvel           #+#    #+#              #
#    Updated: 2016/05/26 14:20:48 by anouvel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------------------------------------- #
# PROJECT DATA
# ---------------------------------------------------------------------------- #

NAME		=	42sh

# ---------------------------------------------------------------------------- #

SRCS		=	\
				main.c							\
				exit/shell_exit.c				\
				i18n/i18n_translate.c			\
				init/shell_fd.c					\
				init/shell_init.c				\
				init/shell_is_interactive.c		\
				init/shell_language.c			\
				stdin_loop.c					\
				parse.c							\
				job/job_alloc.c					\
				job/job_foreground.c			\
				job/job_is_completed.c			\
				job/job_launch.c				\
				job/proc_find.c					\
				job/proc_launch.c				\
				job/proc_update_status.c		\
				list/list_node__proc_alloc.c	\
				signal/signal_sigchld.c			\
				signal/signal_to_default.c		\
				signal/signal_to_ignore.c		\
				lexer/lexer.c					\
				lexer/token_list.c				\
				lexer/tokenize.c				\

# ---------------------------------------------------------------------------- #
# PROJECT CONFIGURATION
# ---------------------------------------------------------------------------- #

CFLAGS		=	\
				-g 								\
				-Wall -Wextra -Werror			\

# >>> REQUIRED FOR LIBRARIES >>> THINK ABOUT CHANGING THE *LIBS rules

CPPFLAGS	=	\
				-I $(DIRINC)					\
				-I $(DIRLIB)libft/$(DIRINC)		\
				-I $(DIRLIB)logger/$(DIRINC)	\
				-I $(DIRLIB)libcaps/$(DIRINC)	\

LDFLAGS		=	\
				-L $(DIRLIB)libft				\
				-L $(DIRLIB)logger				\
				-L $(DIRLIB)libcaps				\

LDLIBS		=	\
				-lft							\
				-llogger						\
				-lcaps							\

# GLOBAL SETUP
AR			=	ar
CC			=	clang
RM			=	rm
MKDIR		=	mkdir
MAKE		=	make

DIRSRC		=	./srcs/
DIROBJ		=	./.objs/
DIRINC		=	./incs/
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
	@cd $(DIRTST) && sh 42shTests.sh $$PWD/../$(NAME) --hard

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
  libs/logger/./incs/logger_utils.h incs/job.h incs/statuses.h \
  incs/i18n.h libs/libft/./incs/get_next_line.h incs/lexer.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/main.c\n"
		@$(CC) -c ./srcs/main.c -o ./.objs/main.o $(CPPFLAGS) $(CFLAGS)

$(DIROBJ)shell_exit.o: srcs/exit/shell_exit.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/job.h incs/statuses.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/exit/shell_exit.c\n"
		@$(CC) -c ./srcs/exit/shell_exit.c -o ./.objs/shell_exit.o $(CPPFLAGS) $(CFLAGS)

$(DIROBJ)i18n_translate.o: srcs/i18n/i18n_translate.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/job.h incs/statuses.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/i18n/i18n_translate.c\n"
		@$(CC) -c ./srcs/i18n/i18n_translate.c -o ./.objs/i18n_translate.o $(CPPFLAGS) $(CFLAGS)

$(DIROBJ)shell_fd.o: srcs/init/shell_fd.c incs/shell.h libs/libft/./incs/libft.h \
  libs/libft/./incs/list.h libs/logger/./incs/logger.h \
  libs/logger/./incs/logger_utils.h incs/job.h incs/statuses.h \
  incs/i18n.h libs/libft/./incs/get_next_line.h incs/lexer.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/init/shell_fd.c\n"
		@$(CC) -c ./srcs/init/shell_fd.c -o ./.objs/shell_fd.o $(CPPFLAGS) $(CFLAGS)

$(DIROBJ)shell_init.o: srcs/init/shell_init.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/job.h incs/statuses.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/init/shell_init.c\n"
		@$(CC) -c ./srcs/init/shell_init.c -o ./.objs/shell_init.o $(CPPFLAGS) $(CFLAGS)

$(DIROBJ)shell_is_interactive.o: srcs/init/shell_is_interactive.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/job.h incs/statuses.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/init/shell_is_interactive.c\n"
		@$(CC) -c ./srcs/init/shell_is_interactive.c -o ./.objs/shell_is_interactive.o $(CPPFLAGS) $(CFLAGS)

$(DIROBJ)shell_language.o: srcs/init/shell_language.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/job.h incs/statuses.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/init/shell_language.c\n"
		@$(CC) -c ./srcs/init/shell_language.c -o ./.objs/shell_language.o $(CPPFLAGS) $(CFLAGS)

$(DIROBJ)stdin_loop.o: srcs/stdin_loop.c incs/shell.h libs/libft/./incs/libft.h \
  libs/libft/./incs/list.h libs/logger/./incs/logger.h \
  libs/logger/./incs/logger_utils.h incs/job.h incs/statuses.h \
  incs/i18n.h libs/libft/./incs/get_next_line.h incs/lexer.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/stdin_loop.c\n"
		@$(CC) -c ./srcs/stdin_loop.c -o ./.objs/stdin_loop.o $(CPPFLAGS) $(CFLAGS)

$(DIROBJ)parse.o: srcs/parse.c incs/shell.h libs/libft/./incs/libft.h \
  libs/libft/./incs/list.h libs/logger/./incs/logger.h \
  libs/logger/./incs/logger_utils.h incs/job.h incs/statuses.h \
  incs/i18n.h libs/libft/./incs/get_next_line.h incs/lexer.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parse.c\n"
		@$(CC) -c ./srcs/parse.c -o ./.objs/parse.o $(CPPFLAGS) $(CFLAGS)

$(DIROBJ)job_alloc.o: srcs/job/job_alloc.c incs/shell.h libs/libft/./incs/libft.h \
  libs/libft/./incs/list.h libs/logger/./incs/logger.h \
  libs/logger/./incs/logger_utils.h incs/job.h incs/statuses.h \
  incs/i18n.h libs/libft/./incs/get_next_line.h incs/lexer.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/job_alloc.c\n"
		@$(CC) -c ./srcs/job/job_alloc.c -o ./.objs/job_alloc.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)job_foreground.o: srcs/job/job_foreground.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/job.h incs/statuses.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/job_foreground.c\n"
		@$(CC) -c ./srcs/job/job_foreground.c -o ./.objs/job_foreground.o $(CPPFLAGS) $(CFLAGS)

$(DIROBJ)job_is_completed.o: srcs/job/job_is_completed.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/job.h incs/statuses.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/job_is_completed.c\n"
		@$(CC) -c ./srcs/job/job_is_completed.c -o ./.objs/job_is_completed.o $(CPPFLAGS) $(CFLAGS)

$(DIROBJ)job_launch.o: srcs/job/job_launch.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/job.h incs/statuses.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/job_launch.c\n"
		@$(CC) -c ./srcs/job/job_launch.c -o ./.objs/job_launch.o $(CPPFLAGS) $(CFLAGS)

$(DIROBJ)proc_find.o: srcs/job/proc_find.c incs/shell.h libs/libft/./incs/libft.h \
  libs/libft/./incs/list.h libs/logger/./incs/logger.h \
  libs/logger/./incs/logger_utils.h incs/job.h incs/statuses.h \
  incs/i18n.h libs/libft/./incs/get_next_line.h incs/lexer.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/proc_find.c\n"
		@$(CC) -c ./srcs/job/proc_find.c -o ./.objs/proc_find.o $(CPPFLAGS) $(CFLAGS)

$(DIROBJ)proc_launch.o: srcs/job/proc_launch.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/job.h incs/statuses.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/proc_launch.c\n"
		@$(CC) -c ./srcs/job/proc_launch.c -o ./.objs/proc_launch.o $(CPPFLAGS) $(CFLAGS)

$(DIROBJ)proc_update_status.o: srcs/job/proc_update_status.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/job.h incs/statuses.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/proc_update_status.c\n"
		@$(CC) -c ./srcs/job/proc_update_status.c -o ./.objs/proc_update_status.o $(CPPFLAGS) $(CFLAGS)

$(DIROBJ)list_node__proc_alloc.o: srcs/list/list_node__proc_alloc.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/job.h incs/statuses.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/list/list_node__proc_alloc.c\n"
		@$(CC) -c ./srcs/list/list_node__proc_alloc.c -o ./.objs/list_node__proc_alloc.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)signal_sigchld.o: srcs/signal/signal_sigchld.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/job.h incs/statuses.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/signal/signal_sigchld.c\n"
		@$(CC) -c ./srcs/signal/signal_sigchld.c -o ./.objs/signal_sigchld.o $(CPPFLAGS) $(CFLAGS)

$(DIROBJ)signal_to_default.o: srcs/signal/signal_to_default.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/job.h incs/statuses.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/signal/signal_to_default.c\n"
		@$(CC) -c ./srcs/signal/signal_to_default.c -o ./.objs/signal_to_default.o $(CPPFLAGS) $(CFLAGS)

$(DIROBJ)signal_to_ignore.o: srcs/signal/signal_to_ignore.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/job.h incs/statuses.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/signal/signal_to_ignore.c\n"
		@$(CC) -c ./srcs/signal/signal_to_ignore.c -o ./.objs/signal_to_ignore.o $(CPPFLAGS) $(CFLAGS)

$(DIROBJ)lexer.o: srcs/lexer/lexer.c incs/shell.h libs/libft/./incs/libft.h \
  libs/libft/./incs/list.h libs/logger/./incs/logger.h \
  libs/logger/./incs/logger_utils.h incs/job.h incs/statuses.h \
  incs/i18n.h libs/libft/./incs/get_next_line.h incs/lexer.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/lexer/lexer.c\n"
		@$(CC) -c ./srcs/lexer/lexer.c -o ./.objs/lexer.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)token_list.o: srcs/lexer/token_list.c incs/shell.h \
  libs/libft/./incs/libft.h libs/libft/./incs/list.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/job.h incs/statuses.h incs/i18n.h \
  libs/libft/./incs/get_next_line.h incs/lexer.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/lexer/token_list.c\n"
		@$(CC) -c ./srcs/lexer/token_list.c -o ./.objs/token_list.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)tokenize.o: srcs/lexer/tokenize.c incs/shell.h libs/libft/./incs/libft.h \
  libs/libft/./incs/list.h libs/logger/./incs/logger.h \
  libs/logger/./incs/logger_utils.h incs/job.h incs/statuses.h \
  incs/i18n.h libs/libft/./incs/get_next_line.h incs/lexer.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/lexer/tokenize.c\n"
		@$(CC) -c ./srcs/lexer/tokenize.c -o ./.objs/tokenize.o $(CPPFLAGS) $(CFLAGS) 


#end
