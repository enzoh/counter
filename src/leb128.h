#ifndef LEB128_H
#define LEB128_H

#include <stdint.h>
#include <tommath.h>

size_t read_sleb128(const uint8_t *buf, size_t len, int off, int budget, mp_int *n);

size_t write_sleb128(const mp_int *n, void (*write_byte)(uint8_t));

#endif /* LEB128_H */
