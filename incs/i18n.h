#ifndef I18N_H
# define I18N_H

# include "statuses.h"

/*
** This file contains the translations of each status message.
**
** The enumeration `e_language` contains the list of available languages.
** LANG_GET must be at top of the enumeration and set to 0.
** LANG_TOTAL must be at bottom to represent the count of languages.
**
** Each language is associated to a static const char[] suffixed with `g_i18n_`.
** The first key `ST_OK`, or 0, must contain the name of the described language.
**
** Use the function i18n_translate(int *status) to get a translation at runtime.
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
	[ST_PIPE] = "impossible de créer le tube",
	[ST_TTYNAME] = "impossible de récupérer le nom de l'interface du fd",
	[ST_MALLOC] = "allocation de memoire impossible",
	[ST_TCSETPGRP] = "impossible d'associer le PID à l'interface du terminal",
	[ST_SIGNAL] = "impossible d'intercepter le signal",
	[ST_NOT_A_BUILTIN] = NULL,
	[ST_CHDIR] = "imposible de changer de répertoire courant",
	[ST_ENOENT] = "fichier ou dossier introuvable",
	[ST_EINVAL] = "argument invalide",
	[ST_E2BIG] = "liste des arguments trop longue",
	[ST_BLTIN_CD] = "change le répertoire courant avec DIR",
	[ST_BLTIN_CD_OPT_P2] = "résoudre les liens symboliques",
	[ST_BLTIN_HELP] = "montre le manuel de BUILTIN",
	[ST_BLTIN_JOBS] = "affiche le status des jobs de la session courante",
	[ST_BLTIN_JOBS_OPT_L] = "affiche plus d'informations sur les jobs",
	[ST_BLTIN_JOBS_OPT_P] = "affiche seulement les IDs maîtres",
	[ST_DONE] = "terminé",
	[ST_RUNNING] = "en cours",
	[ST_USAGE] = "mode d'emploi"
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
	[ST_TCSETPGRP] = "failed setting the PID with the terminal device",
	[ST_SIGNAL] = "failed catching signal",
	[ST_NOT_A_BUILTIN] = NULL,
	[ST_CHDIR] = "failed changing current directory",
	[ST_ENOENT] = "no such file or directory",
	[ST_EINVAL] = "invalid argument",
	[ST_E2BIG] = "argument list too long",
	[ST_BLTIN_CD] = "change the current directory to DIR",
	[ST_BLTIN_CD_OPT_P2] = "do not follow symbolic links",
	[ST_BLTIN_HELP] = "show the manual of BUILTIN",
	[ST_BLTIN_JOBS] = "display status of jobs in the current session",
	[ST_BLTIN_JOBS_OPT_L] = "provide more information about each job listed",
	[ST_BLTIN_JOBS_OPT_P] = "display only the leaders process IDs",
	[ST_DONE] = "done",
	[ST_RUNNING] = "running",
	[ST_USAGE] = "usage"
};

static const char		**g_i18n_translations[] = {
	[LANG_EN] = g_i18n_en,
	[LANG_FR] = g_i18n_fr
};

#endif
