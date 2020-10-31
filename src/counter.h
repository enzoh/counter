#ifndef COUNTER_H
#define COUNTER_H

#include "ic0.h"

void canister_init() WASM_EXPORT("canister_init");

void get() WASM_EXPORT("canister_query get");

void set() WASM_EXPORT("canister_update set");

void inc() WASM_EXPORT("canister_update inc");

void dec() WASM_EXPORT("canister_update dec");

#endif /* COUNTER_H */
