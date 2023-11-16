#include "shell.h"

/**
 * **convw_str - convert string into words
 * @str: inputed string
 * @v: delimetered string
 * Return: array of strings pointer, else = NULL
 */
char **convw_str(char *str, char *v)
{
	int x, y, b, w, cntwrd = 0;
	char **z;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!v)
		v = " ";
	for (x = 0; str[x] != '\0'; x++)
		if (!deli_st(str[x], v) && (deli_st(str[x + 1], v) || !str[x + 1]))
			cntwrd++;
	if (cntwrd == 0)
		return (NULL);
	z = malloc((1 + cntwrd) * sizeof(char *));
	if (!z)
		return (NULL);
	for (x = 0, y = 0; y < cntwrd; y++)
	{
		while (deli_st(str[x], v))
			x++;
		b = 0;
		while (!deli_st(str[x + b], v) && str[x + b])
			b++;
		z[y] = malloc((b + 1) * sizeof(char));
		if (!z[y])
		{
			for (b = 0; b < y; b++)
				free(z[b]);
			free(z);
			return (NULL);
		}
		for (w = 0; w < b; w++)
			z[y][w] = str[x++];
		z[y][w] = 0;
	}
	z[y] = NULL;
	return (z);
}

/**
 * **conv2w_str - convert string into words
 * @str: inputed string
 * @v: delimeter string
 * Return: array of strings pointer, else = NULL
 */
char **conv2w_str(char *str, char v)
{
	int x, y, b, w, cntwrd = 0;
	char **z;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (x = 0; str[x] != '\0'; x++)
		if ((str[x] != v && str[x + 1] == v) ||
		    (str[x] != v && !str[x + 1]) || str[x + 1] == v)
			cntwrd++;
	if (cntwrd == 0)
		return (NULL);
	z = malloc((1 + cntwrd) * sizeof(char *));
	if (!z)
		return (NULL);
	for (x = 0, y = 0; y < cntwrd; y++)
	{
		while (str[x] == v && str[x] != v)
			x++;
		b = 0;
		while (str[x + b] != v && str[x + b] && str[x + b] != v)
			b++;
		z[y] = malloc((b + 1) * sizeof(char));
		if (!z[y])
		{
			for (b = 0; b < y; b++)
				free(z[b]);
			free(z);
			return (NULL);
		}
		for (w = 0; w < b; w++)
			z[y][w] = str[x++];
		z[y][w] = 0;
	}
	z[y] = NULL;
	return (z);
}
