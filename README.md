# Wireless Network Simulations

This repository hosts the project "Wireless Network Simulations" developed for the EC200 Data Structures course at the National University of Sciences and Technology (NUST). The project simulates wireless network topologies using Unit Disk Graph (UDG), Cross-Layer Topology Control (XTC) upon the UDG, and Compass Routing algorithm for navigation.

## Project Overview

The project aims to create efficient wireless network topologies by minimizing interference and ensuring connectivity through the following steps:

1. **UDR Graph Generation**: Randomly generate nodes and connect them based on a distance threshold.
2. **Topology Control Algorithm**: Optimize the network by adjusting connections to reduce interference.
3. **Routing Algorithm**: Use Compass Routing to determine optimal data transmission paths.

## Methodology

### Unit Disk Graph Generation
Generate a random network by placing nodes randomly within the specified area and connecting them based on proximity in unit radius disks of each other.

### Topology Control Algorithm
Enhance network efficiency by iteratively analyzing and adjusting the adjacency matrix of the graph.

### Routing Algorithm
Implement Compass Routing to find efficient paths between nodes in the optimized network.

## Experimentation

The project includes a comparative analysis of network performance with and without topology control. Results indicate significant improvements in network connectivity and efficiency after applying the XTC algorithm.

## Limitations

- **Scalability**: Performance may degrade with a large number of nodes.
- **Dynamic Environments**: The current implementation assumes a static network.
- **Overhead**: Computational resources may increase due to the iterative adjustments.

## Conclusion

The project demonstrates how topology control can improve wireless network efficiency. Further research could address scalability and adaptability to dynamic environments.

## References

- R. Wattenhofer and A. Zollinger, "XTC: a practical topology control algorithm for ad-hoc networks," 18th International Parallel and Distributed Processing Symposium, 2004.
- E. Kranakis, H. Singh, & J. Urrutia, "Compass routing on geometric networks," Canadian Conference on Computational Geometry, 1999.

## Getting Started

### Prerequisites

- C++ Compiler (e.g., G++)
- Standard C++ Libraries

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/wireless-network-simulations.git

2. Navigate to the project directory:
   ```bash
   cd wireless-network-simulations

3. Compile the project:
   ```bash
   g++ main.cpp -o wireless_network_simulations

4. Run the executable:
   ```bash
   ./wireless_network_simulations
