#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"

void config_ctor (void) {
    config.max.s = 59;
    config.max.m = 59;
    config.max.h = 23;
}

static SECURITY_ATTRIBUTES security_attributes = {
    .nLength = sizeof (SECURITY_ATTRIBUTES),
    .lpSecurityDescriptor = NULL,
    .bInheritHandle = FALSE
};

static char natStrData [sizeof "(1)(2)(3)(04)"];

__attribute__ ((constructor)) static void natStrData_ctor (void) {
    memcpy (natStrData, "(0)(0)(0)(00)", sizeof "(0)(0)(0)(00)");
}

char* natStr (int x) {
    #define x9 (x <= 9)
    #define x99 (x <= 99)
    #define x999 (x <= 999)

    #define m(n) (x##n ? 1 : 10)

    natStrData [1] = '0' + x % 10;
    natStrData [4] = '0' + x / m (999) % 10;
    natStrData [7] = '0' + x / ( m (99) * m (999) ) % 10;
    natStrData [11] = '0' + x / ( m (9) * m (99) * m (999) ) % 10;
    return &natStrData [x9 ? 9 : (x99 ? 6 : (x999 ? 3 : 0))];
}

void (createDirWithErrMan) (char* pa, debugInfo info) {
    if (!createDir (pa)) {
        switch (GetLastError ()) {
            case ERROR_PATH_NOT_FOUND:
                fprintf (stderr
                        ,"\nError: path not found."
                         "\n  Path reveived : %s"
                         "\n    %s"
                         "\n    [%i] %s"
                        ,pa, info.func, info.line, info.file
                        );
                exit (EXIT_FAILURE);
        }
    }
}

bool createDir (char* path) {
    return CreateDirectory (path, &security_attributes);
}

FILE* (fopenWithErrMan) (char* path, const char* mode, debugInfo info) {
    FILE* fp = fopen (path, mode);
    if (fp == NULL) {
        fprintf (stderr
                ,"\nError: couldn't open file."
                 "\n  Path received: %s"
                 "\n    %s"
                 "\n    [%i] %s"
                ,path, info.func, info.line, info.file
                );
        exit (EXIT_FAILURE);
    }
    return fp;
}




