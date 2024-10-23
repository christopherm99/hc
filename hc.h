#ifndef __HC_H
#define __HC_H

#include <sys/ioctl.h>
#include <locale.h>
#include <string.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <libutil.h>

#define STDOUT 1
#define _HC_NS 0x008294E2
#define _HC_WE 0x008094E2
#define _HC_NW 0x008C94E2
#define _HC_NE 0x009094E2
#define _HC_SE 0x009894E2
#define _HC_SW 0x009494E2

#define _HC_STACK      0x01u
#define _HC_FIRST_LINE 0x80u

struct hc_state {
  int  term_width;
  int  term_height;
  char flags;
};

struct hc_state *_HC_STATE = NULL;

static void initialize(void) {
  struct winsize w;

  setlocale(LC_ALL, "");

  if (_HC_STATE != NULL) return;
  _HC_STATE = (struct hc_state *)malloc(sizeof(struct hc_state));
  ioctl(STDOUT, TIOCGWINSZ, &w);
  _HC_STATE->term_width = w.ws_col;
  _HC_STATE->term_height = w.ws_row;
}

static void destroy(void) {
  if (_HC_STATE == NULL) return;
  free(_HC_STATE);
  _HC_STATE = NULL;
}

static void _render_line(char *left, char *center, char *right, int w) {
  char buf[w + 8];

  // pad to center box
  memset(buf, ' ', w/2);
  write(STDOUT, buf, w/2);

  *((uint32_t *)&(buf[0])) = _HC_NS;
  *((uint32_t *)&(buf[w + 4])) = _HC_NS;
  memset(&buf[4], ' ', w);
  if (left) memcpy(&buf[5], left, strlen(left));
  if (center) memcpy(&buf[(w / 2) - (strlen(center) / 2) + 4], center, strlen(center));
  if (right) memcpy(&buf[w + 3 - strlen(right)], right, strlen(right));

  write(STDOUT, buf, w + 8);
  if (_HC_STATE->flags & _HC_STACK) {
    uint32_t buf[1];
    buf[0] = _HC_STATE->flags & _HC_FIRST_LINE ? _HC_NE : _HC_NS ;
    _HC_STATE->flags &= ~_HC_FIRST_LINE;
    write(STDOUT, buf, 4);
  }
  write(STDOUT, "\n", 1);
}

static void render(char *phone, char *desc, char *header, char *subheader) {
  uint32_t *buf;
  int h, w, i;

  initialize();
  _HC_STATE->flags = _HC_STACK | _HC_FIRST_LINE;

  w = (_HC_STATE->term_width / 2);
  buf = (uint32_t *)malloc((4 * (w + 2)) + 1);
  // pad to center box
  memset(buf, ' ', w/2);
  write(STDOUT, buf, w/2);

  buf[0] = _HC_NW;
  for (i = 1; i < w + 1; i++) buf[i] = _HC_WE;
  buf[i] = _HC_NE;
  *(char *)(&buf[i+1]) = '\n';
  write(STDOUT, buf, (4 * (w + 2)) + 1);
  _render_line(phone, NULL, desc, w);
  _render_line(NULL, NULL, "at UCLA", w);
  _render_line(NULL, NULL, NULL, w);
  _render_line(NULL, header, NULL, w);
  _render_line(NULL, subheader, NULL, w);
  _render_line(NULL, NULL, NULL, w);
  _render_line("uid=chris", NULL, "groups=chris,admin", w);

  // pad to center box
  memset(buf, ' ', w/2);
  write(STDOUT, buf, w/2);

  buf[0] = _HC_SW;
  for (i = 1; i < w + 1; i++) buf[i] = _HC_WE;
  buf[i] = _HC_SE;
  write(STDOUT, buf, (4 * (w + 2)));
  if (_HC_STATE->flags & _HC_STACK) {
    uint32_t b[1];
    char c[w/2];
    b[0] = _HC_STATE->flags & _HC_FIRST_LINE ? _HC_NE : _HC_NS ;
    write(STDOUT, b, 4);
    write(STDOUT, "\n ", 2);
    // pad to center box
    memset(c, ' ', w/2);
    write(STDOUT, c, w/2);
    write(STDOUT, buf, (4 * (w + 2)));
  }
  write(STDOUT, "\n", 1);
}

#endif

