theorem mul_one_nat (x : Nat) : x * 1 = x := by
  exact Nat.mul_one x

#print mul_one_nat

def main (args : List String) : IO UInt32 := do
  IO.println s!"ends{args}"
  return 0
