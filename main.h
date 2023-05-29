#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <limits.h>

#define BUFFER_SIZE 1024

extern char **environ;

/**
 * struct okeoma - structs fro the strtok funtion
 * @cur_tok_st: holds the current token
 * @nxt_tok_st: holds the next token
*/
typedef struct okeoma
{
	char *cur_tok_st;
	char *nxt_tok_st;
} Tokenizer;

typedef struct variables
{
	char *cmd;
	char **av;
	char *tok;
	char *Name;
	char *ec;
	char *ok;
	char *old;
	char *new;
	char **command;
	int y;
	int status;
	int i;
	size_t n;
	ssize_t com_num;
	Tokenizer tokens;
	Tokenizer Hook;
	Tokenizer baxi;
	pid_t child_pid;
	bool it;
} okeoma;

void interactive(okeoma *oki);
void non_interactive(okeoma *oki);

void *p_Input();
void read_in(okeoma *oki);

void help_command(okeoma *oki);
void unsetenv_command(okeoma *oki);
void setenv_command(okeoma *oki);
void exit_command(okeoma *oki);
void cd_command(okeoma *oki);
int execute_command(okeoma *oki);
char *find_executable(okeoma *oki);
int execute_builtin_command(okeoma *oki);
void B_exc(okeoma *oki);
char *env_pos(okeoma *oki);
void free_all(okeoma *oki);
void f_tokenizer(okeoma *oki, char *cm);
char *s_tok(okeoma *oki, const char *delimiters);
void prs(okeoma *oki, char *coms);
void prs_2(okeoma *oki);
void _in(okeoma *oki, char **argv);
void my_free(size_t count, ...);
void read_input(char *buffer, int *buffer_pos, int *buffer_size);
char *_getline(char *buffer, int *buffer_pos, int *buffer_size);

#endif /* MAIN_H */