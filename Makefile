TS ?= tree-sitter

all install uninstall clean:
	$(MAKE) -C grammars/sml $@

test:
	$(TS) test
	$(TS) parse --quiet --stat --paths examples/mlton.txt
	$(TS) parse --quiet --stat --paths examples/smlnj.txt

files: examples/mlton.txt examples/smlnj.txt
	cat $^ > test/files.txt

generate:
	cd grammars/sml && $(TS) generate

build:
	cd grammars/sml && $(TS) build


.PHONY: all install uninstall clean test update generate build
