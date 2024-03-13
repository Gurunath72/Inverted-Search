#include "invertedIndex.h"

/* 
   function to create database
Inputs:- head pointer of valid files linked list, adress of hash table
Outputs :- database created
return value :- SUCCESS
*/

int create_DB(file_node_t *f_head, wlist_t **HT)
{
	//traverse all nodes of linked list
	// and parse words in the file
	while(f_head)
	{
		read_datafile(HT,f_head->f_name);
		f_head = f_head->link;
	}
	return SUCCESS;
}


/* 
   function to parse words from file
Inputs :- adress of hashtable, filename
Outputs :- database added with new file
return value :- None
*/
void read_datafile(wlist_t **arr, char *f_name)
{
	/*check if file exists*/
	FILE *fptr;
	fptr = fopen(f_name,"r");
	if(!fptr)
	{
		printf("%sError : %s%s%s%s%s is not existing%s\n",RED,RESET,BLU,f_name,RESET,BOLD,RESET);
	}
	/*if file exists, parse words from file and */
	int index;
	char word[NAMELENGTH];
	/* read word by word from file*/
	while(fscanf(fptr,"%s",word) != EOF)
	{
		int flag = 1;
		if(isalpha(word[0]) && isupper(word[0]))
		{
			index = word[0]-65;
		}
		else if(isalpha(word[0]) && islower(word[0]))
		{
			index = word[0]-97;
		}
		else if(!isdigit(word[0]))
		{
			index = 26;
		}
		/* if index is null , pointer in that index
		   is pointed to new word node created 
		   or if none of words added in index is matching
		   insert word node at last */
		if(arr[index] != NULL)
		{
			wlist_t *temp = arr[index];
			while(temp)
			{
				/*if word in node is matching 
				  update word count in the file*/
				if(strcmp(temp->word,word))
				{
					temp = temp->link;
				}
				else
				{
					flag = 0;
					update_word_count(&temp,f_name);
					break;
				}
			}		
		}
		if(flag == 1)
			insert_at_last_main(&arr[index],word,f_name);
	}
	printf("%sSuccesful : Creation of database for file %s%s%s\n",GRN,BLU,f_name,RESET);
}


/* 
   function to insert wordnode 
inputs :- adress of the pointer to first word node in word list,
          word, filename
outputs:- word node added with table_link_t node
return value:- FAILURE,SUCCESS
*/
int insert_at_last_main(wlist_t **head, char *word, char *f_name)
{
	wlist_t *new = malloc(sizeof(wlist_t));
	if(!new)
	{
		return FAILURE;
	}
	new->f_count =1;
	strcpy(new->word,word);
	new->link = NULL;
	new->t_link = NULL;
	update_link_table(&new,f_name);
	if(!*head)
	{
		*head = new;
		return SUCCESS;
	}
	wlist_t *temp = *head;
	while(temp->link)
	{
		temp = temp->link;
	}
	temp->link = new;
	return SUCCESS;
}


/* 
   function to add table_link_t node for wordnode
Inputs:- adress of pointer to wordnode, filename
Outputs :- word node updated with table_link_t
           file node
return value :- FAILURE,SUCCESS
*/

int update_link_table(wlist_t **word_node, char *f_name)
{
	table_link_t *new = malloc(sizeof(table_link_t));
	if(!new)
	{
		return FAILURE;
	}
	new->w_count =1;
	strcpy(new->f_name,f_name);
	new->link = NULL;
	if((*word_node)->t_link == NULL)
	{
		(*word_node)->t_link = new;
		return SUCCESS;
	}
	table_link_t *temp = (*word_node)->t_link;
	while(temp->link)
	{
		temp = temp->link;
	}
	temp->link = new;
	(*word_node)->f_count++;
	return SUCCESS;			
}


/*
   function to update word count in a file
Inputs :- pointer to wordnode, filename
Outputs :- current file updated with  word count
		   for given word
return value :- SUCCESS
*/

int update_word_count(wlist_t **temp, char *f_name)
{
	table_link_t *curr = (*temp)->t_link;
	while(curr)
	{
		if(strcmp(curr->f_name,f_name))
		{
			curr = curr->link;
		}
		else
		{
			curr->w_count++;
			return SUCCESS;
		}
	}
	update_link_table(temp,f_name);
	return SUCCESS;
}


