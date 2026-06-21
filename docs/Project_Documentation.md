# Case Study Report

## Cover Page Details
**Institution:** ITM Skills University  
**School:** School of Future Tech  
**Report Type:** Case Study Report  
**Case Study No.:** 66  
**Topic:** Urban Bike-Share Asset Allocation Optimizer  
**Student Name:** Anurag Dattatray Kharke  
**Batch:** B.Tech CSE 2025-29  
**Course:** Data Structure & Algorithms with CPP  
**Semester:** II  

## Problem Statement
PedalCity is a bike sharing platform managing bikes across docking stations. The system must track bike locations, schedule repairs, rollback failed rental charges, sort stations by available capacity, calculate safe paths, and optimize bike redistribution.

## Objectives
- Implement the system strictly in C++.
- Demonstrate DSA concepts clearly.
- Build a working console application.
- Justify data structure and algorithm choices.
- Provide sample input, output, and execution screenshots.

## Design / Architecture
The application uses separate modules for each real-world feature. The central `BikeShareSystem` class integrates bikes, stations, locks, charges, repair queue, route graph, and rebalancing logic.

## Algorithm Description
- `unordered_map` is used for bike lookup.
- `map` is used for sorted lock register.
- `stack` is used for charge rollback.
- `queue` is used for repair line.
- `priority_queue` is used for station capacity ranking.
- Graph adjacency list is used to represent bike lanes.
- Dijkstra's algorithm is used for safest/fastest route search.
- Greedy algorithm is used for truck rebalancing.

## Complexity Analysis
| Feature | Complexity |
|---|---|
| Bike lookup | O(1) average |
| Lock search | O(log n) |
| Charge rollback | O(1) |
| Repair queue | O(1) |
| Capacity ranking | O(n log n) |
| Dijkstra pathfinding | O((V + E) log V) |
| Rebalancing | O(n log n) |

## Screenshots of Execution
The repository includes a VS Code terminal style execution screenshot at:
- `screenshots/vscode_terminal_output.png`

## Results and Findings
The project shows how different DSA techniques solve different operational problems in a bike-sharing platform similar to Yulu or Citi Bike.

## Conclusion
The system is a complete C++ console project focused on DSA. It is suitable for VIVA demonstration because each feature clearly maps to a data structure or algorithm.
