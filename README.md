#  An Arbitrary-Precision Counter for the Internet Computer in C

[![Build Status](https://github.com/enzoh/counter/workflows/build/badge.svg)](https://github.com/enzoh/counter/actions?query=workflow%3Abuild)

## Overview

This repository provides a simple example that demonstrates how to build an application for the [Internet Computer](https://dfinity.org) in C. The source files provided here are compiled down to [WebAssembly](https://webassembly.org) via [Clang](https://clang.llvm.org) and linked against WebAssembly build targets for [`libc`](https://musl.libc.org) and [`libtommath`](https://www.libtom.net/LibTomMath) via [LLD](https://lld.llvm.org/WebAssembly.html).

## Prerequisites

- [Clang + LLD](https://releases.llvm.org)
- [WASI Libc](https://github.com/WebAssembly/wasi-libc)
- [libtommath-wasm](https://github.com/enzoh/libtommath-wasm/releases)
- [DFINITY SDK](https://sdk.dfinity.org)

See the [workflow](https://github.com/enzoh/counter/blob/master/.github/workflows/ci.yml) for installation details.

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

## Contribute

Feel free to join in. All are welcome. Open an [issue](https://github.com/enzoh/counter/issues)!
