#ifndef LOG_H
# define LOG_H

# include <stdio.h>
# include "types.h"

# define LF ":%s:%s():%d#"
# define LA __FILE__, __func__, __LINE__

# define LOG_ERROR(FMT,...) fprintf(stdout,"FATAL"LF FMT"\n",LA,__VA_ARGS__)
# define LOG_WARNING(FMT,...) fprintf(stdout,"WARNING"LF FMT"\n",LA,__VA_ARGS__)
# define LOG_DEBUG(FMT,...) fprintf(stdout,"DEBUG"LF FMT"\n",LA,__VA_ARGS__)

# define FATAL(FMT, ...) do{LOG_ERROR(FMT,__VA_ARGS__);return 0;}while (0)

# define ASSERT(expr) if (!(expr)) FATAL("(%s) failed\r", #expr)

#endif
