#include "gen_pp.h"
#include "common.h"

#include <windows.h>



int gen_if (FILE* fp, char* text) {
    return fprintf (fp
                   ,"#if %s\n"
                   ,text
                   );
}
int gen_else (FILE* fp) {
    return fprintf (fp
                   ,"#else\n"
                   );
}
int gen_undef (FILE* fp, char* macro) {
    return fprintf (fp
                   ,"#undef %s\n"
                   ,macro
                   );
}
int gen_endif (FILE* fp) {
    return fprintf (fp
                   ,"#endif\n"
                   );
}
int gen_pragma (FILE* fp, char* text) {
    return fprintf (fp
                   ,"#pragma %s\n"
                   ,text
                   );
}
int gen_define (FILE* fp, char* macro, char* text) {
    return fprintf (fp
                   ,"#define %s %s\n"
                   ,macro, text
                   );
}
int gen_unassert (FILE* fp, char* pred) {
    return fprintf (fp
                   ,"#unassert %s\n"
                   ,pred
                   );
}
int gen_include (FILE* fp, char* path) {
    return fprintf (fp
                   ,"#include %s\n"
                   ,path
                   );
}
int gen_ifdef (FILE* fp, char* macro) {
    return fprintf (fp
                   ,"#ifdef %s\n"
                   ,macro
                   );
}
int gen_nl (FILE* fp) {
    return fputc ('\n', fp);
}
