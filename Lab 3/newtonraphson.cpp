#include<bits/stdc++.h>
 
using namespace std;

double equation(double x,double y, double z, double i){
    return ((i*i*x) + (y*i) + z);
}

int main(){
    double x,y,z;
    cin>>x>>y>>z;
    double x0=10,x1=10,fx,fxp;
    int i = 0;
    while(true){
        cout<<"iteration no "<<i<<": "<<x0<<endl;
        fx = equation(x,y,z,x0);
        fxp = 2*x*x0+y;
        x1 = x0 - (fx/fxp);
        cout<<"Error: "<<fabs(x0-x1)<<endl;
        if(fx>(-1e-9) && fx<(1e-9)){
            cout<<"The root is "<<x0<<endl;
            break;
        }
        swap(x1,x0);
        i++;
    }
    }
 