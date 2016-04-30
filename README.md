# 42sh
Shell implementation

credits : @jgigault, @gkuma, @anouvel


Branch     | Travis-CI status
-----------| ---
master     | [![Build Status](https://travis-ci.org/42shTests/42sh.svg?branch=master)](https://travis-ci.org/42shTests/42sh)
develop    | [![Build Status](https://travis-ci.org/42shTests/42sh.svg?branch=develop)](https://travis-ci.org/42shTests/42sh)



### Makefile
#### custom rules
**libs** : build the internal libraries (located in ./libs/)
**fcleanlibs** : apply fclean rule to all internal libs (located in ./libs)
**test** : run the test suite located in ./test/
**submodule** : pull the last version of master of all submodules
**norme** : check the norme of all the .c and .h files (excepted some)  

and all rules such as all, clean, fclean and re.

#### depend rule
The 'depend' rule create all the compilation rules including their dependencies.
Run ```make depend``` when :

+ adding a source file
+ changing the includes of a source file

The rule use ```gcc -MM```, because of it, the static header should be quoted (```#include "libft.h"```) and not ```#include <libft.h>```.

### Git workflow
The is the basic git workflow to work on the 42sh repository :

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
