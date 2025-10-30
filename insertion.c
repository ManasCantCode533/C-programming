#include <stdio.h>
void insert(int arr[],int n ){
    int i,j,key;
    for (int i = 0; i < n; i++)
    {
        key=arr[i];
        j=i-1;
        while(j>=0&&arr[j]>key){
            arr[j+1]=arr[j];
            j=j-1;
        }
        arr[j+1]=key;
    }
}
void printArray(int arr[],int n){
    for (int i = 0; i < n; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
    
}
int main(){
    int n;
    printf("Enter number of elements: ");
    scanf("%d",&n);
    int arr[n];
    printf("Enter %d elements: ",n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&arr[i]);
    }
    printf("Original Array:\n");
    printArray(arr,n);
    insert(arr,n);
    printf("Sorted Array:\n");
    printArray(arr,n);
    return 0;
}