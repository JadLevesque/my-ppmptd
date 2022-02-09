#include <windows.h>
#include <stdio.h>

#include "lib.h"
#include "common.h"


void gd_libDir (char* libP, char* pa, size_t paz) {
    snprintf (pa
             ,paz
             ,"%s/my_ppmptd"
             ,libP
             );

    createDirWithErrMan (pa);
}
