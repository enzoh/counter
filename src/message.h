#ifndef MESSAGE_H
#define MESSAGE_H

#include <tommath.h>

void send_empty();

void send_integer(const mp_int *n);

void receive_empty();

void receive_integer(int budget, mp_int *n);

#endif /* MESSAGE_H */
