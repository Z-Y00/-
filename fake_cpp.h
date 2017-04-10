#ifndef CPP_H_INCLUDED
#define CPP_H_INCLUDED
#include <stdint.h>

#define _enable_cxx_class
#define _enable_cxx_vector
#define _enable_cxx_binary_tree

/**
 * If you're trying to include this header for your c homework/project, 
 * maybe you must go to libcello.org.
 *
 * Recolic Keghart. at Apr. 10, 2017.
 */


#ifndef NULL
#define NULL 0
#endif
#define CALLBACK
#define INVALID_INT INT_MAX
#define INVALID_LONG LONG_MAX
#define nullptr NULL
#define new(data_type) malloc(sizeof(data_type))
#ifndef __cplusplus
    #ifndef __STDC__
        #error Fuck??? Why not __STDC__???
    #endif
    #if __STDC_VERSION__ < 201100L
        typedef int bool;
    #elif __STDC_VERSION__ < 199900L
        #error Try to compile with -std=c99 or -std=c11, or donate your computer to history museums. 
    #else
        typedef _Bool bool;
    #endif
    #define false (bool)0;
    #define true (bool)1;
#else
    #error Sorry, library "fake_cpp.h" is only designed for pure C. Do not use C++ compiler please.
#endif
#define throw
#define class struct
#define bad_alloc(printf_args...) {printf("At %s(LINE%d):",__FILE__,__LINE__);printf("\nFatal: std::bad_alloc(%s):",strerror(errno));printf(printf_args);printf("\nprogram is terminating...\n");exit(127);}
#define invalid_argument(printf_args...) {printf("At %s(LINE%d):",__FILE__,__LINE__);printf("\nFatal: std::invalid_argument(%s):",strerror(errno));printf(printf_args);printf("\nprogram is terminating...\n");exit(127);}
#define runtime_error(printf_args...) {printf("At %s(LINE%d):",__FILE__,__LINE__);printf("\nFatal: std::runtime_error(%s):",strerror(errno));printf(printf_args);printf("\nprogram is terminating...\n");exit(127);}
#define logic_error(printf_args...) {printf("At %s(LINE%d):",__FILE__,__LINE__);printf("\nFatal: std::logic_error(%s):",strerror(errno));printf(printf_args);printf("\nprogram is terminating...\n");exit(127);}

#ifdef _enable_stdint_recheck
    #ifndef int8_t
    #if sizeof(char) == 1
    #define int8_t char
    #elif sizeof(short) == 1
    #define int8_t short
    #else
    #error No 8 bit integar type detected!Compile failed.
    #endif
    #endif

    #ifndef uint8_t
    #if sizeof(unsigned char) == 1
    #define uint8_t unsigned char
    #elif sizeof(unsigned short) == 1
    #define uint8_t unsigned short
    #else
    #error No 8 bit unsigned integar type detected!Compile failed.
    #endif
    #endif

    #ifndef int16_t
    #if sizeof(short) == 2
    #define int16_t short
    #elif sizeof(char) == 2
    #define int16_t char
    #elif sizeof(int) == 2
    #define int16_t int
    #else
    #error No 16 bit integar type detected!Compile failed.
    #endif
    #endif

    #ifndef uint16_t
    #if sizeof(unsigned short) == 2
    #define uint16_t unsigned short
    #elif sizeof(unsigned char) == 2
    #define uint16_t unsigned char
    #elif sizeof(unsigned int) == 2
    #define uint16_t unsigned int
    #else
    #error No 16 bit unsigned integar type detected!Compile failed.
    #endif
    #endif

    #ifndef int32_t
    #if sizeof(long) == 4
    #define int32_t long
    #elif sizeof(int) == 4
    #define int32_t int
    #elif sizeof(short) == 4
    #define int32_t short
    #else
    #error No 32 bit integar type detected!Compile failed.
    #endif
    #endif

    #ifndef uint32_t
    #if sizeof(unsigned long) == 4
    #define uint32_t unsigned long
    #elif sizeof(unsigned int) == 4
    #define uint32_t unsigned int
    #elif sizeof(unsigned short) == 4
    #define uint32_t unsigned short
    #else
    #error No 32 bit unsigned integar type detected!Compile failed.
    #endif
    #endif

    #ifndef int64_t
    #if sizeof(long long) == 8
    #define int64_t long long
    #elif sizeof(long) == 8
    #define int64_t long
    #else
    #error No 64 bit integar type detected!Compile failed.
    #endif
    #endif

    #ifndef uint64_t
    #if sizeof(unsigned long long) == 8
    #define uint64_t unsigned long long
    #elif sizeof(unsigned long) == 8
    #define int64_t unsigned long
    #else
    #error No 64 bit unsigned integar type detected!Compile failed.
    #endif
    #endif
