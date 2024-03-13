#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio_ext.h>

#define SUCCESS 0
#define FAILURE -1
#define NOELEMENT -2
#define EMPTYLIST -3
#define REPEATED -4
#define FILE_EMPTY -5
#define NOT_PRESENT -6

#define RED   "\x1B[1;31m"
#define GRN   "\x1B[1;32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[1;34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
#define BOLD  "\x1B[1m"

#define SIZE 27
//#define BUFF_SIZE 255
#define NAMELENGTH 50

//inverted table

typedef struct table_link
{
	char f_name[NAMELENGTH];
	int w_count;
	struct table_link *link;
}table_link_t;

typedef struct node
{
	int f_count;
	char word[NAMELENGTH];
	struct node *link;
	table_link_t *t_link;
}wlist_t;

typedef struct file_node
{
    char f_name[NAMELENGTH];
    struct file_node *link;
}file_node_t;

/* File validation */
void validate_n_store_filenames(file_node_t **, char *filenames[]);
int IsFileValid(char *);
int store_filenames_to_list(char *f_name, file_node_t **head);

/*Create DB*/
int create_DB(file_node_t *file_head, wlist_t **head);
void read_datafile(wlist_t **, char *f_name);
int insert_at_last_main(wlist_t **head, char *word, char *f_name);
int update_link_table(wlist_t **word_node, char *f_name);
int update_word_count(wlist_t **temp, char *);

/*Display*/
int display_DB(wlist_t **head);
int display_word(wlist_t *head,int i);
int display_files(wlist_t *wordnode);

/*search */
int search_DB(wlist_t **head, char *word);
int search_files(wlist_t *wordnode);

/*Save*/
int save_DB(wlist_t **head, char *fname);
int backup_word(wlist_t *head,FILE *fptr);
int backup_files(wlist_t *wordnode,FILE *fptr);

/*Update */
int update_DB(file_node_t **, wlist_t **, char *f_name);



#endif
