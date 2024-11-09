(*Ben Potter*)

(*Restrictions: has to use currying*)

(*
  Description: Eval will represent a polynomial using
  a list of its (real) coefficents starting with the constant
  and going as high as necessary. The second parameter
  will determine the X value for the polynomial and compute
  as such for the final return value.
  Ex: eval [1.0, 5.0, 3.0] 2.0 returns 23.0 (x=2, in 3x^2 + 5x + 1)
*)

(*
  constant at first position, so we leave it alone and move down
  and multiply each remaining element by the x value.
*)
fun eval [] _ = 0.0
|   eval (coeff_list:real list) (elemX:real) = hd (coeff_list) + eval (map (fn y => elemX * y) (tl coeff_list)) elemX;