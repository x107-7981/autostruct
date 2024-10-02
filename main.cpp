#include <bits/stdc++.h>
#include "autotruct.h"
using namespace std;
using namespace xxx;

int main(){
#if 1
    autostruct<int,bool,char,vector<int>> a;
    cout<< sizeof(a) << endl
        << "int : " << sizeof(int) << endl
        << "bool : " << sizeof(bool) << endl
        << "char : " << sizeof(char) << endl
        << "vector<int> " << sizeof(vector<int>) << endl
    ;
    scanf("%d",&a.getmember<1>());
    a.getmember<2>() = true;
    getchar();
    scanf("%c",&a.getmember<3>());
    do{
        int k;
        scanf("%d",&k);
        a.getmember<4>().push_back(k);
    }while(getchar()!=';');
    cout<< "int : " << a.getmember<1>() << endl
        << "bool : " << a.getmember<2>() << endl
        << "char : " ; putchar(a.getmember<3>());cout << endl
        << "vector : " << endl
    ;
    for(auto k:a.getmember<4>())
        cout << k << endl;
#else
    autounion<int,char,vector<int>,set<int>> b;
    b.getmember<1>() = 1234567;
    printf("%d",b.getmember<1>());
    b.setmember<4>();
    int x,y;scanf("%d%d",&x,&y);
    b.getmember<4>().insert(x);
    b.getmember<4>().insert(y);
    cout << "The small one is : " << *b.getmember<4>().begin() << endl;
    b.delmember<4>();
    b.setmember<pair<int,int>>();
    b.getmember<pair<int,int>>() = {x,y};
    cout<< "x : " << b.getmember<pair<int,int>>().first << endl
        << "y : " << b.getmember<pair<int,int>>().second << endl
    ;
#endif
    return 0;
}