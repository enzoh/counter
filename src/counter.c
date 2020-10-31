#include <malloc.h>
#include <tommath.h>

#include "counter.h"
#include "message.h"
#include "util.h"

mp_int *N = NULL;

/**
 * Initialize this canister.
 */
void canister_init() {
  N = (mp_int *)(malloc(sizeof(mp_int)));
  if (N == NULL) {
    trap("Out of memory!");
  }
  mp_okay_or_trap(mp_init(N));
}

/**
 * Get the value of the counter.
 */
void get() {
  receive_empty();
  send_integer(N);
}

/**
 * Set the value of the counter.
 */
void set() {
  receive_integer(256, N);
  send_empty();
}

/**
 * Increment the value of the counter.
 */
void inc() {
  receive_empty();
  mp_okay_or_trap(mp_incr(N));
  send_empty();
}

/**
 * Decrement the value of the counter.
 */
void dec() {
  receive_empty();
  mp_okay_or_trap(mp_decr(N));
  send_empty();
}
