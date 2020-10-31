# Count 256-Bit Integers on the Internet Computer in C

[![Build Status](https://github.com/enzoh/counter/workflows/build/badge.svg)](https://github.com/enzoh/counter/actions?query=workflow%3Abuild)

## Prerequisites

- [Clang + LLVM](https://releases.llvm.org)
- [WASI Libc](https://github.com/WebAssembly/wasi-libc)
- [libtommath-wasm](https://github.com/enzoh/libtommath-wasm/releases)
- [DFINITY SDK](https://sdk.dfinity.org)

See the [build script](https://github.com/enzoh/counter/blob/master/.github/workflows/ci.yml) for details.

## Deployment

```
dfx start --background
dfx canister create counter
dfx build
dfx canister install counter
```

## Usage

### Get

Get the value of the counter.

```
dfx canister call counter get
```

### Set

Set the value of the counter.

```
dfx canister call counter set '(123456)'
```

### Increment

Increment the value of the counter.

```
dfx canister call counter inc
```

### Decrement

Decrement the value of the counter.

```
dfx canister call counter dec
```
