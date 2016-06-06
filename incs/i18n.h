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
	[ST_TCSETATTR] = "impossible de modifier la configuration du terminal",
	[ST_SIGNAL] = "impossible d'intercepter le signal",
	[ST_SIGCONT] = "impossible de relancer le job",
	[ST_NOT_A_BUILTIN] = NULL,
	[ST_EXIT] = NULL,
	[ST_CHDIR] = "imposible de changer de répertoire courant",
	[ST_ENOENT] = "fichier ou dossier introuvable",
	[ST_EINVAL] = "argument invalide",
	[ST_E2BIG] = "liste des arguments trop longue",
	[ST_E2SMALL] = "liste des arguments trop courte",
	[ST_NAN] = "argument de type numérique attendu",
	[ST_BLTIN_CD] = "change le répertoire courant",
	[ST_BLTIN_CD_OPT_P2] = "résoudre les liens symboliques",
	[ST_BLTIN_EXIT] = "quitte le shell avec le status N",
	[ST_BLTIN_HELP] = "montre le manuel d'un builtin",
	[ST_BLTIN_JOBS] = "affiche le status des jobs de la session courante",
	[ST_BLTIN_JOBS_OPT_L] = "affiche plus d'informations sur les jobs",
	[ST_BLTIN_JOBS_OPT_P] = "affiche seulement les IDs maîtres",
	[ST_BLTIN_SETENV] = "est utilisé pour initialiser ou modifier une variable d'environnement",
	[ST_BLTIN_ENV] = "est utilisé pour afficher les variables d'environnement",
	[ST_BLTIN_ENV_OPT_I] = "est utilisé pour envoyer un environnement NULL a un programme",
	[ST_BLTIN_SETENV_ALPHA_NUM] = "Le nom de variable doit contenir des characters alphanumeric.",
	[ST_BLTIN_SETENV_FIRST_CHAR] = "Le nom de variable doit commencer avec une lettre.",
	[ST_BLTIN_SETENV_TMANY_ARGV] = "setenv: trop d'arguments",
	[ST_BLTIN_UNSETENV] = "est utilisé pour supprimer une variable d'environnement",
	[ST_OPTION_C] = "lire les commandes à partir de STRING",
	[ST_OPTION_HELP] = "affiche le manuel du shell",
	[ST_DONE] = "terminé",
	[ST_RUNNING] = "en cours",
	[ST_STOPPED] = "suspendu",
	[ST_TERMINATED] = "interrompu",
	[ST_USAGE] = "mode d'emploi",
	[ST_TERMCAPS_INIT] = "erreur lors de l'initialisation des termcaps",
	[ST_OPTIONS] = "options"
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
	[ST_TCSETPGRP] = "failed setting the job to control the terminal",
	[ST_TCSETATTR] = "failed updating the terminal configuration",
	[ST_SIGNAL] = "failed catching signal",
	[ST_SIGCONT] = "failed continuing job",
	[ST_NOT_A_BUILTIN] = NULL,
	[ST_EXIT] = NULL,
	[ST_CHDIR] = "failed changing current directory",
	[ST_ENOENT] = "no such file or directory",
	[ST_EINVAL] = "invalid argument",
	[ST_E2BIG] = "argument list too long",
	[ST_E2SMALL] = "argument list too small",
	[ST_NAN] = "numeric argument required",
	[ST_BLTIN_CD] = "change the current directory",
	[ST_BLTIN_CD_OPT_P2] = "do not follow symbolic links",
	[ST_BLTIN_EXIT] = "cause the shell to exit with a status of N",
	[ST_BLTIN_HELP] = "show the manual of a builtin",
	[ST_BLTIN_JOBS] = "display status of jobs in the current session",
	[ST_BLTIN_JOBS_OPT_L] = "provide more information about each job listed",
	[ST_BLTIN_JOBS_OPT_P] = "display only the leaders process IDs",
	[ST_BLTIN_ENV] = "is used to display environment variables",
	[ST_BLTIN_ENV_OPT_I] = "is used to send empties environment variables to a program",
	[ST_BLTIN_SETENV] = "Is used to initialize or modify an environment variable",
	[ST_BLTIN_SETENV_ALPHA_NUM] = "Variable name must contain alphanumeric characters.",
	[ST_BLTIN_SETENV_FIRST_CHAR] = "Variable name must begin with a letter.",
	[ST_BLTIN_SETENV_TMANY_ARGV] = "setenv: too many arguments",
	[ST_BLTIN_UNSETENV] = "Is used to delete an environment variable",
	[ST_OPTION_C] = "read commands from STRING",
	[ST_OPTION_HELP] = "show the manual of the shell",
	[ST_DONE] = "done",
	[ST_RUNNING] = "running",
	[ST_STOPPED] = "suspended",
	[ST_TERMINATED] = "terminated",
	[ST_USAGE] = "usage",
	[ST_TERMCAPS_INIT] = "failed to initialize termcaps",
	[ST_OPTIONS] = "options"
};

static const char		**g_i18n_translations[] = {
	[LANG_EN] = g_i18n_en,
	[LANG_FR] = g_i18n_fr
};

#endif
