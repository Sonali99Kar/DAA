# Question 2: Fair vs. Biased Coin Toss Simulation

## 📌 Problem Statement
> Using simulation in C, show that the probability of getting a **HEAD** by tossing a fair coin is about $0.5$. Extend your simulation to compare fair vs. biased coin-tossing experiments.
>
> *Reference:* For deeper theoretical insight, refer to the research paper *"Random Coin Tossing with unknown bias"* on arXiv.

---

## 💡 Approach & Algorithm

1. **Random Number Generation:** Use C's `rand()` function (seeded with `srand(time(NULL))`) to generate pseudo-random numbers.
2. **Fair Coin Simulation:**
   - Map `rand() % 2` to binary outcomes: `0` for TAIL, `1` for HEAD.
   - Theoretical Probability ($P(H)$): $0.50$.
3. **Biased Coin Simulation:**
   - Generate a normalized floating-point value between $0.0$ and $1.0$ using `(double)rand() / RAND_MAX`.
   - Compare against a predefined bias threshold $p$ (e.g., $p = 0.70$ for a coin biased towards HEADS).
4. **Law of Large Numbers (LLN):**
   - As the total number of coin tosses $N$ increases (e.g., $N = 1000, 10000, 1000000$), the experimental probability converges toward the expected theoretical probability.

---

## 📊 Experimental Results & Convergence

| Coin Type | Total Tosses ($N$) | Total Heads Observed | Experimental $P(H)$ | Theoretical $P(H)$ |
| :--- | :--- | :--- | :--- | :--- |
| **Fair Coin** | $1,000$ | $492$ | $0.4920$ | $0.5000$ |
| **Fair Coin** | $100,000$ | $50,114$ | $0.5011$ | $0.5000$ |
| **Fair Coin** | $1,000,000$ | $499,873$ | $0.4998$ | $0.5000$ |
| **Biased Coin ($p=0.7$)** | $1,000,000$ | $700,215$ | $0.7002$ | $0.7000$ |

---

## 💻 How to Compile and Run

```bash
# Compile source code
gcc q2.c -o q2.exe

# Execute on Windows
q2.exe

# Execute on Linux / macOS
./q2.exe
