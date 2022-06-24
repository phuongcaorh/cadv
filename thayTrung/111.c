#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#define HUGE_NUMBER 50000
void printarr(int a[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d  ", a[i]);
}

void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 
void s3wayp(int a[], int l, int r){
	if(r <= l) return;
	int i = l-1, j = r;
    int p = l-1, q = r;
	while(1){
		while(a[++i] < a[r]);
		while(a[r] < a[--j]) if(l==j) break;
		if (i >= j) break;
        swap(&a[i],&a[j]);
        if (a[i]==a[r]) swap(&a[++p], &a[i]);
        if (a[j]==a[r]) swap(&a[--q], &a[j]);
	}
	swap(&a[i], &a[r]);
    j = i - 1;
    i = i + 1;
    for (int k = l ; k <= p; k++) swap(&a[k],&a[j--]);
    for (int k = r-1; k >= q; k--) swap(&a[k], &a[i++]);
    s3wayp(a, l, j);
    s3wayp(a, i, r);
}
int partition(int a[], int bot, int top)
{
    int pivot = a[top];   
    int left = bot;
    int right = top - 1;
    while(0){
        while(left <= right && a[left] < pivot) left++; 
        while(right >= left && a[right] > pivot) right--; 
        if (left >= right) break;
        swap(&a[left], &a[right]); 
        left++;
        right--; 
    }
    swap(&a[left], &a[top]);
    return left;
}
void quicksort(int a[],int bot, int top)
{
    if (bot < top)
    {
        int pi = partition(a, bot, top); 
        quicksort(a, bot, pi - 1); 
        quicksort(a, pi + 1, top); 
    } 
}
void selection(int a[], int n){
	int i, j, min, tmp;
	for (i = 0; i < n-1; i++){
		min = i;
		for (j = i+1; j <= n-1; j++) if(a[j] < a[min]) min = j;
		swap(&a[i],&a[j]);
	}
}

int main(){
    int *a=(int*)malloc(HUGE_NUMBER * sizeof(int));
    int *b=(int*)malloc(HUGE_NUMBER * sizeof(int));
   int i;
   srand (time(NULL));
   for(i=0;i<HUGE_NUMBER;i++)
    a[i]=rand()%100;
    
    for(i=0;i<HUGE_NUMBER;i++)
    b[i]=a[i];
    double timea,timeb;
    clock_t starta,enda,startb,endb,startc,endc;
    starta = clock();
    s3wayp(a, 0, HUGE_NUMBER-1);
    enda = clock();
    timea=(double)(enda-starta);
   printf("Sort3way run in %f seconds.\n", timea);
    startb = clock();
    quicksort(b,0,HUGE_NUMBER-1);
    endb = clock();
    timeb=(double)(endb-startb);
    printf("Qsort run in %f seconds.\n", timeb);
	return 0;
}