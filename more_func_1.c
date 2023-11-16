#include "shell.h"

/**
 * act_er - in case the shell is on interactive mode
 * @info: address struction
 *
 * Return: interactive mode = 1, else 0
 */
int act_er(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->rdfd <= 2);
}

/**
 * deli_st - delimeter characters checker
 * @g: the checked chararcter
 * @deli_str: stringt of delimeter
 * Return: true = 1, else = 0
 */
int deli_st(char g, char *deli_str)
{
	while (*deli_str)
		if (*deli_str++ == g)
			return (1);

	return (0);
}

/**
 *alp_st - alphabetic characters checker
 *@g: the checked chararcter
 *Return: true = 1, else = 0
 */

int alp_st(int g)
{
	if ((g >= 'a' && g <= 'z') || (g >= 'A' && g <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *a2i - converts from string to integer
 *@z: the converted string
 *Return: no numbers = 0 , else = converted number
 */

int a2i(char *z)
{
	int x, mrk = 1, flg = 0, outs;
	unsigned int ans = 0;

	for (x = 0;  z[x] != '\0' && flg != 2; x++)
	{
		if (z[x] == '-')
			mrk *= -1;

		if (z[x] >= '0' && z[x] <= '9')
		{
			flg = 1;
			ans *= 10;
			ans += (z[x] - '0');
		}
		else if (flg == 1)
			flg = 2;
	}

	if (mrk == -1)
		outs = -ans;
	else
		outs = ans;

	return (outs);
}
