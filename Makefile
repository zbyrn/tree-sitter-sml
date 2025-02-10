TS ?= tree-sitter

all install uninstall clean:
	$(MAKE) -C grammars/sml $@

test:
	$(TS) test

generate:
	$(TS) generate grammars/sml

build:
	$(TS) build grammars/sml


.PHONY: all install uninstall clean test update generate build
