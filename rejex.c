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

void replace_match(char *result, char *string, char *replace, int match_len, int match_index) {
  int replace_len = strlen(replace);
  memset(result, 0, sizeof(result));
  char *cpy_start = result;
  memcpy(cpy_start, string, match_index);
  cpy_start += match_index;
  memcpy(cpy_start, replace, replace_len);
  cpy_start += replace_len;
  char *after_match = string + match_index + match_len;
  int remaining_len = strlen(string) - match_index - match_len;
  memcpy(cpy_start, after_match, remaining_len);
}

int main(int argc, char *argv[]) {
  char *string = argv[1];
  char *match = argv[2];
  char *replace = argv[3];

  int match_index = find_match_index(string, match);
  printf("Match at %d\n", match_index);

  char result[strlen(string) + strlen(match)];
  replace_match(result, string, replace, strlen(match), match_index);

  printf("Result: %s\n", result);

  return 0;
}
