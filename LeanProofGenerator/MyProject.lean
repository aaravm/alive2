import Init.Data.Nat.Bitwise

def myAdd : Nat → Nat → Nat
  | x, 0        => x
  | x, Nat.succ y => Nat.succ (myAdd x y)

infixl:65 " +ₘ " => myAdd

/-- Zero is a right identity for addition -/
theorem add_zero (x : Nat) : x +ₘ 0 = x := by
  rfl

/-- Zero is a left identity for addition, shown by induction -/
theorem zero_add (x : Nat) : 0 +ₘ x = x := by
  induction x with
  | zero =>
    simp [myAdd]
  | succ x ih =>
    simp [myAdd, ih]

#print zero_add

def main (args : List String) : IO UInt32 := do
  IO.println s!"ends{args}"
  return 0

open Nat

-- direct one-liner proof
theorem one_shiftLeft_eq_pow (a : Nat) : (1 <<< a) = 2 ^ a := by
  rw [Nat.shiftLeft_eq]
  simp

-- -- induction proof
-- theorem one_shiftLeft_eq_pow_ind (a : Nat) : (1 <<< a) = 2 ^ a := by
--   induction a with
--   | zero =>
--     -- Base case: 1 <<< 0 = 1, 2^0 = 1
--     simp [shiftLeft, Nat.pow_zero]
--   | succ k ih =>
--     -- Step case: use shiftLeft_eq
--     calc
--       1 <<< (k + 1)
--         = 1 * 2 ^ (k + 1) := by rw [Nat.shiftLeft_eq]
--       _ = (2 ^ k) * 2     := by rw [Nat.pow_succ]
--       _ = (1 <<< k) * 2   := by rw [← ih]
