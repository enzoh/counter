#include <malloc.h>
#include <stdint.h>
#include <tommath.h>

#include "ic0.h"
#include "leb128.h"
#include "message.h"
#include "util.h"

uint8_t IDL_MAGIC[4] = {0x44, 0x49, 0x44, 0x4C};
uint8_t IDL_TYPE_int = 0x7C;

size_t MESSAGE_SIZE_LIMIT = 16384;

void write_byte(uint8_t byte) {
  ic0_msg_reply_data_append((uint32_t)(&byte), 1);
}

void write_magic() {
  ic0_msg_reply_data_append((uint32_t)(IDL_MAGIC), 4);
}

void match_byte(const uint8_t *buf, size_t len, int off, uint8_t byte) {
  if (off >= len || buf[off] != byte) {
    trap("Invalid byte!");
  }
}

void match_magic(const uint8_t *buf, size_t len) {
  for (int i = 0; i < 4; i++) {
    match_byte(buf, len, i, IDL_MAGIC[i]);
  }
}

void send_empty() {
  write_magic();
  write_byte(0x00);
  write_byte(0x00);
  ic0_msg_reply();
}

void send_integer(const mp_int *n) {
  write_magic();
  write_byte(0x00);
  write_byte(0x01);
  write_byte(IDL_TYPE_int);
  write_sleb128(n, write_byte);
  ic0_msg_reply();
}

void receive_empty() {
  size_t len = (size_t)(ic0_msg_arg_data_size());
  if (len != 6) {
    trap("Invalid argument data!");
  }
  uint8_t *buf = (uint8_t *)(malloc(len));
  ic0_msg_arg_data_copy((uint32_t)(buf), 0, (uint32_t)(len));
  match_magic(buf, len);
  match_byte(buf, len, 4, 0x00);
  match_byte(buf, len, 5, 0x00);
  free(buf);
}

void receive_integer(int budget, mp_int *n) {
  size_t len = (size_t)(ic0_msg_arg_data_size());
  if (len < 8) {
    trap("Invalid argument data!");
  }
  if (len > MESSAGE_SIZE_LIMIT) {
    trap("Message too large!");
  }
  uint8_t *buf = (uint8_t *)(malloc(len));
  ic0_msg_arg_data_copy((uint32_t)(buf), 0, (uint32_t)(len));
  match_magic(buf, len);
  match_byte(buf, len, 4, 0x00);
  match_byte(buf, len, 5, 0x01);
  match_byte(buf, len, 6, IDL_TYPE_int);
  read_sleb128(buf, len, 7, budget, n);
  free(buf);
}
