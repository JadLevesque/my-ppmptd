#pragma once
#include <stdlib.h>

int gen_defTime (FILE* fp, int h, int m, int s);
void gf_secondsVariant (char* libP, char* pa, size_t paz, int h, int m);
void gf_time (char* libP, char* pa, size_t paz);
int gen_assertT (FILE* fp, int h, int m, int s);
