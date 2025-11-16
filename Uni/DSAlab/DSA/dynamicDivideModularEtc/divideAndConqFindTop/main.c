#include <stdio.h>
#include <stdlib.h>

int findthetop(int a[], int low, int high){
    int mid;
    mid = low + (high - low) / 2;
    if (a[mid] > a[mid - 1] && a[mid] > a[mid + 1]) {
        return a[mid];
    }
    if (a[mid] > a[mid - 1] && a[mid] < a[mid + 1]) {
        return findthetop(a, mid + 1, high);
    }
        return findthetop(a, low, mid - 1);
}


int main()
{
    int a[100],n=0,low,high,top;
    n=9;
    a[0]=1;
    a[1]=5;
    a[2]=9;
    a[3]=7;
    a[4]=5;
    a[5]=4;
    a[6]=3;
    a[7]=2;
    a[8]=1;
    top= findthetop(a,0,n-1);
    printf("%d", top);
    return 0;
}
