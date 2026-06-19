#include<iostream>
using namespace std;
int main (){

char ch='A';
int num=3;


for(int i=0;i<=num;i++){
    for (int j=i+1;j>0;j--){
        cout << ch;
        ch++;
    }
    cout << endl;


}
return 0;

}