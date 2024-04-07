// Calculate the DFS order, {1, 2, 3, 3, 4, 4, 2, 5, 6, 6, 5, 1}.
// Let a query be (u, v), ST(u) <= ST(v), P = LCA(u,v)
// Case 1: P = u : the query range would be [ST(u), ST(v)]
// Case 2: P != u : range would be [EN(u), ST(v)] + [ST(P), ST(P)].
// the path will be the nodes that appears exactly once in that range