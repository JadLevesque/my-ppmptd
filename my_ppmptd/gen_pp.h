#pragma once

#include <stdbool.h>
#include <stdio.h>

int gen_if (FILE* fp, char* text);
int gen_else (FILE* fp);
int gen_undef (FILE* fp, char* macro);
int gen_endif (FILE* fp);
int gen_pragma (FILE* fp, char* text);
int gen_define (FILE* fp, char* macro, char* text);
int gen_unassert (FILE* fp, char* pred);
int gen_include (FILE* fp, char* path);
int gen_ifdef (FILE* fp, char* macro);
int gen_nl (FILE* fp);
