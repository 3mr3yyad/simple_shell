#include "shell.h"

/**
 * lst_hst - List the command history.
 * @info: A pointer to a struct containing information about the shell's state.
 *
 * Return: Always 0.
 */
int lst_hst(info_t *info)
{
	lstf(info->history);
	return (0);
}

/**
 * unstr_alias - Remove an alias from the list of aliases.
 * @info: A pointer to a struct containing information about the shell's state.
 * @str: The alias to remove.
 *
 * Return: 0 on success, 1 on failure.
 */
int unstr_alias(info_t *info, char *str)
{
	char *p, g;
	int ret;

	p = cr_str(str, '=');
	if (!p)
		return (1);
	g = *p;
	*p = 0;
	ret = rm_ind_node(&(info->alias),
		gind_node(info->alias, start_node_with(info->alias, str, -1)));
	*p = g;
	return (ret);
}

/**
 * str_alias - Add an alias to the list of aliases.
 * @info: A pointer to a struct containing information about the shell's state.
 * @str: The alias to add.
 *
 * Return: 0 on success, 1 on failure.
 */
int str_alias(info_t *info, char *str)
{
	char *p;

	p = cr_str(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unstr_alias(info, str));

	unstr_alias(info, str);
	return (end_noded(&(info->alias), str, 0) == NULL);
}

/**
 * alias_f - Print an alias.
 * @node: A pointer to the alias node to print.
 *
 * Return: 0 on success, 1 on failure.
 */
int alias_f(list_t *node)
{
	char *p = NULL, *q = NULL;

	if (node)
	{
		p = cr_str(node->str, '=');
		for (q = node->str; q <= p; q++)
			_putchar(*q);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * alias_man - Manage aliases.
 * @info: A pointer to a struct containing information about the shell's state.
 *
 * If there is only one argument, it lists all aliases.
 * If there are more arguments, it adds or removes
 *			aliases based on the arguments.
 *
 * Return: Always 0.
 */
int alias_man(info_t *info)
{
	int x = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			alias_f(node);
			node = node->next;
		}
		return (0);
	}
	for (x = 1; info->argv[x]; x++)
	{
		p = cr_str(info->argv[x], '=');
		if (p)
			str_alias(info, info->argv[x]);
		else
			alias_f(start_node_with(info->alias, info->argv[x], '='));
	}

	return (0);
}
