from WeightedGraph import *

# Island names (8 islands)
islands = ['Island1', 'Island2', 'Island3', 'Island4', 'Island5', 'Island6', 'Island7', 'Island8']

# Bridge distances from the table (only upper triangle since graph is undirected)
bridge_distances = [
    (0, 1, 240), (0, 2, 210), (0, 3, 340), (0, 4, 280), (0, 5, 200), (0, 6, 345), (0, 7, 120),
    (1, 2, 265), (1, 3, 175), (1, 4, 215), (1, 5, 180), (1, 6, 185), (1, 7, 155),
    (2, 3, 260), (2, 4, 115), (2, 5, 350), (2, 6, 435), (2, 7, 195),
    (3, 4, 160), (3, 5, 330), (3, 6, 295), (3, 7, 230),
    (4, 5, 360), (4, 6, 400), (4, 7, 170),
    (5, 6, 175), (5, 7, 205),
    (6, 7, 305)
]

# Create the weighted graph
graph = WeightedGraph()

# Add all 8 islands as vertices
for island in islands:
    graph.addVertex(Vertex(island))

# Add all possible bridges as edges
for i, j, distance in bridge_distances:
    graph.addEdge(i, j, distance)

# Find the minimum spanning tree starting from Island 1 (index 0)
mst = graph.minimumSpanningTree(0)

# Calculate total cost and display only the MST solution
total_cost = 0
print('Bridges to build for minimum cost:')

# Extract and display the MST edges with their costs
for i in range(mst.nVertices()):
    for j in range(i + 1, mst.nVertices()):
        if mst.hasEdge(i, j):
            weight = mst.edgeWeight(i, j)
            total_cost += weight
            island_i = mst.getVertex(i).name
            island_j = mst.getVertex(j).name
            print(f'{island_i} to {island_j}: {weight}')

print(f'Minimumcost: {total_cost}')