#include "shell.h"

/**
 **cp_strn - string copier
 *@dest: past destination
 *@src: string source
 *@i: size of copied characters
 *Return: chain of strings
 */

char *cp_strn(char *dest, char *src, int i)
{
	int x, y;
	char *z = dest;

	x = 0;

	while (src[x] != '\0' && x < i - 1)
	{
		dest[x] = src[x];
		x++;
	}

	if (x < i)
	{
		y = x;
		while (y < i)
		{
			dest[y] = '\0';
			y++;
		}
	}

	return (z);
}

/**
 **cat_strn - chains two strings
 *@dest: string 1
 *@src: string 2
 *@i: max bytes to use
 *Return: chained string
 */
char *cat_strn(char *dest, char *src, int i)
{
	int x, y;
	char *z = dest;

	x = 0;
	y = 0;

	while (dest[x] != '\0')
		x++;

	while (src[y] != '\0' && y < i)
	{
		dest[x] = src[y];
		x++;
		y++;
	}

	if (y < i)
		dest[x] = '\0';

	return (z);
}

/**
 **cr_str - string charcters locator
 *@z: parsed string
 *@g: searched character
 *Return: memory pointer area "s"
 */
char *cr_str(char *z, char g)
{
	do {
		if (*z == g)
			return (z);
	} while (*z++ != '\0');

	return (NULL);
}
