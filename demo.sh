#!/bin/sh

dfx start --background
dfx canister create counter
dfx build
dfx canister install counter
dfx canister call counter set '(-57896044618658097711785492504343953926634992332820282019728792003956564819968)'
dfx canister call counter inc
dfx canister call counter dec
dfx canister call counter get
