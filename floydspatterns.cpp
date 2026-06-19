#include<iostream>
using namespace std;
int main(){
    int num = 3;
    int num1 =1;
    for (int i=0;i<=num;i++){
        for( int j=i+1;j>0;j--){
            cout << num1;
            num1++;
        }
        cout<<endl;
    }
    return 0;
}