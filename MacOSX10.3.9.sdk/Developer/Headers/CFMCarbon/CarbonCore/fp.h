#pragma once
#include <math.h>
#include <ansi_fp.h>
extern double x80tod(const extended80 * x80);
extern void dtox80(const double *x, extended80 *x80);
extern void dec2str(const decform *f, const decimal *d, char *s);
#define DECSTROUTLEN   80
