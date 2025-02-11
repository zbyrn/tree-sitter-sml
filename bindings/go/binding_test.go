package tree_sitter_sml_test

import (
	"testing"

	tree_sitter "github.com/tree-sitter/go-tree-sitter"
	tree_sitter_sml "github.com/zbyrn/tree-sitter-sml/bindings/go"
)

func TestCanLoadGrammar(t *testing.T) {
	language := tree_sitter.NewLanguage(tree_sitter_sml.Language())
	if language == nil {
		t.Errorf("Error loading Sml grammar")
	}
}
