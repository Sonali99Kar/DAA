# README: Shortest Path on Parity-Constrained Graphs via 0-1 BFS

## Overview
This repository/program implements an optimized **0-1 Breadth-First Search (BFS)** algorithm in C to solve the **Shortest Path on Parity-Constrained Graphs** problem (from DAA Lab-11, Question 1). It computes the minimum effective cost from a designated source vertex $S$ to every other vertex in a directed graph where edge weights are restricted to $0$ or $1$, incorporating a parity constraint based on the count of weight-$1$ edges traversed along the path.

---

## Problem Definition
* **Graph:** Directed graph $G = (V, E)$ with a designated source vertex $S \in V$.
* **Edge Weights:** Every directed edge $(u, v) \in E$ has an integer weight $w(u, v) \in \{0, 1\}$.
* **Penalty Cost:** An extra penalty cost $C \geq 0$.
* **Effective Cost of Path $P$:**
  * Let $W(P)$ be the sum of all edge weights along $P$.
  * Let $k_1(P)$ be the total count of weight-$1$ edges traversed in $P$.
  * The effective cost is defined as:
    $$\text{Cost}(P) = W(P) + \begin{cases} 0, & \text{if } k_1(P) \text{ is even} \\ C, & \text{if } k_1(P) \text{ is odd} \end{cases}$$
* **Objective:** For every vertex $v \in V$, compute the minimum possible $\text{Cost}(P)$ among all valid paths from $S$ to $v$. If a node $v$ cannot be reached from $S$, report that it is unreachable.

---

## Algorithm Description (0-1 BFS with State Expansion)
Standard Dijkstra or 0-1 BFS tracks only the minimum distance to a vertex. Because the cost depends on the parity of the number of weight-$1$ edges, the state space must be expanded to include the parity of $k_1(P)$.

* **State Representation:** Define each state as $(u, \text{parity})$, where $u \in V$ and $\text{parity} \in \{0, 1\}$ ($0$ for even, $1$ for odd).
* **Deque Usage:** Use a Double-Ended Queue (Deque) to maintain the states efficiently:
  * **0-weight edges:** Do not change the parity, adding $0$ cost. These states are pushed to the **front** of the deque.
  * **1-weight edges:** Toggle the parity ($\text{parity} \oplus 1$), adding $1$ cost. These states are pushed to the **back** of the deque.
* **Initialization:** Distance/cost tracking array `dist[V][2]` is initialized to infinity, with `dist[S][0] = 0`. The initial state $(S, 0)$ is pushed to the deque.

---

## Complexity Analysis
* **Time Complexity:** $\mathcal{O}(V + E)$
  * There are $2|V|$ distinct states (each vertex combined with parity $0$ or $1$). 
  * Each edge is examined a constant number of times, and deque operations take $\mathcal{O}(1)$ time.
* **Space Complexity:** $\mathcal{O}(V + E)$
  * Required for storing the adjacency list representation of the graph and $\mathcal{O}(V)$ for the distance/cost tracking table (`dist[V][2]`) and deque structures.

---
