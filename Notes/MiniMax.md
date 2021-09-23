# MiniMax Algorithm

- Backtracking Algorithm
- Best player statergy is used
- There are two player **Minimizer and Maximizer**
    - Maximizer will try to maximize the utility (Best Move)
    - Minimizer will try to minimize the utility (Worst Move)
- Used in two player games, e.g. Tictaktoe, Chess

## Example  
_Let's consider square as max and circle as min_  
If the given game has 8 final states and paths to reach final state are from root to 8 leaves of a perfect binary tree as shown below  
<p align=center>
  <img src="https://user-images.githubusercontent.com/69967336/134572172-22fb3e24-ccea-4c25-9036-19141861561a.png" alt="Sublime's custom image"/>
</p>

As we go down on left part, it's maximizers turn to maximize the value, so the result will be 
<p align=center>
  <img src="https://user-images.githubusercontent.com/69967336/134572817-3d476e77-b24d-4091-847f-c67723e1bb05.png" alt="Sublime's custom image"/>
</p>

Now, it's minimizer's turn to try to minimize the utility
<p align=center>
  <img src="https://user-images.githubusercontent.com/69967336/134573036-2daaad35-73d9-4284-af08-74845c73b6d6.png" alt="Sublime's custom image"/>
</p>

And finally the answer will be maximized result.
<p align=center>
  <img src="https://user-images.githubusercontent.com/69967336/134573270-dfa10f1e-08c2-4cc0-98a9-9d4ae9dbd520.png" alt="Sublime's custom image"/>
</p>


## Time Complexity
As it performs DFS for the game-tree, so the time complexity of Min-Max algorithm is O(bm)
where,
  - b is branching factor of the tree.
  - m is the maximum depth of the tree.


## Space Complexity
Space complexity of Mini-max algorithm is also similar to DFS which is O(bm).  
