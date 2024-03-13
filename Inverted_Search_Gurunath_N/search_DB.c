#include "invertedIndex.h"

/*
   function to search database
Inputs :- adress of hashtable, word
Outputs:- file_count of word and filenames with wordcount
return value :- SUCCESS,FAILURE
*/
int search_DB(wlist_t **head, char *word)
{
	//calculate hashindex of word
	int index;
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
	//if index is NULL, list is empty hence print error
	if(head[index] == NULL)
	{
		printf("%sError : %s%sword %s%s%s%s not found in the Database%s\n",RED,RESET,BOLD,GRN,word,RESET,BOLD,RESET);
		return FAILURE;
	}
	//traverse the word list 
	wlist_t *temp = head[index];
	while(temp)
	{
		//if word is found , print file_count and call search_files()
		if(strcmp(temp->word,word))
		{
			temp = temp->link;
		}
		else
		{
			printf("%sword %s%s%s%s found in the Database and it is present in %s%d%s%s file(s)%s\n",BOLD,GRN,temp->word,RESET,BOLD,BLU,temp->f_count,RESET,BOLD,RESET);
			search_files(temp);//function call to print the files 
			return SUCCESS;
		}
	}
	printf("%sError : %s%sword %s%s%s%s not found in the Database%s\n",RED,RESET,BOLD,GRN,word,RESET,BOLD,RESET);
	return FAILURE;
}

/*
   function to search files for a wordnode
Inputs :- pointer to wordnode
Outputs :- filenames with wordcount
return value :- SUCCESS;
*/
int search_files(wlist_t *wordnode)
{
	/* traverse table_link_t file nodes*/
	table_link_t *temp = wordnode->t_link;
	while(temp)
	{
		printf("%sIn file %s%s%s  %s%d%s%s time(s)%s\n",BOLD,GRN,temp->f_name,RESET,BLU,temp->w_count,RESET,BOLD,RESET);//print the filename and word count
		temp = temp->link;
	}
	return SUCCESS;
}


			
