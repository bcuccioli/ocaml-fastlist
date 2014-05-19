all: clist.cma

clist.cma:
	@ocamlc -i clist.ml > clist.mli
	@ocamlc -c clist.mli
	@ocamlc -c clist.ml
	@gcc -c -I"`ocamlc -where`" -Werror list_stubs.c
	@ocamlmklib -o list_stubs list_stubs.o
	@ocamlc -a -custom -o clist.cma clist.cmo -dllib dlllist_stubs.so

clean:
	@rm -f *.[oa] *.so *.cm[ixoa] *.cmxa clist.mli

.PHONY: clean
