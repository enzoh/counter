#include <malloc.h>
#include <stdbool.h>
#include <stdint.h>
#include <tommath.h>

#include "leb128.h"
#include "util.h"

size_t read_sleb128(const uint8_t *buf, size_t len, int off, int budget, mp_int *n) {

  int i = off;
  int j = budget;

  bool more = true;

  uint8_t byte = 0x00;
  uint8_t mask = 0x00;

  mp_zero(n);

  mp_int *r = (mp_int *)(malloc(sizeof(mp_int)));
  if (r == NULL) {
    trap("Out of memory!");
  }
  mp_okay_or_trap(mp_init(r));

  while (more) {
    if (i >= len) {
      trap("Out of bounds!");
    }
    if (j <= 0) {
      trap("Out of bits!");
    }
    byte = buf[i];
    mask = (0xFF << (j - 1)) & 0x7F;
    if ((j < 7) && ((byte & mask) != 0x00) && ((byte & mask) != mask)) {
      trap("Integer overflow!");
    }
    if ((byte & 0x80) == 0x80) {
      mp_set_i32(r, (int32_t)(byte & 0x7F));
      mp_okay_or_trap(mp_mul_2d(r, budget - j, r));
      mp_okay_or_trap(mp_or(n, r, n));
      i++;
      j -= 7;
    } else {
      more = false;
    }
  }

  mp_set_i32(r, (int32_t)(int8_t)(((byte << 1) & 0x80) | byte));
  mp_okay_or_trap(mp_mul_2d(r, budget - j, r));
  mp_okay_or_trap(mp_or(n, r, n));

  mp_clear(r);

  free(r);

  return i - off;
}

size_t write_sleb128(const mp_int *n, void (*write_byte)(uint8_t)) {

  int i = 0;

  bool more = true;
  bool negative = mp_isneg(n);

  uint8_t byte = 0x00;
  uint8_t mask = negative ? 0xFF : 0x00;

  mp_int *r = (mp_int *)(malloc(sizeof(mp_int)));
  if (r == NULL) {
    trap("Out of memory!");
  }
  mp_okay_or_trap(mp_init_copy(r, n));

  mp_int *s = (mp_int *)(malloc(sizeof(mp_int)));
  if (s == NULL) {
    trap("Out of memory!");
  }
  mp_okay_or_trap(mp_init_u32(s, 0xFF));

  while (more) {
    byte = (uint8_t)(mp_get_i32(r)) & 0x7F;
    mp_okay_or_trap(mp_signed_rsh(r, 7, r));
    if ((mp_cmp(r, s) == MP_GT) || ((uint8_t)(mp_get_i32(r)) != mask)) {
      byte |= 0x80;
      write_byte(byte);
      i++;
    } else {
      more = false;
    }
  }

  int sign = (byte & 0x40) == 0x40;
  if (((!sign) && (!negative)) || (sign && negative)) {
    write_byte(byte);
    i++;
  } else {
    byte |= 0x80;
    write_byte(byte);
    i++;
    byte = mask & 0x7F;
    write_byte(byte);
    i++;
  }

  mp_clear(r);
  mp_clear(s);

  free(r);
  free(s);

  return i;
}
