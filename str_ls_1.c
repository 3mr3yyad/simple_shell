#include "shell.h"

/**
 * noded - add a node in the begining
 * @head: head node adress
 * @str: node string
 * @nom: node history number
 *
 * Return: size of list
 */
list_t *noded(list_t **head, const char *str, int nom)
{
	list_t *add_head;

	if (!head)
		return (NULL);

	add_head = malloc(sizeof(list_t));

	if (!add_head)
		return (NULL);

	set_memo((void *)add_head, 0, sizeof(list_t));

	add_head->nom = nom;

	if (str)
	{
		add_head->str = pud_str(str);

		if (!add_head->str)
		{
			free(add_head);
			return (NULL);
		}
	}

	add_head->next = *head;
	*head = add_head;

	return (add_head);
}

/**
 * end_noded - add a node in the end
 * @head: head node address
 * @str: node string
 * @nom: node history number
 *
 * Return: size of list
 */
list_t *end_noded(list_t **head, const char *str, int nom)
{
	list_t *add_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	add_node = malloc(sizeof(list_t));

	if (!add_node)
		return (NULL);

	set_memo((void *)add_node, 0, sizeof(list_t));

	add_node->nom = nom;

	if (str)
	{
		add_node->str = pud_str(str);

		if (!add_node->str)
		{
			free(add_node);
			return (NULL);
		}
	}

	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = add_node;
	}
	else
		*head = add_node;
	return (add_node);
}

/**
 * str_lstf - print the list_t linked listonly the str element
 * @h: points to the head node
 *
 * Return: the size of the list
 */
size_t str_lstf(const list_t *h)
{
	size_t x = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		x++;
	}
	return (x);
}

/**
 * rm_ind_node - removes node
 * @head: head node address
 * @ipx: index of the emoved node
 *
 * Return: 1 = success, 0 = failure
 */
int rm_ind_node(list_t **head, unsigned int ipx)
{
	list_t *node, *sub_node;
	unsigned int x = 0;

	if (!head || !*head)
		return (0);

	if (!ipx)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);

		return (1);
	}

	node = *head;

	while (node)
	{
		if (x == ipx)
		{
			sub_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		x++;
		sub_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * frlst - frees the nodes of all of the list
 * @p_head: head node address
 */
void frlst(list_t **p_head)
{
	list_t *node, *add_node, *head;

	if (!p_head || !*p_head)
		return;

	head = *p_head;
	node = head;
	while (node)
	{
		add_node = node->next;
		free(node->str);
		free(node);
		node = add_node;
	}
	*p_head = NULL;
}
