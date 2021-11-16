## State Space Search

- Deals with no of possible states in the problem
- S : {S, A, Action (s), Result (s, a), Cost (s, a)}  
  where,
  - S : Start, Goal
  - A : All possible actions


- Searching Types:  
  | **Uninformed Search**                    | **Informed Search**                           |  
  | ---------------------------------------- | --------------------------------------------- |  
  | Searching without Information            | Searching with Information                    |  
  | Exponential States                       | Heuristic is used                             |  
  |  T.C in Searching state is (n-1)!        | **T.C: O(b^d)**                               |  
  | Time consuming but gives accurate answer | Quick Solution (not sure optimality)          |  
  | More complexity (time, space)            | Less complexity comparitivly (time, space)    |  
  | Example: BFS, DFS, etc                   | Example: A*, Heuristic DFS, Best first Search |  


- Heuristic Funtion
  - Denoted by h(n)
  - Used in Non polynomial problems
 
