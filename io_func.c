#include "shell.h"

/**
 * file_ghst - Get the history file name.
 * @info: A struct containing information about the shell's state.
 *
 * Return: The history file name.
 */

char *file_ghst(info_t *info)
{
	char *fub, *dir;

	dir = _genvir(info, "HOME=");
	if (!dir)
		return (NULL);
	fub = malloc(sizeof(char) * (strlng(dir) + strlng(file_hst) + 2));
	if (!fub)
		return (NULL);
	fub[0] = 0;
	cp_str(fub, dir);
	cat_str(fub, "/");
	cat_str(fub, file_hst);
	return (fub);
}

/**
 * hst_wr - Write to the history file.
 * @info: A struct containing information about the shell's state.
 *
 * Return: 1 if successful, -1 otherwise.
 */
int hst_wr(info_t *info)
{
	ssize_t d_file;
	char *file_n = file_ghst(info);
	list_t *node = NULL;

	if (!file_n)
		return (-1);

	d_file = open(file_n, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_n);
	if (d_file == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		fd_puts(node->str, d_file);
		fd_put('\n', d_file);
	}
	fd_put(fub_blush, d_file);
	close(d_file);
	return (1);
}

/**
 * hst_rd - Read from the history file.
 * @info: A struct containing information about the shell's state.
 *
 * Return: The number of lines read from the history file.
 */
int hst_rd(info_t *info)
{
	int x, last = 0, lncount = 0;
	ssize_t d_file, rdlen, fsize = 0;
	struct stat st;
	char *fub = NULL, *file_n = file_ghst(info);

	if (!file_n)
		return (0);

	d_file = open(file_n, O_RDONLY);
	free(file_n);
	if (d_file == -1)
		return (0);
	if (!fstat(d_file, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	fub = malloc(sizeof(char) * (fsize + 1));
	if (!fub)
		return (0);
	rdlen = read(d_file, fub, fsize);
	fub[fsize] = 0;
	if (rdlen <= 0)
		return (free(fub), 0);
	close(d_file);
	for (x = 0; x < fsize; x++)
		if (fub[x] == '\n')
		{
			fub[x] = 0;
			hst_lst_bld(info, fub + last, lncount++);
			last = x + 1;
		}
	if (last != x)
		hst_lst_bld(info, fub + last, lncount++);
	free(fub);
	info->counthst = lncount;
	while (info->counthst-- >= max_hst)
		rm_ind_node(&(info->history), 0);
	hst_renom(info);
	return (info->counthst);
}

/**
 * hst_lst_bld - Build a linked list of the history.
 * @info: A struct containing information about the shell's state.
 * @fub: The buffer containing the history.
 * @lncount: The number of lines in the history.
 *
 * Return: Always 0.
 */
int hst_lst_bld(info_t *info, char *fub, int lncount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	end_noded(&node, fub, lncount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * hst_renom - Rename the history.
 * @info: A struct containing information about the shell's state.
 *
 * Return: The number of lines in the history.
 */
int hst_renom(info_t *info)
{
	list_t *node = info->history;
	int x = 0;

	while (node)
	{
		node->nom = x++;
		node = node->next;
	}
	return (info->counthst = x);
}
