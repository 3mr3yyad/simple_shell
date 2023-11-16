#include "shell.h"

/**
 * cp_str - string copier
 * @dest: destination to past
 * @src: source of copied
 *
 * Return: destination point
 */

char *cp_str(char *dest, char *src)
{
	int x = 0;

	if (dest == src || src == 0)
		return (dest);

	while (src[x])
	{
		dest[x] = src[x];
		x++;
	}

	dest[x] = 0;

	return (dest);
}

/**
 * pud_str - string duplicator
 * @str: duplicated string
 *
 * Return: duplicated string pointer
 */

char *pud_str(const char *str)
{
	int lng = 0;
	char *bk;

	if (str == NULL)
		return (NULL);

	while (*str++)
		lng++;

	bk = malloc(sizeof(char) * (lng + 1));
	if (!bk)
		return (NULL);

	for (lng++; lng--;)
		bk[lng] = *--str;

	return (bk);
}

/**
 *_puts - prints inputed string
 *@str: printed string
 */
void _puts(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		_putchar(str[x]);
		x++;
	}
}

/**
 * _putchar - prints "c" to stdout
 * @g: printed character
 *
 * Return: 1 = success, else - error, returned = -1
 */
int _putchar(char g)
{
	static int x;
	static char fub[wr_fub_size];

	if (g == fub_blush || x >= wr_fub_size)
	{
		write(1, fub, x);
		x = 0;
	}

	if (g != fub_blush)
		fub[x++] = g;

	return (1);
}
