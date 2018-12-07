# Assignment 7

VE281

Bingcheng HU

516021910219

## Q1

<img src="https://ws3.sinaimg.cn/large/006tNbRwly1fxwwvv8uq7j30eq080gm5.jpg" width=220 />

Adjacency matrix repre- sentation of the graph. 

<img src="https://ws3.sinaimg.cn/large/006tNbRwly1fxwwlnm4elj30hm0h6t9g.jpg" width=200 />

## Q2

Apply Prim’s algorithm to the graph, the intermediate steps of applying the algorithm is:

1. a->b
2. b->c
3. c->e
4. e->f
5. e->d

The minimum spanning tree is

<img src="https://ws1.sinaimg.cn/large/006tNbRwly1fxwwlwohxpj30mc0a0ab6.jpg" width=220 />

## Q3

I'll use **Dijkstra’s Algorithm** with some changes. Keep distance estimate 𝐷(𝑣) and predecessor 𝑃(𝑣) for each node 𝑣.

The time complexity is $O(V + E)$.

### Algorithm:

1. Initially, 𝐷(𝑠) = 0; 𝐷(𝑣) for other nodes is +∞; 𝑃(𝑣) is unknown.
2. Store all the nodes in a set 𝑅.
3. While 𝑅 is not empty
   1. Choose node 𝑣 in 𝑅 such that 𝐷(𝑣) is the smallest. Remove 𝑣 from the set 𝑅.
   2. Declare that 𝑣’s shortest distance is known, which is 𝐷(𝑣).
   3. For each of 𝑣’s neighbors 𝑢 that is still in 𝑅, update distance estimate 𝐷(𝑢) and predecessor 𝑃(𝑢). For each of 𝑣’s neighbors 𝑢 that is still in 𝑅, if 𝐷(𝑣) + 𝑤(𝑣, 𝑢) ==>== 𝐷(𝑢), then update 𝐷(𝑢) = 𝐷(𝑣) + 𝑤(𝑣, 𝑢) and the predecessor 𝑃(𝑢) = 𝑣.
4. By backtracking, if we cannot find the s point, there is no path exists between the two nodes. Otherwise, we can obtain the longest path by backtracking. 

## Q4

Again, similar to Q3, with change <u>𝐷(𝑣) + 𝑤(𝑣, 𝑢) > 𝐷(𝑢)</u>  to <u>𝐷(𝑣) $\times$𝑤(𝑣, 𝑢) < 𝐷(𝑢)</u>. 

### Algorithm:

1. Initially, 𝐷(𝑠) = 0; 𝐷(𝑣) for other nodes is +∞; 𝑃(𝑣) is unknown.
2. Store all the nodes in a set 𝑅.
3. While 𝑅 is not empty
   1. Choose node 𝑣 in 𝑅 such that 𝐷(𝑣) is the smallest. Remove 𝑣 from the set 𝑅.
   2. Declare that 𝑣’s shortest distance is known, which is 𝐷(𝑣).
   3. For each of 𝑣’s neighbors 𝑢 that is still in 𝑅, update distance estimate 𝐷(𝑢) and predecessor 𝑃(𝑢). For each of 𝑣’s neighbors 𝑢 that is still in 𝑅, if 𝐷(𝑣) $\times$ 𝑤(𝑣, 𝑢) ==<== 𝐷(𝑢), then update 𝐷(𝑢) = 𝐷(𝑣) $\times$ 𝑤(𝑣, 𝑢) and the predecessor 𝑃(𝑢) = 𝑣.
4. By backtracking, if we cannot find the s point, there is no path exists between the two nodes. Otherwise, we can obtain the longest path by backtracking. 

## Q5

```c++
DFS(v) {
  visit v;
  v.edges --;
  for(each node u adjacent to v)
    if(u.edges != 0) DFS(u);
}
      

path(s){
	for(each node v in the graph){
    	set v.edges = # of edges adjacent to v;
	}
	DFS(s);
}
```
This is an O(|V |+|E|)-time algorithm.

For example: path(A) for the following graph, we can get `A→B→C→D→C→A→C→B→A`

<img src="https://ws1.sinaimg.cn/large/006tNbRwly1fxx1pgjse4j30g208k3ys.jpg" width=320 />

