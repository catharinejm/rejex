#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_match(char *input, char *regex) {
  if (strlen(regex) < 1) return false;

  char *cur = input, *tok1 = regex, *tok2 = regex+1;
  bool matches = true, escaped = false;
  while(matches && *tok2) {
    if ('\\' == *tok1) {
      if (escaped) {
        matches = '\\' == *cur;
        ++cur;
      }

      escaped = !escaped;

      ++tok1;
      ++tok2;
    } else if ('?' == *tok2) {
      if (*cur == *tok1) ++cur;
      tok1 += 2;
      tok2 += 2;
    } else if ('*' == *tok2) {
      if (*cur == *tok1) ++cur;
      else {
        tok1 += 2;
        tok2 += 2;
      }
    } else {
      matches = *cur == *tok1;
      if (*cur) ++cur;

      ++tok1;
      ++tok2;
    }
  }

  matches = *cur == *tok1;

  return matches;
}

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
  if (argc < 3) {
    printf("Usage: %s <string> <regex>\n", argv[0]);
    return 1;
  }

  char *string = argv[1];
  char *regex = argv[2];

  if (is_match(string, regex))
    printf("Matches!\n");
  else
    printf("No match...\n");

  return 0;
}
