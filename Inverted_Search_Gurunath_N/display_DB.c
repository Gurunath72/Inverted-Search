#include "invertedIndex.h"

/*
   function to display database
Inputs:- adress of hash table
Outputs :- database displayed
return value :- SUCCESS;
*/

int display_DB(wlist_t **head)
{
	/*traverse the indexes which has list*/
	int i=0;
	while(i<27)
	{
		if(head[i] == NULL)
		{
			i++;
			continue;
		}
		else
		{
			display_word(head[i],i);
			i++;
		}
	}
	return SUCCESS;
}


/*
   function to display word nodes
Inputs:- headpointer to word list of that index, index
Outputs :- for each word : word,file_count, word count of each file
return value :- SUCCESS;
*/
int display_word(wlist_t *head,int i)
{
	wlist_t *temp1 = head;
	int flag = 0;
	char word[52];
	char index[5];
	//traverse the w_list linked list of given index
	while(temp1)
	{
		sprintf(index,"[%d]",i);
		sprintf(word,"[%s]",temp1->word);
		if(flag == 0)
		{
			printf("%s%-7s%s%-10s%s",BLU,index,GRN,word,RESET);	//display index,first  word 
			flag = 1;
		}
		else
		{
			printf("%-7s%s%-10s%s"," ",GRN,word,RESET);	//display word
		}
		printf("%s%-3d%s",RED,temp1->f_count,RESET);	//print file count of current word
		printf("file(s) ");
		display_files(temp1);//function call to display files of current word
		temp1 = temp1->link;
	}
	return SUCCESS;
}

/* function to display filename and wordcount
Inputs:- pointer to wordnode
Outputs:- filenames with wordcount
return value:- SUCCESS;
*/
int display_files(wlist_t *wordnode)
{
	table_link_t *temp = wordnode->t_link;
	/* traverse the table_link_t list of files
	   and print filenames with their wordcount*/
	while(temp)
	{
		printf(": File : %s%s%-12s%s",BOLD,CYN,temp->f_name,RESET);
		printf("%s%d%s time(s) ",RED,temp->w_count,RESET);
		temp = temp->link;
	}
	printf("-> NULL\n");
	return SUCCESS;
}
		


