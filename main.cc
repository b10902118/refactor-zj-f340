#include<iostream>

using namespace std;

int main(){
    int X,Y;
    cin>>X>>Y;
    int n;
    cin>>n;

    int x= X/2+X%2,y=Y,d=0;

    for (int i=0;i<n;++i){
        int op;
        cin>>op;

        --y;

        switch (op){
        case 1:
            if (((d==0||d==2||d==3)&&(x<X-1))||(d==1&&x<X)) ++x;
            break;
        case 2:
            if (((d==0||d==2||d==1)&&(x>2))||(d==3&&x>1)) --x;
            break;
        case 3:
            if (d==2) y=1;
            else y=2;
            goto RESULT;
        case 4:
            if (!(d==1&&x==X)&&!(d==3&&x==1)&&!(d==2&&y==1)){
                d=(d+1)%4;
            }
            break;
        }
        if (((d==0||d==1||d==3)&&(y==2))||(d==2&&y==1)) break;
    }

RESULT:
    if (d!=0){
        for (int i=Y;i>y+1;--i){
            for (int j=1;j<=X;++j) cout<<0;
            cout<<endl;
        }

        for (int i=1;i<x;++i){
            cout<<0;
        }
        cout<<1;
        for (int i=x+1;i<=X;++i){
            cout<<0;
        }
        cout<<endl;
    }
    else{
        for (int i=Y;i>y;--i){
            for (int j=1;j<=X;++j) cout<<0;
            cout<<endl;
        }
    }

    if (d==0||d==2){
        for (int i=1;i<x-1;++i) cout<<0;
        cout<<"111";
        for (int i=x+2;i<=X;++i) cout<<0;
        cout<<endl;
    }
    else{
        if (d==1){
            for (int i=1;i<x-1;++i) cout<<0;
            cout<<"11";
            for (int i=x+1;i<=X;++i) cout<<0;
        }
        else{
            for (int i=1;i<x;++i) cout<<0;
            cout<<"11";
            for (int i=x+2;i<=X;++i) cout<<0;
        }
        cout<<endl;
    }

    if (d!=2){
        for (int i=1;i<x;++i){
            cout<<0;
        }
        cout<<1;
        for (int i=x+1;i<=X;++i){
            cout<<0;
        }
        cout<<endl;

        for (int i=y-2;i>= 1;--i){
            for (int j=1;j<=X;++j) cout<<0;
            cout<<endl;
        }
    }
    else{
        for (int i=y-1;i>= 1;--i){
            for (int j=1;j<=X;++j) cout<<0;
            cout<<endl;
        }
    }

    return 0;
}
