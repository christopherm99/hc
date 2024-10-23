#include "hc.h"

int main(int argc, char **argv) {
  if (argc != 2) return -1;

  printf("\n");
  render("", "AI Safety", argv[1], "A user account");
  printf("\n");

  return 0;
}

