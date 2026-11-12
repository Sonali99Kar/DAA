# README: Multi-Source BFS for Radius-Constrained Voronoi Cell Partitioning

## Overview
This program implements a **Multi-Source Breadth-First Search (BFS)** algorithm in C to solve the **Radius-Constrained Voronoi Cell Partitioning** problem (from DAA Lab-11, Question 2). It partitions an unweighted, undirected graph into service coverage zones managed by $K$ designated hub vertices based on shortest-path distances and an integer radius threshold $R$.

---

## Problem Definition
* **Graph:** Unweighted, undirected graph $G = (V, E)$.
* **Service Hubs:** A set of $K$ designated hub vertices $H = \{h_1, h_2, \dots, h_K\} \subseteq V$, indexed from $1$ to $K$.
* **Radius Threshold:** An integer radius threshold $R \ge 0$.
* **Distance Metric:** Let $\text{dist}(u, v)$ denote the shortest path distance (minimum number of edges) between vertices $u$ and $v$ in $G$.
* **Ownership Label Rules (`owner[v]` for each $v \in V$):**
  1. **Distance Calculation:** Find the distance from $v$ to each service hub: $d_i = \text{dist}(v, h_i)$ for all $i \in \{1, \dots, K\}$. Let $d_{\min}(v) = \min_{1 \le i \le K} d_i$.
  2. **Reachability Threshold ($R$):** If $d_{\min}(v) > R$, vertex $v$ lies outside the service coverage area. Set `owner[v] = -1`.
  3. **Closest Hub Assignment:** If $d_{\min}(v) \le R$, assign $v$ to the hub $h_i$ that minimizes $d_i$.
  4. **Deterministic Tie-Breaking:** If multiple hubs achieve the exact same minimum distance $d_{\min}(v)$, choose the hub with the **smallest numerical index $i$**.

---

## Algorithm Description (Multi-Source BFS with Tie-Breaking)
* **Queue Initialization:** 
  * Push all hubs $h_1, h_2, \dots, h_K$ into the BFS queue simultaneously.
  * Initialize distance array `dist[v] = \infty` and `owner[v] = -1` for all $v \in V$.
  * For each hub $h_i$, set `dist[h_i] = 0`, `owner[h_i] = i`, and track its source hub index.
* **Traversal & Tie-Breaking:**
  * Standard BFS queue processes neighbors level by level.
  * When exploring a neighbor $v$ from a current node $u$:
    * If $v$ is unvisited (`dist[v] == \infty`), set `dist[v] = dist[u] + 1`, assign `owner[v] = owner[u]`, and push $v$ to the queue.
    * If $v$ has already been visited at the **same distance** (`dist[v] == dist[u] + 1`), apply **deterministic tie-breaking** by updating `owner[v] = min(owner[v], owner[u])` to ensure the hub with the smaller index takes ownership.
* **Radius Filtering:**
  * After the multi-source BFS completes, iterate through all vertices and verify if `dist[v] > R`. If true, override `owner[v] = -1`.

---

## Complexity Analysis
* **Time Complexity:** $\mathcal{O}(V + E)$
  * Since multiple sources are initialized concurrently and each vertex/edge is processed at most a constant number of times in a standard BFS traversal, the time complexity remains linear in terms of vertices and edges.
* **Space Complexity:** $\mathcal{O}(V + E)$
  * Required for storing the adjacency list representation of the graph $G$, along with $\mathcal{O}(V)$ auxiliary storage for the queue, distance table (`dist`), and ownership array (`owner`).

---

