#!/bin/sh
clang src/main.c src/autocomplete.c src/list.c -o autocomp -ggdb -std=c11
