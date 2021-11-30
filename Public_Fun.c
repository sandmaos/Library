#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "library.h"
#include "Admin_Fun.h"
#include "User_Fun.h"


void Search(){									//this Function is for both users and the administrator
	struct book_struct *S;
	S=bookhead;
	int c = 0;
	char name_S[100];
	if(book_count==0){
		printf("No books!");
		Sleep(1200);system("cls");
		return;								//return if no books in the library shift
	}
	printf("Which book to find: ");
	getchar();
	gets(name_S);
	printf("Id\tBookname\tYear\t  count\n");
	while (S != NULL)
	{
		if(strcmp(S->bookname,name_S)==0)
		{
			printf("%d \t%-15s %-10d %d\n",S->id,S->bookname,S->year,S->count);
			c=1;
			break;
		}												
		S=S->next;									//find the book matches the input
	}
	if(c==0)
		printf("No books were found");
	printf("\nInput 0 and go to the interface: ");
	int n;
	scanf("%d", &n);
	while (1)
	{
		if (n == 0)
			break;
		else
		{
			printf("Retry: ");
			scanf("%d", &n);
		}
	}
	system("cls");
}													//Allow the students and the administrator find the book in the library shift.

void BookList(){
	int sel;
	int num=0;
	struct book_struct *S;
	S=bookhead;
	if(book_count==0){
		printf("No books!");
		Sleep(1400);system("cls");
		return ;								//return if no books in the booklist
	}
	printf("\t\t\t\t\t\t~~~BOOK LIST~~~\n\n\t\t\tId\t  Bookname \t\t\t\t  Year\t  Quantity \n\t\t\t------------------------------------------------------------------\n");
	while(S!=NULL){
		printf("\t\t\t%-10d%-39s %-10d%d\n\t\t\t------------------------------------------------------------------\n",S->id,S->bookname,S->year,S->count);
		num+=1;
		S=S->next;
	}
	printf("\t\t\t\t\t   Total sorts of book:%d",num);
	printf("\nInput 0 to exit: ");
	scanf("%d",&sel);
	while(sel!=0){
		printf("Error! Try again: ");
		scanf("%d",&sel);
	}
	printf("System leaping...");
	Sleep(1200);
	system("cls");
}											//Print a list of the stored book in the library for both students and the administrator.

void WriteFile(int flag){
	FILE *fp;
	struct user_struct *userp;
	struct book_struct *bookp;
	userp = head;
	bookp = bookhead;
	if (flag == 1)							//write the uesrs' file
	{
		fp = fopen("user_info", "w");
		while (userp != NULL)
		{
			fwrite(userp, sizeof(struct user_struct), 1, fp);
			userp = userp->next;
		}
	}
	else if(flag==0)						//write the books' file
	{
		fp = fopen("book_info", "w");
		while (bookp != NULL)
		{
			fwrite(bookp, sizeof(struct book_struct), 1, fp);
			bookp = bookp->next;
		}
	}
	fclose(fp);
}										//Updating the previous data if was changed and create a new file in the folder.

void read_bookfile(){
	struct book_struct *p;
	p=bookhead;
	FILE *fp;
	fp=fopen("book_info","ab+");
	while (fread(p, sizeof(struct book_struct), 1, fp))
	{
		if (p->next != NULL)
		{
			p = (struct book_struct *)malloc(sizeof(struct book_struct));
			bookend->next = p;
			bookend = p;
			bookend->next = NULL;
		}
	}
	fclose(fp);
}											//Initialize the book struct from the created file

void read_userfile(){
	struct user_struct *p;
	p=head;
	FILE *fp;
	fp=fopen("user_info","ab+");
	while (fread(p, sizeof(struct user_struct), 1, fp))
	{
		if (p->next != NULL)
		{
			p = (struct user_struct *)malloc(sizeof(struct user_struct));
			end->next = p;
			end = p;
			end->next = NULL;
		}
	}
	fclose(fp);
}									//Initialize the user struct from the created file.
