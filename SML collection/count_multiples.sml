(*Ben Potter*)

(*Restrictions: no higher-order functions, and use recursion*)

(*
  Description: count_multiples will take an element and
  a list of type int. The function will return an int
  that reports how many multiples of the element are
  present in the list. 
  ex: count_multiples(3,[1,0,3,10,12]) returns the int 3.
*)

fun count_multiples(_, []) = 0
|   count_multiples(elem, head::tail) =
(*
  mod works exactly like % in python or Java, in that if we take head n and
  mod by elem m (n mod m), and it equals 0 then we found a multiple of m.
*)
    if ((head mod elem) = 0) then 1 + count_multiples(elem, tail)
    else count_multiples(elem, tail);