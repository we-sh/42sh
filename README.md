# weSH
Shell implementation

credits : @abombard, @jgigault, @gkuma, @anouvel


Branch     | Travis-CI status
-----------| ---
master     | [![Build Status](https://travis-ci.org/42shTests/42sh.svg?branch=master)](https://travis-ci.org/we-sh/42sh)
develop    | [![Build Status](https://travis-ci.org/42shTests/42sh.svg?branch=develop)](https://travis-ci.org/we-sh/42sh)

## Install & launch

## Makefile
#### custom rules
**libs** : build the internal libraries (located in ./libs/)

**fcleanlibs** : apply fclean rule to all internal libs (located in ./libs)

**test** : run the test suite located in ./test/

**submodule** : initialize the git submodules and pull the last version of master of all submodules

**norme** : check the norme of all the .c and .h files (excepted some)  

and all rules such as all, clean, fclean and re.

#### depend rule
The 'depend' rule create all the compilation rules including their dependencies.
Run ```make depend``` when :

+ adding a source file
+ changing the includes of a source file

The rule use ```gcc -MM```, because of it, the static header should be quoted (```#include "libft.h"```) and not ```#include <libft.h>```.

### Git workflow
The is the basic git workflow to work on the weSH repository :

+ setup the repository
```
$ git checkout master
$ git branch develop && git push -u origin develop
```
The base of the git workflow is to start working on `develop`, when the developer want to start a new job, he will create a new `feature` branch, and when the feature is achieved, he will merge it into `develop`. When `develop` accumulate enough features, the team will create a `release` branch if necessary, and merge `release` (or `develop`) into master.

+ create a new feature
```
$ git checkout develop
$ git pull origin develop
$ git checkout -b feature-<name>
($ git push --set-upstream feature-<name> origin/feature-<name>)
```
+ merging a feature into `develop`
```
$ git checkout develop
$ git pull origin develop
$ git merge feature-<name>
$ git push
$ git branch -d feature-<name>
# if necessary
$ git push origin --delete feature-<name>
```
+ creating a release
```
$ git checkout develop
$ git pull origin develop
$ git checkout -b release/<x.y.z> develop
# work on the release
```
+ incorporate the release into master
```
$ git checkout master
$ git merge release/<x.y.z>
$ git tag -a <x.y.z> -m <message>
$ git push && git push --tags
$ git checkout develop
$ git merge release/<x.y.z>
$ git push
$ git branch -d release/<x.y.z>
# if necessary
$ git push origin --delete release/<x.y.z>
```
+ incorporate the develop into master (if no release branch)
```
$ git checkout master
$ git merge develop
$ git tag -a <x.y.z> -m <message>
$ git push && git push --tags
```

# Development

## Coding convention

### C Coding

The prior code standard to be used in this project is the one from School 42 called `norme`. There is a binary called `norminette` - only available at school - that tells you if a file is code standard friendly (Use it with the option `-R CheckHeaders`). 

Here are the additional rules to be applied in this project:

- There must be only one non-static function per file.
- Filename must exactly match with the non-static function it declares (e.g. `parser.c` declares the function `int parser(...);`).
- Static functions must be prefixed by `s_` (e.g. `void s_do_something(void);`).
- Functions that returns true `1` or false `0` must be prefixed with `is_`, or `s_is_` if it is a static function (e.g. `int job_is_stopped(...);`).
- Non-static functions should mostly return a positive integer called "status". On success, a function should return the status `ST_OK`. The list of available statuses is described in the enumeration `e_status`.
- Each status of the enumeration `e_status` should be translated in each language described in the header "i18n.h".
- A single-character variable named `j` must be a `t_job` structure.
- A single-character variable named `p` must be a `t_proc` structure.

### Git workflow

- The default branch on Github is the `develop` branch.
- Each feature branch must start from `develop` branch and be linked with a PR on Github.
- The name of the PR must be prefixed by `[WIP]` (that means Work In Progress) during the development phase.
- When a code review is success, the feature branch is rebased on `develop` branch.
- When the list of new features is acceptable by the team `we-sh`, it can be merged on `master` branch.

### Submodules

#### Logger
The project includes the logger library, and its configured to display all log messages :

```logger_init(D_FATAL, "out.log");```

To see the output of the logging, run the following command in an other shell :

```$ tail -f out.log```

#### Libft

#### Libcaps

## Statuses

## Lists

## Main loop

## Job control

```c

struct                      s_job
{
    t_list                  list_job
    t_list                  proc_head;
    int                     id;
    char                    *command;
    int                     foreground;
    int                     launched;
    pid_t                   pgid;
    int                     exit_status;
    int                     notified;
    int                     is_interrupted;
    t_termios               tmodes;
    t_flag_job_separator    separator;
}                           t_job;

```

```c

struct                      s_proc
{
    t_list                  list_proc;
    t_job                   *j;
    char                    *command;
    int                     argc;
    char                    **argv;
    char                    **envp;
    int                     stdin;
    int                     stdout;
    int                     stderr;
    int                     is_valid;           // to be renamed
    pid_t                   pid;
    int                     exit_status;
    char                    completed;
    char                    stopped;
    char                    signaled;
    int                     bltin_status;
    char                    *bltin_char;
    t_list                  bltin_opt_head;
};
```

### Launching jobs

### Redirections

## Environment and local variables

## Parser

```c
int     parser( t_sh         *shell_configuration,
                char const   *input,
                int          parsing_mode,
                t_list       *target_list_head     ); 
```

### Parsing modes

#### `F_PARSING_TERMCAPS`

#### `F_PARSING_NONE`

#### `F_PARSING_JOBS`

#### `F_PARSING_PROCS`

#### `F_PARSING_GLOBING`

#### `F_PARSING_PATHEXP`


## Built-in Utilities

```c
int     builtin_template( t_builtin const   *builtin_configuration,
                          int               callback_code,
                          t_sh              *shell_configuration,
                          t_proc            *process                );
```

### Callbacks

#### `BLTIN_CB_BEFORE`

#### `BLTIN_CB_EXEC`

#### `BLTIN_CB_AFTER`

## Options

## Termcaps

## Internationalization
