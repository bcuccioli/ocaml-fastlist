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
  if (v == Val_emptylist) {
    /* List is empty, so failwith "hd". */
    caml_failwith("tl");
  }
  v = Field(v, 1);
  CAMLreturn(v);
}

CAMLprim value
clist_nth(value v, value n) {
  CAMLparam2(v, n);
  if (Int_val(n) < 0) {
    caml_invalid_argument("List.nth");
  }
  for (int curr = 0; curr < Int_val(n); curr++) {
    if (v == Val_emptylist) {
      caml_failwith("nth");
    }
    v = Field(v, 1);
  }
  if (v == Val_emptylist) {
    caml_failwith("nth");
  }
  v = Field(v, 0);
  CAMLreturn(v);
}
