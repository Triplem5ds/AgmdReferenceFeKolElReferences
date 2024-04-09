// 1- Burnside's_lemma
// |Classes|=sum (k ^C(pi))  / |G| 
// C(pi)  the number of cycles in the permutation pi 
// |G| the number of permutations

// 2- FibonacciNumbers
// F(n-1) * F(n+1) - F(n)^2 = (-1)^n
// F(n+k) = F(k) * F(n+1) + F(k-1) * F(n)
// F(2*n) = F(n) * (F(n+1) + F(n-1))
// GCD ( F(m) , F(n) ) = F(GCD(n,m))

// 3- FFT Applications
//------------------------
//1-All possible sums
//2-All possible scalar products. We are given two arrays a[] and b[] of length n.
//We have to compute the products of a with every cyclic shift of b.
//We generate two new arrays of size 2n: We reverse a and append n zeros to it. 
//And we just append b to itself. When we multiply these two arrays as polynomials, 
//and look at the coefficients c[n-1], c[n], ..., c[2n-2] of the product c, we get:
//c[k]=sum i+j=k  a[i]b[j]

//3-Two stripes
//We are given two Boolean stripes (cyclic arrays of values 0 and 1) a and b.
//We want to find all ways to attach the first stripe to the second one,
//s.t at no position we have a 1 of the first stripe next to a 1 of the second stripe.


// 4- Catalan Number
// 1- Number of correct bracket sequence consisting of n opening and n closing brackets.
// 2- The number of rooted full binary trees with n+1 leaves (vertices are not numbered). 
// 3- The number of ways to completely parenthesize n+1 factors.
// 4- The number of triangulations of a convex polygon with n+2 sides
// 5- The number of ways to connect the 2n points on a circle to form n disjoint chords.
// 6- The number of non-isomorphic full binary trees with n internal nodes (i.e. nodes having at least one son).
// 7- The number of monotonic lattice paths from point (0,0) to point (n,n) in a square lattice of size nxn, which do not pass above the main diagonal (i.e. connecting (0,0) to (n,n)).
// 8- Number of permutations of length n that can be stack sorted (it can be shown that the rearrangement is stack sorted if and only if there is no such index i<j<k, such that ak<ai<aj).
// 9- The number of non-crossing partitions of a set of n elements.
// 10- The number of ways to cover the ladder 1..n using n rectangles (The ladder consists of n columns, where ith column has a height i).