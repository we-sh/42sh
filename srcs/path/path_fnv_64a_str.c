#include <stdlib.h>
#include "fnv.h"
#include "longlong.h"

/*
* hash_64 - 64 bit Fowler/Noll/Vo-0 FNV-1a hash code
*
* @(#) $Revision: 5.1 $
* @(#) $Id: hash_64a.c,v 5.1 2009/06/30 09:01:38 chongo Exp $
* @(#) $Source: /usr/local/src/cmd/fnv/RCS/hash_64a.c,v $
*
*
* Fowler/Noll/Vo hash
*
* The basis of this hash algorithm was taken from an idea sent
* as reviewer comments to the IEEE POSIX P1003.2 committee by:
*
*      Phong Vo (http://www.research.att.com/info/kpv/)
*      Glenn Fowler (http://www.research.att.com/~gsf/)
*
* In a subsequent ballot round:
*
*      Landon Curt Noll (http://www.isthe.com/chongo/)
*
* improved on their algorithm.  Some people tried this hash
* and found that it worked rather well.  In an EMail message
* to Landon, they named it the ``Fowler/Noll/Vo'' or FNV hash.
*
* FNV hashes are designed to be fast while maintaining a low
* collision rate. The FNV speed allows one to quickly hash lots
* of data while maintaining a reasonable collision rate.  See:
*
*      http://www.isthe.com/chongo/tech/comp/fnv/index.html
*
* for more details as well as other forms of the FNV hash.
*
*
* To use the recommended 64 bit FNV-1a hash, pass FNV1A_64_INIT as the
* Fnv64_t hashval argument to fnv_64a_buf() or fnv_64a_str().
*
*
* Please do not copyright this code.  This code is in the public domain.
*
* LANDON CURT NOLL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
* INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO
* EVENT SHALL LANDON CURT NOLL BE LIABLE FOR ANY SPECIAL, INDIRECT OR
* CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
* USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
* OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
* PERFORMANCE OF THIS SOFTWARE.
*
* By:
*	chongo <Landon Curt Noll> /\oo/\
*      http://www.isthe.com/chongo/
*
* Share and Enjoy!	:-)
* FNV-1a defines the initial basis to be non-zero
*/

#if !defined(HAVE_64BIT_LONG_LONG)

const Fnv64_t g_fnv1a_64_init = { 0x84222325, 0xcbf29ce4 };

#endif

Fnv64_t					fnv_64a_str(char *str)
{
	unsigned char		*s;
	Fnv64_t				hval;

	hval = FNV1A_64_INIT;
	s = (unsigned char *)str;
	while (*s)
	{
		hval ^= (Fnv64_t)*s++;
		hval += (hval << 1) + (hval << 4) + (hval << 5) +
			(hval << 7) + (hval << 8) + (hval << 40);
	}
	return (hval % FNV_64_PRIME);
}
