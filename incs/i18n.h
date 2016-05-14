#ifndef I18N_H
# define I18N_H

# include "statuses.h"

/*
** This file contains translations for each status message
**
** The enumeration `e_language` contains the list of available languages
** LANG_GET must be at top of the enumeration and set to 0
** LANG_TOTAL must be at bottom to represent the count of languages
**
** Each language is associated to a static const char[] suffixed with `g_i18n_`
** The first key `ST_OK`, or 0, must contain the name of the described language
**
** Use the function i18n_translate(int *status) to get a translation at runtime
*/

typedef enum			e_language
{
	LANG_GET = 0,
	LANG_EN,
	LANG_FR,
	LANG_TOTAL
}						t_language;

static const char		*g_i18n_fr[] = {
	[ST_OK] = "Français",
	[ST_SETPGID] = "impossible d'associer le PID à un groupe",
	[ST_OPEN] = "impossible d'ouvrir le descripteur de fichier",
	[ST_READ] = "impossible de lire le descripteur de fichier",
	[ST_FORK] = "impossible de dupliquer le processus actuel",
	[ST_PIPE] = "impossible de créer le pipe",
	[ST_TTYNAME] = "impossible de récupérer le nom de l'interface du fd",
	[ST_MALLOC] = "allocation de memoire impossible",
	[ST_TCSETPGRP] = "impossible d'associer le PID à l'interface du terminal"
};

static const char		*g_i18n_en[] = {
	[ST_OK] = "English",
	[ST_SETPGID] = "unable to set the process group of the PID",
	[ST_OPEN] = "failed opening file descriptor",
	[ST_READ] = "failed reading file descriptor",
	[ST_FORK] = "failed copying the calling process",
	[ST_PIPE] = "failed creating a pipe",
	[ST_TTYNAME] = "failed getting the related device name of the fd",
	[ST_MALLOC] = "memory allocation failed",
	[ST_TCSETPGRP] = "failed setting the PID with the terminal device"
};

static const char		**g_i18n_translations[] = {
	[LANG_EN] = g_i18n_en,
	[LANG_FR] = g_i18n_fr
};

#endif
