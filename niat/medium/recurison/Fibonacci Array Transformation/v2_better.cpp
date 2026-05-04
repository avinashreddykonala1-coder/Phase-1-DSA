#include <bits/stdc++.h>
using namespace std;

class solution {
    public:
    unordered_map<int,int> m; // memory box to save answers we already figured out

    int fibonacciVal(int n){
        if(n == 0) return 0;                          // fib(0) is always 0
        if(n == 1) return 1;                          // fib(1) is always 1
        if(m.count(n)) return m[n];                   // already solved this? just return saved answer
        m[n] = fibonacciVal(n-1) + fibonacciVal(n-2); // solve it and save it
        return m[n];                                  // return the saved answer
    }

    vector<int> getTransformedArray(vector<int>& arr, int n) {
        for(int i = 0; i < n; i++){
            arr[i] = fibonacciVal(arr[i]); // replace each number with its fibonacci value
        }
        return arr; // return the updated array
    }
};

/*
┌─────────────────────────────────────────────────────────────────────┐
│                     WHAT DOES THIS CODE DO?                         │
└─────────────────────────────────────────────────────────────────────┘

  You have a list of numbers. This code replaces each number with its
  Fibonacci value — the number you get when you follow the Fibonacci
  chain that many steps.

  Fibonacci chain: 0, 1, 1, 2, 3, 5, 8, 13, 21 ...
  fib(0)=0, fib(1)=1, fib(2)=1, fib(3)=2, fib(4)=3, fib(5)=5

  The smart trick: it uses a memory box (map) so if you already
  figured out fib(4) once, next time you just look it up instead
  of doing all that work again!

  Example:
    Input  → arr = [3, 5, 4, 3], n = 4
    Output → arr = [2, 5, 3, 2]

    because: fib(3)=2, fib(5)=5, fib(4)=3, fib(3)=2 (looked up!)

┌─────────────────────────────────────────────────────────────────────┐
│               HOW DOES getTransformedArray WORK?                    │
└─────────────────────────────────────────────────────────────────────┘

  It walks through every slot in the array one by one.
  For each slot, it asks fibonacciVal: "hey, what is fib of this number?"
  Then it puts that answer back in the same slot.
  Like swapping each price tag on items in a shop with a new price.

  Dry run with arr = [3, 5, 4, 3], n = 4:

    i=0 → arr[0]=3 → fibonacciVal(3)=2  → arr becomes [2, 5, 4, 3]
    i=1 → arr[1]=5 → fibonacciVal(5)=5  → arr becomes [2, 5, 4, 3]
    i=2 → arr[2]=4 → fibonacciVal(4)=3  → arr becomes [2, 5, 3, 3]
    i=3 → arr[3]=3 → fibonacciVal(3)=?  → already in memory box! → 2
                                         → arr becomes [2, 5, 3, 2]

    Final output → [2, 5, 3, 2]

┌─────────────────────────────────────────────────────────────────────┐
│                  HOW DOES fibonacciVal WORK?                        │
└─────────────────────────────────────────────────────────────────────┘

  It's like a helper who figures out fib(n) by asking two smaller
  helpers: "what is fib(n-1)?" and "what is fib(n-2)?"
  Before doing that work, it checks its memory box first.
  If the answer is already saved, it skips all the work!

  Without memory box — fib(5) would look like this (lots of repeats!):

    fib(5)
    ├── fib(4)
    │   ├── fib(3)
    │   │   ├── fib(2)
    │   │   │   ├── fib(1) → 1
    │   │   │   └── fib(0) → 0
    │   │   └── fib(1) → 1
    │   └── fib(2)          ← would repeat this!
    │       ├── fib(1) → 1
    │       └── fib(0) → 0
    └── fib(3)              ← would repeat this too!
        ├── fib(2)
        │   ├── fib(1) → 1
        │   └── fib(0) → 0
        └── fib(1) → 1

  WITH memory box — fib(5) looks like this (no repeats!):

    fib(5) → not in box, compute it
    ├── fib(4) → not in box, compute it
    │   ├── fib(3) → not in box, compute it
    │   │   ├── fib(2) → not in box, compute it
    │   │   │   ├── fib(1) → 1  (base case)
    │   │   │   └── fib(0) → 0  (base case)
    │   │   │   └── save m[2]=1, return 1
    │   │   └── fib(1) → 1  (base case)
    │   │   └── save m[3]=2, return 2
    │   └── fib(2) → found in box! return 1  ✓ (skipped!)
    │   └── save m[4]=3, return 3
    └── fib(3) → found in box! return 2  ✓ (skipped!)
    └── save m[5]=5, return 5

  Memory box after fib(5): { 2:1, 3:2, 4:3, 5:5 }

  Next call fib(3) for arr[3]=3 → found in box instantly! return 2 ✓

┌─────────────────────────────────────────────────────────────────────┐
│                        TIME COMPLEXITY                              │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│  fibonacciVal(n)                                                    │
│  ───────────────                                                    │
│  O(M) where M = the biggest number in the array                     │
│                                                                     │
│  Why? Each fib value from 0 to M is computed exactly ONCE.         │
│  After that, every call just looks it up in the memory box.         │
│  In our example: fib(3) was computed once, then looked up           │
│  instantly the second time → saved a whole chain of calls!          │
│                                                                     │
│  getTransformedArray(arr, n)                                        │
│  ───────────────────────────                                        │
│  O(n + M)                                                           │
│                                                                     │
│  Why? The loop visits n slots → O(n)                                │
│  First time we see a new fib value, we compute it → O(M)           │
│  After that, every repeat is O(1) (just a box lookup)               │
│                                                                     │
│  In our example [3,5,4,3]:                                          │
│    n=4 slots visited                                                │
│    M=5 unique fib values computed (fib 0 through 5)                 │
│    fib(3) on 2nd visit → 1 lookup, 0 work                          │
│    Total steps ≈ 4 + 5 = 9 steps instead of 30+ without memory     │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────────┐
│                       SPACE COMPLEXITY                              │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│  fibonacciVal(n)                                                    │
│  ───────────────                                                    │
│  O(M) for memory box  +  O(M) for call stack = O(M)                │
│                                                                     │
│  Memory box: stores one answer per fib number → grows up to M      │
│  Call stack: deepest chain is fib(M)→fib(M-1)→...→fib(0) = M deep  │
│                                                                     │
│  In our example: M=5 → box holds at most 4 entries {2,3,4,5}       │
│  Stack goes at most 5 levels deep on first call to fib(5)           │
│                                                                     │
│  getTransformedArray(arr, n)                                        │
│  ───────────────────────────                                        │
│  O(M) — just the memory box (the array is given to us, not new)     │
│                                                                     │
│  Why not O(n)? The loop uses no extra space.                        │
│  The only space we own is the memory box which grows with M,        │
│  not with the number of items in the array.                         │
│                                                                     │
│  In our example: n=4 items, M=5, box has 4 saved values → O(5)=O(M)│
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
*/
