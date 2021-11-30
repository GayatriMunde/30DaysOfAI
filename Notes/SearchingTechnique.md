## Breadth First Search
- Uninformed Search / Brute Force / Blind Technique
- Level order 
- FIFO (Queue is used)
- Shallowest Node
- Complete and Optimal
- TC: O(b^d) where,  
  b: branch factor
  d: depth  
    
   ![image](https://user-images.githubusercontent.com/69967336/142064783-1f23ea61-b9b5-4ba6-8adf-673c8a73c635.png)

  
  
## Depth First Search
- Uninformed Search / Brute Force / Blind Technique
- LIFO (Stack is used)
- Deepest Node
- Incomplete (If cycle is there, it may get stuck in loop) and not optimal
- TC: O(b^d) where,  
  b: branch factor
  d: depth  
    
  ![image](https://user-images.githubusercontent.com/69967336/142065523-a09b8cfe-6276-48f5-9fbc-df1ecdbd8b9c.png)



## Bidirectional Search Technique
- Two simulataneous search from on initial node to goal and backtracks from goel to initial, stopping when two meet
- TC: 2(b^(d/2)) where,  
  b: branch factor
  d: depth  
 - Complete in BFS, not in DFS



## 
