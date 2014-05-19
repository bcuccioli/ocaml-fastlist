module FastList = struct

  external length : 'a list -> int = "clist_length"
  external hd : 'a list -> 'a = "clist_hd"
  external tl : 'a list -> 'a list = "clist_tl"
  external nth : 'a list -> int -> 'a = "clist_nth"

end
