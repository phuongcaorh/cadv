#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INITIAL_SIZE 10
#define INCREMENTAL_SIZE 5

typedef struct {
	void * key;
	void * value;
} Entry;

typedef struct {
	Entry * entries;
	int size, total;
	Entry (*makeNode)(void*, void*);
	int (*compare)(void*, void*);
} SymbolTable;

SymbolTable createSymbolTable(
		Entry (*makeNode)(void*, void*),
		int (*compare)(void*, void*)
);

void dropSymbolTable(SymbolTable* tab);
void addEntry(void* key, void* value, SymbolTable* book);
Entry* getEntry(void* key, SymbolTable book);

Entry makePhone(void* name, void* phone) {
	Entry res;
	res.key = strdup( (char*)name );
	res.value = malloc(sizeof(long));
	memcpy( res.value, phone, sizeof(long) );
	return res;
}
int comparePhone(void * key1, void* key2) {
	return strcmp((char*)key1, (char*)key2);
}

int main()
{
    int i, n;
    long sdt;
    char name[80];
    Entry *entry;
    SymbolTable book = createSymbolTable(makePhone, comparePhone);
    sdt = 983456789; 
    addEntry("Dung", &sdt, &book);
    sdt = 945678978; 
    addEntry("Thang", &sdt, &book);
    sdt = 123456789; 
    addEntry("Huong", &sdt, &book);
    sdt = 983984775; 
    addEntry("Anh", &sdt, &book);
    
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
                   addEntry(name, &sdt, &book);
                   break;
              case 2:
                   fflush(stdin);
                   printf("Name:");
                   gets(name);
                   entry = getEntry(name, book);
                   if (entry==NULL) printf("Not found number for %s!\n", name);
                   else printf("Phone number of %s is %d", name, *((long*)entry->value));
                   getch();
                   break;
              case 3:
                   for (i=0; i<book.total; i++)
                       printf("%-15s%10d\n", book.entries[i].key, *((long*)book.entries[i].value));
                   getch();
                   break;
              case 4:         
                   dropSymbolTable(&book);
                   break;
          }
     }while(n!=4);
     return 0;
}

SymbolTable createSymbolTable(Entry (*makeNode)(void*, void*), int (*compare)(void*, void*) )
{
    SymbolTable tab;
    tab.total = 0;
    tab.size = INITIAL_SIZE;
    tab.entries = (Entry*)malloc(INITIAL_SIZE*sizeof(Entry));
    tab.makeNode = makeNode;
    tab.compare = compare;
    return tab;
}

void dropSymbolTable(SymbolTable* table)
{
    int i;
    // free the memory allocated for each entry
    for (i=0; i<table->total; i++)
    {
        free(table->entries[i].key);
        free(table->entries[i].value);
    }
    free(table->entries);
    table->total=0;
    table->size=0;
}

int binarySearch(Entry* entries, int l, int r, void* key, int* found, int (*compare)(void*, void*))
{
	int i, res;
    if (r < l)
    {
       *found = 0;
       return l;
    }   
	i = (l + r)/2;
	res = compare(key, entries[i].key);
	if (res==0)
	{
        *found = 1;       
    	return i;
    }else if (res < 0)
    {
		return binarySearch(entries, l, i-1, key, found, compare);
    }else
	{
        return binarySearch(entries, i+1, r, key, found, compare);
    }    
}

void addEntry(void* key, void* value, SymbolTable* book)
{
    int found, pos;
    if (book->total > 0)
    {
        pos = binarySearch(book->entries, 0, book->total-1, key, &found, book->compare);
    }else
    {
        pos = 0;
        found = 0;     
    }   
    if (found) // rewrite the entry
    {
        free(book->entries[pos].key);
        free(book->entries[pos].value);
        book->entries[pos] = book->makeNode(key, value);
    }else // insert new entry
    {
        if(book->total >= book->size) 
        {
            Entry *p;
            int newsize = (book->size+INCREMENTAL_SIZE);
            p = (Entry*) malloc(newsize*sizeof(Entry));
            memcpy(p, book->entries, book->total*sizeof(Entry));
            free(book->entries); 
            book->entries = p;
            book->size = newsize;
        }
        if (pos < book->total) // move the entries
        {
            memcpy(&(book->entries[pos+1]), &(book->entries[pos]), (book->total-pos)*sizeof(Entry));
        }
        // make new entry at pos
        book->entries[pos] = book->makeNode(key, value);
        book->total++;       
    } 
}

Entry* getEntry(void* key, SymbolTable book)
{
     int found, pos;
     pos = binarySearch(book.entries, 0, book.total-1, key, &found, book.compare);
     if (found)
        return &(book.entries[pos]);
     else
        return NULL;
}
