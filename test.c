#include "hc.h"

int main(int argc, char **argv) {
  if (argc != 2) return -1;

  printf("\n");
  struct hc_data f0 = { .left = "uid=chris", .right = "groups=chris,admin" };
  struct hc_data e1 = { .next = &f0 };
  struct hc_data m1 = { .center = argv[1], .next = &e1 };
  struct hc_data m0 = { .center = "Christopher Milan", .next = &m1 };
  struct hc_data e0 = { .next = &m0 };
  struct hc_data h0 = { .left = "chrismilan@ucla.edu", .right = "AI Safety at UCLA", .next = &e0 };
  render(&h0);
  printf("\n");

  return 0;
}

