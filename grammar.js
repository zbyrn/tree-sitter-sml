/**
 * @file Tree-sitter parser for Standard ML
 * @author Byron Zhong <zhongbangyuan@gmail.com>
 * @license MIT
 */

/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
  name: "sml",

  rules: {
    // TODO: add the actual grammar rules
    source_file: $ => "hello"
  }
});
