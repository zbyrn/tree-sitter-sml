#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 5
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 9
#define ALIAS_COUNT 0
#define TOKEN_COUNT 7
#define EXTERNAL_TOKEN_COUNT 1
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 1
#define PRODUCTION_ID_COUNT 1

enum ts_symbol_identifiers {
  sym_real_constant = 1,
  sym_integer_constant = 2,
  sym_word_constant = 3,
  sym_string_constant = 4,
  sym_char_constant = 5,
  sym_comment = 6,
  sym_source_file = 7,
  sym__atomic_expression = 8,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_real_constant] = "real_constant",
  [sym_integer_constant] = "integer_constant",
  [sym_word_constant] = "word_constant",
  [sym_string_constant] = "string_constant",
  [sym_char_constant] = "char_constant",
  [sym_comment] = "comment",
  [sym_source_file] = "source_file",
  [sym__atomic_expression] = "_atomic_expression",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym_real_constant] = sym_real_constant,
  [sym_integer_constant] = sym_integer_constant,
  [sym_word_constant] = sym_word_constant,
  [sym_string_constant] = sym_string_constant,
  [sym_char_constant] = sym_char_constant,
  [sym_comment] = sym_comment,
  [sym_source_file] = sym_source_file,
  [sym__atomic_expression] = sym__atomic_expression,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [sym_real_constant] = {
    .visible = true,
    .named = true,
  },
  [sym_integer_constant] = {
    .visible = true,
    .named = true,
  },
  [sym_word_constant] = {
    .visible = true,
    .named = true,
  },
  [sym_string_constant] = {
    .visible = true,
    .named = true,
  },
  [sym_char_constant] = {
    .visible = true,
    .named = true,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym__atomic_expression] = {
    .visible = false,
    .named = true,
    .supertype = true,
  },
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static const TSStateId ts_primary_state_ids[STATE_COUNT] = {
  [0] = 0,
  [1] = 1,
  [2] = 2,
  [3] = 3,
  [4] = 4,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(33);
      if (lookahead == '"') ADVANCE(1);
      if (lookahead == '#') ADVANCE(2);
      if (lookahead == '0') ADVANCE(36);
      if (lookahead == '~') ADVANCE(5);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(38);
      END_STATE();
    case 1:
      if (lookahead == '"') ADVANCE(42);
      if (lookahead == '\\') ADVANCE(10);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(1);
      END_STATE();
    case 2:
      if (lookahead == '"') ADVANCE(9);
      END_STATE();
    case 3:
      if (lookahead == '"') ADVANCE(43);
      if (lookahead == '\\') ADVANCE(14);
      END_STATE();
    case 4:
      if (lookahead == '"') ADVANCE(43);
      if (lookahead == '\\') ADVANCE(14);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(4);
      END_STATE();
    case 5:
      if (lookahead == '0') ADVANCE(37);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(38);
      END_STATE();
    case 6:
      if (lookahead == '\\') ADVANCE(1);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\f' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(6);
      END_STATE();
    case 7:
      if (lookahead == '\\') ADVANCE(9);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\f' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(7);
      END_STATE();
    case 8:
      if (lookahead == '\\') ADVANCE(3);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\f' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(8);
      END_STATE();
    case 9:
      if (lookahead == '\\') ADVANCE(11);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '"') ADVANCE(4);
      END_STATE();
    case 10:
      ADVANCE_MAP(
        '^', 31,
        'u', 29,
        '\t', 6,
        '\n', 6,
        '\f', 6,
        '\r', 6,
        ' ', 6,
        '"', 1,
        '\\', 1,
        'a', 1,
        'b', 1,
        'f', 1,
        'n', 1,
        'r', 1,
        't', 1,
        'v', 1,
      );
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(19);
      END_STATE();
    case 11:
      ADVANCE_MAP(
        '^', 32,
        'u', 30,
        '\t', 7,
        '\n', 7,
        '\f', 7,
        '\r', 7,
        ' ', 7,
        '"', 3,
        '\\', 3,
        'a', 3,
        'b', 3,
        'f', 3,
        'n', 3,
        'r', 3,
        't', 3,
        'v', 3,
      );
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(20);
      END_STATE();
    case 12:
      if (lookahead == 'x') ADVANCE(24);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(40);
      END_STATE();
    case 13:
      if (lookahead == '~') ADVANCE(17);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(35);
      END_STATE();
    case 14:
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\f' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(8);
      END_STATE();
    case 15:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(1);
      END_STATE();
    case 16:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(34);
      END_STATE();
    case 17:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(35);
      END_STATE();
    case 18:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(3);
      END_STATE();
    case 19:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(15);
      END_STATE();
    case 20:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(18);
      END_STATE();
    case 21:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(1);
      END_STATE();
    case 22:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(39);
      END_STATE();
    case 23:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(3);
      END_STATE();
    case 24:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(41);
      END_STATE();
    case 25:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(21);
      END_STATE();
    case 26:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(23);
      END_STATE();
    case 27:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(25);
      END_STATE();
    case 28:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(26);
      END_STATE();
    case 29:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(27);
      END_STATE();
    case 30:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(28);
      END_STATE();
    case 31:
      if (('@' <= lookahead && lookahead <= '_')) ADVANCE(1);
      END_STATE();
    case 32:
      if (('@' <= lookahead && lookahead <= '_')) ADVANCE(3);
      END_STATE();
    case 33:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 34:
      ACCEPT_TOKEN(sym_real_constant);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(13);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(34);
      END_STATE();
    case 35:
      ACCEPT_TOKEN(sym_real_constant);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(35);
      END_STATE();
    case 36:
      ACCEPT_TOKEN(sym_integer_constant);
      if (lookahead == '.') ADVANCE(16);
      if (lookahead == 'w') ADVANCE(12);
      if (lookahead == 'x') ADVANCE(22);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(13);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(38);
      END_STATE();
    case 37:
      ACCEPT_TOKEN(sym_integer_constant);
      if (lookahead == '.') ADVANCE(16);
      if (lookahead == 'x') ADVANCE(22);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(13);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(38);
      END_STATE();
    case 38:
      ACCEPT_TOKEN(sym_integer_constant);
      if (lookahead == '.') ADVANCE(16);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(13);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(38);
      END_STATE();
    case 39:
      ACCEPT_TOKEN(sym_integer_constant);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(39);
      END_STATE();
    case 40:
      ACCEPT_TOKEN(sym_word_constant);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(40);
      END_STATE();
    case 41:
      ACCEPT_TOKEN(sym_word_constant);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(41);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(sym_string_constant);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(sym_char_constant);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0, .external_lex_state = 1},
  [1] = {.lex_state = 0, .external_lex_state = 1},
  [2] = {.lex_state = 0, .external_lex_state = 1},
  [3] = {.lex_state = 0, .external_lex_state = 1},
  [4] = {.lex_state = 0, .external_lex_state = 1},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_real_constant] = ACTIONS(1),
    [sym_integer_constant] = ACTIONS(1),
    [sym_word_constant] = ACTIONS(1),
    [sym_string_constant] = ACTIONS(1),
    [sym_char_constant] = ACTIONS(1),
    [sym_comment] = ACTIONS(3),
  },
  [1] = {
    [sym_source_file] = STATE(3),
    [sym__atomic_expression] = STATE(4),
    [sym_real_constant] = ACTIONS(5),
    [sym_integer_constant] = ACTIONS(7),
    [sym_word_constant] = ACTIONS(5),
    [sym_string_constant] = ACTIONS(5),
    [sym_char_constant] = ACTIONS(5),
    [sym_comment] = ACTIONS(3),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(9), 1,
      ts_builtin_sym_end,
  [7] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(11), 1,
      ts_builtin_sym_end,
  [14] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(13), 1,
      ts_builtin_sym_end,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 7,
  [SMALL_STATE(4)] = 14,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [7] = {.entry = {.count = 1, .reusable = false}}, SHIFT(2),
  [9] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__atomic_expression, 1, 0, 0),
  [11] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [13] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1, 0, 0),
};

