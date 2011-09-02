#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int find_match_index(char *string, char *match) {
  int m_idx = -1;

  char *s_cur, *m_cur;
  bool matched = false, in_match = false;
  for (s_cur = string, m_cur = match;
      *s_cur != '\0' && !matched;
      ++s_cur) {

    if (*s_cur == *m_cur) {
      if (!in_match) {
        m_idx = s_cur - string;
        in_match = true;
      }

      ++m_cur;

      if (*m_cur == '\0') matched = true;
    } else if (in_match) {
      in_match = false;
      m_cur = match;
      m_idx = -1;
    }
  }

  return m_idx;
}

int main(int argc, char *argv[]) {
  char *string = argv[1];
  char *match = argv[2];

  printf("Match at %d\n", find_match_index(string, match));

  return 0;
}
