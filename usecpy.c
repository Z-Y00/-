#define SOURCE_URL "https://tdl.recolic.net/hustc.py" //Url to code file, which's for 'bare' wget. Valid demos: https://tdl.recolic.net/hustc.cpp and hustc.py.
#define L_PYTHON //Select the language you want.
//#define L_CPP //Select the language you want.

//g++ 5.2.1 and python 2.7 is used on server.
/***************************************************
 * Usage tips:
 * Python file MUST started by '#!/bin/env python2.7' or '#!/bin/env python' or '#!/bin/env python2'.
 * Cpp file MUST be single.
 * C++14 is not supported by FUCKed gnu-c++ provided by server.
 * 
 * This program have NOT been fully-tested yet.
 * 
 * by Recolic Keghart, at Mar. 7, 2017.
 * Codes below needn't be modified unless severe bugs are detected.
 * My email: admin@recolic.net / recolickeghart@gmail.com
 * Have fun!
 */


/***
 * 
 * Passed compilation:
 * ~/c/test ❯❯❯ gcc -std=c99 usecpy.c 
 * ~/c/test ❯❯❯ gcc -std=c11 usecpy.c 
 * ~/c/test ❯❯❯ g++ -std=c++98 usecpy.c
 * ~/c/test ❯❯❯ g++ -std=c++11 usecpy.c
 * ~/c/test ❯❯❯ g++ -std=c++14 usecpy.c
 * ~/c/test ❯❯❯ g++ -std=c++17 usecpy.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
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
//Disable some warnings here from cpp compilers.
#endif
#ifdef L_PYTHON
    #ifdef L_CPP
        #error Specified language is invalid.
    #endif
#endif
#ifdef L_PYTHON
    #define LANGUAGE py
    #define usedProc pyProc
#endif
#ifdef L_CPP
    #define LANGUAGE cpp
    #define usedProc cppProc
#endif
#ifndef LANGUAGE
    #error Specified language is invalid.
#endif
#define filePostfix #LANGUAGE
//#define SYS_BSD
typedef int fileDescriptor;

bool cppProc(const char *filePath, const char *usedRandCode/*Help to simplify my work*/)
{
    char compileCmd[128] = "";
    sprintf(compileCmd, "g++ -std=c++11 %s -o /tmp/%s", filePath, usedRandCode);
    system(compileCmd);
    char runCmd[20] = "";
    sprintf(runCmd, "/tmp/%s", usedRandCode);
    execl(runCmd, NULL);
    remove(filePath);
    remove(runCmd);
    return true;
}
bool pyProc(const char *filePath, const char *usedRandCode/*Help to simplify my work*/)
{
    #ifndef SYS_BSD
        chmod(filePath, S_IXUSR | S_IRUSR | S_IWUSR);
        execl(filePath, NULL);
    #else
        char pyStartCmd[35] = "";
        sprintf(pyStartCmd, "python %s", filePath);
        execl(pyStartCmd, NULL);
    #endif
    remove(filePath);
    return true;
}
int main()
{
    time_t timeVar;
    srand((unsigned) time(&timeVar));
    char fileName[20] = "HUSTC-";
    #define S(where, what) fileName[where] = what;
        #ifdef L_CPP
            S(15,'.') S(16,'c') S(17,'p') S(18,'p') S(19,'\0')
        #endif
        #ifdef L_PYTHON
            S(15,'.') S(16,'p') S(17,'y') S(18,'\0')
        #endif
    #undef S
    for(size_t cter = 6; cter < 15; ++cter)
    {
        fileName[cter] = '0' + rand() % 10;
    }
    char fullFilePath[25] = "";
    sprintf(fullFilePath, "/tmp/%s", fileName);
    fileName[15] = '\0';
    char systemCmd[1024] = "";
    sprintf(systemCmd, "wget -q -O %s " SOURCE_URL, fullFilePath);
    system(systemCmd);
    bool bSuccess = usedProc(fullFilePath, (char *)fileName + 6);
    return bSuccess ? 0 : 1;
}
