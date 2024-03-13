#include "invertedIndex.h"

/*
   function to update database
Inputs :- head pointer of valid files linked list 
		  adress of hash table, file name
OUtputs:- database updated with new file
return value :- NOT_PRESENT, REPEATED,FILE_EMPTY,SUCCESS,FAILURE
*/
int update_DB(file_node_t **f_head, wlist_t **head, char *f_name)
{
	/* validate the given file*/
	int valid_flag =0;
	if((valid_flag = IsFileValid(f_name))== NOT_PRESENT)
	{
		printf("%sError : %s%sThe file %s%s%s%s is not present.%s\n%sSo this file is not added to list%s\n",RED,RESET,BOLD,BLU,f_name,RESET,BOLD,RESET,CYN,RESET);
		return FAILURE;
	}
	else if(valid_flag == FILE_EMPTY)
	{
		printf("%sError : %s%sThe file %s%s%s%s is empty.%s\n%sSo this file is not added to list%s\n",RED,RESET,BOLD,BLU,f_name,RESET,BOLD,RESET,CYN,RESET);
		return FAILURE;
	}	
	/* if file is valid and not repeated , store filename in valid files linked list*/
	else
	{
		int rep_flag = store_filenames_to_list(f_name,f_head);
		if(rep_flag == REPEATED)
		{
			printf("%sError : %s%sThe file %s%s%s%s is repeated%s\n%sSo this file is not added to list%s\n",RED,RESET,BOLD,BLU,f_name,RESET,BOLD,RESET,CYN,RESET);
			return FAILURE;
		}
		else if(rep_flag == FAILURE)
		{
			printf("%sError : %s%sfile node creation failed.%s\n%sSo this file is not added to list%s\n",RED,RESET,BOLD,RESET,CYN,RESET);
		}
		else
		{
			printf("%sSuccessful :  %s%s%s%s%s added to list%s\n",GRN,RESET,BLU,f_name,RESET,BOLD,RESET);
		}
	}
	//parse words of the file
	read_datafile(head,f_name);
	return SUCCESS;
}

	
	