#endif


#ifdef _enable_cxx_class
////You can easily design a C++ class according to this template!
/* Recolic's class template
typedef void (* func_t)(void *func_arg);
typedef void (* classname_t)(void *func_arg);
struct classname
{
    classname_t classname;
    func_t func;
    var_t var;
    #define _var this->var
};
void classname_exe(struct classname *this, void *construct_arg)
{
    printf("constructor!%d",construct_arg);
}
void func_exe(struct classname *this, void *func_arg)
{
    printf("func!%d",func_arg);
}
void classname_exe_pre(struct classname *pObject,void *func_arg) //Constructor!
{
    pObject->classname = &classname_exe;
    pObject->func=&func_exe;
    //attach function to function pointers.
    return pObject->classname(pObject, func_arg);
}
#define _classname struct classname
*/

#define CLASS(type,name,pv_construct_arg) struct type name;type##_exe_pre(&name,pv_construct_arg)
#define C(i_objectname,i_funcname, ...) i_objectname.i_funcname(&i_objectname, ##__VA_ARGS__) //ONLY static public function can be called directly!!!
#define PC(p_objectname,i_funcname, ...) p_objectname->i_funcname(p_objectname, ##__VA_ARGS__)
#endif

/*********************cvector***************************/
#ifdef _enable_cxx_vector
#ifndef _enable_cxx_class
#error Please define _enable_cxx_class before using fake_cxx_vector
#endif

#define CVECTOR_DATA_TYPE uint64_t
#define INVALID_RETURN INVALID_LONG
class cvector;
typedef void (* cvector_t)(struct cvector *this, void *func_arg);
typedef void (* push_back_t)(struct cvector *this, CVECTOR_DATA_TYPE push_back_arg);
typedef void (* release_cv_t)(struct cvector *this);
typedef CVECTOR_DATA_TYPE (* at_t)(struct cvector *this, long at_arg);
class cvector//CVECTOR_DATA_TYPE vector
{
    cvector_t cvector;
    push_back_t push_back;
    at_t at;
    release_cv_t release;
    CVECTOR_DATA_TYPE *buf;
    long buf_size;
    long buf_capicity;
#define _buf_capicity this->buf_capicity
#define _buf this->buf
#define _buf_size this->buf_size
};
void push_back_exe(struct cvector *this, CVECTOR_DATA_TYPE push_back_arg)
{
    if(!_buf_capicity)
    {
        _buf=malloc(sizeof(CVECTOR_DATA_TYPE));
        _buf_capicity = 1;
        *(_buf) = push_back_arg;
        _buf_size = 1;
        return;
    }
    else if(_buf_size < _buf_capicity)
    {
        (_buf)[_buf_size] = push_back_arg;
        _buf_size ++;
        return;
    }
    else if(_buf_size == _buf_capicity)
    {
        CVECTOR_DATA_TYPE *hold_pbuf = _buf;
        _buf_capicity <<= 1;
        _buf = malloc(sizeof(CVECTOR_DATA_TYPE)*_buf_capicity);
        memcpy(_buf,hold_pbuf,sizeof(CVECTOR_DATA_TYPE)*_buf_size);
        free(hold_pbuf);
        (_buf)[_buf_size] = push_back_arg;
        _buf_size ++;
        return;
    }
    else
    {
        printf("FATAL ERROR AT cpp.h,line87.\n");
        abort();
    }
}
CVECTOR_DATA_TYPE at_exe(struct cvector *this, long at_arg)
{
    return at_arg < _buf_size ? (_buf)[at_arg] : INVALID_RETURN;
}
void cvector_exe(struct cvector *this, void *construct_arg)
{
    _buf = nullptr;
    _buf_size = _buf_capicity = 0;
}
void release_cv_exe(struct cvector *this)
{
    if(_buf)
        free(_buf);
}
void cvector_exe_pre(struct cvector *this,void *func_arg)
{
    this->cvector = &cvector_exe;
    this->push_back = &push_back_exe;
    this->at = &at_exe;
    this->release = &release_cv_exe;
    //attach function to function pointers.
    return this->cvector(this, func_arg);
}
#define _cvector struct cvector

