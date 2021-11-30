#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "library.h"
#include "Admin_Fun.h"
#include "Public_Fun.h"

void Borrow(struct user_struct *U){
	FILE *fp;
	fp=fopen("user_info","ab+");
	struct book_struct *B;
	char name_B[100];
	int sel=0;
	B=bookhead;
	printf("Which book you want :");
	getchar();
	gets(name_B);
	Sleep(600);system("cls");
	while(B!=NULL){
		if(strcmp(B->bookname,name_B)!=0){
			B=B->next;
		}								//Find the book in the linkedlist
		else if(B->count<1){
			printf("Book %s has no inventory!",&name_B);
			Sleep(2000);system("cls");
			return ;					//return as long as the book is not enough
		}
		else{
			B->count--;
			U->bookcount++;
			strcpy(U->booklist[U->bookcount-1] , name_B);
			break;							//add the book to the user's book list
		}
	}
	if(B==NULL){
		printf("Book %s is not in the booklist!\n",name_B);
		Sleep(2000);system("cls");
		return ;							//return if the book is not here
	}
	WriteFile(0);
	WriteFile(1);
	fclose(fp);
	printf("Borrow Successful!!!\n");
	Sleep(2000);system("cls");
}										//Allow the student to borrow books from the library.

void Return(struct user_struct *U){
	struct book_struct *B;
	int num=0 , arr=0;
	char name_R[40],null[40]="";
	printf("Please input bookname : ");
	getchar();	gets(name_R);	Sleep(200);
	while(arr<=U->bookcount){
		if(arr==U->bookcount){
			printf("You don't have this book!");
			Sleep(2000);
			return ;			//return if the user do not have such a book
		}
		if(strcmp(U->booklist[arr],name_R)==0)
			break;
		arr++;
	}
	strcpy(U->booklist[arr],null);		//clear the array for the returned book
	printf("%s",U->booklist[arr]);
	B=bookhead;
	while(B!=NULL){
		if(strcmp(B->bookname,name_R)==0)
			break;
		B=B->next;
	}
	if(B!=NULL)
		B->count++;					//add the book back to the library system
	int count=arr;					//adjust count to the present char array
	while(count<U->bookcount){
		strcpy(U->booklist[count],U->booklist[count+1]);
		count++;					//make sure the next adding book is always at last
	}
	U->bookcount--;
	WriteFile(0);
	WriteFile(1);
	printf("***Book %s is returned***!!!System leaping...",name_R);
	Sleep(2500);
}										//Allow the student to return books to the library.

void user_register(){
	struct user_struct *p;
	p=head;
	int sel=0;
	char user_N[30];
	printf("\t\t\t\tCreate an account to use library system! \n\t\t\t\t\t\tUser name: ");
	scanf("%s",&user_N);
	Sleep(1200);system("cls");
	if (user_count==0){
		strcpy(head->username,user_N);
		head->bookcount=0;
		end=head;
		end->next=NULL;
	}									//add as the first student
	else{
		while(p!=NULL){
			if(strcmp(p->username,user_N)==0){
			printf("User already exist!\n");
			Sleep(1800);system("cls");
			return;
			}
			p=p->next;
		}
			p=(struct user_struct*)malloc(sizeof(struct user_struct));		//now p is pointing at the end
			p->bookcount=0;
			strcpy(p->username,user_N);
			end->next=p;
			end=p;
			end->next=NULL;
	}
		p=head;
		FILE *fp;
		fp=fopen("user_info","w");
		while(p!=NULL){
			fwrite(p,sizeof(struct user_struct),1,fp);
			p=p->next;
		}
		fclose(fp);
		user_count++;
		printf("User %s signed up successful!\nSystem leaping in 2 seconds...",end->username);
		Sleep(2000);
		system("cls");
	return ;
}							// Help the unsigned students to sign up to the system.

void user_login(){
	void user_fun();
	struct user_struct *p;
	p=head;
	int sel=0;
	char name_u[30];
	if (user_count==0){
		printf("No users exists!Sign up first!");
		Sleep(1400);
		system("cls");
		return ;				 //return if no users exist
	}
	else{
	printf("Please input username: ");
	scanf("%s",name_u);
	Sleep(200);
	system("cls");
	while(p!=NULL){
		if(strcmp(p->username,name_u)==0){
			printf("Welcome, %s!\n",p->username);
			Sleep(1800);system("cls");
			break;
		  }
		else p=p->next;					//find the user in the library system
   	  }
	if(p==NULL){
		printf("User name is wrong or not exists!");
		Sleep(2200);system("cls");
		return ;							//return if the user not here
	}
	user_fun(p);
	return ;
	}
}									// Allow the registered student get into the system

void user_interface(){
	int end2=0,select;
	while (1)
		{
		printf("\t\t\t\t\t>>>>>>The Student Interface<<<<<<\n\n\t\t\t\t\t\t=======================\n\t\t");
		printf("\t\t\t\t| 1.  Students Login   | \n\t\t\t\t\t\t| 2.  Students Sign Up | \n\t\t\t\t\t\t| 0.      Exit         | \n\t\t\t\t\t\t=======================\n\n\t\t\t\t\t  Pease input your choice: ");
		scanf("%d", &select);
		printf("\n\nSystem automatically leap in 2 seconds...\n");
		Sleep(1200);										//adjust the interface
		system("cls");
		switch (select)
		{
		case 1:
		{
			user_login();
			break;
		}
		case 2:
		{
			user_register();
			break;
		}
		case 0:
		{
			end2 = 1;
			break;
		}
		default:
			printf("Error input! Try again: \n");
			Sleep(1000);
		}
		system("cls");
		if (end2 == 1)
			break;
		}
}								//The interface for the students. Switch sytnax used to judge the situation

void user_fun(struct user_struct *userS){
	int end3=0,select=0;
		while (1)
		{
		printf("\t\t\t\t\t>>>>>>The Students Library Function<<<<<<\n\n\t\t\t\t\t\t================\n\t\t\t\t\t\t| ");
		printf("1.  BookList  | \n\t\t\t\t\t\t| 2.  Search    | \n\t\t\t\t\t\t| 3.  Borrow    | \n\t\t\t\t\t\t| 4.  Return    | \n\t\t\t\t\t\t| 0.   Exit     | \n\t\t\t\t\t\t================\n\n\t\t\t\t\t  Please input your choice: ");
		scanf_s("%d", &select);
		printf("\n\nSystem automatically leap in 2 seconds...\n");
		Sleep(1200);
		system("cls");
		switch (select)
		{
		case 1:
		{
			BookList();
			break;
		}
		case 2:
		{
			Search();
			break;
		}
		case 3:
		{
			Borrow(userS);
			break;
		}
		case 4:
		{
			Return(userS);
			break;
		}
		case 0:
		{
			end3 = 1;
			break;
		}
		default:
			printf("Error input! Try again: \n");
			Sleep(1000);
		}
		system("cls");
		if (end3 == 1)
			break;
		}
	}						//Print a list of the functions which allows the student to operate.Switch sytnax used to judge the situation
