#include "invertedIndex.h"

/* 
   function to backup database
Inputs:- address of hash table, filename
Outputs:- backup file
return value :- SUCCESS,FAILURE
*/
int save_DB(wlist_t **head, char *fname)
{
	/* create backup file in write mode*/
	FILE *fptr;
	fptr = fopen(fname,"w");
	if(!fptr)
	{
		printf("%sFailed to create backup file%s\n",RED,RESET);
		return FAILURE;
	}
	/*traverse all the indices of hash table*/
	int i=0;
	while(i<27)
	{
		/* skip index is pointer is NULL*/
		if(head[i] == NULL)
		{
			i++;
			continue;
		}
		/*print the index into backup file*/
		else
		{
			//print the index into backup file
			if(i==0)
			fprintf(fptr,"#%d;",i);
			else
			fprintf(fptr,"\n#%d;",i);
			backup_word(head[i],fptr);	//function call to backup all words in index
			i++;
		}
	}
	printf("%sSuccessful : %s%sDatabase saved in %s%s%s%s file.%s\n",GRN,RESET,BOLD,BLU,fname,RESET,BOLD,RESET);
	fseek(fptr,0L,SEEK_SET);
	return SUCCESS;
}

/*
   function to backup words
Inputs :- pointer to wordlist of an index,
		 file pointer of backup file.
Outputs :- words,filecount, filenames with word count
return value:- SUCCESS,
*/

int backup_word(wlist_t *head,FILE *fptr)
{
	/* traverse all word nodes*/
	wlist_t *temp1 = head;
	while(temp1)
	{
		fprintf(fptr,"\n%s;%d;",temp1->word,temp1->f_count);	//print the word and file count into backup file
		backup_files(temp1,fptr);
		temp1 = temp1->link;
	}
	return SUCCESS;
}


/* 
   function to backup files of wordnode
Inputs:- pointer to word node,
		 file pointer of backup file.
Outputs:- filenames with wordcount
return value :- SUCCESS
*/
int backup_files(wlist_t *wordnode,FILE *fptr)
{
	/* traverse the table_link_t file list*/
	table_link_t *temp = wordnode->t_link;
    while(temp)
    {
	    fprintf(fptr,"%s;%d;",temp->f_name,temp->w_count);	//print the filename and its wordcount into backup file
        temp = temp->link;
    }
    fprintf(fptr,"#");	//print "#" to backup file  before adding next index into backup
	return SUCCESS;
}



	



