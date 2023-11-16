#include "shell.h"

/**
 * lng_lst - the linked list length
 * @hp: head node pointer
 *
 * Return: the size of the list
 */

size_t lng_lst(const list_t *hp)
{
	size_t x = 0;

	while (hp)
	{
		hp = hp->next;
		x++;
	}
	return (x);
}

/**
 * lst_2str - returns array of strings from list->str
 * @head: head node pointer
 *
 * Return: strings array
 */
char **lst_2str(list_t *head)
{
	list_t *node = head;
	size_t x = lng_lst(head), y;
	char **str_ad;
	char *str;

	if (!head || !x)
		return (NULL);

	str_ad = malloc(sizeof(char *) * (x + 1));

	if (!str_ad)
		return (NULL);

	for (x = 0; node; node = node->next, x++)
	{
		str = malloc(strlng(node->str) + 1);

		if (!str)
		{
			for (y = 0; y < x; y++)
				free(str_ad[y]);
			free(str_ad);

			return (NULL);
		}

		str = cp_str(str, node->str);
		str_ad[x] = str;
	}
	str_ad[x] = NULL;

	return (str_ad);
}


/**
 * lstf - print the list_t linked list
 * @hp: head node pointer
 *
 * Return: the size of the list
 */
size_t lstf(const list_t *hp)
{
	size_t x = 0;

	while (hp)
	{
		_puts(nom_conv(hp->nom, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(hp->str ? hp->str : "(nil)");
		_puts("\n");

		hp = hp->next;
		x++;
	}
	return (x);
}

/**
 * start_node_with - return the node which has string starts with prefix
 * @node: list head pointer
 * @m_str: matched string
 * @g: the character after matched prefix
 *
 * Return: match node on success | null on failure
 */
list_t *start_node_with(list_t *node, char *m_str, char g)
{
	char *p = NULL;

	while (node)
	{
		p = inc_start(node->str, m_str);
		if (p && ((g == -1) || (*p == g)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * gind_node - gets the node's index
 * @head: list head pointer
 * @node: node pointer
 *
 * Return: index of node or -1
 */
ssize_t gind_node(list_t *head, list_t *node)
{
	size_t x = 0;

	while (head)
	{
		if (head == node)
			return (x);
		head = head->next;
		x++;
	}
	return (-1);
}
