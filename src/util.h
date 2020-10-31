#ifndef UTIL_H
#define UTIL_H

#include <tommath.h>

void trap(const char *str);

void mp_okay_or_trap(mp_err err);

void mp_print(const mp_int *n);

#endif /* UTIL_H */
