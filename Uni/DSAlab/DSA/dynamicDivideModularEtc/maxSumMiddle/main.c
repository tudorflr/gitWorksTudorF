#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max ( int a, int b)
{
    return ( a>b )? a : b;
}

int max3nr( int a , int b , int c)
{
    return max ( max(a,b) , c);
}

int maxSumMiddle ( int arr[] , int left , int mid , int right)
{
    //sum that crosses the middle : calc in both directions
    int sum=0;
    int leftSum = INT_MIN;
    int rightSum = INT_MIN;

    for ( int i = mid ; i>= left ; i--)
    {
        //calc sum from mid towards the left
        sum += arr[i];
        if ( sum > leftSum ) leftSum = sum;
    }
    sum = 0;

    for ( int i = mid+1 ; i<= right ; i++)
    {
        //calc sum from mid+1 to right
        sum += arr[i];
        if ( sum > rightSum ) rightSum = sum;
    }

    return leftSum + rightSum;
}

int maxSubArraySum ( int arr[] , int left , int right)
{
    if ( left == right)  //only one element
        return arr[left];

    int mid = ( left + right ) / 2;

    return max3nr( maxSubArraySum(arr , left , mid), //sum of the left elemets
                  maxSubArraySum( arr , mid+1 , right ), // sum of the right elements
                  maxSumMiddle( arr , left , mid , right)); // max subarray that contains the middle

}

int main()
{
    int vec[8] = { -2,-5,6,-2,-3,1,5,-6};
    int n=sizeof(vec)/sizeof(vec[0]);
    printf( "Max sum is: %d" , maxSubArraySum(vec, 0 , n-1));
    return 0;
}
