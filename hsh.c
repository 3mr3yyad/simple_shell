#include "shell.h"

/**
 * hsh - Main function of the shell.
 * @info: A struct containing information about the shell's state.
 * @impliv: An array of strings representing the command line arguments.
 *
 * Return: The exit status of the last command executed.
 */
int hsh(info_t *info, char **impliv)
{
	ssize_t rc = 0;
	int builtin_bk = 0;

	while (rc != -1 && builtin_bk != -2)
	{
		info_cl(info);
		if (act_er(info))
			_puts("$ ");

		_putchar_error(fub_blush);
		rc = ginput(info);

		if (rc != -1)
		{
			int_info(info, impliv);
			builtin_bk = bltn_fnd(info);

			if (builtin_bk == -1)
				prom_fnd(info);
		}
		else if (act_er(info))
			_putchar('\n');
		_frinfo(info, 0);
	}
	hst_wr(info);
	_frinfo(info, 1);

	if (!act_er(info) && info->stts)
		exit(info->stts);

	if (builtin_bk == -2)
	{
		if (info->nom_error == -1)
			exit(info->stts);

		exit(info->nom_error);
	}
	return (builtin_bk);
}

/**
 * bltn_fnd - Finds the built-in function associated with a command.
 * @info: A struct containing information about the shell's state.
 *
 * Return: The exit status of the built-in function,
 *			or -1 if the command is not built-in.
 */

int bltn_fnd(info_t *info)
{
	int x, built_in_bk = -1;

	builtin_table builtintbl[] = {
		{"exit", exit_sh},
		{"env", fenvir},
		{"help", cd_hlp},
		{"history", lst_hst},
		{"setenv", fset_envir},
		{"unsetenv", funset_envir},
		{"cd", cd_cwd},
		{"alias", alias_man},
		{NULL, NULL}
	};

	for (x = 0; builtintbl[x].type; x++)
		if (promstr(info->argv[0], builtintbl[x].type) == 0)
		{
			info->countln++;
			built_in_bk = builtintbl[x].func(info);

			break;
		}
	return (built_in_bk);
}

/**
 * prom_fnd - Finds the command to be executed.
 * @info: A struct containing information about the shell's state.
 */

void prom_fnd(info_t *info)
{
	char *path = NULL;
	int x, b;

	info->path = info->argv[0];

	if (info->countlnf == 1)
	{
		info->countln++;
		info->countlnf = 0;
	}

	for (x = 0, b = 0; info->arg[x]; x++)
		if (!deli_st(info->arg[x], " \t\n"))
			b++;

	if (!b)
		return;

	path = pathfnd(info, _genvir(info, "PATH="), info->argv[0]);

	if (path)
	{
		info->path = path;
		prom_fork(info);
	}
	else
	{
		if ((act_er(info) || _genvir(info, "PATH=")
			|| info->argv[0][0] == '/') && prom_being(info, info->argv[0]))
			prom_fork(info);
		else if (*(info->arg) != '\n')
		{
			info->stts = 127;
			f_err(info, "not found\n");
		}
	}
}

/**
 * prom_fork - forks an executed thread to run the cmd.
 * @info: parameter & return info struct.
 *
 * Return: void.
 */

void prom_fork(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}

	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, genvir(info)) == -1)
		{
			_frinfo(info, 1);

			if (errno == EACCES)
				exit(126);

			exit(1);
		}
	}
	else
	{
		wait(&(info->stts));
		if (WIFEXITED(info->stts))
		{
			info->stts = WEXITSTATUS(info->stts);

			if (info->stts == 126)
				f_err(info, "Permission denied\n");
		}
	}
}
