#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdargs.h>

struct State {
  bool(transition_fn*(char **cur, ...));
  struct State *next_state;
}

struct State END_STATE;

bool dot_matcher(char **cur, ...) {
  ++(*cur);
  return true;
}

bool lit_matcher(char **cur, ...) {
  va_list arg_list;
  char re_cur = va_arg(arg_list, char);
  va_end(arg_list);

  bool is_match;
  if (**cur == re_cur) {
    is_match = true;
    ++(*cur);
  } else 
    is_match = false;
  return is_match;
}

bool(normal_match*(char **cur, ...))(char re_cur) {
  if (re_cur == '.')
    return dot_matcher;
  else
    return lit_matcher;
}

bool(qmark_match*(char **cur, ...))(char re_cur) {
  if (re_cur == '.')
    return qm_dot_matcher;
  else
    return qm_lit_matcher;
}

struct State *normal_state(struct State *state, char **re_cur) {
  state->next_state = malloc(sizeof(struct State));

  if (*(*re_cur+1) == '?') {
    state->transition_fn = qmark_match(**re_cur);
    *re_cur += 2;
  } else if (*(*re_cur+1) == '*') {
    state->transition_fn = star_match(**re_cur);
    *re_cur += 2;
  } else {
    state->transition_fn = normal_match(**re_cur);
    ++(*re_cur);
  }
  return state->next_state;
}

void build_regex(struct State *result, char *regex) {
  char *re_cur = regex;
  
  result = malloc(sizeof(struct State));
  struct State cur_state = result;

  for(; *re_cur != '\0'; ++re_cur) {
    if (*re_cur == '\\')
      cur_state = escape_state(cur_state, &re_cur);
    else
      cur_state = normal_state(cur_state, &re_cur);
  }
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
