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
#include <signal.h>
#include <time.h>

#define BUFFER_SIZE 1024
#define STO 1
#define STE 2
#define v (void)
#define MAX_PATH 4096

extern char **environ;

typedef struct environ_list
{
	char *NAME;
	char *value;
	struct environ_list *next;
} env_list;

/**
 * struct okeoma - structs for the strtok funtion
 * @cur_tok_st: holds the current token
 * @nxt_tok_st: holds the next token
*/
typedef struct
{
	char *cur_tok_st;
	char *nxt_tok_st;
} Tokenizer;

typedef struct variables
{
	char **command;
	char **av;
	char *tok;
	char *tok2;
	char *Name;
	char *ec;
	char *ok;
	char *old;
	char *path;
	char *cmd;

	int y;
	int status;
	int i;
	int check;

	size_t n;
	ssize_t com_num;

	Tokenizer tokens;
	Tokenizer Hook;
	Tokenizer baxi;

	env_list *head;

	pid_t mypid;
	pid_t child_pid;

	bool it;
} okeoma;

void interactive(okeoma *oki);
void non_interactive(okeoma *oki);

void *p_Input();
void read_in(okeoma *oki);

void env_command(okeoma *oki);
void get_env_command(okeoma *oki);
void find_char(okeoma *oki);
int find_set(char *str);
void unsetenv_command(okeoma *oki);
void setenv_command(okeoma *oki);
void exit_command(okeoma *oki);
void cd_command(okeoma *oki);
int execute_command(okeoma *oki);
char *find_executable(okeoma *oki);
int execute_builtin_command(okeoma *oki);
void B_exc(okeoma *oki);
void process(okeoma *oki);
void file(okeoma *oki, char *argv);
char *read_file(const char *filename);
char *read_lines(int fd);
int open_file(const char *filename);
char *env_pos(okeoma *oki);
void free_all(okeoma *oki);
int _put(const char *str);
int _putchar(char c);
char *s_tok(Tokenizer *tokenizer, const char *delimiters);
void f_tokenizer(Tokenizer *tokenizer, char *input_string);
void prs(okeoma *oki, char *coms);
void prs_2(okeoma *oki);
void _in(okeoma *oki, char **argv);
void my_free(size_t count, ...);
void read_input(char *buffer, int *buffer_pos, int *buffer_size);
char *_getline(char *buffer, int *buffer_pos, int *buffer_size);
void p(int stream, const char *format, ...);
void print_integer(int num, int n);
void print_string(char *s, int n);
void write_string(int n, const char *s);
int _isspace(int c);

void free_list(env_list *head);
void free_list_recursive(env_list *head);
char *get_env(env_list *env, const char *NAME);
env_list *list_from_env(char **env);
bool is_value(env_list *head, const char *value);
bool is_NAME(env_list *head, const char *NAME);
void print(env_list *head);
env_list *insert_env(env_list *head, const char *NAME, const char *value);
env_list *delete_match(env_list *head, char *delete_NAME);
void delete_duplicate(env_list *head);
env_list *revers_list(env_list *head);
void set_env_value(env_list *env, const char *NAME, const char *value);
/*-------------------------------------------------------------------*/
void _alias(okeoma *oki);
void define_alias(env_list *head, char *name);
env_list *add_alias(env_list *head, char *name, char *value);
void print_aliases(env_list *head, char *name);
void process_array(env_list *head, char **array);
int replace_with_alias(env_list *head, char *str);
char *get_cwd(void);

char *value(char *str);
bool checker(char *arr);
char *second(okeoma *oki, char *av);
char *first(env_list *head, char *av);
void int_char(int n1, int n2, char **str);
void r_char(int value, char* str, int base);
char *replace(env_list *head, okeoma *oki,char *value);
#endif /* MAIN_H */