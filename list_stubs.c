#include <stdio.h>

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/custom.h>

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
