#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct State;
struct Transition;

struct Transition {
  char literal;
  enum Transition_type type;
  struct State * next_state;
};

struct State {
  struct Transition transitions[10];
  int t_count;
};

enum Transition_type {
  LITERAL,
  ANY_CHAR,
  LAMBDA
};

const struct State END_STATE;

void add_transition(struct State * cur_state, struct State * next_state, enum Transition_type ttype, char literal) {
  struct Transition &new_trans = cur_state->transitions[cur_state->t_count];
  new_trans.literal = literal;
  new_trans.type = ttype;
  new_trans.next_state = next_state;
  cur_state->t_count++;
}

bool is_match(char chr, char *m_cur) {
  return *m_cur == '.' || *m_cur == chr;
}

// consume regex on match
// consume input on miss
// is escaped

struct state * build_NFA(char *regex) {
  struct state * start = malloc(sizeof(struct State));
  memset(start, 0, sizeof(struct State));

  struct state * cur_state = start;
  char *cur_tok;
  bool escaped = false, star = false;
  for (cur_tok = regex; cur_tok != '\0'; ++cur_tok) {
    switch (*cur_tok) {
      case '.': add_transition(cur_state
    }
  }
}

int find_match_index(char *string, char *match) {
  int m_idx = -1;

  char *s_cur, *m_cur;
  bool matched = false, in_match = false;
  for (s_cur = string, m_cur = match;
      *s_cur != '\0' && !matched;
      ++s_cur) {

    if (is_match(*s_cur, m_cur)) {
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
  printf("Match at %d\n", match_index);

  char result[strlen(string) + (strlen(replace) - strlen(match)) + 1];
  replace_at_index(result, string, replace, match_index, strlen(match));

  printf("Result: %s\n", result);

  return 0;
}
