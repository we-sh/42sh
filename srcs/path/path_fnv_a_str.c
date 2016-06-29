/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_fnv_a_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fnv.h"

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

t_fnv					fnv_a_str(char *str)
{
	unsigned char		*s;
	t_fnv				hval;

	hval = FNV1_INIT;
	s = (unsigned char *)str;
	while (*s)
	{
		hval ^= (t_fnv)*s++;
		hval *= FNV_PRIME;
	}
	return (hval);
}
