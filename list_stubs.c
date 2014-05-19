#include <stdio.h>

#include <caml/alloc.h>
#include <caml/callback.h>
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

CAMLprim value
clist_rev(value v) {
  CAMLparam1(v);
  CAMLlocal2(cons, old_cons);
  old_cons = cons = Val_emptylist;
  while (v != Val_emptylist) {
    cons = caml_alloc(2 /* 2 fields - head/tail */, 0 /* gc tag */);
    Store_field(cons, 0, Field(v, 0));
    Store_field(cons, 1, old_cons);
    old_cons = cons;
    v = Field(v, 1);
  }
  CAMLreturn(cons);
}

CAMLprim value
clist_assoc(value v, value l) {
  CAMLparam2(v, l);
  CAMLlocal3(head, key, cbres);
  static value* closure_eq = NULL;
  if (closure_eq == NULL) {
    closure_eq = caml_named_value("pervasives compare");
  }

  while (l != Val_emptylist) {
    head = Field(l, 0);
    key = Field(head, 0);

    cbres = caml_callback2(*closure_eq, key, v);
    if (Int_val(cbres) == 0) {
      CAMLreturn(Field(head, 1));
    }
    l = Field(l, 1);
  }
  /* The key was not found in the list. */
  caml_raise_constant(*caml_named_value("not found"));
}

CAMLprim value
clist_append(value l1, value l2) {
  CAMLparam2(l1, l2);
  CAMLlocal2(cons, head);
  if (l1 == Val_emptylist) {
    CAMLreturn(l2);
  }
  head = cons = caml_alloc(2 /* 2 fields - hd/tl */, 0 /* gc tag */);
  while (l1 != Val_emptylist) {
    Store_field(cons, 0, Field(l1, 0));
    if (Field(l1, 1) != Val_emptylist) {
      value tl = caml_alloc(2 /* 2 fields - hd/tl */, 0 /* gc tag */);
      Store_field(cons, 1, tl);
      cons = tl;
    }
    l1 = Field(l1, 1);
  }
  Store_field(cons, 1, l2);
  CAMLreturn(head);
}
