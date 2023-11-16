#include "shell.h"

/**
 * info_cl - to initializes info_t struct.
 * @info: a struct address.
 */
void info_cl(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * int_info - to initializ info_t struct.
 * @info: a struct address.
 * @impliv: implicit vector.
 */

void int_info(info_t *info, char **impliv)
{
	int x = 0;

	info->namef = impliv[0];
	if (info->arg)
	{
		info->argv = convw_str(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = pud_str(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (x = 0; info->argv && info->argv[x]; x++)
			;
		info->argc = x;

		alias_mv(info);
		var_mv(info);
	}
}

/**
 * _frinfo - to frees info_t struct fields.
 * @info: a struct address.
 * @allof: true if freeing all the fields.
 */

void _frinfo(info_t *info, int allof)
{
	free_str(info->argv);

	info->argv = NULL;
	info->path = NULL;

	if (allof)
	{
		if (!info->fub_prom)
			free(info->arg);

		if (info->env)
			frlst(&(info->env));

		if (info->history)
			frlst(&(info->history));

		if (info->alias)
			frlst(&(info->alias));

		free_str(info->environ);
			info->environ = NULL;

		free_ptr((void **)info->fub_prom);

		if (info->rdfd > 2)
			close(info->rdfd);

		_putchar(fub_blush);
	}
}
