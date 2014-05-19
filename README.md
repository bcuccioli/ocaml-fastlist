# OCaml C Lists

This is an implementation of the OCaml `List` library in C using the standard
OCaml-C interface.

The default OCaml `List` module functions are implemented in OCaml and in
some cases are not tail recursive. This project aims to provide a more
efficient implementation by using low-level code without recursion.

## License

This project is licensed under the MIT Open Source license.
