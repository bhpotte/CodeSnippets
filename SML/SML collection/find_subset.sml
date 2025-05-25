(*Ben Potter*)

(*Restrictions: Has to use currying*)

(*
  Description: find_subset will return a subset of a
  list that adds up to the first argument.
  ex: find_subset 10 [4,3,2,12,5] returns [3,2,5]
      find subset 10 [4,3,2,12] returns []
*)

(*base case: if we have an empty list, we return an empty list*)
fun find_subset elem [] = []
|   find_subset elem given_list = 

(*if we have a element less than or equal to the first argument, then we
  lock it in and check the next sequence of elements in the list*)

      if (hd given_list) <= elem then

      (*let: we declare search_nextElem that checks the next sequence of elements in
             the list one by one. It will subtract the element as we go down the list
             with some catches.

        in: if search_nextElem is empty and the current element matches with the target
            element, then we got a match, otherwise we go back and check the next element
            in the list and repeat the process (still with the same first element locked in)
            
            if either case fails, then we go back and unlock the first element and start at
            element 2 instead IF it's not larger than the first argument.*)
        let
          val search_nextElem = find_subset (elem - (hd given_list)) (tl given_list)
        in
          if search_nextElem = [] andalso (elem - (hd given_list)) = 0 then [hd given_list]
          else
            if (search_nextElem = []) = false then (hd given_list)::search_nextElem
            else find_subset elem (tl given_list)
        end

(*If we have an element larger, then we go down the list*)

      else find_subset elem (tl given_list);