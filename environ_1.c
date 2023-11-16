#include "shell.h"

/**
 * fenvir - Prints the current environment.
 * @info: A struct containing information about the shell's state.
 *
 * Return: Always 0.
 */
int fenvir(info_t *info)
{
	str_lstf(info->env);
	return (0);
}

/**
 * _genvir - Retrieves the value of an environment variable.
 * @info: A struct containing information about the shell's state.
 * @named: The name of the environment variable.
 *
 * Return: The value of the environment variable.
 */
char *_genvir(info_t *info, const char *named)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = inc_start(node->str, named);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * fset_envir - Initializes a new environment
 *			variable or modifies an existing one.
 * @info: A struct containing information about the shell's state.
 *
 * Return: 0 if successful, 1 otherwise.
 */
int fset_envir(info_t *info)
{
	if (info->argc != 3)
	{
		_puts_error("Incorrect number of arguements\n");
		return (1);
	}
	if (st_envir(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * funset_envir - Removes an environment variable.
 * @info: A struct containing information about the shell's state.
 *
 * Return: Always 0.
 */
int funset_envir(info_t *info)
{
	int x;

	if (info->argc == 1)
	{
		_puts_error("Too few arguements.\n");
		return (1);
	}
	for (x = 1; x <= info->argc; x++)
		un_envir(info, info->argv[x]);

	return (0);
}

/**
 * poplst_envir - Populates an environment linked list.
 * @info: A struct containing information about the shell's state.
 *
 * Return: Always 0.
 */
int poplst_envir(info_t *info)
{
	list_t *node = NULL;
	size_t x;

	for (x = 0; environ[x]; x++)
		end_noded(&node, environ[x], 0);
	info->env = node;
	return (0);
}
