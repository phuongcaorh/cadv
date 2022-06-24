#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INITIAL_SIZE 10
#define INCREMENTAL_SIZE 5

typedef struct {
	char name[80];
	long number;
} PhoneEntry;

typedef struct {
	PhoneEntry * entries;
	int total;
	int size;
} PhoneBook;

PhoneBook createPhoneBook();
void dropPhoneBook(PhoneBook* book);
void addPhoneNumber(char * name, long number, PhoneBook* book);
PhoneEntry * getPhoneNumber(char * name, PhoneBook book);
  
int main()
{
    int i, n;
    long sdt;
    char name[80];
    PhoneEntry *entry;
    PhoneBook book;
    book = createPhoneBook();
    addPhoneNumber("Anh", 983984775, &book);
    addPhoneNumber("Huong", 123456789, &book);
    addPhoneNumber("Dung", 983456789, &book);
    
    do
    {
        system("cls");
        printf("1.Add phone\n2.Search phone\n3.Print list\n4.Exit\nYour choice:");
        scanf("%d",&n);
        switch(n){
              case 1:
                   fflush(stdin);
                   printf("Name:");
                   gets(name);
                   fflush(stdin);
                   printf("Number:");
                   scanf("%d",&sdt);
                   addPhoneNumber(name, sdt, &book);
                   break;
              case 2:
                   fflush(stdin);
                   printf("Name:");
                   gets(name);
                   entry = getPhoneNumber(name, book);
                   if (entry==NULL) printf("Not found number for %s!\n", name);
                   else printf("Phone number of %s is %d", name, entry->number);
                   getch();
                   break;
              case 3:
                   for (i=0; i<book.total; i++)
                       printf("%-15s%10d\n", book.entries[i].name, book.entries[i].number);
                   getch();
                   break;
              case 4:
                   dropPhoneBook(&book);
                   break;
          }
     }while(n!=4);
     return 0;
}

PhoneBook createPhoneBook()
{
    PhoneBook p;
    p.total = 0;
    p.size = INITIAL_SIZE;
    p.entries = (PhoneEntry*)malloc(INITIAL_SIZE*sizeof(PhoneEntry));
    return p;
}

void dropPhoneBook(PhoneBook* book)
{
    free(book->entries);
    book->total=0;
    book->size=0;
}

int binarySearch(PhoneEntry* entries, int l, int r, char * name, int* found)
{
	int i, res;
    if (r < l)
    {
       *found = 0;
       return l;
    }   
	i = (l + r)/2;
	res = strcmp(name, entries[i].name);
	if (res==0)
	{
        *found = 1;       
    	return i;
    }else if (res < 0)
    {
		return binarySearch(entries, l, i-1, name, found);
    }else
	{
        return binarySearch(entries, i+1, r, name, found);
    }    
}

void addPhoneNumber(char * name, long number, PhoneBook* book)
{
    int found, pos;
    if (book->total > 0)
    {
        pos = binarySearch(book->entries, 0, book->total-1, name, &found);
    }else
    {
        pos = 0;
        found = 0;     
    }            
    if (found)
    {
        book->entries[pos].number = number;
    }else // insert new entry
    {
        if(book->total >= book->size) 
        {
            PhoneEntry *p;
            int newsize = (book->size+INCREMENTAL_SIZE);
            p = (PhoneEntry*) malloc(newsize*sizeof(PhoneEntry));
            memcpy(p, book->entries, book->total*sizeof(PhoneEntry));
            free(book->entries); 
            book->entries = p;
            book->size = newsize;
        }
        if (pos < book->total) // move the entries
        {
            memcpy(&(book->entries[pos+1]), &(book->entries[pos]), (book->total-pos)*sizeof(PhoneEntry));
        }
        // make new entry at pos
        strcpy(book->entries[pos].name, name);
        book->entries[pos].number = number;
        book->total++;       
    } 
}

PhoneEntry * getPhoneNumber(char * name, PhoneBook book)
{
     int found, pos;
     pos = binarySearch(book.entries, 0, book.total-1, name, &found);
     if (found)
        return &(book.entries[pos]);
     else
        return NULL;
}
