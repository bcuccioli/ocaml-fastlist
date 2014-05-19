module FastList = struct

  exception Not_found

  external length : 'a list -> int = "clist_length"
  external hd : 'a list -> 'a = "clist_hd"
  external tl : 'a list -> 'a list = "clist_tl"
  external nth : 'a list -> int -> 'a = "clist_nth"
  external rev : 'a list -> 'a list = "clist_rev"
  external append : 'a list -> 'a list -> 'a list = "clist_append"

  external iter : ('a -> unit) -> 'a list -> unit = "clist_iter"
  external iteri : (int -> 'a -> unit) -> 'a list -> unit = "clist_iteri"
  external map : ('a -> 'b) -> 'a list -> 'b list = "clist_map"
  external fold_left : ('a -> 'b -> 'a) -> 'a -> 'b list -> 'a =
    "clist_fold_left"

  external assoc : 'a -> ('a * 'b) list -> 'b = "clist_assoc"

  let _ =
    Callback.register_exception "not found" Not_found;
    Callback.register "pervasives compare" Pervasives.compare

end
