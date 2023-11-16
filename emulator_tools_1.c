#include "shell.h"

/**
 * exit_sh - Exit the shell.
 * @info: A pointer to a struct containing information about the shell's state.
 *
 * If there is an exit argument, it checks if it's a valid number.
 * If it's not a valid number, it prints an error message and returns 1.
 * If there is no exit argument, it sets the error number to -1.
 *
 * Return: If there is an error, return 1.
 *         If there is no error, return -2.
 */
int exit_sh(info_t *info)
{
	int extchk;

	if (info->argv[1])
	{
		extchk = a2i_err(info->argv[1]);
		if (extchk == -1)
		{
			info->stts = 2;
			f_err(info, "Illegal number: ");
			_puts_error(info->argv[1]);
			_putchar_error('\n');
			return (1);
		}
		info->nom_error = a2i_err(info->argv[1]);
		return (-2);
	}
	info->nom_error = -1;
	return (-2);
}

/**
 * cd_cwd - Change the current directory.
 * @info: A pointer to a struct containing information about the shell's state.
 *
 * If there is no argument, it changes the directory to the user's home
 * directory. If the argument is "-", it changes the directory to the previous
 * directory. If there is another argument, it changes the directory to the
 * specified directory.
 *
 * Return: If there is an error, return 1.
 *         If there is no error, return 0.
 */
int cd_cwd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdiy_rt;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _genvir(info, "HOME=");
		if (!dir)
			chdiy_rt =
				chdir((dir = _genvir(info, "PWD=")) ? dir : "/");
		else
			chdiy_rt = chdir(dir);
	}
	else if (promstr(info->argv[1], "-") == 0)
	{
		if (!_genvir(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_genvir(info, "OLDPWD=")), _putchar('\n');
		chdiy_rt =
			chdir((dir = _genvir(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdiy_rt = chdir(info->argv[1]);
	if (chdiy_rt == -1)
	{
		f_err(info, "can't cd to ");
		_puts_error(info->argv[1]), _putchar_error('\n');
	}
	else
	{
		st_envir(info, "OLDPWD", _genvir(info, "PWD="));
		st_envir(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * cd_hlp - Display help information.
 * @info: A pointer to a struct containing information about the shell's state.
 *
 * It prints a message indicating the help function is not yet implemented.
 *
 * Return: Always 0.
 */
int cd_hlp(info_t *info)
{
	char **argum_ary;

	argum_ary = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argum_ary);
	return (0);
}
