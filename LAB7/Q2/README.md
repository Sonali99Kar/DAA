# README - Super Egg Drop Problem (DAA Lab-07)

## **1. Problem Statement**
Determine the minimum number of droppings guaranteed to find the highest safe floor in a 100-storey building using 2 identical eggs, and generalize the dynamic programming solution for $E$ eggs and $F$ floors.

---

## **2. Algorithm Design & Recurrence Relation**
* **State:** $DP[e][f]$ = minimum trials needed with $e$ eggs and $f$ floors.
* **Recurrence:** 
  $$DP[e][f] = 1 + \min_{1 \le x \le f} \left( \max(DP[e-1][x-1], \, DP[e][f-x]) \right)$$
* **Base Cases:**
  * $DP[1][f] = f$
  * $DP[e][0] = 0$
  * $DP[e][1] = 1$

---

## **3. Complexity Analysis**
* **Time Complexity:** $O(E \times F^2)$ (can be optimized to $O(E \times F \log F)$ or $O(E \times F)$).
* **Space Complexity:** $O(E \times F)$ using a 2D lookup table.
