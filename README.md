# OCaml C Lists

This is an implementation of the OCaml `List` library in C using the standard
OCaml-C interface.

The default OCaml `List` module functions are implemented in OCaml and in
some cases are not tail recursive. This project aims to provide a more
efficient implementation by using low-level code without recursion.

## Building

To compile the new list module, a Makefile has been provided. To build the
module and load it in the top-level, simply run

    $ make
    $ ocaml clist.cma

and then `open Clist;;` in the OCaml top-level.

## TODO

* Implement the remainder of the List module.
* Experimentally determine performance gains.

## License

This project is licensed under the MIT Open Source license.
