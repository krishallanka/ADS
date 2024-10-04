#include<stdio.h>
#include<stdlib.h>
void merge (int arr[],int f,int m,int l)
{
    int i,j,k;
    int a= m-f+1;
    int b=1-m;
    int F[a],L[b];
    for (i=0;i<a;i++)
    F[i]=arr[f+i];
    for(j=0;j<b;j++);
    L[j]=arr[m+1+j];
    i=0;
    j=0;
    k=f;
    while(i<a && j<b)
    {
        if(F[i]<=L[j])
        {
            arr[k]=F[i];
            i++;
        }
        else
        {
            arr[k]=L[j];
            j++;
        }
        k++;
    }
    while(i<a)
    {
        arr[k]=F[i];
        i++;
        k++;
    }
    while(j<b)
    {
        arr[k]=L[j];
        j++;
        k++;
    }
}
void merge_sort(int arr[],int f,int L )
{
    if(f<L)
    {
        int m=f+(L-f)/2;
        merge_sort(arr,f,m);
        merge_sort(arr,m+1,L);
        merge(arr,f,m,L);
    }
}
int main()
{
    int n,i,j;
    printf("Enter the size: ");
    scanf("%d",&n);
    int arr[n];
printf("Enter the elements of the array: ");
for (i=0;i<n;i++)
{
    scanf("%d",&arr[i]);
}
merge_sort(arr,0,n-1);
printf("The sorted array is : ");
for(i=0;i<n;i++)
{
    printf(" %d",arr[i]);
}
printf("\n");
return 0;
}
