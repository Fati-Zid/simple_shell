#include "shell.h"

/**
 * list_push - Adds a new node with data to the end of a linked list.
 * @head: Pointer to the head of the list.
 * @data: Data to be added.
 * Return: The newly added node, or NULL on failure.
 */
list_t *list_push(list_t **head, const char *data)
{
	list_t *new_node, *node;

	if (!head || !data)
		return (NULL);

	node = *head;

	new_node = (list_t *)malloc(sizeof(list_t));
	if (new_node == NULL)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->data = _strdup(data, 0, -1);
	if (new_node->data == NULL)
	{
		free(new_node);
		return (NULL);
	}

	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * list_remove_at - Removes a node at a specific index from a linked list.
 * @head: Pointer to the head of the list.
 * @index: Index of the node to be removed.
 * Return: 1 on success, 0 on failure.
 */
unsigned int list_remove_at(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (index == 0)
	{
		node = *head;
		*head = (*head)->next;
		free(node->data);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->data);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * list_to_strings - ....
 * @head: ...
 * Return: ...
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->data) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->data);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * list_len- ....
 * @h: ...
 * Return: ...
 */
size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_free - Frees all nodes and their data in a linked list.
 * @head_ptr: Pointer to the head of the list.
 */
void list_free(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->data);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
