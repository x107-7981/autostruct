/*
    Do you know "std::tuple<>" ?
    It can work to instead it.
    made by x107.
    recent update : 2024.11.2
*/
#ifndef AUTOSTRUCT_H
#define AUTOSTRUCT_H
#if !defined __cplusplus || __cplusplus < 201103L
#error autostruct is only for C++ which more than c++11
#endif
#include <cstring>
#include <algorithm>

namespace xxx{

//get union's size (body)
template <typename Tp, typename...Tail>
class __getunionsize{
public: const static unsigned long long
    value = (__getunionsize<Tail...>::value < sizeof(Tp))?
    sizeof(Tp):__getunionsize<Tail...>::value;
};
//get union's size (exit)
template <typename Tp>
class __getunionsize<Tp>{
public: const static unsigned long long
    value = sizeof(Tp);
};

//get union's type (body)
template <unsigned int num,typename Tp,typename...Tail>
class __getuniontype{public:
    using type = typename __getuniontype<num-1,Tail...>::type;
};
//get union's type (exit)
template <typename Tp,typename...Tail>
class __getuniontype<1,Tp,Tail...>{public:
    using type = Tp;
};

//autounion
template <typename...Args>
class autounion{
    unsigned char __body[__getunionsize<Args...>::value];
public:
    autounion(){memset(__body,0,sizeof(__body));};

    template <unsigned int num>
    typename __getuniontype<num,Args...>::type &
    getmember(){
        return *(typename __getuniontype<num,Args...>::type *)
        (__body);
    }

    template <unsigned int num>
    void setmember(){
        new((typename __getuniontype<num,Args...>::type *)
        (__body)) typename __getuniontype<num,Args...>::type;
    }

    template <unsigned int num>
    void delmember(){
        using Tp = typename __getuniontype<num,Args...>::type;
        (*(Tp*)(__body)).~Tp();
    }
    
    template <typename Tp>
    Tp & getmember()
    {return *(Tp *)(__body);}

    template <typename Tp>
    void setmember()
    {new((Tp *)(__body)) Tp;}

    template <typename Tp>
    void delmember()
    {(*(Tp*)(__body)).~Tp();}
};

//--------------------------beautiful-cutline---------------------------

//get struct's size (body)
template <typename Tp, typename...Tail>
class __getstructsize{
public: const static unsigned long long
    value = __getstructsize<Tail...>::value + sizeof(Tp);
};
//get struct's size (exit)
template <typename Tp>
class __getstructsize<Tp>{
public: const static unsigned long long
    value = sizeof(Tp);
};

//get struct's type and address (body)
template <unsigned int num,typename Tp,typename...Tail>
class __getstructtype{public:
    using type = typename __getstructtype<num-1,Tail...>::type;
    const static unsigned long long address = 
    __getstructtype<num-1,Tail...>::address + sizeof(Tp);
};
//get struct's type and address (exit)
template <typename Tp,typename...Tail>
class __getstructtype<1,Tp,Tail...>{public:
    using type = Tp;
    const static unsigned long long address = 0;
};

//init struct (body)
template <unsigned int num,typename...Args>
class __init_struct{
public: inline static void
For(unsigned char *body){
    //Placement new (it is importent!!)
    new((typename __getstructtype<num,Args...>::type *)
        (body + __getstructtype<num,Args...>::address))
        typename __getstructtype<num,Args...>::type;
    __init_struct<num-1,Args...>::For(body);
    return;
}};
//init struct(exit)
template <typename...Args>
class __init_struct<0,Args...>{
public: inline static void
For(unsigned char *body){return;}};

//copy init struct(body)
template <unsigned int num,typename...Args>
class __copy_init_struct{
public: inline static void
For(unsigned char *thisbody,const unsigned char *xbody){
    using Tp = typename __getstructtype<num,Args...>::type;
    const unsigned long long address = __getstructtype<num,Args...>::address;
    new((Tp*)(thisbody + address)) Tp(*(Tp*)(xbody + address));
    __copy_init_struct<num-1,Args...>::For(thisbody,xbody);
    return;
}};
//copy init struct(exit)
template <typename...Args>
class __copy_init_struct<0,Args...>{
public: inline static void
For(unsigned char *thisbody,const unsigned char *xbody){return;}};

//move init struct(body)
template <unsigned int num,typename...Args>
class __move_init_struct{
public: inline static void
For(unsigned char *thisbody,const unsigned char *xbody){
    using Tp = typename __getstructtype<num,Args...>::type;
    const unsigned long long address = __getstructtype<num,Args...>::address;
    new((Tp*)(thisbody + address)) Tp(std::move(*(Tp*)(xbody + address)));
    __move_init_struct<num-1,Args...>::For(thisbody,xbody);
    return;
}};
//move init struct(exit)
template <typename...Args>
class __move_init_struct<0,Args...>{
public: inline static void
For(unsigned char *thisbody,const unsigned char *xbody){return;}};

//copy struct(body)
template <unsigned int num,typename...Args>
class __copy_struct{
public: inline static void
For(unsigned char *thisbody,const unsigned char *xbody){
    using Tp = typename __getstructtype<num,Args...>::type;
    const unsigned long long address = __getstructtype<num,Args...>::address;
    *(Tp*)(thisbody + address) = *(Tp*)(xbody + address);
    __copy_struct<num-1,Args...>::For(thisbody,xbody);
    return;
}};
//copy struct(exit)
template <typename...Args>
class __copy_struct<0,Args...>{
public: inline static void
For(unsigned char *thisbody,const unsigned char *xbody){return;}};

//move struct(body)
template <unsigned int num,typename...Args>
class __move_struct{
public: inline static void
For(unsigned char *thisbody,const unsigned char *xbody){
    using Tp = typename __getstructtype<num,Args...>::type;
    const unsigned long long address = __getstructtype<num,Args...>::address;
    *(Tp*)(thisbody + address) = std::move(*(Tp*)(xbody + address));
    __move_struct<num-1,Args...>::For(thisbody,xbody);
    return;
}};
//move struct(exit)
template <typename...Args>
class __move_struct<0,Args...>{
public: inline static void
For(unsigned char *thisbody,const unsigned char *xbody){return;}};

//delete struct (body)
template <unsigned int num,typename...Args>
class __del_struct{
public: inline static void
For(unsigned char *body){
    using _Tp = typename __getstructtype<num,Args...>::type;
    (*(_Tp *)(body + __getstructtype<num,Args...>::address)).~_Tp();
    __del_struct<num-1,Args...>::For(body);
    return;
}};
//delete struct (exit)
template <typename...Args>
class __del_struct<0,Args...>{
public: inline static void
For(unsigned char *body){return;}};

//autostruct
template <typename...Args>
class autostruct{
    unsigned char __body[__getstructsize<Args...>::value];
public:
    autostruct(){
        memset(__body,0,sizeof(__body));
        __init_struct<sizeof...(Args),Args...>
        ::For(__body);
    }

