#pragma once
#include <time.h>

const char* const monthNames [13];

int gen_assertD (FILE* fp, int y, int m, int d);

int gen_defDate (FILE* fp, int y, int m, int d);

int maxDay (int m, int y);
int formatDate (char* buf, size_t n, int d, int m, int y);

void gf_ppmptdDirs (char* libP, char* pa, size_t paz);

void gf_yearVariants (char* libP, char* pa, size_t paz);
void gf_date (char* libP, char* pa, size_t paz);


void gf_date_fileCall (char* libP, char* pa, size_t paz);
void gf_date_assert (char* libP, char* pa, size_t paz);
