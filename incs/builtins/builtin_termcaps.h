#ifndef BUILTIN_TERMCAPS_H
# define BUILTIN_TERMCAPS_H

# include "builtin.h"

static const char			*g_builtin_termcaps_usage_multiline[] = {
	[0] = "-----------------------------------------------",
	[1] = "|CTR-A : Go to the beginning of the command line",
	[2] = "|CTR-E : Go to the end of the command line",
	[3] = "|CTR-R : Find a command inside the historic",
	[4] = "|CTR-W : Cut the end of the commande line",
	[5] = "|CTR-D : Delete the current caractere",
	[6] = "|CTR-Q : Delete the line",
	[7] = "|CTR-K : Delete the end of the line",
	[8] = "|CTR-C : Delete the line and print a new prompt",
	[9] = "|CTR/MAJ-LEFT : Move to the word on the left",
	[10] = "|CTR/MAJ-RIGHT : Move to the word on the right",
	[11] = "|CTR/MAJ-UP : Move the cursor up if a line exist",
	[12] = "|CTR/MAJ-DOWN : Move the cursor down if a line exist",
	[13] = "|CTR/MAJ-SPACE : SELECTION MODE",
	[14] = "|CTR-X : SELECTION MODE Copy your selection",
	[15] = "|CTR-W : SELECTION MODE Cut your selection",
	[16] = "|CTR-Y : SELECTION MODE Past your selection",
	[17] = "|TAB : <3 AUTO-completion <3",
	[18] = "|HOME : Go to the beginning of the command line",
	[19] = "|END : Go to the end of the command line",
	[20] = "-----------------------------------------------",
	[21] = NULL
};

static const t_builtin		g_builtin_termcaps = {
	.index = BLTIN_TERMCAPS,
	.name = "Termcaps",
	.usage = "Here is a list of all termcaps available for the user",
	.usage_multiline = g_builtin_termcaps_usage_multiline,
	.description = ST_BLTIN_TERMCAPS,
	.exe = &builtin_termcaps,
	.options = NULL
};

#endif
