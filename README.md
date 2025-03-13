# Resident Evil 3: Mercenaries Mode & Escape Simulation (C++)

## Overview
This project simulates two key gameplay mechanics from **Resident Evil 3**:  
1. **Mercenaries Mode** – A max-heap priority queue dynamically ranks mercenaries based on combat performance.  
2. **Escape Simulation** – A graph-based depth-first search (DFS) algorithm models Jill Valentine’s escape from RPD, integrating health management and Nemesis encounters.

## Features
- **Mercenaries Mode:**
  - Implements a **max-heap priority queue** for dynamically ranking mercenaries based on their in-game performance.
  - Uses **bubble-up and bubble-down operations** to update rankings efficiently.
  - Supports real-time score adjustments with **operator overloading**.

- **Escape Simulation:**
  - Models RPD as a **graph using an adjacency list**.
  - Implements **DFS pathfinding** to simulate Jill’s survival routes.
  - Dynamically adjusts Jill’s health based on **environmental hazards and Nemesis encounters**.

## How to Run
### Prerequisites
- C++ compiler (G++ recommended)
- Standard Template Library (STL) support

### Compilation & Execution
```bash
# Compile the program
g++ main.cpp -o RE3_Sim

# Run the program
./RE3_Sim
