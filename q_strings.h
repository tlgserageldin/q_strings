#pragma once

#include <stddef.h>
#include <string.h>
#include <stdbool.h>

#define S(lit) ((str){.data = (unsigned char *)lit, .len = (ptrdiff_t)sizeof(lit) - 1})

typedef struct {
  unsigned char *data;
  ptrdiff_t len;
} str;

typedef struct {
  str head;
  str tail;
  bool ok;
} snip;

// returns a substring from start to end
str slice(const unsigned char *start, const unsigned char *end);

// returns a snip, splitting s on first instance of c
snip cut(const str s, const char c);

bool are_equal(const str a, const str b);
bool is_valid_str(const str a);

void fprint_str(FILE *out, str s);