enum ts_external_scanner_symbol_identifiers {
  ts_external_token_comment = 0,
};

static const TSSymbol ts_external_scanner_symbol_map[EXTERNAL_TOKEN_COUNT] = {
  [ts_external_token_comment] = sym_comment,
};

static const bool ts_external_scanner_states[2][EXTERNAL_TOKEN_COUNT] = {
  [1] = {
    [ts_external_token_comment] = true,
  },
};

#ifdef __cplusplus
extern "C" {
#endif
void *tree_sitter_sml_external_scanner_create(void);
void tree_sitter_sml_external_scanner_destroy(void *);
bool tree_sitter_sml_external_scanner_scan(void *, TSLexer *, const bool *);
unsigned tree_sitter_sml_external_scanner_serialize(void *, char *);
void tree_sitter_sml_external_scanner_deserialize(void *, const char *, unsigned);

#ifdef TREE_SITTER_HIDE_SYMBOLS
#define TS_PUBLIC
#elif defined(_WIN32)
#define TS_PUBLIC __declspec(dllexport)
#else
#define TS_PUBLIC __attribute__((visibility("default")))
#endif

TS_PUBLIC const TSLanguage *tree_sitter_sml(void) {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
    .external_scanner = {
      &ts_external_scanner_states[0][0],
      ts_external_scanner_symbol_map,
      tree_sitter_sml_external_scanner_create,
      tree_sitter_sml_external_scanner_destroy,
      tree_sitter_sml_external_scanner_scan,
      tree_sitter_sml_external_scanner_serialize,
      tree_sitter_sml_external_scanner_deserialize,
    },
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
