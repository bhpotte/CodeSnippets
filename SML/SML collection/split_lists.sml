(*Ben Potter*)

(*Restrictions: required to use higher-order functions*)

(*
  Description: split_lists will take a lists of tuples
  and transform it into a tuple of lists with matching
  element types
  ex: split_lists[(1,"a",4.0),(3,"b",1.3),(19, "cat", 3.14)]
  returns ([1,3,19],["a","b", "cat"],[4.0,1.3,3.14])
*)

fun split_lists (List_of_tuples) = 
(*define 3 functions that identify which element is in 
  List_of_tuples, then we use a map for each of those defined
  functions to build the individual lists in the final tuple 
  of lists.*)
  let
    fun first_elem (first,_,_) = first;
    fun second_elem (_,second,_) = second;
    fun third_elem (_,_,third) = third;
  in
    (map first_elem List_of_tuples, map second_elem List_of_tuples, map third_elem List_of_tuples)
  end;