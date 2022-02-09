#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <time.h>

#include "common.h"
#include "gen_pp.h"
#include "gen_time.h"
#include "gen_date.h"
#include "lib.h"


enum DateGenMode {
    DateGenMode_assert = 0,
    DateGenMode_3_6M_files = 1,
} typedef DateGenMode;


int main (int argc, char** argv)
{
    DateGenMode m;
    bool mf = false;
    char* libP;


    if (argc == 3) {
        printf ("\n%s", argv [0]);
        if (strcmp (argv [2], "3_6M_files") == 0) {
            m = DateGenMode_3_6M_files;
            printf ("\n3_6M_files");
            mf = true;
        }
        else if (strcmp (argv [2], "assert") == 0) {
            m = DateGenMode_assert;
            printf ("\nassert");
            mf = true;
        }
    }
    if (mf == false || argc != 3) {
        fprintf (stderr
                ,"\nError: wrong number of arguments."
                 "\n  This code generator may be called in the following ways:"
                 "\n    time.exe <path>"
                 "\n    time.exe <path> <mode>"
                 "\n  where:"
                 "\n    <mode> :: assert | 3_6M_files"
                );
        exit (EXIT_FAILURE);
    }

    libP = argv [1];

    size_t paz = strlen (libP)
               + MY_PPMPTD_GEN_MAX (strlen ("/my_ppmptd/time/hh/mm.h")
                                   ,strlen ("/my_ppmptd/date/y/y/y/y/mm.h")
                                   )
               + sizeof "";

    char pa [paz];


    // gen directories
//    gd_lib (libP, pa, paz);
//    gd_lib (char* libP, char* pa, size_t paz);


//    gd_time
//    gd_date

    // gen lib dir
    gd_libDir (libP, pa, paz);


    // gen time.h
    gf_time (libP, pa, paz);




    // gen ppmptd/date/
    snprintf (pa
             ,paz
             ,"%s/my_ppmptd/date"
             ,libP
             );

    createDirWithErrMan (pa);


    void (*ftable[2]) (char*,char*,size_t) = {
        [DateGenMode_3_6M_files] = gf_date_fileCall,
        [DateGenMode_assert] = gf_date_assert
    };

    ftable [m] (libP, pa, paz);




    return 0;
}
