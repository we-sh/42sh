#ifndef BUILTIN_TERMCAPS_H
# define BUILTIN_TERMCAPS_H

# include "builtin.h"

static const char			*g_builtin_termcaps_usage_multiline[] = {
	[0] = "-----------------------------------------------",
	[1] = "|CTR-A : Go to the beginning of the command line",
	[2] = "|CTR-E : Go to the end of the command line",
	[3] = "|CTR-R : Find a command inside the historic",
	[4] = "|CTR-W : Cut the prev word of the commande line",
	[5] = "|CTR-D : Delete the current caractere",
	[6] = "|CTR-Q : Delete the line",
	[7] = "|CTR-K : Delete the end of the line",
	[8] = "|CTR-L : Clear the screen",
	[9] = "|CTR-C : Delete the line and print a new prompt",
	[10] = "|CTR/MAJ-LEFT : Move to the word on the left",
	[11] = "|CTR/MAJ-RIGHT : Move to the word on the right",
	[12] = "|CTR/MAJ-UP : Move the cursor up if a line exist",
	[13] = "|CTR/MAJ-DOWN : Move the cursor down if a line exist",
	[14] = "|\e[94mCTR/MAJ-SPACE : SELECTION MODE\e[0m",
	[15] = "|\e[94mCTR-X : SELECTION MODE Copy your selection\e[0m",
	[16] = "|\e[94mCTR-W : SELECTION MODE Cut your selection\e[0m",
	[17] = "|\e[94mCTR-Q : SELECTION MODE Delete your selection\e[0m",
	[18] = "|CTR-Y : Past your selection",
	[19] = "|TAB : \e[31m<3\e[0m AUTO-completion \e[31m<3\e[0m",
	[20] = "|HOME : Go to the beginning of the command line",
	[21] = "|END : Go to the end of the command line",
	[22] = "-----------------------------------------------",
	[23] = NULL
};

static const t_builtin		g_builtin_termcaps = {
	.index = BLTIN_TERMCAPS,
	.name = "termcaps",
	.usage = "Here is a list of all termcaps available for the user",
	.usage_multiline = g_builtin_termcaps_usage_multiline,
	.description = ST_BLTIN_TERMCAPS,
	.exe = &builtin_termcaps,
	.options = NULL
};

#endif
