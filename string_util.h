#ifndef __STRING_UTIL_H
#define __STRING_UTIL_H

#include <ctype.h>

int starts_with(char *s, const char *with) {
  return strncmp(s, with, strlen(with)) == 0;
}

int ends_with(const char *s, const char *with) {
  int len_s = strlen(s);
  int len_with = strlen(with);

  if (len_with <= len_s) {
    return strncmp(s + len_s - len_with, with, len_with) == 0;
  } else {
    return 0;
  }
}

int contains(const char *s1, const char *s2) {
  return strstr(s1, s2) != NULL;
}

char* substr(const char* input, int offset, int len, char* dest) {
  int input_len = strlen (input);

  if (offset + len > input_len) {
    return NULL;
  }

  strncpy(dest, input + offset, len);
  return dest;
}

int ends_with_extension(const char *inp) {
  int end_pos = strlen(inp);

  while (--end_pos >= 0) {
    if (inp[end_pos] == '.') return 1;
    if (!isalpha(inp[end_pos])) return 0;
  }

  return 0;
}

char *concat(const char *s1, const char *s2) {
  char *r = malloc(strlen(s1) + strlen(s2) + 1);
  strcpy(r, s1);
  strcat(r, s2);
  return r;
}

char *concat3(const char *s1, const char *s2, const char *s3) {
  char *r = malloc(strlen(s1) + strlen(s2) + strlen(s3) + 1);
  strcpy(r, s1);
  strcat(r, s2);
  strcat(r, s3);
  return r;
}

#endif
