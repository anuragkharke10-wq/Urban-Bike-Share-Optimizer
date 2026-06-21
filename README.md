<<<<<<< HEAD
# Urban Bike-Share Asset Allocation Optimizer

## Project Title
Urban Bike-Share Asset Allocation Optimizer using C++ Data Structures and Algorithms.

## Student Details
- Name: Anurag Dattatray Kharke
- Case Study No.: 66
- School: School of Future Tech
- Course: Data Structure & Algorithms with CPP

## Problem Statement
PedalCity is a bike-sharing platform managing thousands of bikes across many docking stations. The system must track bike locations, schedule repairs, maintain rental charge logs, sort stations by capacity, calculate safe routes, and help trucks rebalance bikes efficiently.

The project implements a console-based C++ solution that demonstrates core DSA concepts instead of using GUI, web apps, or databases.

## Objectives
- Track bikes and quickly find bike details by ID.
- Maintain sorted lock records for fast lock search.
- Record charge transactions and rollback the latest transaction.
- Maintain a repair line where broken bikes are fixed in reporting order.
- Rank stations by available empty spots.
- Model the city bike-lane network as a graph.
- Find safest/fastest rider path between stations.
- Generate a truck rebalancing plan to move bikes from surplus stations to deficit stations.

## System Overview / Architecture
The program is menu-driven and divided into separate classes:

- `Bike`: stores bike details.
- `Station`: stores docking station details.
- `LockRegister`: manages locks using sorted map.
- `ChargeLog`: manages rental charges using stack.
- `RepairQueue`: handles broken bikes using queue.
- `CityGraph`: stores city routes using adjacency list and finds paths using Dijkstra.
- `RebalancingOptimizer`: uses greedy logic and priority queues to redistribute bikes.
- `main.cpp`: integrates all modules and provides the console menu.

## Data Structures and Algorithms Used

| Requirement | Data Structure / Algorithm | Purpose |
|---|---|---|
| Lock Register | `map<int, LockInfo>` | Sorted lock IDs and O(log n) search |
| Charge Log | `stack<ChargeTransaction>` | Rollback last charge in O(1) |
| Repair Line | `queue<int>` | FIFO repair order |
| Bike Finder | `unordered_map<int, Bike>` | Fast bike lookup by ID |
| Capacity Sorter | `priority_queue<pair<int,int>>` | Rank stations by empty spots |
| City Grid | Graph adjacency list | Store bike lanes and safe paths |
| Rider Path | Dijkstra's Algorithm | Minimum cost route between stations |
| Rebalancing Optimizer | Greedy + Priority Queue | Efficient bike redistribution |

## Implementation Approach
1. Store all bikes using an unordered map for quick lookup.
2. Store docking stations using an unordered map.
3. Use a sorted map for lock records so lock IDs remain ordered.
4. Use a stack for rental charge logs so latest charge can be rolled back.
5. Use a queue for repair line so bikes are repaired in the order they are reported.
6. Use priority queue to rank stations by empty spots.
7. Use graph adjacency list for city bike lanes.
8. Use Dijkstra's algorithm where route cost = travel time + safety penalty.
9. Use greedy rebalancing to move bikes from most surplus stations to most deficit stations.

## Time and Space Complexity Analysis

| Operation | Time Complexity | Space Complexity |
|---|---:|---:|
| Bike lookup by ID | O(1) average | O(n) |
| Lock search | O(log n) | O(n) |
| Charge rollback | O(1) | O(n) |
| Add/repair broken bike | O(1) | O(n) |
| Rank stations by empty spots | O(n log n) | O(n) |
| Add bike lane | O(1) average | O(V + E) |
| Dijkstra route search | O((V + E) log V) | O(V + E) |
| Rebalancing optimizer | O(n log n) | O(n) |

## Execution Steps

### Option 1: Compile directly using g++
```bash
g++ -std=c++17 src/main.cpp -o bike_optimizer
./bike_optimizer
```

### Option 2: Use CMake
```bash
mkdir build
cd build
cmake ..
cmake --build .
./UrbanBikeShareOptimizer
```

### VS Code Steps
1. Open the folder `Urban-Bike-Share-Optimizer` in VS Code.
2. Install C/C++ extension if needed.
3. Open terminal in VS Code.
4. Run:
```bash
g++ -std=c++17 src/main.cpp -o bike_optimizer
./bike_optimizer
```
5. Choose option `1` first to load sample data.

## Menu Options
```text
1. Load Sample Data
2. Add Bike
3. Add Station
4. Register Lock
5. Search Lock by ID
6. Rent Bike
7. Rollback Last Charge
8. Report Broken Bike
9. Repair Next Bike
10. Find Bike by ID
11. Show Stations by Empty Capacity
12. Add Bike Lane
13. Find Safest/Fastest Route
14. Run Rebalancing Optimizer
15. Display All Data
0. Exit
```

## Sample Input
See `input/sample_input.txt`.

## Sample Output
See `output/sample_output.txt`.

## Screenshots
- VS Code terminal style execution screenshot: `screenshots/vscode_terminal_output.png`

## Results and Observations
- The system demonstrates multiple DSA concepts in one real-world case study.
- Fast bike lookup is achieved using hashing.
- Sorted lock searching is handled using a balanced tree map.
- Stack allows quick rollback of the last charge transaction.
- Queue ensures fair first-come-first-served repair scheduling.
- Graph and Dijkstra provide realistic route calculation.
- Priority queue helps rank station capacity and supports efficient rebalancing.

## Conclusion
This project successfully implements the Urban Bike-Share Asset Allocation Optimizer using C++. It focuses on Data Structures and Algorithms instead of GUI or database features. The design is modular, readable, and suitable for DSA-I viva evaluation.

=======
# Urban-Bike-Share-Optimizer
>>>>>>> ee30b82c410380268ece0a42e1448369c633a99e
