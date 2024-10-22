#include <iostream>
using namespace std;
#include <iomanip>
#include <cmath>
int main()
{
    //FOR SPI:
    const int N=3;//number of courses in a semester
    
    //array of grades and credits:
    int arr[N][3]={{5,7},{2,8},{1,9}};
    
    float sum=0,creditsum=0;
    
    cout<<"SPI:"<<endl;
    for (int i=0; i<N; i++)
    {
        if(arr[i][0]>=0)
        {
            if(arr[i][1]<=10 && arr[i][1]>0)
            {
                sum+=arr[i][0]*arr[i][1];
                creditsum+=arr[i][0];
            }
            else{cout<<"Error: Grade cannot be greater than 10 or less than 0."<<endl;break; }
        }
        else
        {   sum=0.0/0.0;
            cout<<"Error:Credits assigned cannot be negative"<<endl;
            break;}
    }
    
    float spi=sum/creditsum;
    //output SPI
    
    if(!isnan(sum)){
        cout<<"SPI is: "<<setprecision(3)<<spi<<endl;}
    
    //FOR CPI
    cout<<"SPI:"<<endl;
    
    const int n=1;
    float psum=0; //Number of semesters:
    //array of spi
    float spi_list[n]={spi};
    
    if(n<=8 && n>0){
        for(int i=0; i<n;i++)
        {
            if(spi_list[i]<=10 && spi_list[i]>0 ){
                psum+=spi_list[i];
            }
            else{
                cout<<"SPI cannot be greater than 10 or less than 0."<<endl;
                break;
            }
        }
        
        //output CPI
        cout<<"CPI is: "<<setprecision(3)<<psum/n<<endl;
    }
    else {cout<<"Error: Number of semesters cannot be greater than 8 or less than 1.";}
    
    
}

