# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anouvel <adrien.nouvel@outlook.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/30 13:39:33 by anouvel           #+#    #+#              #
#    Updated: 2016/05/09 19:55:43 by anouvel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------------------------------------- #
# PROJECT DATA
# ---------------------------------------------------------------------------- #

NAME		=	42sh

# ---------------------------------------------------------------------------- #

SRCS		=	\
				main.c							\
				init/shell_init.c				\
				init/shell_is_interactive.c		\
				stdin_loop.c					\
				parse.c							\
				job/job_launch.c				\
				job/proc_launch.c				\

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

LDFLAGS		=	\
				-L $(DIRLIB)libft				\
				-L $(DIRLIB)logger				\

LDLIBS		=	\
				-lft							\
				-llogger						\

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

fcleanlibs	:
	@make -C $(DIRLIB)libft fclean
	@make -C $(DIRLIB)logger fclean

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
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/types.h incs/job.h incs/statuses.h \
  libs/libft/./incs/get_next_line.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/main.c\n"
		@$(CC) -c ./srcs/main.c -o ./.objs/main.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)shell_init.o: srcs/init/shell_init.c incs/shell.h \
  libs/libft/./incs/libft.h libs/logger/./incs/logger.h \
  libs/logger/./incs/logger_utils.h incs/types.h incs/job.h \
  incs/statuses.h libs/libft/./incs/get_next_line.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/init/shell_init.c\n"
		@$(CC) -c ./srcs/init/shell_init.c -o ./.objs/shell_init.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)shell_is_interactive.o: srcs/init/shell_is_interactive.c incs/shell.h \
  libs/libft/./incs/libft.h libs/logger/./incs/logger.h \
  libs/logger/./incs/logger_utils.h incs/types.h incs/job.h \
  incs/statuses.h libs/libft/./incs/get_next_line.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/init/shell_is_interactive.c\n"
		@$(CC) -c ./srcs/init/shell_is_interactive.c -o ./.objs/shell_is_interactive.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)stdin_loop.o: srcs/stdin_loop.c incs/shell.h libs/libft/./incs/libft.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/types.h incs/job.h incs/statuses.h \
  libs/libft/./incs/get_next_line.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/stdin_loop.c\n"
		@$(CC) -c ./srcs/stdin_loop.c -o ./.objs/stdin_loop.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)parse.o: srcs/parse.c incs/shell.h libs/libft/./incs/libft.h \
  libs/logger/./incs/logger.h libs/logger/./incs/logger_utils.h \
  incs/types.h incs/job.h incs/statuses.h \
  libs/libft/./incs/get_next_line.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/parse.c\n"
		@$(CC) -c ./srcs/parse.c -o ./.objs/parse.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)job_launch.o: srcs/job/job_launch.c incs/shell.h \
  libs/libft/./incs/libft.h libs/logger/./incs/logger.h \
  libs/logger/./incs/logger_utils.h incs/types.h incs/job.h \
  incs/statuses.h libs/libft/./incs/get_next_line.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/job_launch.c\n"
		@$(CC) -c ./srcs/job/job_launch.c -o ./.objs/job_launch.o $(CPPFLAGS) $(CFLAGS) 

$(DIROBJ)proc_launch.o: srcs/job/proc_launch.c incs/shell.h \
  libs/libft/./incs/libft.h libs/logger/./incs/logger.h \
  libs/logger/./incs/logger_utils.h incs/types.h incs/job.h \
  incs/statuses.h libs/libft/./incs/get_next_line.h
		@printf "$(C_GRE)[ 42sh ] [ %-6s ]$(C_DFL) " "clang"
		@printf "compiling ./srcs/job/proc_launch.c\n"
		@$(CC) -c ./srcs/job/proc_launch.c -o ./.objs/proc_launch.o $(CPPFLAGS) $(CFLAGS) 


#end
