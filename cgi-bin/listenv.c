#include <unistd.h>
#include <stdio.h>

extern char **environ;

void W(const char *tag) {
  printf("<%s>\n", tag);
}

int main() {
  W("html");
  W("b");
  printf("Environment variables:");
  W("/b");
  W("br");
  W("br");
  for (int i = 0; environ[i]; i++) {
    printf("%s\n", environ[i]);
    W("br");
  }
  W("/html");
}
