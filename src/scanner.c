#include "tree_sitter/parser.h"
#include "tree_sitter/alloc.h"
#include "tree_sitter/array.h"

#include <stdlib.h>
#include <stdbool.h>
#include <wctype.h>

enum TokenType {
    COMMENT
};

/* empty struct */
typedef struct State *StateT;

/******************** Helper Functions ***********************/

static inline void advance(TSLexer *lexer)
{
    lexer->advance(lexer, false);
}

static inline void skip(TSLexer *lexer)
{
    lexer->advance(lexer, true);
}

static inline bool eof(TSLexer *lexer)
{
    return lexer->eof(lexer);
}

/********************* Scanner Functions ********************/

static inline StateT create()
{
    return NULL;
}

static inline void destroy(StateT s)
{
    (void) s;
}

static inline unsigned serialize(StateT s, char *buffer)
{
    (void) s, (void) buffer;
    return 0;
}

static inline void deserialize(StateT s, const char *buffer, unsigned length)
{
    (void) s, (void) buffer, (void) length;
}

static inline bool scan_comment(StateT s, TSLexer *lexer)
{
    (void) s;
    while (iswspace(lexer->lookahead)) {
        skip(lexer);
    }

    if (lexer->lookahead != '(') {
        return false;
    }
    advance(lexer);
    if (lexer->lookahead != '*') {
        return false;
    }
    advance(lexer);
    /* committed to parsing a comment now */
    lexer->result_symbol = COMMENT;
    uint32_t depth = 1;

    for (;;) {
        switch (lexer->lookahead) {
        case '\0':
            if (eof(lexer)) {
                /* allowing unclosed comments */
                return true;
            }
            /* NULL character in comments */
            advance(lexer);
            break;
        case '(':
            advance(lexer);
            if (lexer->lookahead == '*') {
                depth++;
                advance(lexer);
            }
            break;
        case '*':
            advance(lexer);
            if (lexer->lookahead == ')') {
                depth--;
                advance(lexer);
            }
            if (depth == 0) {
                return true;
            }
            break;
        default:
            advance(lexer);
        }
    }

    /* unreachable */
    assert(0);
}

static inline bool scan(StateT s, TSLexer *lexer, const bool *valid_symbols)
{
    if (valid_symbols[COMMENT] && scan_comment(s, lexer)) {
        return true;
    }

    return false;
}

/********************** Entry Points ************************/
void *tree_sitter_sml_external_scanner_create()
{
    return create();
}

void tree_sitter_sml_external_scanner_destroy(void *payload)
{
    destroy(payload);
}

unsigned tree_sitter_sml_external_scanner_serialize(void *payload, char *buffer)
{
    return serialize(payload, buffer);
}

void tree_sitter_sml_external_scanner_deserialize(
        void *payload,
        const char *buffer,
        unsigned length
) {
    deserialize(payload, buffer, length);
}

bool tree_sitter_sml_external_scanner_scan(
        void *payload,
        TSLexer *lexer,
        const bool *valid_symbols
) {
    return scan(payload, lexer, valid_symbols);
}
