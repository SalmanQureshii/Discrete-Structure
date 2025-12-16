# Campus Navigation System

A console-based pathfinding application that finds the shortest route between campus locations using **Dijkstra's Algorithm** and **Graph Theory**.

##  Overview

This project models Salim Habib University campus as a weighted graph with 20 locations (nodes) connected by pathways (edges). It calculates and displays the optimal route between any two points along with the total distance.

**Course Project:** Discrete Structures | Fall 2025

##  Features

-  Finds shortest path between 20 campus locations
-  Calculates total distance and shows step-by-step route
-  Handles restricted areas and special cases
-  Displays adjacency matrix representation
-  Fast computation using priority queue optimization

##  Quick Start

### Compile & Run
```bash
g++ -std=c++11 campus_navigation.cpp -o campus_nav
./campus_nav
```

### Usage
1. View the location map (1-20)
2. Enter starting point
3. Enter destination
4. Get shortest path and distance

##  Algorithm

**Dijkstra's Shortest Path Algorithm**
- Time Complexity: O((V + E) log V)
- Space Complexity: O(V²)
- Uses min-heap priority queue for efficiency

##  Campus Locations

20 locations including:
- Classrooms (C22, Rooms 1-4)
- Labs (Lab 1-4)
- Administrative (Office, Finance, Department)
- Facilities (Sports Complex, Mosque, Cafe, Library, Washrooms)

##  Tech Stack

- **Language:** C++11
- **Data Structures:** Adjacency Matrix, Priority Queue, Vectors
- **Algorithm:** Dijkstra's Shortest Path
  
## 📄 License

MIT License - Feel free to use for educational purposes 

---

**Salim Habib University | Department of Computer Science**
