TS ?= tree-sitter

all install uninstall clean:
	$(MAKE) -C grammars/sml $@

test:
	$(TS) test

generate:
	cd grammars/sml && $(TS) generate


.PHONY: all install uninstall clean test update generate
