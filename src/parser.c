#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 21
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 23
#define ALIAS_COUNT 0
#define TOKEN_COUNT 13
#define EXTERNAL_TOKEN_COUNT 1
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 4
#define PRODUCTION_ID_COUNT 1

enum ts_symbol_identifiers {
  sym_identifier = 1,
  sym_real_literal = 2,
  sym_integer_literal = 3,
  sym_word_literal = 4,
  sym_string_literal = 5,
  sym_char_literal = 6,
  aux_sym__selector_token1 = 7,
  anon_sym_EQ = 8,
  anon_sym_LBRACE = 9,
  anon_sym_COMMA = 10,
  anon_sym_RBRACE = 11,
  sym_comment = 12,
  sym_source_file = 13,
  sym__literal = 14,
  sym__selector = 15,
  sym_expression_row = 16,
  sym_record_expression = 17,
  sym__atomic_expression = 18,
  sym__expression = 19,
  sym_expression_declaration = 20,
  sym__declaration = 21,
  aux_sym_record_expression_repeat1 = 22,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_identifier] = "identifier",
  [sym_real_literal] = "real_literal",
  [sym_integer_literal] = "integer_literal",
  [sym_word_literal] = "word_literal",
  [sym_string_literal] = "string_literal",
  [sym_char_literal] = "char_literal",
  [aux_sym__selector_token1] = "_selector_token1",
  [anon_sym_EQ] = "=",
  [anon_sym_LBRACE] = "{",
  [anon_sym_COMMA] = ",",
  [anon_sym_RBRACE] = "}",
  [sym_comment] = "comment",
  [sym_source_file] = "source_file",
  [sym__literal] = "_literal",
  [sym__selector] = "_selector",
  [sym_expression_row] = "expression_row",
  [sym_record_expression] = "record_expression",
  [sym__atomic_expression] = "_atomic_expression",
  [sym__expression] = "_expression",
  [sym_expression_declaration] = "expression_declaration",
  [sym__declaration] = "_declaration",
  [aux_sym_record_expression_repeat1] = "record_expression_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym_identifier] = sym_identifier,
  [sym_real_literal] = sym_real_literal,
  [sym_integer_literal] = sym_integer_literal,
  [sym_word_literal] = sym_word_literal,
  [sym_string_literal] = sym_string_literal,
  [sym_char_literal] = sym_char_literal,
  [aux_sym__selector_token1] = aux_sym__selector_token1,
  [anon_sym_EQ] = anon_sym_EQ,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_COMMA] = anon_sym_COMMA,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [sym_comment] = sym_comment,
  [sym_source_file] = sym_source_file,
  [sym__literal] = sym__literal,
  [sym__selector] = sym__selector,
  [sym_expression_row] = sym_expression_row,
  [sym_record_expression] = sym_record_expression,
  [sym__atomic_expression] = sym__atomic_expression,
  [sym__expression] = sym__expression,
  [sym_expression_declaration] = sym_expression_declaration,
  [sym__declaration] = sym__declaration,
  [aux_sym_record_expression_repeat1] = aux_sym_record_expression_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [sym_identifier] = {
    .visible = true,
    .named = true,
  },
  [sym_real_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_integer_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_word_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_string_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_char_literal] = {
    .visible = true,
    .named = true,
  },
  [aux_sym__selector_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COMMA] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACE] = {
    .visible = true,
    .named = false,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym__literal] = {
    .visible = false,
    .named = true,
    .supertype = true,
  },
  [sym__selector] = {
    .visible = false,
    .named = true,
  },
  [sym_expression_row] = {
    .visible = true,
    .named = true,
  },
  [sym_record_expression] = {
    .visible = true,
    .named = true,
  },
  [sym__atomic_expression] = {
    .visible = false,
    .named = true,
    .supertype = true,
  },
  [sym__expression] = {
    .visible = false,
    .named = true,
    .supertype = true,
  },
  [sym_expression_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym__declaration] = {
    .visible = false,
    .named = true,
    .supertype = true,
  },
  [aux_sym_record_expression_repeat1] = {
    .visible = false,
    .named = false,
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
  [5] = 5,
  [6] = 6,
  [7] = 7,
  [8] = 8,
  [9] = 9,
  [10] = 10,
  [11] = 11,
  [12] = 12,
  [13] = 13,
  [14] = 14,
  [15] = 15,
  [16] = 16,
  [17] = 17,
  [18] = 18,
  [19] = 19,
  [20] = 20,
};

