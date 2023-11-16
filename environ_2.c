#include "shell.h"

/**
 * genvir - Get the environment variables.
 * @info: A struct containing information about the shell's state.
 *
 * Return: The environment variables.
 */
char **genvir(info_t *info)
{
	if (!info->environ || info->chmd_env)
	{
		info->environ = lst_2str(info->env);
		info->chmd_env = 0;
	}

	return (info->environ);
}

/**
 * un_envir - Remove an environment variable.
 * @info: A struct containing information about the shell's state.
 * @env_var: The name of the environment variable to remove.
 *
 * Return: 1 if the environment was changed, 0 otherwise.
 */
int un_envir(info_t *info, char *env_var)
{
	list_t *node = info->env;
	size_t x = 0;
	char *p;

	if (!node || !env_var)
		return (0);

	while (node)
	{
		p = inc_start(node->str, env_var);
		if (p && *p == '=')
		{
			info->chmd_env = rm_ind_node(&(info->env), x);
			x = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		x++;
	}
	return (info->chmd_env);
}

/**
 * st_envir - Set an environment variable.
 * @info: A struct containing information about the shell's state.
 * @env_var: The name of the environment variable to set.
 * @val: The value to set the environment variable to.
 *
 * Return: 0 if successful, 1 otherwise.
 */
int st_envir(info_t *info, char *env_var, char *val)
{
	char *fub = NULL;
	list_t *node;
	char *p;

	if (!env_var || !val)
		return (0);

	fub = malloc(strlng(env_var) + strlng(val) + 2);
	if (!fub)
		return (1);
	cp_str(fub, env_var);
	cat_str(fub, "=");
	cat_str(fub, val);
	node = info->env;
	while (node)
	{
		p = inc_start(node->str, env_var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = fub;
			info->chmd_env = 1;
			return (0);
		}
		node = node->next;
	}
	end_noded(&(info->env), fub, 0);
	free(fub);
	info->chmd_env = 1;
	return (0);
}
