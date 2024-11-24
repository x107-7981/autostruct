#include <bits/stdc++.h>
#include "autotruct.h"
///*
#include <xxx_tools/strnum.h>
#include <xxx_tools/strnum.cpp>
//*/
using namespace std;
using namespace xxx;

int main(){
#if 1
    autostruct<int,char,bool,strflt> x;
    printf("%d %d\n",sizeof(int)+sizeof(char)+sizeof(bool)+sizeof(strflt),sizeof(x));
    auto& [a,b,c,d] = x;
    c = true;
    scanf("%d%c",&a,&b);
    d.gain();
    d *= d;
    cout << get<0>(x) << endl;
    putchar(x.getmember<2>());
    printf("\n%d\n",get<2>(x));
    x.getmember<4>().soutln(16);
    printf("////////////////////////////\n");
    x = make_autostruct(1,'0',false,d+d);
    cout << get<0>(x) << endl;
    putchar(x.getmember<2>());
    printf("\n%d\n",get<2>(x));
    x.getmember<4>().soutln(16);
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
