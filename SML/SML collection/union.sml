(*Ben Potter*)

(*Restrictions: has to be efficient (O(M + N)) 
                and use currying*)

(*
  Description: union will take two lists in smallest
  to largest order and return a list of all of the 
  elements of both lists in the same order with no
  duplicates.
  ex: union [1,4,6][3,4,5] returns [1,3,4,5,6]
*)

fun union [] [] = []

(*base cases: if we have a empty list in either first 
  or second position or both, we recur the union so 
  that we get the processed list in that case.*)

|   union list1 [] = (hd list1)::union (tl list1) []
|   union [] list2 = (hd list2)::union [] (tl list2)
|   union list1 list2 = 

(*if the element in list1 is less than the element in list2, then we apply
  the element to the processed list and go down list1*)

      if (hd list1) < (hd list2) then (hd list1)::union (tl list1) list2
      else 

      (*same reasoning above, but this time it handles the case of list2 instead*)

        if (hd list2) < (hd list1) then (hd list2)::union list1 (tl list2)

        (*if they equal, we simply apply one of the element from either list
          and go down 1 element for both lists (avoids duplicates)*)
          
        else (hd list1)::union (tl list1) (tl list2);