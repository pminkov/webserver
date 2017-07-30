#ifndef __UTILS_H_
#define __UTILS_H_

#include "string_util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void error(char *message) {
  perror(message);
  exit(1);
}

char *read_text_from_socket(int sockfd) {
  const int BUF_SIZE = 256;
  char *buffer = malloc(BUF_SIZE);

  char *result = malloc(1);
  result[0] = '\0';

  int n;
  while (1) {
    int n = read(sockfd, buffer, BUF_SIZE - 1);
    if (n < 0) {
      error("Error reading from socket");
    }
    buffer[n] = '\0';
    char *last_result = result;
    result = strappend(last_result, buffer);
    free(last_result);
    if (n < BUF_SIZE - 1) {
      break;
    }
  }

  free(buffer);

  return result;
}

void write_to_socket(int sockfd, const char *message) {
  if (write(sockfd, message, strlen(message)) == -1) {
    error("write_to_socket");
  }
}

#endif
