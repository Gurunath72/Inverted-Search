/*************************************************************************
Name :- Gurunath N
Date :- 17/07/2023
Description :- Implement the inverted search using hash algorithms
*************************************************************************/

#include "invertedIndex.h"

int main(int argc, char *argv[])
{
	//if argument count is <2 , file arguments not passed , hence print error
	if(argc <2)
	{
		printf("%sError :%s%s Invalid no of arguments\n%sUsage :%s%s ./inverted_index.exe <file1.txt>  <file2.txt> ...%s\n",RED,RESET,BOLD,RED,RESET,BOLD,RESET);
		return FAILURE;
	}
	//intialize a head pointer for file_node_t linked list
	file_node_t *f_head = NULL;
	//call function to validate files given in cla
	validate_n_store_filenames(&f_head, argv+1);
	/* after validation if f_head is null , no files are valid*/
	if(!f_head)
	{
		printf("%sThere is no valid files\nPlease enter valid files%s\n",RED,RESET);
		return FAILURE;
	}
	else
	{
		//initialize an array of struct pointer with NULL;
		wlist_t *HT[27] ={0};
		char ch = 'y';
		int choice;
		//declaration of arrays to read word, update word, backup file 
		char word[NAMELENGTH];
		char update[NAMELENGTH];
		char backup_file[NAMELENGTH];
		//display menu if user enters 'y/Y'
		while(ch=='y' || ch=='Y')
		{
			//print menu and read choice
			printf("%s%s1. Create Database\n2. Display Database\n3. Search Database\n4. Update Database\n5. Save Database%s\n",BOLD,BLU,RESET);
			printf("%sPlease enter your choice : %s",RED,RESET);
			scanf("%d",&choice);
			switch(choice)
			{
				case 1 : 
						int create_DB_flag = create_DB(f_head,HT);
						break;
				case 2 :
						display_DB(HT);
						break;
				case 3 :
						printf("%s%sEnter the word to be searched in database : %s",BOLD,CYN,RESET);
						scanf("%s",word);
						search_DB(HT,word);
						break;
				case 4 :
						printf("%s%sEnter the filename to be added in Database : %s",BOLD,MAG,RESET);
						scanf("%s",update);
						update_DB(&f_head,HT, update);
						break;
				case 5 :
						printf("%s%sEnter the backup filename : %s",BOLD,MAG,RESET);
						scanf("%s",backup_file);
						save_DB(HT,backup_file);
						break;
			}
			printf("%sDo you want to continue :%s",BOLD,RESET);
			__fpurge(stdin);
			scanf("%c",&ch);
		}
	}
	return 0;
}

/* 
function to validate n store filenames in linked list
Inputs :- filenames,head pointer of linked list
Outputs :- linked list added with valid filenames
return values :- None 
*/

void validate_n_store_filenames(file_node_t **head, char *filenames[])
{
	int i=0;
	int valid_flag =0;
	while(filenames[i] != NULL)
	{
		if((valid_flag = IsFileValid(filenames[i]))== NOT_PRESENT)
		{
			printf("%sError : %s%sThe file %s is not present.%s\n%sSo this file is not added to list%s\n",RED,RESET,BOLD,filenames[i],RESET,CYN,RESET);
		}
		else if(valid_flag == FILE_EMPTY)
		{
			printf("%sError : %s%sThe file %s is empty.%s\n%sSo this file is not added to list%s\n",RED,RESET,BOLD,filenames[i],RESET,CYN,RESET);
		}
		else
		{
			int rep_flag = store_filenames_to_list(filenames[i],head);
			if(rep_flag == REPEATED)
			{
				printf("%sError : %s%sThe file %s is repeated%s\n%sSo this file is not added to list%s\n",RED,RESET,BOLD,filenames[i],RESET,CYN,RESET);
			}
			else if(rep_flag == FAILURE)
			{
				printf("%sError : %s%sfile node creation failed.%s\n%sSo this file is not added to list%s\n",RED,RESET,BOLD,RESET,CYN,RESET);
			}
			else
			{
				printf("%sSuccessful :  %s%s%s%s%s added to list%s\n",GRN,RESET,BLU,filenames[i],RESET,BOLD,RESET);
			}
		}
		i++;
	}
}

/* 
function to check if file is valid
Inputs :- file name
Outputs :- NOne
return values :- NOT_PRESENT,FILE_EMPTY,SUCCESS;
*/
int IsFileValid(char *f_name)
{

		FILE *fptr;
		fptr = fopen(f_name,"r");
		if(!fptr)
		{
			return NOT_PRESENT;
		}
		fseek(fptr,0L,SEEK_END);
		if(ftell(fptr) == 0)
		{
			return FILE_EMPTY;
		}
		fseek(fptr,0,SEEK_SET);
		return SUCCESS;		
}

/*
   function to store filenames
Inputs :- filename, adress of Head pointer of linked list
Outputs :- linked list added with filename
return value :- REPEATED, SUCCESS
*/

int store_filenames_to_list(char *f_name, file_node_t **head)
{
	file_node_t *new = malloc(sizeof(file_node_t));
	if(!new)
	{
		return FAILURE;
	}
	strcpy(new->f_name,f_name);
	new->link = NULL;
	if(!*head)
	{
		*head = new;
		return SUCCESS;
	}
	file_node_t *temp = *head;
	file_node_t *prev = NULL;
	while(temp)
	{
		if(strcmp(temp->f_name,f_name)==0)
		{
			return REPEATED;
		}
		prev = temp;
		temp = temp->link;
	}
	prev->link = new;
	return SUCCESS;
}






