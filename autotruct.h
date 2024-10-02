/*
    Do you know "std::tuple<>" ?
    It can work to instead it.
    made by x107.
    recent update : 2024.10.1
*/
#ifndef AUTOSTRUCT_H
#define AUTOSTRUCT_H
#ifndef __cplusplus
#error autostruct is only for cpp
#endif
namespace xxx{

//get union's size (body)
template <typename Tp, typename...Tail>
class __getunionsize{
public: const static unsigned long long
    value = std::max(__getunionsize<Tail...>::value, sizeof(Tp));
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
        typename __getuniontype<num,Args...>::type __del = std::
        move(*(typename __getuniontype<num,Args...>::type*)(__body));
    }
    
    template <typename Tp>
    Tp & getmember()
    {return *(Tp *)(__body);}

    template <typename Tp>
    void setmember()
    {new((Tp *)(__body)) Tp;}

    template <typename Tp>
    void delmember()
    {Tp __del = std::move(*(Tp*)(__body));}
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

//delete struct (body)
template <unsigned int num,typename...Args>
class __del_struct{
public: inline static void
For(unsigned char *body){
    typename __getstructtype<num,Args...>::type __del =
    std::move(*(typename __getstructtype<num,Args...>::type *)
    (body + __getstructtype<num,Args...>::address));
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

    template <unsigned int num>
    typename __getstructtype<num,Args...>::type &
    getmember(){
        return *(typename __getstructtype<num,Args...>::type *)
        (__body + __getstructtype<num,Args...>::address);
    }

    ~autostruct(){
        __del_struct<sizeof...(Args),Args...>
        ::For(__body);
    }
};

}
#endif