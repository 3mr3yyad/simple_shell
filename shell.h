#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>


/* nom_conv  */

#define lwcase_conv	1
#define unsigned_conv	2


#define fub_blush -1
#define rd_fub_size 1024
#define wr_fub_size 1024


/* gline */
#define gline 0
#define stark 0


/* chains */
#define norm_prom	0
#define or_prom		1
#define and_prom	2
#define chain_prom	3


#define file_hst	".simple_shell_history"
#define max_hst	4096


extern char **environ;

/**
 * struct liststr - linked list main
 * @nom: number
 * @str: string
 * @next: the next node
*/

typedef struct liststr
{
	int nom;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo arg and pass it into a function,
 *					allowing uniform prototype for function pointer struct
 *
 *@arg: a string
 *@argv: array of strings
 *@path: the command str path
 *@argc: argument count
 *@countln: counts err
 *@nom_error: exti err nom
 *@countlnf: counts iputs of the line
 *@namef: filename of the programme
 *@env: environ linked list copy
 *@environ: points to array of pointers to strings
 *@history: node of history
 *@alias: node of alias
 *@chmd_env: in case of changing environment
 *@stts: last excuted command status
 *@fub_prom: address of fub_prom in case its chained
 *@fub_type_prom: shell tools
 *@rdfd: reading line of file discribtion
 *@counthst:  history of line number counts
 */

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int countln;
	int nom_error;
	int countlnf;
	char *namef;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int chmd_env;
	int stts;

	char **fub_prom; /* pointer to cmd ; chain buffer, for memory mangement */
	int fub_type_prom; /* CMD_type ||, &&, ; */
	int rdfd;
	int counthst;
} info_t;


#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}


/**
 *struct builtin - related functions and builtin str
 *@type: flag of builtin command
 *@func: function
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* hsh.c */
int hsh(info_t *, char **);
int bltn_fnd(info_t *);
void prom_fnd(info_t *);
void prom_fork(info_t *);

/* 20-path.c */
int prom_being(info_t *, char *);
char *chr_pud(char *, int, int);
char *pathfnd(info_t *, char *, char *);

/* loophsh.c */
int hsh_lp(char **);

/* 19-chain.c */
int chain_being(info_t *, char *, size_t *);
void chain_st(info_t *, char *, size_t *, size_t, size_t);
int alias_mv(info_t *);
int var_mv(info_t *);
int str_mv(char **, char *);

/* 18-str_func_error.c */
void _puts_error(char *);
int _putchar_error(char);
int fd_put(char c, int d_file);
int fd_puts(char *str, int d_file);

/* 01-str_func_1.c */
int strlng(char *);
int promstr(char *, char *);
char *inc_start(const char *, const char *);
char *cat_str(char *, char *);

/* 02-str_func_2.c */
char *cp_str(char *, char *);
char *pud_str(const char *);
void _puts(char *);
int _putchar(char);

/* 03-str_func_3.c */
char *cp_strn(char *, char *, int);
char *cat_strn(char *, char *, int);
char *cr_str(char *, char);

/* 04-str_func_4.c */
char **convw_str(char *, char *);
char **conv2w_str(char *, char);

/* 05-memo_func_1.c */
char *set_memo(char *, char, unsigned int);
void free_str(char **);
void *loc_fr(void *, unsigned int, unsigned int);

/* 06-memo_func_2.c */
int free_ptr(void **);

/* 07-more_func_1.c */
int act_er(info_t *);
int deli_st(char, char *);
int alp_st(int);
int a2i(char *);

/* 08-more_func_2.c */
int a2i_err(char *);
void f_err(info_t *, char *);
int f_deci(int, int);
char *nom_conv(long int, int, int);
void cmt_rm(char *);

/* 15-io_func.c */
char *file_ghst(info_t *info);
int hst_wr(info_t *info);
int hst_rd(info_t *info);
int hst_lst_bld(info_t *info, char *buf, int linecount);
int hst_renom(info_t *info);

/* 16-str_ls_1.c */
list_t *noded(list_t **, const char *, int);
list_t *end_noded(list_t **, const char *, int);
size_t str_lstf(const list_t *);
int rm_ind_node(list_t **, unsigned int);
void frlst(list_t **);

/* 17-str_ls_2.c */
size_t lng_lst(const list_t *);
char **lst_2str(list_t *);
size_t lstf(const list_t *);
list_t *start_node_with(list_t *, char *, char);
ssize_t gind_node(list_t *, list_t *);

/* 09-emulator_tools_1.c */
int exit_sh(info_t *);
int cd_cwd(info_t *);
int cd_hlp(info_t *);

/* 10-emulator_tools_2.c */
int lst_hst(info_t *);
int alias_man(info_t *);

/* 11-liner.c */
ssize_t ginput(info_t *);
int g_ln(info_t *, char **, size_t *);
void y_blocks(int);

/* 12-info.c */
void info_cl(info_t *);
void int_info(info_t *, char **);
void _frinfo(info_t *, int);

/* 13-envir_1.c */
char *_genvir(info_t *, const char *);
int fenvir(info_t *);
int fset_envir(info_t *);
int funset_envir(info_t *);
int poplst_envir(info_t *);

/* 14-envir_2.c */
char **genvir(info_t *);
int un_envir(info_t *, char *);
int st_envir(info_t *, char *, char *);

#endif
