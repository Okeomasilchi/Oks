#include "main.h"

/**
 * cd_command - changes directory to the specified path
 * @args: arguments to work with
 * @NAME: name of the compiled program
 * @num: argument count
 *
 * Return: void
*/
void cd_command(okeoma *oki)
{
	if (oki->av[1] == NULL)
	{
		oki->ok = get_env(oki->env, "HOME");
		oki->old = get_env(oki->env, "PWD");
		chdir(oki->ok);
		set_env_value(oki->env, "OLDPWD", oki->old);
		set_env_value(oki->env, "PWD", oki->ok);
		/*oki->env = list_from_env(environ);*/
		return;
	}
	if (strcmp(oki->av[1], "-") == 0)
	{
		oki->ok = get_env(oki->env, "PWD");
		oki->old = get_env(oki->env, "OLDPWD");
		if (chdir(oki->old) == 0)
		{
			set_env_value(oki->env, "PWD", oki->old);
			set_env_value(oki->env, "OLDPWD", oki->ok);
			p(STO, "%s\n", oki->old);
			return;
		}
	}
	else
	{
		if (chdir(oki->av[1]) == 0)
		{
			oki->env = list_from_env(environ);
			oki->ok = get_env(oki->env, "PWD");
			p(STO, "%s\n", oki->ok);
		}
		else
			p(STE, "%s: %d: %s: can't cd to %s\n", oki->Name, oki->com_num, oki->av[0], oki->av[1]);
	}
}

/**
 * exit_command - exits the program
 * @args: arguments to work with
 * @NAME: name of the compiled program
 * @num: argument count
 *
 * Return: void
*/

void exit_command(okeoma *oki)
{
	int i;
	int isNumber = 1;

	if (oki->av[1] == NULL)
	{
		free_list(oki->env);
		free_all(oki);
		exit(EXIT_SUCCESS);
	}
	else if (oki->av[1] != NULL)
	{
		for (i = 0; oki->av[1][i] != '\0'; i++)
		{
			if (!isdigit(oki->av[1][i]))
			{
				isNumber = 0;
				break;
			}
		}
		if (!isNumber)
			p(STE, "%s: %d: %s: Illegal number: %s\n", oki->Name, oki->com_num, oki->av[0], oki->av[1]);
		else
		{
			free_list(oki->env);
			free_all(oki);
			exit(atoi(oki->av[1]));
		}
	}
}

/**
 * setenv_command - sets the specified environ
 * @args: arguments to work with
 * @NAME: name of the compiled program
 * @num: argument count
 *
 * Return: void
*/
void setenv_command(okeoma *oki)
{
	if (oki->av[1] == NULL || oki->av[2] == NULL)
		p(STE, "%s: %d: %s: Usage: setenv NAME value\n", oki->Name, oki->com_num, oki->av[0]);
	else
	{
		oki->env = insert_env(oki->env, oki->av[1], oki->av[2]);
		delete_duplicate(oki->env);
		return;
	}
}

/**
 * unsetenv_command - unsets an environmental variable
 * @args: arguments to work with
 * @NAME: name of the compiled program
 * @num: argument count
 *
 * Return: void
*/
void unsetenv_command(okeoma *oki)
{
	if (oki->av[1] == NULL)
		p(STE, "%s: %d: %s: missing argument\n", oki->Name, oki->com_num, oki->av[0]);
	else
	{
		if (get_env(oki->env, oki->av[1]) == NULL)
			p(STE, "%s: %d: %s: %s not set\n", oki->Name, oki->com_num, oki->av[0], oki->av[1]);
		else
			oki->env = delete_match(oki->env, oki->av[1]);
	}
}

/**
 * env_command - print help
 * @oki: structure with all variables
 *
 * Return: void
*/
void env_command(okeoma *oki)
{
	delete_duplicate(oki->env);
	print(oki->env);
}

/**
 * get_env_command - print a particular environ
 * @args: arguments to work with
 * @NAME: name of the compiled program
 * @num: argument count
 *
 * Return: void
*/
void get_env_command(okeoma *oki)
{
	bool nv = is_NAME(oki->env, oki->av[1]);

	if (nv == true && oki->av[2] == NULL)
	{
		p(STO, "%s\n", get_env(oki->env, oki->av[1]));
	}
	else if (oki->av[2] != NULL)
	{
		p(STE, "%s: %d: %s: Usage: %s <NAME of environmental variable>\n", oki->Name, oki->com_num, oki->av[0], oki->av[0]);
	}
	else
	{
		p(STE, "%s: %d: %s: %s not set\n", oki->Name, oki->com_num, oki->av[0], oki->av[1]);
	}
}