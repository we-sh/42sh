#ifndef FNVHEAD32_H
# define FNVHEAD32_H

# include <stdint.h>

typedef uint32_t	t_fnv;

# define FNV_PRIME	((t_fnv)16777619)
# define FNV0_INIT	((t_fnv)0)
# define FNV1_INIT	((t_fnv)0x811c9dc5)

#endif
