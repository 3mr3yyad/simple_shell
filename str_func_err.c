#include "shell.h"

/**
 * _puts_error - Print a string to the stderr.
 * @str: The string to print.
 */
void _puts_error(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		_putchar_error(str[x]);
		x++;
	}
}

/**
 * _putchar_error - Print a character to the stderr.
 * @g: The character to print.
 *
 * Return: Always 1.
 */
int _putchar_error(char g)
{
	static int x;
	static char fub[wr_fub_size];

	if (g == fub_blush || x >= wr_fub_size)
	{
		write(2, fub, x);
		x = 0;
	}
	if (g != fub_blush)
		fub[x++] = g;
	return (1);
}

/**
 * fd_put - Print a character to a given file descriptor.
 * @g: The character to print.
 * @d_file: The file descriptor to print to.
 *
 * Return: Always 1.
 */
int fd_put(char g, int d_file)
{
	static int x;
	static char buf[wr_fub_size];

	if (g == fub_blush || x >= wr_fub_size)
	{
		write(d_file, buf, x);
		x = 0;
	}
	if (g != fub_blush)
		buf[x++] = g;
	return (1);
}

/**
 * fd_puts - Print a string to a given file descriptor.
 * @str: The string to print.
 * @d_file: The file descriptor to print to.
 *
 * Return: The number of characters printed.
 */
int fd_puts(char *str, int d_file)
{
	int x = 0;

	if (!str)
		return (0);
	while (*str)
	{
		x += fd_put(*str++, d_file);
	}
	return (x);
}
