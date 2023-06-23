#include "main.h"

/**
 * list_from_env - Builds a linked list from the environmental variable
 * @env: pointer to the environmental list
 *
 * Return: Returns pointer to the linked list 
*/
env_list *list_from_env(char **env)
{
	env_list *head = NULL, *current = NULL, *new_node = NULL;
	char *variable, *separator, *name, *value;
	int i = 0, name_len;

	while (env[i] != NULL)
	{
		variable = env[i];
		separator = strchr(variable, '=');
		
		if (separator != NULL)
		{
			/* Extract the variable name */
			name_len = separator - variable;
			name = (char *)malloc((name_len + 1) * sizeof(char));
			strncpy(name, variable, name_len);
			name[name_len] = '\0';
			
			value = strdup(separator + 1);	/* Extract the variable value */
			/* Create a new env_list for the variable */
			new_node = (env_list *)malloc(sizeof(env_list));
			new_node->NAME = name;
			new_node->value = value;
			new_node->next = NULL;
			if (head == NULL) /* First env_list in the list */
			{
				head = new_node;
				current = new_node;
			}
			else /* Append the env_list to the end of the list */
			{
				current->next = new_node;
				current = new_node;
			}
		}
		i++;
	}
	return (head);
}

/**
 * free_list - free's memory allocated by list_from_env
 * @head: pointer to the head of the linked list
 *
 * Return: Void
*/
void free_list(env_list *head)
{
	env_list *current = head, *temp = NULL;
	
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp->NAME);
		free(temp->value);
		free(temp);
	}
}

/**
 * free_list_recursive - free's memory allocated by list_from_env recursively
 * @head: pointer to the head of the linked list
 *
 * Return: Void
*/
void free_list_recursive(env_list *head)
{
	if (head == NULL) return;

	free_list(head->next);
	free(head->NAME);
	free(head->value);
	free(head);
}

/**
 * is_value - Checks if a value is present in a linked list
 * @head: The head of the linked list
 * @value: The value to search for
 *
 * Return: true if the value is found, false otherwise
 */
bool is_value(env_list *head, const char *value)
{
	if (head == NULL) return (false);
	else if (strcmp(head->NAME, value) == 0) return (true);
	else return (is_value(head->next, value));
}

/**
 * is_NAME - Checks if a NAME is present in a linked list
 * @head: The head of the linked list
 * @NAME: The value to search for
 *
 * Return: true if the value is found, false otherwise
 */
bool is_NAME(env_list *head, const char *NAME)
{
	if (head == NULL) return (false);
	else if (strcmp(head->NAME, NAME) == 0) return (true);
	else return (is_NAME(head->next, NAME));
}

/**
 * print - Prints the values of an env_linked list
 * @head: The head of the linked list
 *
 * Return: void
 */
void print(env_list *head)
{
	env_list *current;
	current = head;

	while (current != NULL)
	{
		printf("%s=%s\n", current->NAME, current->value);
		current = current->next;
	}
	return;
	
}

/**
 * insert_env - Inserts a new env_list with a given NAME and value at the tail of a linked list
 * @head: The head of the linked list
 * @NAME: name of variable
 * @value: The value to be inserted
 *
 * Return: A pointer to the modified linked list
 */
env_list *insert_env(env_list *head, const char *NAME, const char *value)
{
	env_list *new_node = NULL, *current = head;

	new_node = malloc(sizeof(env_list));
	new_node->value = strdup(value);
	new_node->NAME = strdup(NAME);
	new_node->next = NULL;

	if (head == NULL)
		return (new_node);
	else if (is_NAME(current, NAME) == true)
	{
		while (current != NULL)
		{
			if (strcmp(current->NAME, NAME) == 0)
			{
				free(current->value);
				current->value = strdup(value);
			}
			current = current->next;
		}
		return (head);
	}
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
		return (head);
	}
}

/**
 * delete_match - Deletes the first matching node from an env_list with a given NAME
 * @head: The head of the linked list
 * @delete_NAME: The NAME of list to be deleted
 *
 * Return: A pointer to the modified linked list
 */
env_list *delete_match(env_list *head, char *delete_NAME)
{
	env_list *temp = NULL;

	if (head == NULL) return (NULL);
	else if (head->next != NULL && strcmp(head->next->NAME, delete_NAME) == 0)
	{
		temp = head->next;
		head->next = temp->next;
		free(temp);
		return (head);
	}
	else
	{
		head->next = delete_match(head->next, delete_NAME);
		return (head);
	}
}

