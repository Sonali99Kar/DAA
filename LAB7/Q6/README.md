# README - The Best Time to Be Alive (DAA Lab-07)

## **1. Problem Statement**
Given the index of a book containing biographical data of prominent scientists (where entries are sorted alphabetically and specify their birth and death years), determine the **time period (year) when the largest number of prominent scientists were alive**. 
* *(Note: If person A died the same year person B was born, the former event is treated as happening before the latter).*

---

## **2. Algorithm Design (Sweep-Line / Event-Point Approach)**
1. **Extract and Separate Events:** For each scientist, create two distinct timeline events:
   * A **Birth** event at year $Y_{birth}$ (adds $+1$ to the active count).
   * A **Death** event at year $Y_{death}$ (removes $-1$ from the active count, ensuring death is processed before birth if the years match).
2. **Sort Events:** Sort all events chronologically. If two events happen in the same year, sort the death event before the birth event to correctly handle the boundary condition.
3. **Sweep and Track Maximum:** Iterate through the sorted events while maintaining a running count of active scientists. Record the year(s) where this count reaches its global maximum.

---

## **3. Complexity Analysis**
* **Time Complexity:** **$O(N \log N)$** where $N$ is the number of scientists, dominated by the sorting step of the $2N$ birth/death events. The linear sweep takes $O(N)$ time.
* **Space Complexity:** **$O(N)$** to store the decoupled birth and death event arrays.
