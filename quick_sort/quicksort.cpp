#include<stdio.h>
 
void printarray(int a[], int);
 
void swap (int a[], int left, int right)
{
 	int tmp = a[left];
 	a[left] = a[right];
 	a[right] = tmp;
}//end swap
  
int partition( int a[], int low, int high )
{	
	int left = low, right = high, pivot_item = a[low];
	int pivot = low;
	
	while (left < right) {
		while(a[left] <= pivot_item) {
			left++;
		}
		while(a[right] > pivot_item) {
			right--;
		}
		if(left < right) {
			swap(a, left, right);
		}
	}
	
	a[low] = a[right];
	a[right] = pivot_item;
	return right;
}//end partition
 
void quicksort( int a[], int low, int high )
{	
	int pivot;
	if (high > low) {
		pivot = partition (a, low, high);
		quicksort(a, low, pivot-1);
		quicksort(a, pivot+1, high);
	}
} //end quicksort 
 
int main()
{
 int a[50], i, n;
 printf("\nEnter no. of elements: "); 
 scanf("%d", &n);
 printf("\nEnter the elements: \n");
 for (i=0; i<n; i++)
  scanf ("%d", &a[i]);
 printf("\nUnsorted elements: \n");
 printarray(a,n);
 quicksort(a,0,n-1);
 printf("\nSorted elements: \n");
 printarray(a,n);
 return 0;
}//end main
 
 
void printarray(int a[], int n)
{
 int i;
 for (i=0; i<n; i++)
  printf(" %d ", a[i]);
 printf("\n");
}//end printarray