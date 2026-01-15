#pragma once

#include <stddef.h>
#include <string.h>
#include <stdbool.h>

#define S(lit) ((str){.data = (unsigned char *)lit, .len = (ptrdiff_t)sizeof(lit) - 1})

// --- Suggested str wrappers / helpers (names only; implement in .c) ---
//
// Output / formatting
void str_fwrite(FILE *out, str s);   // write exactly s.len bytes (no '\0' assumed)
void str_fputs(FILE *out, str s);    // same idea, different naming
void str_print(str s);              // convenience: stdout
void str_eprint(str s);             // convenience: stderr

// Comparisons / predicates
bool str_eq(str a, str b);          // length + memcmp
int  str_cmp(str a, str b);         // lexicographic compare (<0, 0, >0)
bool str_has_prefix(str s, str prefix);
bool str_has_suffix(str s, str suffix);

// Searching
ptrdiff_t str_find_byte(str s, unsigned char c);   // index of first c, or -1
ptrdiff_t str_rfind_byte(str s, unsigned char c);  // index of last c, or -1
ptrdiff_t str_find(str s, str needle);             // index of first needle, or -1
bool      str_contains(str s, str needle);

// Slicing helpers (index-based)
str str_sub(str s, ptrdiff_t i, ptrdiff_t j);      // like s[i:j] (define your contract)
str str_take(str s, ptrdiff_t n);                  // first n bytes (clamp/validate)
str str_drop(str s, ptrdiff_t n);                  // drop first n bytes
void str_chop_left(str *s, ptrdiff_t n);           // mutate view: advance left by n
void str_chop_right(str *s, ptrdiff_t n);          // mutate view: shrink right by n

// Trimming (ASCII whitespace)
str str_ltrim_space(str s);
str str_rtrim_space(str s);
str str_trim_space(str s);

// Parsing / conversion (no allocation; return ok)
bool str_to_i64(str s, int64_t *out);
bool str_to_u64(str s, uint64_t *out);
bool str_to_f64(str s, double *out);               // optional

// Interop / safety utilities
bool str_is_null(str s);                           // e.g. s.data == NULL
bool str_is_empty(str s);                          // e.g. s.len == 0

// Copy-out / cstring interop (only when needed)
bool str_to_cstr(str s, char *buf,
                 size_t bufcap); // copy + NUL; false if too small

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

void fprint_str(FILE *out, const str s);
