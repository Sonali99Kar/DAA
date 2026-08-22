# Application of Sorting-I: Stable Color Sort Algorithm

An $\mathcal{O}(n)$ time complexity algorithm that processes a numeric sequence of paired items pre-sorted by number and sorts them by color category (**RED** $\rightarrow$ **BLUE** $\rightarrow$ **YELLOW**) while maintaining the relative numeric order within each color group.

---

## Problem Overview

Given $n$ item pairs as input, where:
* The first element is a numeric value.
* The second element is one of three colors: `RED`, `BLUE`, or `YELLOW`.
* The input list is pre-sorted by numeric value.

**Goal:** Reorder the items into color blocks (`RED` first, `BLUE` second, `YELLOW` third) in linear time $\mathcal{O}(n)$ such that elements within the same color group retain their original numeric relative order (stability).

---

## Data Model & Representation

* **Color Enumeration:** Colors are assigned discrete categorical ranks: `RED = 0`, `BLUE = 1`, and `YELLOW = 2`.
* **Item Pair:** Each entry is modeled as a composite record containing a numeric key and a color attribute.
* **Input Constraints:** The array is passed along with its size $n$. The underlying sequence guarantees $A[i].number \le A[i+1].number$.

---

## Algorithmic Workflow

1. **Frequency Counting ($\mathcal{O}(n)$):** 
   Iterate through the array once to calculate the total count of items belonging to each color category (`count[RED]`, `count[BLUE]`, `count[YELLOW]`).

2. **Offset Computation ($\mathcal{O}(1)$):** 
   Determine the exact target index boundaries for each color block:
   * `RED` boundary starts at index `0`.
   * `BLUE` boundary starts at index `count[RED]`.
   * `YELLOW` boundary starts at index `count[RED] + count[BLUE]`.

3. **Stable Distribution ($\mathcal{O}(n)$):** 
   Iterate through the original array sequentially from index $0$ to $n-1$. Place each item into a auxiliary destination array at its designated color offset, then increment that specific color's offset counter.

4. **In-Place Copy Back ($\mathcal{O}(n)$):** 
   Overwrite the original array with the ordered entries from the auxiliary array.

---

## Complexity Analysis

* **Time Complexity: $\mathcal{O}(n)$**
  The algorithm executes three independent linear passes over the input data:
  * Pass 1: Frequency collection across $n$ elements.
  * Pass 2: Distribution into auxiliary storage across $n$ elements.
  * Pass 3: Memory copy back to original array across $n$ elements.

* **Auxiliary Space Complexity: $\mathcal{O}(n)$**
  Requires a temporary buffer of size $n$ to store intermediate placements and guarantee stability.

---

## Theoretical Proof of Stability

A sorting algorithm is defined as stable if equal keys appear in the same order in the output as they appear in the input. 

Since the input list arrives pre-sorted by number, for any two items $A[i]$ and $A[j]$ where $i < j$ and $A[i].color == A[j].color$:
* The linear pass visits index $i$ prior to index $j$.
* Item $A[i]$ is inserted into the auxiliary buffer at the current offset position for its color, after which the offset increments.
* When item $A[j]$ is subsequently processed, it is inserted into the next adjacent offset position.
* Consequently, $A[i]$ always precedes $A[j]$ in the output, preserving original numerical order within each color block.
