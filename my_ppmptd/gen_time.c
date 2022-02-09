#include <stdio.h>
#include <windows.h>

#include "gen_pp.h"
#include "gen_time.h"
#include "common.h"




#if 0
//\\code{
./my_ppmptd/time.h
#pragma push_macro ("T")
#undef T
#define T GCC_ASSERT (T,__TIME__)
#unassert T

#include "./my_ppmptd/time/0/0.h"
    #ifdef T                          // + [1]
    #include "./my_ppmptd/time/0/1.h" // +
    [1] ...

    #ifdef T
    #include "./my_ppmptd/time/23/59.h"
    #else
    #define MY_PPMPTD_TIME_HOURS Error_couldnt_match_time
    #define MY_PPMPTD_TIME_MINUTES Error_couldnt_match_time
    #define MY_PPMPTD_TIME_SECONDS Error_couldnt_match_time

    #endif
    ...
    #endif

#pragma pop_macro ("T")
//}
#endif

int gen_defTime (FILE* fp, int h, int m, int s) {
    return fprintf (fp // MY_PPMPTD : my ppmp time date
                   ,"#define MY_PPMPTD_TIME_HOURS %u\n"
                    "#define MY_PPMPTD_TIME_MINUTES %u\n"
                    "#define MY_PPMPTD_TIME_SECONDS %u\n"
                   ,h, m, s
                   );
}

int gen_assertT (FILE* fp, int h, int m, int s) {
    return fprintf (fp
                   ,"#assert T (\"%02u:%02u:%02u\")\n"
                   ,h, m, s
                   );
}


void gf_secondsVariant (char* libP, char* pa, size_t paz, int h, int m) {
    int s;
    FILE* fp;


    snprintf (pa
             ,paz
             ,"%s/my_ppmptd/time/%u/%u.h"
             ,libP, h, m
             );
    printf ("\nFile: %s", pa);

    fp = fopenWithErrMan (pa, "w+");

    for (s = 0; s <= config.max.s; s++) {
        gen_assertT  (fp, h, m, s);
        gen_if      (fp, "T");
        gen_defTime (fp, h, m, s);
        gen_undef   (fp, "T");
        gen_else    (fp);
    }

    gen_unassert (fp, "T");

    for (s = 0; s <= config.max.s; s++)
        gen_endif (fp);

    fclose (fp);
}

//void gf_timeH

void gf_time (char* libP, char* pa, size_t paz) {
    FILE* fp;

    // time dir
    snprintf (pa
             ,paz
             ,"%s/my_ppmptd/time/"
             ,libP
             );

    createDirWithErrMan (pa);


    // file my_ppmptd/utils.h
    snprintf (pa
             ,paz
             ,"%s/my_ppmptd/utils.h"
             ,libP
             );

    fp = fopenWithErrMan (pa, "w+");

    gen_pragma (fp, "once");

    gen_nl (fp);

    gen_define (fp, "MY_PPMPTD_PCAT(a,b)", "a##b");
    gen_define (fp, "MY_PPMPTD_GCC_ASSERT(p,a...)", "MY_PPMPTD_PCAT(%,:) p (a)");

    fclose (fp);


    // file my_ppmptd/time.h
    snprintf (pa
             ,paz
             ,"%s/my_ppmptd/time.h"
             ,libP
             );

    fp = fopenWithErrMan (pa, "w+");

    gen_pragma (fp, "once");

    gen_nl (fp);

    gen_include (fp, "<my_ppmptd/utils.h>");

    gen_pragma   (fp, "push_macro (\"T\")");
    gen_undef    (fp, "T");
    gen_define   (fp, "T", "MY_PPMPTD_GCC_ASSERT(T,__TIME__)");
    gen_unassert (fp, "T");

    gen_nl (fp);

    int m, h;

    for (h = 0; h <= config.max.h; h++) {
        snprintf (pa
                 ,paz
                 ,"%s/my_ppmptd/time/%u/"
                 ,libP, h
                 );
        createDirWithErrMan (pa);

        for (m = 0; m <= config.max.m; m++) {
            // minutes variants

            gen_ifdef (fp, "T");

            snprintf (pa // reusing pa since it has the right size
                     ,paz
                     ,"<my_ppmptd/time/%u/%u.h>"
                     ,h, m
                     );

            gen_include (fp, pa);
        }

        gen_else (fp);

        gen_define (fp, "MY_PPMPTD_TIME_HOURS",   "Error_couldnt_match_time");
        gen_define (fp, "MY_PPMPTD_TIME_MINUTES", "Error_couldnt_match_time");
        gen_define (fp, "MY_PPMPTD_TIME_SECONDS", "Error_couldnt_match_time");

        for (m = 0; m <= config.max.m; m++)
            gen_endif (fp);


        for (m = 0; m <= config.max.m; m++) {
            // seconds variants
            gf_secondsVariant (libP, pa, paz, h, m);
        }
    }

    gen_pragma (fp, "pop_macro (\"T\")");

    fclose (fp);
}
