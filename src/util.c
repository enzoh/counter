#include <stdint.h>
#include <string.h>
#include <tommath.h>

#include "ic0.h"
#include "util.h"

void trap(const char *str) {
  size_t len = strlen(str);
  ic0_trap((uint32_t)(str), (uint32_t)(len));
}

void mp_okay_or_trap(mp_err err) {
  if (err != MP_OKAY) {
    trap(mp_error_to_string(err));
  }
}

void mp_print(const mp_int *n) {
  char str[128];
  size_t len = 0;
  mp_okay_or_trap(mp_to_radix(n, str, 128, &len, 10));
  ic0_debug_print((uint32_t)(str), (uint32_t)(len));
}
