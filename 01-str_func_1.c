#include "shell.h"

/**
 * strlng - string length
 * @z: checked string
 *
 * Return: string length integer
 */

int strlng(char *z)
{
	int x = 0;

	if (!z)
		return (0);

	while (*z++)
		x++;

	return (x);
}

/**
 * promstr - compares lexicogarphic of two strings
 * @z1: input 1
 * @z2: input 2
 *
 * Return: 1 < z2 = negatives, z1 > z2 = positive, z1 == z2 = zero
 */

int promstr(char *z1, char *z2)
{
	while (*z1 && *z2)
	{
		if (*z1 != *z2)
			return (*z1 - *z2);
		z1++;
		z2++;
	}

	if (*z1 == *z2)
		return (0);

	else
		return (*z1 < *z2 ? -1 : 1);
}

/**
 * inc_start - in case meow start in box
 * @box: searched string
 * @meow: substring found
 *
 * Return:  next char address in box, else = NULL
 */
char *inc_start(const char *box, const char *meow)
{
	while (*meow)
		if (*meow++ != *box++)
			return (NULL);

	return ((char *)box);
}

/**
 * cat_str - attatch two strings in order
 * @dest: destinated buffer
 * @src: source buffer
 *
 * Return: destinated buffer pointer
 */

char *cat_str(char *dest, char *src)
{
	char *bk = dest;

	while (*dest)
		dest++;

	while (*src)
		*dest++ = *src++;

	*dest = *src;

	return (bk);
}
