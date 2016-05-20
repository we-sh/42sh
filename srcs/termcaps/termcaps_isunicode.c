#include "shell.h"

# define ISUTF(c) (((c) & 0xc0) != 0x80)

int	termcaps_isunicode(const char c, size_t *out_character_bytes_count)
{
	size_t		character_missing_bytes_count;

	termcaps_get_character_bytes_count(1, &c, &character_missing_bytes_count);
	if (ISUTF(c) && character_missing_bytes_count > 0 &&\
		character_missing_bytes_count < 4)
	{
		*out_character_bytes_count = character_missing_bytes_count;
		return (1);
	}
	return (0);
}