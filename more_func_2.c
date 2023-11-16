#include "shell.h"

/**
 * a2i_err - converts from string to integer
 * @z: the converted string
 * Return: no numbers = 0 , else = converted number, error = -1
 */

int a2i_err(char *z)
{
	int x = 0;
	unsigned long int ans = 0;

	if (*z == '+')
		z++;

	for (x = 0;  z[x] != '\0'; x++)
	{
		if (z[x] >= '0' && z[x] <= '9')
		{
			ans *= 10;
			ans += (z[x] - '0');

			if (ans > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}

	return (ans);
}

/**
 * f_err - message of error
 * @info: return info struct and parameter
 * @str_er: the error in a string
 * Return: 0 = no numbers in string, else = converted number, error = -1
 */

void f_err(info_t *info, char *str_er)
{
	_puts_error(info->namef);
	_puts_error(": ");
	f_deci(info->countln, STDERR_FILENO);
	_puts_error(": ");
	_puts_error(info->argv[0]);
	_puts_error(": ");
	_puts_error(str_er);
}

/**
 * f_deci - prints a decimal number in base 10
 * @ins: input
 * @d_file: the written filed scriptor
 *
 * Return: printed characters numbers
 */

int f_deci(int ins, int d_file)
{
	int (*__putchar)(char) = _putchar;
	int x, acne = 0;
	unsigned int xyz, crnt;

	if (d_file == STDERR_FILENO)
		__putchar = _putchar_error;

	if (ins < 0)
	{
		xyz = -ins;
		__putchar('-');
		acne++;
	}

	else
		xyz = ins;
	crnt = xyz;

	for (x = 1000000000; x > 1; x /= 10)
	{
		if (xyz / x)
		{
			__putchar('0' + crnt / x);
			acne++;
		}
		crnt %= x;
	}
	__putchar('0' + crnt);
	acne++;

	return (acne);
}

/**
 * nom_conv - converter
 * @nom: a number
 * @outpost: a base
 * @flgs: flag arg
 *
 * Return: a string
 */
char *nom_conv(long int nom, int outpost, int flgs)
{
	static char *arr;
	static char fubb[50];
	char mrk = 0;
	char *ptr;
	unsigned long i = nom;

	if (!(flgs & unsigned_conv) && nom < 0)
	{
		i = -nom;
		mrk = '-';

	}

	arr = flgs & lwcase_conv ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &fubb[49];
	*ptr = '\0';

	do	{
		*--ptr = arr[i % outpost];
		i /= outpost;
	} while (i != 0);

	if (mrk)
		*--ptr = mrk;

	return (ptr);
}

/**
 * cmt_rm - replace '#' with '\0'
 * @fub: the modified string adress
 *
 * Return: Always 0
 */

void cmt_rm(char *fub)
{
	int x;

	for (x = 0; fub[x] != '\0'; x++)
		if (fub[x] == '#' && (!x || fub[x - 1] == ' '))
		{
			fub[x] = '\0';
			break;
		}
}
