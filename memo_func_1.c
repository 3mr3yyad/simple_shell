#include "shell.h"

/**
 **set_memo - memories a constant byte
 *@z: memory area pointer
 *@k: the filled byte with *z
 *@i: size of filled bytes
 *Return: memory area pointer "z"
 */
char *set_memo(char *z, char k, unsigned int i)
{
	unsigned int x;

	for (x = 0; x < i; x++)
		z[x] = k;

	return (z);
}

/**
 * free_str - free string of strings
 * @pstrp: the string of strings
 */
void free_str(char **pstrp)
{
	char **q = pstrp;

	if (!pstrp)
		return;

	while (*pstrp)
		free(*pstrp++);

	free(q);
}

/**
 * loc_fr - a block of memory reallocation
 * @ptr: previous malloced block's pointer
 * @former_sz: previous block bytes
 * @adsz: new block bytes
 *
 * Return: old block pointer
 */
void *loc_fr(void *ptr, unsigned int former_sz, unsigned int adsz)
{
	char *p;

	if (!ptr)
		return (malloc(adsz));
	if (!adsz)
		return (free(ptr), NULL);
	if (adsz == former_sz)
		return (ptr);

	p = malloc(adsz);
	if (!p)
		return (NULL);

	former_sz = former_sz < adsz ? former_sz : adsz;
	while (former_sz--)
		p[former_sz] = ((char *)ptr)[former_sz];
	free(ptr);
	return (p);
}

/**
 * free_ptr - free pointer and give NULL to the address
 * @ptr: freed pointer adress
 *
 * Return: 1 = freed, else 0.
 */
int free_ptr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
