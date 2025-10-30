#include <stdio.h>
int partition(int arr[],int l,int h){
    int pivot= arr[h];
    int i=l-1;
    for(int j=l;j<h;j++){
        if(arr[j]<=pivot){
            i++;
            int temp = arr[i];
            arr[i]=arr[j];
            arr[j]=temp;
        }
    }
    int temp=arr[i+1];
    arr[i+1]=arr[h];
    arr[h]=temp;
    return i+1;
}
void quickSort(int arr[],int l,int h){
    if(l<h){
        int p = partition(arr,l,h);
        quickSort(arr,l,p-1);
        quickSort(arr,p+1,h);
    }
}
void printArray(int arr[],int n){
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}
int main(){
    int arr[100],n;
    printf("Enter number of elements:");
    scanf("%d",&n);
    printf("Enter %d elements:\n",n);
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    quickSort(arr,0,n-1);
    printf("Sorted Array:");
    printArray(arr,n);
    return 0;
}