theorem mul_zero_nat (x : Nat) : x * 0 = 0 := by
  exact Nat.mul_zero x

#print mul_zero_nat

def main (args : List String) : IO UInt32 := do
  IO.println s!"ends{args}"
  return 0
