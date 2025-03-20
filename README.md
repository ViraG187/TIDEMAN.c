# Tideman Voting Algorithm

## Figma created to solve:
[My_Tideman_Figma](https://www.figma.com/board/DwU95heb5O30HirnHSU0zl/cs50?node-id=2001-2&t=mZ0wXBTSkmlzQKoJ-1)

![image](https://github.com/user-attachments/assets/c9bb0892-a763-4f63-a31d-b36417e9f350)

### 1. Candidates: `Hare`, `Krishna`, `Radhe`
- **Preferences:**  3x3 Matrix (All values start at 0)
- **Pairs:** Empty
- **Locked Graph:** 3x3 Matrix (All False)

### 2. Get candidates from command-line arguments:
```c
int main(int argc, char *argv[]) {
    candidate_count = argc - 1;
    for (int i = 0; i < candidate_count; i++) {
        cand[i] = argv[i + 1];  // Storing candidate names
    }
}
```

### Storing Candidates as:
```c
cand[] = { "Hare", "Krishna", "Radhe" }
```

### 3. Collect and arrange in preference table (Adjacency Matrix)
```c
int voters;
printf("Enter number of Voters: ");
scanf("%d", &voters);

for (int i = 0; i < voters; i++) {
    int ranks[candidate_count];
    for (int j = 0; j < candidate_count; j++) {
        printf("Rank %i: ", j + 1);
        char name[20];
        scanf("%20s", name);
        
        if (!vote(j, name, ranks)) {
            printf("Invalid Vote\n");
        }
    }
    record_preferences(ranks);
}
```

### Preference Table Formed:
|    | Hare | Krishna | Radhe |
|----|------|---------|-------|
| Hare  | 0    | 2       | 2     |
| Krishna | 1    | 0       | 2     |
| Radhe  | 1    | 1       | 0     |

---
### 4. **Vote Function**
### Logic Flow:
```
Start → User enters candidate name  
↓  
Check if name matches any candidate  
↓  
Yes → Store candidate index in ranks[] → Return true → End  
↓  
No → Print "Invalid Vote" → Return false → End
```

### Example:
| Rank | Candidate Entered | Matches in cand[]? | Updated ranks[] |
|------|------------------|-------------------|----------------|
| 1    | Krishna         | ✅ Yes (Index 1)  | ranks[0] = 1   |
| 2    | Radhe          | ✅ Yes (Index 2)  | ranks[1] = 2   |
| 3    | Hare           | ✅ Yes (Index 0)  | ranks[2] = 0   |

### Code:
```c
bool vote(int rank, char* name, int ranks[]) {
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(cand[i], name) == 0) {  // Check if name matches candidate list
            ranks[rank] = i;  // Assign index to ranks[]
            return true;
        }
    }
    return false;  // Return false if no match found
}
```

---
### 5. **Processing Votes**
### `record_preferences()`
```
Start
  │
  ▼
Loop through ranks[] (for each voter's ranking)
  │
  ▼
Compare higher-ranked candidate with all lower-ranked candidates
  │
  ▼
Increment preferences[winner][loser] count
  │
  ▼
Repeat for all voter rankings
  │
  ▼
End
```

### `add_pairs()`
```
Start
  │
  ▼
Loop through all candidate pairs (i, j)
  │
  ├───(preferences[i][j] > preferences[j][i]?)──► Yes ──► Store (i wins, j loses)
  │
  ├───(preferences[j][i] > preferences[i][j]?)──► Yes ──► Store (j wins, i loses)
  │
  ▼
Increment pair count
  │
  ▼
Repeat for all candidate pairs
  │
  ▼
End
```

### `sort_pairs()`
```
Start
  │
  ▼
Sort pairs by strength of victory (margin of preferences)
  │
  ▼
Use selection sort to find the highest margin pair
  │
  ▼
Swap positions if needed
  │
  ▼
Repeat for all pairs
  │
  ▼
End
```

### `cycle()`
```
Start
  │
  ▼
Check if locking a pair creates a cycle
  │
  ├───(winner == loser?)──► Yes ──► Cycle Found (Return True)
  │
  ▼
Check for recursive cycle through locked pairs
  │
  ├───(Any path back to winner?)──► Yes ──► Cycle Found (Return True)
  │
  ▼
No cycle detected ──► Return False
```

### `lock_pairs()`
```
Start
  │
  ▼
Loop through sorted pairs
  │
  ├───(Does locking create a cycle?)──► Yes ──► Skip locking
  │
  ├───No ──► Lock the pair
  │
  ▼
Repeat for all pairs
  │
  ▼
End
```

---
### 6. **Finding the Winner**
### `print_winner()`
```
Start
  │
  ▼
Find the source node (candidate with no incoming edges)
  │
  ├───(Has incoming edges?)──► Yes ──► Not the winner
  │
  ▼
Candidate with no incoming edges is the winner
  │
  ▼
Print the winner's name
  │
  ▼
End
```

---
## 📌 Summary
- **Implemented Tideman Voting Algorithm** using adjacency matrix, graph locking, and cycle detection.
- **Ensured fairness** by preventing cycles and finding the true ranked-choice winner.
- **Used structured approach** for coding, logic diagrams, and examples.

🔹 _Feel free to contribute or fork this project!_ 🚀

