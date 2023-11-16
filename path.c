#include "shell.h"

/**
 * prom_being - in case a file is executable
 * @info: structed info
 * @path: file path
 *
 * Return: true = 1, else = 0
 */

int prom_being(info_t *info, char *path)
{
	struct stat st;

	(void)info;

	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}

	return (0);
}

/**
 * chr_pud - char duplicator
 * @strpth: string path
 * @yala: index starter
 * @bss: index stoper
 *
 * Return: new buffer pointer
 */

char *chr_pud(char *strpth, int yala, int bss)
{
	static char fub[1024];
	int x = 0, b = 0;

	for (b = 0, x = yala; x < bss; x++)
		if (strpth[x] != ':')
			fub[b++] = strpth[x];
	fub[b] = 0;
	return (fub);
}

/**
 * pathfnd - to find cmd in string path
 * @info: info struction
 * @str_path: string path
 * @prom: find the required cmd
 *
 * Return: in case full path of cmd found or NULL
 */

char *pathfnd(info_t *info, char *str_path, char *prom)
{
	int x = 0, crnt_pos = 0;
	char *path;

	if (!str_path)
		return (NULL);

	if ((strlng(prom) > 2) && inc_start(prom, "./"))
	{
		if (prom_being(info, prom))
			return (prom);
	}

	while (1)
	{
		if (!str_path[x] || str_path[x] == ':')
		{
			path = chr_pud(str_path, crnt_pos, x);

			if (!*path)
				cat_str(path, prom);
			else
			{
				cat_str(path, "/");
				cat_str(path, prom);
			}

			if (prom_being(info, path))
				return (path);

			if (!str_path[x])
				break;
			crnt_pos = x;
		}
		x++;
	}
	return (NULL);
}