/**
 * get_env - returns the value of a NAME in the env_list if it exist
 * @env: the list to search
 * @NAME: the name to search for in the list
 *
 * Return: a pointer to the value if the NAME exits else NULL
*/
char *get_env(env_list *env, const char *NAME)
{
	env_list *current = env;
	
	if (current->next == NULL) return NULL;
	else if (strcmp(current->NAME, NAME) == 0) return (current->value);
	else return get_env(current->next, NAME);	
}

/**
 * delete_duplicate - Deletes duplicate nodes from an env_linked list
 * @head: The head of the linked list
 *
 * Return: void
 */
void delete_duplicate(env_list *head)
{
	env_list *cur1, *cur2, *dup;

	if (head == NULL)
		return;

	head = revers_list(head);
	cur1 = head;

	while (cur1 != NULL && cur1->next != NULL)
	{
		cur2 = cur1;
		while (cur2->next != NULL)
		{
			if (strcmp(cur1->NAME, cur2->next->NAME) == 0)
			{
				dup = cur2->next;
				cur2->next = cur2->next->next;
				free(dup);
			}
			else
			{
				cur2 = cur2->next;
			}
		}
		cur1 = cur1->next;
	}
	head = revers_list(head);
}

/**
 * revers_env_list - Reverses a linked list
 * @head: The head of the linked list
 *
 * Return: A pointer to the reversed linked list
 */
env_list *revers_list(env_list *head)
{
	env_list *current = NULL, *next = NULL, *tmp = NULL; 
	if (head == NULL) return NULL;
	if (head->next == NULL) return head;

	current = head;
	next = head->next;

	current->next = NULL;

	while (next != NULL)
	{
		tmp = next->next;
		next->next = current;
		current = next;
		next = tmp;
	}
	return (current);	
}

/**
 * set_env_value - sets the value of a NAME in the env_list if it exist to the specified value
 * @env: the list to search
 * @NAME: the name to search for in the list
 * @value: value to be inserted
 *
 * Return: a pointer to the value if the NAME exits else NULL
*/
void set_env_value(env_list *env, const char *NAME, const char *value)
{
	env = insert_env(env, NAME, value);	
}

void env_command(okeoma *oki)
{
	env_list *cur = oki->head;

	while (cur != NULL)
	{
		printf("%s=%s\n", cur->NAME, cur->value);
		cur = cur->next;
	}
	return;
}






char *value(char *str)
{
	char *val = strdup(str);

	if (strstr(val, "$") != NULL)
	{
		val = (strstr(val, "$") + 1);
		return (val);
	}

	return (NULL);
}

bool checker(char *arr)
{
	if (arr == NULL) return false;
	else if (strstr(arr, "$") != NULL) return true;
	else return false;
}

int change(env_list *head, char *av)
{
	env_list *cur = head;
	char *tok = NULL, *val = NULL, *rep = NULL, *rem = NULL, *va = NULL, *new;
	int len;
	size_t n_size;

	va = strdup(av);

	v val, v len, v rem;
	val = strstr(va, "$");

	while (cur != NULL)
	{
		len = strlen(cur->NAME) + 2;
		tok = malloc(len);
		strcat(tok, "$");
		strcat(tok, cur->NAME);
		
		if ((rep = strstr(va, tok)) != NULL)
		{
			len = strlen(tok);
			if(strncmp(rep, tok, len) == 0)
			{
				rem = strdup(rep + len);
				n_size = strlen(cur->value) + strlen(rem) + 1;
				new = malloc(n_size);
				strcpy(new, cur->value);
				strcat(new, rem);
				memcpy(rep, new, n_size);
				printf("%s\n", va);
				free(rem), free(new), free(tok), free(va);
				return (0);
			}
		}
		cur = cur->next;
	}
	free(va);
	return (-1);
}

int modify(okeoma *oki)
{
	env_list *current = NULL;
	char *val = value(oki->av[1]);

	if (is_NAME(oki->head, val) == true)
	{
		current = oki->head;
		while (current != NULL)
		{
			if (strcmp(current->NAME, val) == 0)
			{
				printf("%s\n", current->value);
				return (0);
			}
			current = current->next;
		}
		return (-1);
	}
	else if (strcmp(val, "?") == 0)
	{
		printf("%d\n", oki->status);
		return (0);
	}
	else if (strcmp(val, "$") == 0)
	{
		printf("%d\n", oki->mypid);
		return (0);
	}
	else if (oki->av[1] != NULL)
	{
		printf("%s\n", oki->av[1]);
		return (0);
	}
	return (-1);
}

int main()
{
	env_list *env = list_from_env(environ);
	char arr[] = "$HOME";
	char *vl = malloc(strlen(arr));
	strcpy(vl, arr);

	if (checker(vl) == true)
	{
		change(env, vl);
		return (0);
	}
	else
		puts("no");


	return (-1);
}

