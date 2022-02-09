#pragma once
#include <stdbool.h>

#define MY_PPMPTD_GEN_MAX(x,y) ((x) > (y) ? (x) : (y))

#define MY_PPMPTD_PCAT(a,b) a##b
#define MY_PPMPTD_CAT(a,b) MY_PPMPTD_PCAT(a,b)

#define LID(name) MY_PPMPTD_CAT(name,__LINE__)



struct debugInfo {
    char* file;
    char* func;
    int line;
} typedef debugInfo;


struct config {
    struct {
        int s, m, h;
    } max;
} config;

__attribute__ ((constructor)) void config_ctor (void);

char* natStr (int x);

void createDirWithErrMan (char* pa, debugInfo info);
#define createDirWithErrMan(pa) createDirWithErrMan (pa, (debugInfo) {(char*)__FILE__, (char*)__func__, __LINE__})

bool createDir (char* path);

FILE* fopenWithErrMan (char* path, const char* mode, debugInfo info);
#define fopenWithErrMan(path, mode) fopenWithErrMan (path, mode, (debugInfo) {(char*)__FILE__, (char*)__func__, __LINE__})

