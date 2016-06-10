#include "shell.h"

/*
 * hash_32 - 32 bit Fowler/Noll/Vo hash code
 *
 * @(#) $Revision: 5.1 $
 * @(#) $Id: hash_32.c,v 5.1 2009/06/30 09:13:32 chongo Exp $
 * @(#) $Source: /usr/local/src/cmd/fnv/RCS/hash_32.c,v $
 *
 ***
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
 ***
 *
 * NOTE: The FNV-0 historic hash is not recommended.  One should use
 *	 the FNV-1 hash instead.
 *
 * To use the 32 bit FNV-0 historic hash, pass FNV0_32_INIT as the
 * Fnv32_t hashval argument to fnv_32_buf() or fnv_32_str().
 *
 * To use the recommended 32 bit FNV-1 hash, pass FNV1_32_INIT as the
 * Fnv32_t hashval argument to fnv_32_buf() or fnv_32_str().
 *
 ***
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
 */

#include <stdlib.h>
#include "fnv.h"

/*
 * 32 bit magic FNV-0 and FNV-1 prime
 */
#define FNV_32_PRIME ((Fnv32_t)0x01000193)

/*
 * fnv_32_str - perform a 32 bit Fowler/Noll/Vo hash on a string
 *
 * input:
 *	str	- string to hash
 *	hval	- previous hash value or 0 if first call
 *
 * returns:
 *	32 bit hash as a static hash type
 *
 * NOTE: To use the 32 bit FNV-0 historic hash, use FNV0_32_INIT as the hval
 *	 argument on the first call to either fnv_32_buf() or fnv_32_str().
 *
 * NOTE: To use the recommended 32 bit FNV-1 hash, use FNV1_32_INIT as the hval
 *	 argument on the first call to either fnv_32_buf() or fnv_32_str().
 */
Fnv32_t fnv_32_str(char *str, Fnv32_t hval)
{
    unsigned char *s = (unsigned char *)str;	/* unsigned string */

    /*
     * FNV-1 hash each octet in the buffer
     */
    while (*s) {

	/* multiply by the 32 bit FNV magic prime mod 2^32 */
#if defined(NO_FNV_GCC_OPTIMIZATION)
	hval *= FNV_32_PRIME;
#else
	hval += (hval<<1) + (hval<<4) + (hval<<7) + (hval<<8) + (hval<<24);
#endif

	/* xor the bottom with the current octet */
	hval ^= (Fnv32_t)*s++;
    }

    /* return our new hash value */
    return hval;
}


#define n 2000


typedef struct			e_hasht{
	char				*path;
	char				*name;
	t_hasht				*next;
}						t_hasht;

struct body
{
	t_hasht 			*head;
};

struct body bodies[n];

int						path_init_hasht(t_sh *sh)
{
	Fnv32_t 			hval;
	unsigned long 		index;
	DIR					*directory;
	char				*value;
	char				**folders;
	int					i;
	int 				nbr;
	int					collision;
	int					total;


	t_dirent	content;
	hval = 0;
	nbr = 0;
	total = 0;
	collision = 0;
	folders = ft_strsplit(env_get_path(sh->envp), ':');
	i = 0;
	value = NULL;
	while (folders[i] != NULL)
	{
		if ((directory = opendir(folders[i])) != NULL)
		{
			while ((content = readdir(directory)) != NULL)
			{
				total++;
				index = (fnv_32_str(content->d_name, FNV0_32_INIT)%FNV_32_PRIME)%n;
				log_info("index = %d", index);
				log_info("name = %s", content->d_name);
				if (!bodies[index].head)
				{
					log_info("Empty");
					bodies[index].head = (t_hasht *)malloc(sizeof(t_hasht));
					bodies[index].head->path = ft_strdup(folders[i]);
					bodies[index].head->name = ft_strdup(content->d_name);
				}
				else
				{
					t_hasht		*ptr;

					ptr = bodies[index].head;
					while (ptr)
						ptr = ptr->next;
					ptr->path = ft_strdup(folders[i]);
					ptr->name = ft_strdup(content->d_name);
					log_info("collision at index %d, hashing ->", index );
					collision++;
				}
			}
			closedir(directory);
		}
		i++;
	}

	log_info("Nbr of collision  %d", collision);
	log_info("Nbr total de bianry  %d", total);



	//log_info("value = %s", bodies[index].head->path);

	// index = (fnv_32_str("ok", FNV0_32_INIT)%FNV_32_PRIME)%n;
	// log_info("ok = %d", index);
	// bodies[index].path = ft_strdup(ft_strjoin("/bin/usr", "/ok"));
	// log_info("value = %s", bodies[index].path);

	// index = (fnv_32_str("op", FNV0_32_INIT)%FNV_32_PRIME)%n;
	// log_info("op = %d", index);
	// bodies[index].path = ft_strdup(ft_strjoin("/bin/usr", "/op"));
	// log_info("value = %s", bodies[index].path);

	// index = (fnv_32_str("aweaweaweawe aw q12 23rq 3q2r q", FNV0_32_INIT)%FNV_32_PRIME)%n;
	// log_info("aweaweaweawe aw q12 23rq 3q2r q = %d", index);
	// bodies[index].path = ft_strdup(ft_strjoin("/bin/usr", "/aweaweaweawe aw q12 23rq 3q2r q"));
	// log_info("value = %s", bodies[index].path);






	//log_info("ls = %s", tabl[(fnv_32_str("ls", FNV0_32_INIT)%FNV_32_PRIME)%50]);
	// log_info("FNV_32 valeur = %lu", FNV0_32_INIT);
	// log_info("ls = %lu", fnv_32_str("ls", 0)%FNV_32_PRIME);
	// log_info("normal = %lu", fnv_32_str("normal", hval)%FNV_32_PRIME);
	// log_info("salut = %lu", fnv_32_str("salut", hval)%FNV_32_PRIME);
	// log_info("test = %lu", fnv_32_str("test", hval)%FNV_32_PRIME);
	// log_info("ls = %lu", fnv_32_str("ls", hval)%FNV_32_PRIME);
	// log_info("normal = %lu", fnv_32_str("normal", hval)%FNV_32_PRIME);
	// log_info("wada 21e 10 h12092h dq93yfa9 gfag34br92 3323hqQ2IQ003IRF A;F = %lu", fnv_32_str("wada 21e 10 h12092h dq93yfa9 gfag34br92 3323hqQ2IQ003IRF A;F", hval)%FNV_32_PRIME);
	// log_info("Testons une string assez longue = %lu", fnv_32_str("Testons une string assez longue", hval)%FNV_32_PRIME);
	return (0);
}