static TSCharacterRange sym_identifier_character_set_2[] = {
  {'!', '!'}, {'#', '\''}, {'*', '+'}, {'-', '-'}, {'/', '/'}, {':', ':'}, {'<', '@'}, {'\\', '\\'},
  {'^', '^'}, {'|', '|'}, {'~', '~'},
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(35);
      ADVANCE_MAP(
        '"', 2,
        '#', 3,
        ',', 51,
        '0', 40,
        '=', 49,
        '{', 50,
        '}', 52,
        '~', 6,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(42);
      END_STATE();
    case 1:
      if (lookahead == '"') ADVANCE(2);
      if (lookahead == '#') ADVANCE(3);
      if (lookahead == '0') ADVANCE(40);
      if (lookahead == '{') ADVANCE(50);
      if (lookahead == '~') ADVANCE(6);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(1);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(42);
      END_STATE();
    case 2:
      if (lookahead == '"') ADVANCE(46);
      if (lookahead == '\\') ADVANCE(11);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(2);
      END_STATE();
    case 3:
      if (lookahead == '"') ADVANCE(10);
      END_STATE();
    case 4:
      if (lookahead == '"') ADVANCE(47);
      if (lookahead == '\\') ADVANCE(16);
      END_STATE();
    case 5:
      if (lookahead == '"') ADVANCE(47);
      if (lookahead == '\\') ADVANCE(16);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(5);
      END_STATE();
    case 6:
      if (lookahead == '0') ADVANCE(41);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(42);
      END_STATE();
    case 7:
      if (lookahead == '\\') ADVANCE(2);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\f' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(7);
      END_STATE();
    case 8:
      if (lookahead == '\\') ADVANCE(10);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\f' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(8);
      END_STATE();
    case 9:
      if (lookahead == '\\') ADVANCE(4);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\f' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(9);
      END_STATE();
    case 10:
      if (lookahead == '\\') ADVANCE(12);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '"') ADVANCE(5);
      END_STATE();
    case 11:
      ADVANCE_MAP(
        '^', 33,
        'u', 31,
        '\t', 7,
        '\n', 7,
        '\f', 7,
        '\r', 7,
        ' ', 7,
        '"', 2,
        '\\', 2,
        'a', 2,
        'b', 2,
        'f', 2,
        'n', 2,
        'r', 2,
        't', 2,
        'v', 2,
      );
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(21);
      END_STATE();
    case 12:
      ADVANCE_MAP(
        '^', 34,
        'u', 32,
        '\t', 8,
        '\n', 8,
        '\f', 8,
        '\r', 8,
        ' ', 8,
        '"', 4,
        '\\', 4,
        'a', 4,
        'b', 4,
        'f', 4,
        'n', 4,
        'r', 4,
        't', 4,
        'v', 4,
      );
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(22);
      END_STATE();
    case 13:
      if (lookahead == 'x') ADVANCE(26);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(44);
      END_STATE();
    case 14:
      if (lookahead == '}') ADVANCE(52);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(14);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(48);
      if (set_contains(sym_identifier_character_set_2, 11, lookahead)) ADVANCE(36);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(37);
      END_STATE();
    case 15:
      if (lookahead == '~') ADVANCE(19);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(39);
      END_STATE();
    case 16:
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\f' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(9);
      END_STATE();
    case 17:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(2);
      END_STATE();
    case 18:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(38);
      END_STATE();
    case 19:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(39);
      END_STATE();
    case 20:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(4);
      END_STATE();
    case 21:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(17);
      END_STATE();
    case 22:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(20);
      END_STATE();
    case 23:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(2);
      END_STATE();
    case 24:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(43);
      END_STATE();
    case 25:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(4);
      END_STATE();
    case 26:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(45);
      END_STATE();
    case 27:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(23);
      END_STATE();
    case 28:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(25);
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
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(29);
      END_STATE();
    case 32:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(30);
      END_STATE();
    case 33:
      if (('@' <= lookahead && lookahead <= '_')) ADVANCE(2);
      END_STATE();
    case 34:
      if (('@' <= lookahead && lookahead <= '_')) ADVANCE(4);
      END_STATE();
    case 35:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 36:
      ACCEPT_TOKEN(sym_identifier);
      if (set_contains(sym_identifier_character_set_2, 11, lookahead)) ADVANCE(36);
      END_STATE();
    case 37:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '\'' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(37);
      END_STATE();
    case 38:
      ACCEPT_TOKEN(sym_real_literal);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(15);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(38);
      END_STATE();
    case 39:
      ACCEPT_TOKEN(sym_real_literal);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(39);
      END_STATE();
    case 40:
      ACCEPT_TOKEN(sym_integer_literal);
      if (lookahead == '.') ADVANCE(18);
      if (lookahead == 'w') ADVANCE(13);
      if (lookahead == 'x') ADVANCE(24);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(15);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(42);
      END_STATE();
    case 41:
      ACCEPT_TOKEN(sym_integer_literal);
      if (lookahead == '.') ADVANCE(18);
      if (lookahead == 'x') ADVANCE(24);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(15);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(42);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(sym_integer_literal);
      if (lookahead == '.') ADVANCE(18);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(15);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(42);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(sym_integer_literal);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(43);
      END_STATE();
    case 44:
      ACCEPT_TOKEN(sym_word_literal);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(44);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(sym_word_literal);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(45);
      END_STATE();
    case 46:
      ACCEPT_TOKEN(sym_string_literal);
      END_STATE();
    case 47:
      ACCEPT_TOKEN(sym_char_literal);
      END_STATE();
    case 48:
      ACCEPT_TOKEN(aux_sym__selector_token1);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(48);
      END_STATE();
    case 49:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 50:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 52:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0, .external_lex_state = 1},
  [1] = {.lex_state = 1, .external_lex_state = 1},
  [2] = {.lex_state = 1, .external_lex_state = 1},
  [3] = {.lex_state = 14, .external_lex_state = 1},
  [4] = {.lex_state = 14, .external_lex_state = 1},
  [5] = {.lex_state = 0, .external_lex_state = 1},
  [6] = {.lex_state = 0, .external_lex_state = 1},
  [7] = {.lex_state = 0, .external_lex_state = 1},
  [8] = {.lex_state = 0, .external_lex_state = 1},
  [9] = {.lex_state = 0, .external_lex_state = 1},
  [10] = {.lex_state = 0, .external_lex_state = 1},
  [11] = {.lex_state = 0, .external_lex_state = 1},
  [12] = {.lex_state = 0, .external_lex_state = 1},
  [13] = {.lex_state = 0, .external_lex_state = 1},
  [14] = {.lex_state = 0, .external_lex_state = 1},
  [15] = {.lex_state = 0, .external_lex_state = 1},
  [16] = {.lex_state = 0, .external_lex_state = 1},
  [17] = {.lex_state = 0, .external_lex_state = 1},
  [18] = {.lex_state = 0, .external_lex_state = 1},
  [19] = {.lex_state = 0, .external_lex_state = 1},
  [20] = {.lex_state = 0, .external_lex_state = 1},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_real_literal] = ACTIONS(1),
    [sym_integer_literal] = ACTIONS(1),
    [sym_word_literal] = ACTIONS(1),
    [sym_string_literal] = ACTIONS(1),
    [sym_char_literal] = ACTIONS(1),
    [aux_sym__selector_token1] = ACTIONS(1),
    [anon_sym_EQ] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [sym_comment] = ACTIONS(3),
  },
  [1] = {
    [sym_source_file] = STATE(16),
    [sym__literal] = STATE(6),
    [sym_record_expression] = STATE(6),
    [sym__atomic_expression] = STATE(7),
    [sym__expression] = STATE(17),
    [sym_expression_declaration] = STATE(18),
    [sym__declaration] = STATE(19),
    [sym_real_literal] = ACTIONS(5),
    [sym_integer_literal] = ACTIONS(7),
    [sym_word_literal] = ACTIONS(5),
    [sym_string_literal] = ACTIONS(5),
    [sym_char_literal] = ACTIONS(5),
    [anon_sym_LBRACE] = ACTIONS(9),
    [sym_comment] = ACTIONS(3),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      sym_integer_literal,
    ACTIONS(9), 1,
      anon_sym_LBRACE,
    STATE(7), 1,
      sym__atomic_expression,
    STATE(14), 1,
      sym__expression,
    STATE(6), 2,
      sym__literal,
      sym_record_expression,
    ACTIONS(5), 4,
      sym_real_literal,
      sym_word_literal,
      sym_string_literal,
      sym_char_literal,
  [26] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(13), 1,
      anon_sym_RBRACE,
    STATE(10), 1,
      sym_expression_row,
    STATE(20), 1,
      sym__selector,
    ACTIONS(11), 2,
      sym_identifier,
      aux_sym__selector_token1,
  [43] = 4,
    ACTIONS(3), 1,
      sym_comment,
    STATE(15), 1,
      sym_expression_row,
    STATE(20), 1,
      sym__selector,
    ACTIONS(11), 2,
      sym_identifier,
      aux_sym__selector_token1,
  [57] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(15), 3,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [66] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(17), 3,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [75] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(19), 3,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [84] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(21), 3,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [93] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(23), 1,
      anon_sym_COMMA,
    ACTIONS(25), 1,
      anon_sym_RBRACE,
    STATE(13), 1,
      aux_sym_record_expression_repeat1,
  [106] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(23), 1,
      anon_sym_COMMA,
    ACTIONS(27), 1,
      anon_sym_RBRACE,
    STATE(9), 1,
      aux_sym_record_expression_repeat1,
  [119] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(29), 3,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [128] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(31), 3,
      ts_builtin_sym_end,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [137] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(33), 1,
      anon_sym_COMMA,
    ACTIONS(36), 1,
      anon_sym_RBRACE,
    STATE(13), 1,
      aux_sym_record_expression_repeat1,
  [150] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(38), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [158] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(36), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [166] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(40), 1,
      ts_builtin_sym_end,
  [173] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(42), 1,
      ts_builtin_sym_end,
  [180] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(44), 1,
      ts_builtin_sym_end,
  [187] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(46), 1,
      ts_builtin_sym_end,
  [194] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(48), 1,
      anon_sym_EQ,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 26,
  [SMALL_STATE(4)] = 43,
  [SMALL_STATE(5)] = 57,
  [SMALL_STATE(6)] = 66,
  [SMALL_STATE(7)] = 75,
  [SMALL_STATE(8)] = 84,
  [SMALL_STATE(9)] = 93,
  [SMALL_STATE(10)] = 106,
  [SMALL_STATE(11)] = 119,
  [SMALL_STATE(12)] = 128,
  [SMALL_STATE(13)] = 137,
  [SMALL_STATE(14)] = 150,
  [SMALL_STATE(15)] = 158,
  [SMALL_STATE(16)] = 166,
  [SMALL_STATE(17)] = 173,
  [SMALL_STATE(18)] = 180,
  [SMALL_STATE(19)] = 187,
  [SMALL_STATE(20)] = 194,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [7] = {.entry = {.count = 1, .reusable = false}}, SHIFT(5),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [15] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__literal, 1, 0, 0),
  [17] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__atomic_expression, 1, 0, 0),
  [19] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__expression, 1, 0, 0),
  [21] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_record_expression, 2, 0, 0),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [25] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [27] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [29] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_record_expression, 3, 0, 0),
  [31] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_record_expression, 4, 0, 0),
  [33] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_record_expression_repeat1, 2, 0, 0), SHIFT_REPEAT(4),
  [36] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_record_expression_repeat1, 2, 0, 0),
  [38] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expression_row, 3, 0, 0),
  [40] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [42] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expression_declaration, 1, 0, 0),
  [44] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__declaration, 1, 0, 0),
  [46] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1, 0, 0),
  [48] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
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
