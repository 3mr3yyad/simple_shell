#include "shell.h"

/**
 * chain_being - tests if the current character
 *			in a buffer is a chain delimiter
 * @info: pointer to a struct containing information about the shell's state
 * @buf: character buffer
 * @p: address of the current position in a buffer
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int chain_being(info_t *info, char *buf, size_t *p)
{
	size_t y = *p;

	if (buf[y] == '|' && buf[y + 1] == '|')
	{
		buf[y] = 0;
		y++;
		info->fub_type_prom = or_prom;
	}
	else if (buf[y] == '&' && buf[y + 1] == '&')
	{
		buf[y] = 0;
		y++;
		info->fub_type_prom = and_prom;
	}
	else if (buf[y] == ';')
	{
		buf[y] = 0;
		info->fub_type_prom = chain_prom;
	}
	else
		return (0);
	*p = y;
	return (1);
}

/**
 * chain_st - checks if we should continue chaining based on the last status
 * @info: pointer to a struct containing information about the shell's state
 * @buf: character buffer
 * @p: address of the current position in a buffer
 * @x: starting position in a buffer
 * @len: length of a buffer
 */
void chain_st(info_t *info, char *buf, size_t *p, size_t x, size_t len)
{
	size_t y = *p;

	if (info->fub_type_prom == and_prom)
	{
		if (info->stts)
		{
			buf[x] = 0;
			y = len;
		}
	}
	if (info->fub_type_prom == or_prom)
	{
		if (!info->stts)
		{
			buf[x] = 0;
			y = len;
		}
	}

	*p = y;
}

/**
 * alias_mv - replaces the aliases in the tokenized string
 * @info: pointer to a struct containing information about the shell's state
 *
 * Return: 1 if replaced, 0 otherwise
 */
int alias_mv(info_t *info)
{
	int x;
	list_t *node;
	char *p;

	for (x = 0; x < 10; x++)
	{
		node = start_node_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = cr_str(node->str, '=');
		if (!p)
			return (0);
		p = pud_str(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * var_mv - replaces vars in the tokenized string
 * @info: pointer to a struct containing information about the shell's state
 *
 * Return: 1 if replaced, 0 otherwise
 */
int var_mv(info_t *info)
{
	int x = 0;
	list_t *node;

	for (x = 0; info->argv[x]; x++)
	{
		if (info->argv[x][0] != '$' || !info->argv[x][1])
			continue;

		if (!promstr(info->argv[x], "$?"))
		{
			str_mv(&(info->argv[x]),
				pud_str(nom_conv(info->stts, 10, 0)));
			continue;
		}
		if (!promstr(info->argv[x], "$$"))
		{
			str_mv(&(info->argv[x]),
				pud_str(nom_conv(getpid(), 10, 0)));
			continue;
		}
		node = start_node_with(info->env, &info->argv[x][1], '=');
		if (node)
		{
			str_mv(&(info->argv[x]),
				pud_str(cr_str(node->str, '=') + 1));
			continue;
		}
		str_mv(&info->argv[x], pud_str(""));

	}
	return (0);
}

/**
 * str_mv - replaces a string
 * @oldd: address of the old string
 * @newd: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int str_mv(char **oldd, char *newd)
{
	free(*oldd);
	*oldd = newd;
	return (1);
}