    autostruct(const autostruct<Args...> &x){
        memset(__body,0,sizeof(__body));
        __copy_init_struct<sizeof...(Args),Args...>
        ::For(__body,x.__body);
    }

    autostruct(autostruct<Args...> &&x){
        memset(__body,0,sizeof(__body));
        __move_init_struct<sizeof...(Args),Args...>
        ::For(__body,x.__body);
    }

    template <unsigned int num>
    typename __getstructtype<num,Args...>::type &
    getmember() const {
        return *(typename __getstructtype<num,Args...>::type *)
        (__body + __getstructtype<num,Args...>::address);
    }

    void operator=(const autostruct<Args...> &x){
        __copy_struct<sizeof...(Args),Args...>
        ::For(__body,x.__body);
    }

    void operator=(autostruct<Args...> &&x){
        __move_struct<sizeof...(Args),Args...>
        ::For(__body,x.__body);
    }

    ~autostruct(){
        __del_struct<sizeof...(Args),Args...>
        ::For(__body);
    }
};

template <unsigned int num, typename...Args>
typename __getstructtype<num+1,Args...>::type &
get(const autostruct<Args...> &x)
{return x. template getmember<num+1>();}

//make struct for(body)
template <unsigned int num, typename Tp, typename...Tail>
class __make_struct{
public: template <typename...Args> inline static void
For(autostruct<Args...> &_Tmp, Tp x, Tail...args){
    _Tmp. template getmember<num>() = x;
    __make_struct<num+1,Tail...>:: template For<Args...>(_Tmp,args...);
    return;
}};

//make struct for(exit)
template <unsigned int num, typename Tp>
class __make_struct<num,Tp>{
public: template <typename...Args> inline static void
For(autostruct<Args...> &_Tmp, Tp x){
    _Tmp. template getmember<num>() = x;
    return;
}};

template <typename...Args>
autostruct<Args...> make_autostruct(Args...args){
    autostruct<Args...> _Tmp;
    __make_struct<1,Args...>:: template For<Args...>(_Tmp,args...);
    return _Tmp;
}

}

namespace std{
    template <typename...Args>
    class tuple_size<xxx::autostruct<Args...>>
    {public: static constexpr size_t value = sizeof...(Args);};

    template <size_t num,typename...Args>
    class tuple_element<num, xxx::autostruct<Args...>>
    {public: using type = typename xxx::__getstructtype<num+1,Args...>::type;};
}
#endif
