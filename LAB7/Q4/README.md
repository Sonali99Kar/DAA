
## **1. Problem Statement**
Consider a row of $n$ security switches protecting a military installation entrance. The switches can be manipulated under the following rules:
1. The rightmost switch may be turned on or off at will.
2. Any other switch may be turned on or off only if the switch to its immediate right is on and all the other switches to its right, if any, are off.
3. Only one switch may be toggled at a time.

* **Objective:** Devise an algorithm to turn off all the switches (which are initially all on) in the minimum number of moves (similar to the classic "Binary Counter / Gray Code" puzzle).

---

## **2. Algorithm Design & Recurrence Relation**
This puzzle is structurally equivalent to the Gray code generation or the Towers of Hanoi variant where switches can be toggled following recursive state transitions:
* **To turn off the $i$-th switch (from the right):** We must first ensure the switch immediately to its right is ON and all other switches further to its right are OFF.
* **Recurrence for Minimum Moves ($M(n)$):**
  $$M(n) = 2^n - 1$$
  *(Turning off a configuration of $n$ switches all initially set to 'on' takes exactly $2^n - 1$ moves, mirroring the standard binary reflection pattern).*

---

## **3. Complexity Analysis**
* **Time Complexity:** **$O(2^n)$** because the number of state transition steps (moves) grows exponentially with the number of switches $n$.
* **Space Complexity:** **$O(n)$** for recursion stack or bitwise state representation.
