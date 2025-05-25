(*Ben Potter*)

(*Restrictions: has to be efficient (O(M + N)) and
                use currying*)

(*
  Description: intersection will take two lists in 
  smallest to largest order and return a list of elements
  that appear in BOTH lists in that same order. 
  ex: intersection [1,3,4,6][2,4,6,8] returns [4,6]
*)

(*base cases: if we have an empty list in any way, then we
  return an empty list.*)
fun intersection [] [] = []
|   intersection list1 [] = []
|   intersection [] list2 = []
|   intersection list1 list2 = 

    (*if the element in list1 is less than the element in list2, then we go
      down list1 by 1 element until we find a greater or equal number.*)

      if (hd list1) < (hd list2) then intersection (tl list1) list2
      else

      (*same reasoning above for list2 cases*)

        if (hd list2) < (hd list1) then intersection list1 (tl list2)

        (*by this else statement, we found our match in the lists, so we apply
          the element in the processed list. (basically the opposite of union)*)
          
        else (hd list1)::intersection (tl list1) (tl list2);