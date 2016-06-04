#include "shell.h"

/*
** Get the byte count of the next character
*/

#define UNICODE_MASK_0 192
#define UNICODE_MASK_1 224
#define UNICODE_MASK_2 240

size_t		termcaps_get_character_bytes_count(const size_t input_bytes_count,
												const char *input_bytes,
												size_t *out_missing_bytes_count)
{
	size_t	expected_bytes_count;

	*out_missing_bytes_count = 0;
	if (!input_bytes_count)
		return (0);
	expected_bytes_count = 1;
	if ((input_bytes[0] & UNICODE_MASK_0) == UNICODE_MASK_0)
		expected_bytes_count++;
	if ((input_bytes[0] & UNICODE_MASK_1) == UNICODE_MASK_1)
		expected_bytes_count++;
	if ((input_bytes[0] & UNICODE_MASK_2) == UNICODE_MASK_2)
		expected_bytes_count++;
	if (expected_bytes_count > input_bytes_count)
	{
		*out_missing_bytes_count = expected_bytes_count - input_bytes_count;
		return (input_bytes_count);
	}
	return (expected_bytes_count);
}
