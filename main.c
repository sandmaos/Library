#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "library.h"
#include "User_Fun.h"
#include "Admin_Fun.h"
#include "Public_Fun.h"

struct book_struct *bookhead , *bookend ;
struct user_struct *head , *end ;									
int  book_count ,user_count;													//two variates book_count and user_count are used to judge whether the file is empty or not

void main(){
	bookhead = NULL, bookend = NULL;
	head = NULL, end = NULL;	
	
	FILE *fp;
	bookhead = (struct book_struct *)malloc(sizeof(struct book_struct));
	head = (struct user_struct *)malloc(sizeof(struct user_struct));			//create head pointer and end pointer

	fp = fopen("book_info", "a+");
	book_count=fread(bookhead,sizeof(struct book_struct),1,fp);
	fclose(fp);
	bookend=bookhead;
	read_bookfile();

	fp = fopen("user_info", "a+");
	user_count=fread(head,sizeof(struct user_struct),1,fp);
	fclose(fp);
	end=head;
	read_userfile();					//Initialize the bookfile, if don't exist, create a new one

	int select;
	int end1 = 0,end2=0;
  	system("color 8f");
	while(1){
		printf("\t\t\t\t    >>>>>>Welcome to the library system!<<<<<<\n\n\t\t\t\t\t\t===================\n");
		printf("\t\t\t\t\t\t| 1.   Student     |\n\t\t\t\t\t\t| 2. Administrator |\n\t\t\t\t\t\t| 0.    EXIT   \t   |\n\t\t\t\t\t\t===================\n\n\t\t\t\t\t   Choose to entry the system: ");
		scanf("%d", &select);										 //creating the and adorn the interface
		printf("System leap in 2 seconds...");
		Sleep(1800);
		system("cls");
		switch(select){
			case 1:{
				user_interface();
				break;
	 	 	}
			case 2:{
				admin_fun();
				break;
	  		}
			case 0:{
				end1=1;
				break;
	  		}
			default:
				printf("error input!\n");						//avoid inaviled inputing
		}
		if(end1==1)
			break;
	}
}
