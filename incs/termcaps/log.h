#ifndef LOG_H
# define LOG_H

# define ASSERT(expr) if (!(expr)){log_fatal("(%s) failed\r",#expr);return 0;}

#endif
