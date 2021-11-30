#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "library.h"
#include "Public_Fun.h"
#include "User_Fun.h"
#define PIN "OS"			//the administrator's password

void Add_Books(){
  	struct book_struct *p;
  	char book_name[80];
  	FILE *fp;
  	system("cls");
  	if (book_count == 0){				 //add the first book
  		printf("~~~Add  Book~~~:\n");
  		getchar();		gets(book_name);
  		strcpy(bookhead->bookname, book_name);
  		printf("id: \n");
  		scanf("%d", &bookhead->id);
  		printf("bookyear: \n");
  		scanf("%d", &bookhead->year);
  		printf("book count:");
  		scanf("%d", &bookhead->count);
  		bookend = bookhead;				//the bookhsed is already "malloced"
  		bookend->next = NULL;			 //create new pointer
  	}
  	else{
  		int exist=0;
  		printf("Input the book name:\n");
  		getchar();		gets(book_name);
  		p=bookhead;
  		while(p!=NULL){
  			if(strcmp(p->bookname,book_name)==0){
  				exist=1;
  				break;
  			}
  			p=p->next;
  		}
  		if(exist==1){				//only add numbers if the book is already exists
  			int num;
  			printf("Choose the number of books you want add: ");
  			scanf("%d",&num);
  			p->count+=num;
  		}
  		else{
  			p = (struct book_struct *)malloc(sizeof(struct book_struct));
  			strcpy(p->bookname,book_name);
  			printf("~~~Add New Books~~~ \nid: \n");
  			scanf("%d", &p->id);
  			printf("bookyear: \n");
  			scanf("%d", &p->year);
  			printf("book count:");
  			scanf("%d", &p->count);
  			bookend->next = p;			//create space for the last pointer and let p into the pointer
  			bookend = p;				//p is pointing at the new last book
  			bookend->next = NULL;
  		}
  	}
  	book_count+=1;
  	p = bookhead;
  	fp = fopen("book_info", "w");
  	while (p != NULL)
  	{
  		fwrite(p, sizeof(struct book_struct), 1, fp);
  		p = p->next;
  	}								 //update the information
  	fclose(fp);		Sleep(200);
  	system("cls");
  	printf("Adding book complete!\nAutomatically back to the interface in 2 seconds....\n");
  	Sleep(1700);	system("cls");
  }										//Add books to the library.
  

void Delete(){
	struct book_struct *bookD;
	int exist = 0;
	char book_name[50];
	bookD = bookhead;
	printf("Input which book you want to remove: \n");
	getchar();
	gets(book_name);
	Sleep(1000);
	system("cls");
	while (bookD != NULL){
		if (strcmp(bookD->bookname, book_name) == 0) {
				exist = 1;
				break;
			}
		bookD = bookD->next;				//judge the book's existance
	}
	if (!exist) {
		printf("Book %s is not here...\n",book_name);
		return ;
	}
	bookD=bookhead;
	if(strcmp(book_name,bookhead->bookname)==0)
		bookhead=bookhead->next;			//judge the book's existance
	else{
		while(bookD->next!=NULL){
			if(strcmp(bookD->next->bookname,book_name)==0){		//find the book in the sequence
				if(bookD->next->next==NULL)
					bookD->next=NULL;
				else
					bookD->next=bookD->next->next;				//leaping this book
				break;
			}
			bookD=bookD->next;
	 	}
	}
	printf("Book <%s> is removed successfully!",book_name);
	Sleep(2200);system("cls");
	WriteFile(0);
	}													//Delete the book in the library
	
void UserList(){
  	int sel;
  	int num=0;
  	struct user_struct *U;
  	U=head;
  	if(user_count==0){
  		printf("No users!");
  		Sleep(1400);system("cls");
  		return ;									 //return if no users were added
  	}
  	printf("\t\t\t\t\t\t   ~~~USER LIST~~~\n\n");
  	while(U!=NULL){
  		printf("\t\t\t\t\t\t     ###%s###\n\t\t\tBookname \t\t\t\t\t\t    Count\n\t\t\t-----------------------------------------------------------------\n",U->username);
  		int order=0,order1=0;
  		while(order<U->bookcount){
  			if(order==0){
  				int c2=0,c3=0;
  				while(c2<U->bookcount){
  					if(strcmp(U->booklist[c2],U->booklist[0])==0){
  						c3++;
  					}
  					c2++;
  					}
  				printf("\t\t\t%-39s%24d\n\t\t\t-----------------------------------------------------------------\n",U->booklist[0],c3);
  			}											//the first book don't have to compare with the previous book
  			else{
  				order1=0;
  				int c=0,c1=0;
  				while(c<order){
  					if(strcmp(U->booklist[c],U->booklist[order])!=0){
  						c1++;
  					}
  					c++;
  				}
  				if(c1==c){								//to judge whether the previous book is repeated
  					int count=order;						//while not repeated, run
  					while(count<U->bookcount){
  						if(strcmp(U->booklist[count],U->booklist[order])==0){
  							order1++;
  						}
  						count++;
  					}
  					printf("\t\t\t%-39s%24d\n\t\t\t-----------------------------------------------------------------\n",U->booklist[order],order1);
  				}
  			}
  			order++;
  		}
  		putchar('\n');
  		num+=1;
  		U=U->next;				//the pointer is pointing to the next user
  	}
  	printf("\t\t\t\t\t\t     Total user:%d\n",num);
  	printf("Input 0 to exit: ");
  	scanf("%d",&sel);
  	while(sel!=0){
  		printf("Error! Try again: ");
  		scanf("%d",&sel);
  	}
  	printf("System leaping...");
  	Sleep(1200);
  	system("cls");
  }

void admin_fun(){
	char password[30];
	printf("Input Password: ");
	getchar();gets(password);
	if(strcmp(password,PIN)!=0){
		printf("WRONG!!!SYSTEM LEAPING...");
		Sleep(2400);system("cls");
		return ;
	}
	printf("WELCOME!");
	Sleep(2400);system("cls");
	
  	int end2=0,select=0;
  	while(1){
  		printf("\t\t\t\t\t >>>> The Management System<<<<\n\n\t\t\t\t\t\t================\n\t\t\t\t\t\t| 1. Add Books  |\n\t\t\t\t\t\t| 2.  Search    |\n\t\t\t\t\t\t| 3.  Delete    |\n");
  		printf("\t\t\t\t\t\t| 4.  BookList  |\n\t\t\t\t\t\t| 5.  UserList  |\n\t\t\t\t\t\t| 0.   Exit     | \n\t\t\t\t\t\t================\n\n\t\t\t\t\t    Please input your choice: ");
  		scanf_s("%d", &select);
  		Sleep(400);  system("cls");
  		switch(select)
  		{
  			case 1:
  			{
  				Add_Books();
  				break;
  			}
  			case 2:
  			{
  				Search();
  				break;
  			}
  			case 3:
  			{
  				Delete();
  				break;
  			}
  			case 4:
  			{
  				BookList();
  				break;
  			}
  			case 5:
  			{
  				UserList();
  				break;
  			}
  			case 0:
  			{
  				end2 = 1;
  				break;
  			}
  			default:{
  				printf("Error input!Try again\n");
  				Sleep(1000);
			}	
  	  	}
  	  	system("cls");
  		if (end2 == 1)
  			break;
  	}
  }
