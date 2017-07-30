#include "utils.h"
#include "string_util.h"

#include <assert.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h> 
#include <unistd.h>


int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Syntax: client <url>\n");
    exit(1);
  }

  char *url = argv[1];
  
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    error("socket");
  }

  uint16_t port = 8000;

  struct sockaddr_in serv_addr;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);
  serv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in)) == -1) {
    /* Try running the client without the server started and you'll get this error */
    error("connect");
  }

  char *get_str = malloc(128 + strlen(url));;
  sprintf(get_str, "GET %s HTTP/1.1", url);
  printf("%s", get_str);
  write_to_socket(sockfd, get_str);
  // write_to_socket(sockfd, "GET /static/example_org.html HTTP/1.1"); // get_str);

  char *result = read_text_from_socket(sockfd);
  printf("From socket: %s\n\n", result);
  free(result);

  close(sockfd);

  return 0;
}
