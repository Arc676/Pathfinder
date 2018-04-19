# Project Pathfinder: The Graph Library
Library for graph/network and pathfinding related tools

The Graph library handles saving and loading graphs from disk and provides path finding algorithms. It includes the following classes:
- `Node`
- `Graph`
- `Pathfinder`
- `Edge`

Use the static methods in `Pathfinder` to find paths between any two given nodes.

The Graph library abstracts the graph theory and representation to allow for more focus on creating user friendly interfaces or building other functions.

Available algorithms:
- Dijkstra's Algorithm
- Kruskal's Minimum Spanning Tree Algorithm
- Depth First Search Cycle Detection

### Legal

Pathfinder library available under the terms of GPLv3.

Cycle detection algorithm based on sample code [provided here](https://www.geeksforgeeks.org/detect-cycle-undirected-graph/) available under [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/) by GeeksForGeeks..

### Repository info

New features are merged into the `master` branch as soon as they work. For the source code for complete releases, please download the source archives from the release pages.

### Dependencies

Requires C++11 for range based for loops.
