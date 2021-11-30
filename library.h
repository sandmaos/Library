#ifndef _LIBRARY_H_
#define _LIBRARY_H_
struct book_struct		//the books's information
{
	int id;
	char bookname[100];
	int year;
	int count;
	struct book_struct *next;
};

struct user_struct        //the user's sturct
{
	int bookcount;
	char username[10];
	char password[10];
	char booklist[40][40];
	struct stu_struct *next;		//A pointer to the next node
};

extern struct book_struct *bookhead, *bookend;
extern struct user_struct *head, *end;
extern int  book_count,user_count;
#endif
