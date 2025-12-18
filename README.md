# 8-Puzzle Solver Project🧩
### Artificial Intelligence - Search Algorithms Comparison
## 📝 Project Description
This project demonstrates the implementation and performance analysis of four key search algorithms used to solve the 8-puzzle problem:

1. BFS (Breadth-First Search)

2. IDS (Iterative Deepening Search)

3. GBFS (Greedy Best-First Search)

4. A* (A-Star Search)

The goal is to compare their Efficiency, Optimality, and Memory Usage.  

 ---
This project implements and compares four major Artificial Intelligence (AI) search algorithms to solve the 8-puzzle problem using C++.
1. **Breadth-First Search (BFS):**  
   **Mechanism:** Uses a Queue (FIFO) to track nodes.  
   **Strategy:** Explores all neighbors at the current depth before moving to the next level.  
   **Optimal Solution:** Guaranteed to find the shortest path (minimum moves) because it explores moves level-by-level.  
   **Completeness:** Guaranteed to find a solution if one exists.  
2. **Iterative Deepening Search (IDS):**  
   **Mechanism:** Repeatedly runs a Depth-Limited Search (DLS), increasing the depth limit by 1 each time.  
   **Optimality:** Like BFS, it is guaranteed to find the shortest path.  
   **Memory:** Most efficient in RAM usage (Linear space) compared to BFS.  
   **Speed:** Slowest among the four because it re-explores upper levels in every iteration.  
3. **Greedy Best-First Search (GBFS)**  
   **Mechanism:** Uses a Heuristic (like Misplaced Tiles) to estimate the distance to the goal.  
   **Strategy:** Always expands the node that appears closest to the goal using a Priority Queue.  
   **Pros:** Fastest execution time for finding a solution.  
   **Cons:** Not optimal; it might find a solution with a very high step count.  
4. **AStar Search**  
   **Mechanism:** Combines path cost and heuristic using the formula **f(n) = g(n) + h(n)**.  
   **Balance:** Provides the best balance between execution speed and a low step count.  
   **Optimality:** Guaranteed to find the shortest path if the heuristic is admissible.
---
## 📊 Performance Comparison

Here is a quick look at how each algorithm performed:

| Algorithm | 🚀 Speed | 🧠 RAM Usage | 👣 Step Count | 🏆 Optimal? |🔁 Complete?|
| :--- | :--- | :--- | :--- | :--- | :--- |
| **BFS** | Moderate  | Very High  | Minimum  | **Yes** ✅ | **Yes** ✅ |
| **IDS** | Slowest  | **Lowest**  | Minimum  | **Yes** ✅ | **Yes** ✅ |
| **GBFS** | **Fastest**  | Moderate  | High  | No ❌ | No ❌ |
| **A\*** | Fast  | High  | Minimum  | **Yes** ✅ | **Yes** ✅ |

---

## 🏁 Key Takeaways

* **Best for Memory:** **IDS** 🛡️ (Linear space complexity).
* **Best for Speed:** **GBFS** 🚄 (Fast but might take a longer route).
* **Best All-Rounder:** **A\*** 👑 (Finds the best solution efficiently).  
---
## Implementation Notes
- All algorithms are implemented in C++.

- Execution time is measured in **milliseconds (ms)** using the `<chrono>` library.

- Heuristic used: **Misplaced Tiles** and **Manhattan Distance**

---
## 🏁 Conclusion

The performance analysis shows that the choice of algorithm depends on the priority:

* **For guaranteed shortest paths with limited memory:** **IDS** 🛡️ is the best choice.
* **For maximum speed without worrying about the number of steps:** **GBFS** 🚄 is the fastest.
* **For the most efficient balance of speed and optimality:** **A* with Manhattan Distance** is the superior algorithm 👑.

---
## 📂 Project Structure

To keep the project organized, each algorithm is implemented in its own file:

* 🟦 `BFS.cpp`: Logic for Breadth-First Search (Level-order).
* 🟨 `IDS.cpp`: Logic for Iterative Deepening (Depth-limited iterations).
* 🟧 `GBFS.cpp`: Informed search using only the heuristic $h(n)$.
* 🟩 `AStar.cpp`: The optimal search combining $g(n)$ and $h(n)$.