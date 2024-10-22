#include <stdio.h>
#include<iostream>
using namespace std;

void sort (int a[], int n)  
{
  int temp;
  for (int i = 0; i < n; i++)
    {
      for(int j = i + 1; j < n; j++)
        {
          if (a[i] > a[j])
          {
            temp = a[j];
            a[j] = a[i];
            a[i] = temp;
          }
        }
    }
}

int linsearch (int a[], int n, int x)
{
  for(int i = 0; i < n; i++)
    {
      if (a[i]==x)
      {
        return i;
      }
    }
  return -1;
}

int binsearch(int arr[], int n, int x)
{
    int L = 0;
    int H = n - 1;

    while (L <= H)
    {
        int mid = L + (H - L) / 2;
        if (arr[mid] == x)
        {
            return mid;
        }
        else if (arr[mid] < x)
        {
            L = mid + 1;}
            else
            {
                H = mid - 1;
            }
            return -1;
        }
}  
        void display(int a[], int n)
        {
            for (int i = 0; i < n; i++)
            {
                cout<<a[i]<<" ";
            }
        }
        
        int main ()
        {
            int n,x;
            cout<<"enter number of elements to enter in array:"<<endl;
            cin>>n;
            int a[n];
            cout<<"enter the elements:"<<endl;
            for (int i = 0; i < n; i++)
            {
                cin>>a[i];
            }
            cout<<"the array is: ";
            display(a,n);
            sort(a,n);
            cout<<"\nthe array after sorting is: ";
            display(a,n);
            cout<<"\n enter element to be searched for"<<endl;
            cin>>x;
            
            int lindex = linsearch(a,n,x);
            int bindex = binsearch(a,n,x);

            if (lindex!=-1 && bindex !=-1)
            {
                cout<<"by linear search element is present at position "<<lindex+1<<endl;
                cout<<"by binary search element is present at position "<<bindex+1<<endl;
            }
            else
            {
                cout<<"the element is not present in the array"<<endl;
            }
            return 0;
        }
    
