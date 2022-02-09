#include <windows.h>
#include <stdio.h>

#include "gen_date.h"
#include "common.h"
#include "gen_pp.h"


#if 0

my_ppmptd/date.h
#pragma push_macro ("D")
#undef D
#define D GCC_ASSERT (D,__DATE__)
#unassert D

    #ifdef D
    #include <my_ppmptd/date/0/0/0/0.h>
    #ifdef D                            // + [1]
    #include <my_ppmptd/date/0/0/0/1.h> // +
    [1] ...

    #endif
    #endif
    ...

#pragma pop_macro ("D")

#endif



#if 0
my_ppmptd/date/0/0/0/0.h

#assert D ("Jan  1 1000")
#if D
gen_defDate()
#undef D
#else
#assert D ("Jan  1 1001")
#if D
gen_defDate()
#undef D
#else
...

#endif
#endif
...
#endif


int gen_assertD (FILE* fp, int y, int m, int d) {
    return fprintf (fp
                   ,"#assert D (\"%s %2u %4u\")\n"
                   ,monthNames [m], d, y
                   );
}

int gen_defDate (FILE* fp, int y, int m, int d) {
    return fprintf (fp
                   ,"#define MY_PPMPTD_DATE_YEAR %s\n"
                    "#define MY_PPMPTD_DATE_MONTH %u\n"
                    "#define MY_PPMPTD_DATE_DAY %u\n"
                   ,natStr (y), m, d
                   );
}


static int maxDayData [13] = {
    0,
    31, 1, 31, 30, 31, 30,
    31, 31, 30, 31, 30, 31
};

int maxDay (int m, int y) {
    return m == 2 ? (y % 4 ? 28 : 29) : maxDayData [m];
}

const char* const monthNames [13] = {
    0,
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

int formatDate (char* buf, size_t n, int d, int m, int y) {
    return snprintf (buf
                    ,n
                    ,"%s %2u %u"
                    ,monthNames [m], d, y
                    );
}

void gf_ppmptdDirs (char* libP, char* pa, size_t paz) {
    #define for_var(x, min, max) for (x = min; x <= max; x++)

    int a, b, c;

    for_var (a, 0, 9) {
        snprintf (pa
                 ,paz
                 ,"%s/my_ppmptd/date/%u"
                 ,libP, a
                 );
        createDirWithErrMan (pa);
        printf ("Dir: %s\n", pa);

        for_var (b, 0, 9) {
            snprintf (pa
                     ,paz
                     ,"%s/my_ppmptd/date/%u/%u"
                     ,libP, a, b
                     );
            createDirWithErrMan (pa);
            printf ("Dir: %s\n", pa);

            for_var (c, 0, 9) {
                snprintf (pa
                         ,paz
                         ,"%s/my_ppmptd/date/%u/%u/%u"
                         ,libP, a, b, c
                         );
                createDirWithErrMan (pa);
                printf ("Dir: %s\n", pa);
            }
        }
    }

    #undef for_var
}

void gf_yearVariants (char* libP, char* pa, size_t paz) {
    int y, m, d;
    FILE* fp;
    for (y = 0; y <= 9999; y++) {
        snprintf (pa
                 ,paz
                 ,"%s/my_ppmptd/date/%u/%u/%u/%u.h"
                 ,libP, (y / 1000) % 10, (y / 100) % 10, (y / 10) % 10, y % 10
                 );
        fp = fopenWithErrMan (pa, "w+");

        for (m = 1; m <= 12; m++)
        for (d = 1; d <= maxDay (m, y); d++) {
            gen_assertD (fp, y, m, d);
            gen_if (fp, "D");
            gen_defDate (fp, y, m, d);
            gen_undef (fp, "D");
            gen_else (fp);
        }

        for (m = 1; m <= 12; m++)
        for (d = 1; d <= maxDay (m, y); d++)
            gen_endif (fp);

        gen_unassert (fp, "D");

        fclose (fp);

        //printf ("File: %s\n", pa);
    }
}

void gf_date (char* libP, char* pa, size_t paz) {
    snprintf (pa
             ,paz
             ,"%s/my_ppmptd/date.h"
             ,libP
             );

    FILE* fp = fopenWithErrMan (pa, "w+");

    gen_pragma (fp, "once");

    gen_nl (fp);

    gen_include (fp, "<my_ppmptd/utils.h>");

    gen_nl (fp);

    gen_pragma (fp, "push_macro (\"D\")");
    gen_undef (fp, "D");
    gen_define (fp, "D", "MY_PPMPTD_GCC_ASSERT (D,__DATE__)");
    gen_unassert (fp, "D");

    int y;
    for (y = 0; y <= 9999; y++) {

        // yearVariants
        gen_ifdef (fp, "D");

        snprintf (pa
                 ,paz
                 ,"<my_ppmptd/date/%u/%u/%u/%u.h>"
                 ,(y / 1000) % 10, (y / 100) % 10, (y / 10) % 10, y % 10
                 );

        gen_include (fp, pa);

        printf ("Include: %s\n", pa);
    }

    gen_else (fp);

    fprintf (fp
            ,"#define MY_PPMPTD_DATE_DAY Error_couldnt_match_date\n"
             "#define MY_PPMPTD_DATE_MONTH Error_couldnt_match_date\n"
             "#define MY_PPMPTD_DATE_YEAR Error_couldnt_match_date\n"
            );

    for (y = 0; y <= 9999; y++) {
        printf ("\nendif: %u", y);
        gen_endif (fp);
    }

    fclose (fp);
}

void gf_date_fileCall (char* libP, char* pa, size_t paz) {
    int y, m, d;
    FILE* fp;

    for (y = 0; y <= 9999; y++) {
        printf ("\nYear: %u", y);

        for (m = 1; m <= 12; m++)
        for (d = 1; d <= maxDay (m, y); d++) {
            snprintf (pa
                     ,paz
                     ,"%s/my_ppmptd/date/%s %2u %4u"
                     ,libP, monthNames [m], d, y
                     );


            fp = fopenWithErrMan (pa, "w+");

            gen_defDate (fp, y, m, d);

            fclose (fp);
        }
    }
}

void gf_date_assert (char* libP, char* pa, size_t paz) {
    // gen ppmptd/date/y/y/y/
    gf_ppmptdDirs (libP, pa, paz);

    // gen ppmptd/date.h
    gf_date (libP, pa, paz);


    // ppmptd/date/y/y/y/y.h
    gf_yearVariants (libP, pa, paz);
}
