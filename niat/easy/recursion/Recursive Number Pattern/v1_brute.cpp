#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> generatePattern(int n) {

        vector<int> v;                          // create empty box to store numbers
        v.push_back(n);                         // push current number BEFORE going down

        if(n <= 0) return v;                    // STOP SIGN #1: reached 0 or below, stop here

        vector<int> rest = generatePattern(n - 5);  // go down by 5, collect all results

        for(int x : rest) v.push_back(x);      // merge all numbers from smaller call

        v.push_back(n);                         // push current number AGAIN while coming back up

        return v;                               // send full result to whoever called me
    }
};


// ═══════════════════════════════════════════════════
//              WHAT DOES THIS CODE DO?
// ═══════════════════════════════════════════════════
//
// It generates a pattern that counts DOWN by 5 to 0,
// then counts back UP by 5 to n.
//
// It does this using RECURSION — the function calls
// itself with a smaller number each time.
//
// THE SMART TRICK: push n BEFORE recursion (going down)
//                  push n AGAIN AFTER recursion (coming up)
//                  This gives us both sides of the pattern for FREE.
//
// Input  → n = 15
// Output → [15, 10, 5, 0, 5, 10, 15]
// Because it goes 15→10→5→0 then comes back 5→10→15


// ═══════════════════════════════════════════════════
//          HOW DOES generatePattern WORK?
// ═══════════════════════════════════════════════════
//
// Think of it like this:
// Each call is a HELPER. Each helper asks the next
// helper to do a smaller job, waits for the answer,
// then adds itself on BOTH SIDES of that answer.
//
// CALL TREE for n = 15:
//
// generatePattern(15)
// ├── push 15                          → v = [15]
// ├── calls generatePattern(10)
// │     ├── push 10                    → v = [10]
// │     ├── calls generatePattern(5)
// │     │     ├── push 5              → v = [5]
// │     │     ├── calls generatePattern(0)
// │     │     │     ├── push 0        → v = [0]
// │     │     │     └── STOP SIGN #1  → returns [0]
// │     │     ├── merge [0]           → v = [5, 0]
// │     │     ├── push 5 again        → v = [5, 0, 5]
// │     │     └── returns [5, 0, 5]
// │     ├── merge [5, 0, 5]           → v = [10, 5, 0, 5]
// │     ├── push 10 again             → v = [10, 5, 0, 5, 10]
// │     └── returns [10, 5, 0, 5, 10]
// ├── merge [10, 5, 0, 5, 10]         → v = [15, 10, 5, 0, 5, 10]
// ├── push 15 again                   → v = [15, 10, 5, 0, 5, 10, 15]
// └── returns [15, 10, 5, 0, 5, 10, 15]  ✓
//
// Final → [15, 10, 5, 0, 5, 10, 15] ✓


// ═══════════════════════════════════════════════════
//              HOW DOES THE MERGING WORK?
// ═══════════════════════════════════════════════════
//
// After each recursive call returns, we combine results.
// Using n = 15 as example, here is how vector builds up:
//
// generatePattern(0)  returns:
// v = [0]
//
// generatePattern(5) receives [0] as rest:
// v = [5]  →  merge rest  →  v = [5, 0]  →  push 5  →  v = [5, 0, 5]
//
// generatePattern(10) receives [5, 0, 5] as rest:
// v = [10]  →  merge rest  →  v = [10, 5, 0, 5]  →  push 10  →  v = [10, 5, 0, 5, 10]
//
// generatePattern(15) receives [10, 5, 0, 5, 10] as rest:
// v = [15]  →  merge rest  →  v = [15, 10, 5, 0, 5, 10]  →  push 15  →  v = [15, 10, 5, 0, 5, 10, 15]
//
// Final → v = [15, 10, 5, 0, 5, 10, 15] ✓


// ═══════════════════════════════════════════════════
//                  TIME COMPLEXITY
// ═══════════════════════════════════════════════════
//
// ┌─────────────────────────────────────────────────┐
// │  generatePattern(n)                             │
// │                                                 │
// │  Complexity: O(n/5) recursive calls             │
// │              O(n)   for merging at each level   │
// │  Overall   : O(n²)  in worst case               │
// │                                                 │
// │  WHY?                                           │
// │  For n = 15, we make 4 calls (15,10,5,0)        │
// │  At each call we loop through rest to merge     │
// │  Merging gets bigger each time:                 │
// │    generatePattern(5)  → merges 1 item  [0]     │
// │    generatePattern(10) → merges 3 items [5,0,5] │
// │    generatePattern(15) → merges 5 items [10...] │
// │                                                 │
// │  Total merge work = 1 + 3 + 5 = 9 steps        │
// │  This grows as n grows → O(n²) overall          │
// └─────────────────────────────────────────────────┘


// ═══════════════════════════════════════════════════
//                 SPACE COMPLEXITY
// ═══════════════════════════════════════════════════
//
// ┌─────────────────────────────────────────────────┐
// │  generatePattern(n)                             │
// │                                                 │
// │  Complexity: O(n)                               │
// │                                                 │
// │  WHY?                                           │
// │  Two things use memory:                         │
// │                                                 │
// │  1. CALL STACK (recursion depth)                │
// │     For n=15 → 4 calls deep (15, 10, 5, 0)     │
// │     Each call waits for the next                │
// │     Stack depth = n/5 = O(n)                   │
// │                                                 │
// │  2. VECTORS stored at each level                │
// │     generatePattern(0)  → stores [0]        1  │
// │     generatePattern(5)  → stores [5,0,5]    3  │
// │     generatePattern(10) → stores [10..10]   5  │
// │     generatePattern(15) → stores [15..15]   7  │
// │     Total = 1+3+5+7 = 16 = O(n) items          │
// │                                                 │
// │  Overall space = O(n)                           │
// └─────────────────────────────────────────────────┘
