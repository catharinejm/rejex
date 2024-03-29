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

  if (*m_cur == '.' || *m_cur == *s_cur) {
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

  if (!matched) m_idx = -1;

  return m_idx;
}

void replace_at_index(char *result, char *string, char *replace, int match_index, int match_len) {
  memset(result, 0, sizeof(result));
  memcpy(result, string, match_index);

  strcat(result, replace);

  char *after_match = string + match_index + match_len;
  strcat(result, after_match);
}

int main(int argc, char *argv[]) {
  if (argc < 4) {
    printf("Usage: %s <string> <match> <replace>\n", argv[0]);
    return 1;
  }

  char *string = argv[1];
  char *match = argv[2];
  char *replace = argv[3];

  int match_index = find_match_index(string, match);
  if (match_index > -1) {
    printf("Match at %d\n", match_index);

    char result[strlen(string) + (strlen(replace) - strlen(match)) + 1];
    replace_at_index(result, string, replace, match_index, strlen(match));

    printf("Result: %s\n", result);
  } else {
    printf("No match!\n");
  }

  return 0;
}
