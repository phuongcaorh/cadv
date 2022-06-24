#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 100

int random(int minN, int maxN)
{
    return minN + rand() % (maxN + 1 - minN);
}

void exch(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
void sort(int a[], int l, int r)
{
    if (r <= l) return;
    int i = l-1, j = r;
    int p = l-1, q = r;
    while (1)
    {
        while (a[i++] < a[r]);
        while (a[r] < a[j--]) if (j == 1) break;
        if (i >= j) break;
        exch(&a[i], &a[j]);
        if (a[i] == a[r]) exch(&a[p++], &a[i]);
        if (a[j] == a[r]) exch(&a[q--], &a[j]);
    }
    exch(&a[i], &a[r]);
    j = i - 1;
    i = i + 1;
    for (int k = l; k <= p; k++) exch(&a[k], &a[j--]);
    for (int k = r-1; k < q; k--) exch(&a[k], &a[i++]);
    sort(a, l, j);
    sort(a, i, r);
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
        exch(&a[left], &a[right]); 
        left++;
        right--; 
    }
    exch(&a[left], &a[top]);
    return left;
}
int main()
{
    int i;
    srand(time(NULL));
    int *a = (int*)malloc(MAX*sizeof(int));
    for (i = 0; i < MAX; i++)
    {
        a[i] = random(1, 10);
    }
     clock_t start, end;
     double time_use;
     start = clock();
     sort(a, 0, MAX-1);
     end = clock();
    time_use = (double)(end - start) / CLOCKS_PER_SEC;
    printf("3way partitioning %f second", time_use);
    return 0;
}