#endif

/**************************ctree****************************/
#ifdef _enable_cxx_binary_tree
#ifndef _enable_cxx_class
#error Please define _enable_cxx_class before using fake_cxx_binary_tree
#endif

#define CTREE_DATA_TYPE const char *
#define CTREE_ADDITIONAL_DATA_TYPE _cvector
class ctree;
#define _ctree struct ctree
typedef void (* sorted_insert_t)(_ctree *this, CTREE_DATA_TYPE toInsert, uint32_t fileid);
typedef void (* ctree_t)(_ctree *this, void *func_arg);
typedef void (CALLBACK * ctree_walk_callback_t)(CTREE_DATA_TYPE /***/data, CTREE_ADDITIONAL_DATA_TYPE d_cter);//这可不是成员函数定义，这是遍历时的回调！！
typedef void (* for_each_t)(_ctree *this, ctree_walk_callback_t ctree_walk_callback);
typedef void (* release_t)();
void ctree_exe_pre(_ctree *this,void *func_arg);
class ctree
{
    ctree_t ctree;
//    func_t func;
//    var_t var;
//    #define _var this->var
    sorted_insert_t sorted_insert;
    for_each_t for_each;
    release_t release;
    CTREE_DATA_TYPE data;
    CTREE_ADDITIONAL_DATA_TYPE cter;
    _ctree *pleft;
    _ctree *pright;
    #define _pleft this->pleft
    #define _pright this->pright
    #define _data this->data
    #define _cter this->cter
};
void ctree_exe(_ctree *this, void *construct_arg)
{
    _pleft = _pright = nullptr;
    _data = NULL;
}
void release_exe(_ctree *this)
{
    if(_pleft)
    {
        PC(_pleft,release);
        free(_pleft);
    }
    if(_pright)
    {
        PC(_pright,release);
        free(_pright);
    }
    return;
}
void sorted_insert_exe(_ctree *this, CTREE_DATA_TYPE toInsert, uint32_t fileid)
{
    //假定CTREE——DATA——TYPE为const char *
    if(!_cter.buf_size)
    {
        _data = toInsert;
        C(_cter,push_back,MakeInfo(fileid,1));
        return;
    }
    uint32_t topv = (uint32_t)C(_cter,at,_cter.buf_size - 1);
    if(!topv)
    {
        throw runtime_error("Broken data in memory!");
    }
    if(!_data)
    {
        throw runtime_error("Caught invalid data");
    }
    int res = strcmp(toInsert, _data);
    if(!res)
        res = strlen(toInsert) - strlen(_data);
    if(!res)
    {
        uint16_t h32 = 0, l32 = 0;
        DepackInfo(topv,&h32,&l32);
        if(h32 == fileid)
            ++(_cter.buf[_cter.buf_size - 1]);
        else
            C(_cter,push_back,MakeInfo(fileid, 1));
    }
    else if(res < 0)
    {
        if(_pleft)
            PC(_pleft,sorted_insert,toInsert,fileid);
        else
        {
            _pleft = (_ctree *)malloc(sizeof(_ctree));
            ctree_exe_pre(_pleft, NULL);//手动构造
            _pleft->data = toInsert;
            C(_pleft->cter,push_back,MakeInfo(fileid,1));
        }
    }
    else
    {
        if(_pright)
            PC(_pright,sorted_insert,toInsert,fileid);
        else
        {
            _pright = (_ctree *)malloc(sizeof(_ctree));
            ctree_exe_pre(_pright, NULL);//手动构造
            _pright->data = toInsert;
            C(_pright->cter,push_back,MakeInfo(fileid,1));
        }
    }
    return;
}
void for_each_exe(_ctree *this, ctree_walk_callback_t ctree_walk_callback)
{
    if(_pleft)
        PC(_pleft,for_each,ctree_walk_callback);
    ctree_walk_callback(_data,_cter);
    if(_pright)
        PC(_pright,for_each,ctree_walk_callback);
    return;
}
void ctree_exe_pre(_ctree *this,void *func_arg)
{
    this->ctree = &ctree_exe;
    this->sorted_insert = &sorted_insert_exe;
    this->for_each = &for_each_exe;
    this->release = &release_exe;
    cvector_exe_pre(&(this->cter),NULL);
//    pObject->func=&func_exe;
    //attach function to function pointers.
    return this->ctree(this, func_arg);
}
#define _ctree struct ctree
#endif

#endif // CPP_H_INCLUDED
