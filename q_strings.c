#include "q_strings.h"

// Output / formatting
// write exactly s.len bytes (no '\0' assumed)
void str_fwrite(FILE *out, str s) {
		if (str_is_empty(s) || str_is_null(s)) {
				return;
		}
		if (out == NULL) {
				return;
		}                  
		fwrite(s.data, sizeof(s.data[0]), (size_t)s.len, out);
}
// Interop / safety utilities
bool str_is_null(str s) {
		if (s.data == NULL) {
				return true;
		}
		return false;
}

bool str_is_empty(str s) {
		if (s.len == 0) {
				return true;
		}
		return false;  
}  
bool are_equal(str a, str b) {
  if (a.len != b.len) {
    return false;
  } else if (a.data == b.data) {
    return true;
  } else if (!a.data || !b.data) {
    return false;
  }
  return !memcmp(a.data, b.data, a.len);
}

str slice(unsigned char *start, unsigned char *end) {
  str s = {0};
  s.data = start;
  s.len = start ? end - start : 0;
  return s;
}

snip cut(str s, char c) {
  snip n = {0};
  if (!s.len) {
    return n;
  } // null pointer case

  unsigned char *beggining = s.data;
  unsigned char *end = s.data + s.len;
  unsigned char *cut = beggining;

  for (; cut < end && *cut != c; cut++)
    ;

  n.ok = cut < end;
  n.head = slice(beggining, cut);
  // if ok then we want one past the delim,
  // otherwise we hit the end so just return a 0 len str
  n.tail = slice(n.ok ? cut + 1 : cut, end);

  return n;
}

// str is valid if points to something and has > 0 length
inline bool is_valid_str(str a) {
  return a.len && a.data; 
}
