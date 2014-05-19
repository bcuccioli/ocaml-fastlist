#include <stdio.h>

#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/fail.h>
#include <caml/memory.h>
#include <caml/mlvalues.h>

CAMLprim value
clist_length(value v) {
  CAMLparam1(v);
  CAMLlocal1(head);

  int len = 0;

  while (v != Val_emptylist) {
    head = Field(v, 0); /* Access the head. */
    v = Field(v, 1); /* Points to the tail. */
    len++;
  }

  return Val_int(len);
}

CAMLprim value
clist_hd(value v) {
  CAMLparam1(v);
  CAMLlocal1(head);
  if (v == Val_emptylist) {
    /* List is empty, so failwith "hd". */
    caml_failwith("hd");
  }
  head = Field(v, 0);
  CAMLreturn(head);
}

CAMLprim value
clist_tl(value v) {
  CAMLparam1(v);
  CAMLlocal1(head);
  if (v == Val_emptylist) {
    /* List is empty, so failwith "hd". */
    caml_failwith("tl");
  }
  v = Field(v, 1);
  CAMLreturn(v);
}
