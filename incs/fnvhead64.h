#ifndef FNVHEAD64_H
# define FNVHEAD64_H

# include <stdint.h>

typedef uint64_t	t_fnv;

# define FNV_PRIME	((t_fnv)1099511628211)
# define FNV0_INIT	((t_fnv)0)
# define FNV1_INIT	((t_fnv)0xcbf29ce484222325ULL)

#endif
