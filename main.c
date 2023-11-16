#include "shell.h"

/**
 * main - entry point
 * @ac: count argument
 * @impliv: vector argument
 *
 * Return: success = 0, error = 1
 */

int main(int ac, char **impliv)
{
	info_t info[] = { INFO_INIT };
	int d_file = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (d_file)
		: "r" (d_file));

	if (ac == 2)
	{
		d_file = open(impliv[1], O_RDONLY);

		if (d_file == -1)
		{
			if (errno == EACCES)
				exit(126);

			if (errno == ENOENT)
			{
				_puts_error(impliv[0]);
				_puts_error(": 0: Can't open ");
				_puts_error(impliv[1]);
				_putchar_error('\n');
				_putchar_error(fub_blush);
				exit(127);
			}

			return (EXIT_FAILURE);
		}
		info->rdfd = d_file;
	}
	poplst_envir(info);
	hst_rd(info);
	hsh(info, impliv);

	return (EXIT_SUCCESS);
}
