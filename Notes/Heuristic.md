## Heuristic in AI
- Heuristic Function: Denoted by h(n)
- A technique to solve a problem quickly
- Used to solve non polynomial function to polynomial
- Methods:
  - Eucledian Distance
  - Manhatten Distance

### Generate and Test
- Heuristic Technique
- DFS with backtracking
- Steps
  - Infinitly generate a possible solution
  - Test to check if this is a actual solution
  - If solution is found quit, else go to step 1
- Properties of good generator
  - Complete
  - Non redundant
  - Informed


### Best First Search
- Informed and Heuristic Technique
- Always give GOOD solution not sure about optimal
- TC & SC: O(b^d)
- Algorithm:
  - Let 'PQ' be a priority queue contaning inital state
  - Loop  
      _if_ (PQ is empty) _return_ false  
      Node <- Remove first(PQ)  
        _if_ (Node is goal) _return_ path from inital to Node  
      _else_ generate all successor of Node and newly generated nodes in PQ according to their F value  
    END LOOP  
    
    ![image](https://user-images.githubusercontent.com/69967336/142070428-7ecc72c3-e105-4a5c-b0ef-e3d3583fae51.png)



### Beam Search Algorithm
- Informed and Heuristic Technique
- Optimum in case of Space Complexity
- Beam Width (beta) is given
- Same as Best First Search but just put _beta_ no of nodes in priority queue
- For ex. _beta_ = 2, only put best 2 in PQ and remove everything
- TC: O(b^d) and SC: O(1)



### Hill Climbing Algorithm
- Informed and Heuristic Technique
- Local Search Algorithm
- Greedy Approach and no backtrackking
- Same as Beam Search Algorithm with _beta_ = 1
- It evaluate in intial state
- Algorithm  
  Loop (Until solution is found/there are no operators left)  
    - select and apply a new operator  
    - evaluate the new state  
    - if (goal) then quit  
    - if (better than current) then change to current state  
  END LOOP
- Problems
  1. Local Maxima 
  2. Pateau / Flat Maximum
  3. Ridge  
  
  ![image](https://user-images.githubusercontent.com/69967336/142072378-4b587048-f4eb-46bd-9388-bca226b91005.png)



## A* Algorithm
- Informed and Heuristic Technique
- Used BFS with priority queue
- f(n) = g(n) + h(n) where,
  - g(n): Actual cost from start to n  
  - h(n): Estimate cost from n to goal node
- TC & SC: O(b^d)
- How to make A* admissible:
  - Let's say h(n): estimate value and h*(n): actual value  
    - h(n) <= h*(n) then **underestimation**
    - h(n) >= h*(n) then **overestimation**  
  - Underestimation is more likely to give correct answer  
  
  ![image](https://user-images.githubusercontent.com/69967336/142074655-152dd7b5-7545-48d3-9cb5-ba208716557c.png)



## AO* (AND/OR) 
- AND / OR graph is used
- Breakdown into smaller pieces
- AO* does not explore all the solution oath once it got a solution  
  
  ![image](https://user-images.githubusercontent.com/69967336/142075345-20ec0bae-ec98-4b57-a681-4f65f0a372c5.png)



        
       
      
