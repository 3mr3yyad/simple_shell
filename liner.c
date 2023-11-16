#include "shell.h"

/**
 * input_fub - Buffers chained commands.
 * @info: A struct containing information about the shell's state.
 * @fub: Address of buffer.
 * @len: Address of len var.
 *
 * Return: Bytes read.
 */
ssize_t input_fub(info_t *info, char **fub, size_t *len)
{
	ssize_t rc = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*fub);
		*fub = NULL;
		signal(SIGINT, y_blocks);
#if gline
		rc = getline(fub, &len_p, stdin);
#else
		rc = g_ln(info, fub, &len_p);
#endif
		if (rc > 0)
		{
			if ((*fub)[rc - 1] == '\n')
			{
				(*fub)[rc - 1] = '\0';
				rc--;
			}
			info->countlnf = 1;
			cmt_rm(*fub);
			hst_lst_bld(info, *fub, info->counthst++);
			*len = rc;
			info->fub_prom = fub;
		}
	}
	return (rc);
}

/**
 * ginput - Gets a line minus the new line.
 * @info: A struct containing information about the shell's state.
 *
 * Return: Bytes read.
 */
ssize_t ginput(info_t *info)
{
	static char *fub;
	static size_t x, y, len;
	ssize_t rc = 0;
	char **fub_p = &(info->arg), *p;

	_putchar(fub_blush);
	rc = input_fub(info, &fub, &len);
	if (rc == -1)
		return (-1);
	if (len)
	{
		y = x;
		p = fub + x;

		chain_st(info, fub, &y, x, len);
		while (y < len)
		{
			if (chain_being(info, fub, &y))
				break;
			y++;
		}

		x = y + 1;
		if (x >= len)
		{
			x = len = 0;
			info->fub_type_prom = norm_prom;
		}

		*fub_p = p;
		return (strlng(p));
	}

	*fub_p = fub;
	return (rc);
}

/**
 * read_fub - Reads a buffer.
 * @info: A struct containing information about the shell's state.
 * @fub: Buffer.
 * @x: Size.
 *
 * Return: rc.
 */
ssize_t read_fub(info_t *info, char *fub, size_t *x)
{
	ssize_t rc = 0;

	if (*x)
		return (0);
	rc = read(info->rdfd, fub, rd_fub_size);
	if (rc >= 0)
		*x = rc;
	return (rc);
}

/**
 * g_ln - Gets to the next line of the input from STDIN.
 * @info: A struct containing information about the shell's state.
 * @ptr: The address of a pointer to a buffer, preallocated or NULL.
 * @length: The size of preallocated a ptr buffer if not NULL.
 *
 * Return: z.
 */
int g_ln(info_t *info, char **ptr, size_t *length)
{
	static char fub[rd_fub_size];
	static size_t x, len;
	size_t b;
	ssize_t rc = 0, z = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		z = *length;
	if (x == len)
		x = len = 0;
	rc = read_fub(info, fub, &len);
	if (rc == -1 || (rc == 0 && len == 0))
		return (-1);
	c = cr_str(fub + x, '\n');
	b = c ? 1 + (unsigned int)(c - fub) : len;
	new_p = loc_fr(p, z, z ? z + b : b + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);
	if (z)
		cat_strn(new_p, fub + x, b - x);
	else
		cp_strn(new_p, fub + x, b - x + 1);
	z += b - x;
	x = b;
	p = new_p;
	if (length)
		*length = z;
	*ptr = p;
	return (z);
}

/**
 * y_blocks - to block ctrl-C.
 * @sign_nom: signal number.
 *
 * Return: void.
 */
void y_blocks(__attribute__((unused))int sign_nom)
{
	_puts("\n");
	_puts("$ ");
	_putchar(fub_blush);
}
