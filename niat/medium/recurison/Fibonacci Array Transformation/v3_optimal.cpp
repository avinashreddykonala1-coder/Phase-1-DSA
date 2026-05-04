#include <bits/stdc++.h>
using namespace std;

class solution {
public:

    int fibonacciVal(int n) {

        // STOP SIGN #1: position 0 always has value 0. Just return it.
        if (n == 0) return 0;

        // STOP SIGN #2: position 1 always has value 1. Just return it.
        if (n == 1) return 1;

        int prev2 = 0; // this holds fib(0) — two steps behind current
        int prev1 = 1; // this holds fib(1) — one step behind current

        // Walk forward from position 2 all the way up to n
        for (int i = 2; i <= n; i++) {
            int curr = prev1 + prev2; // current = one step back + two steps back
            prev2 = prev1;            // shift: two-steps-back becomes one-step-back
            prev1 = curr;             // shift: current becomes one-step-back
        }

        return prev1; // prev1 now holds fib(n)
    }

    vector<int> getTransformedArray(vector<int>& arr, int n) {

        // Visit every position in the array one by one
        for (int i = 0; i < n; i++) {

            // Replace the current number with its Fibonacci value
            // e.g. if arr[i] = 5, it becomes fib(5) = 5
            //      if arr[i] = 3, it becomes fib(3) = 2
            arr[i] = fibonacciVal(arr[i]);
        }

        // Send back the updated array
        return arr;
    }
};


// ═══════════════════════════════════════════════════════════════════
//                      WHAT DOES THIS CODE DO?
// ═══════════════════════════════════════════════════════════════════
//
// We have an array of numbers.
// We replace every number with its Fibonacci value.
//
// What is Fibonacci? It is a number list where each number
// is the SUM of the two numbers before it.
//
//   Position: 0  1  2  3  4  5  6   7   8
//   Value:    0  1  1  2  3  5  8  13  21
//
// THE SMART TRICK: Instead of recursion or a memory map,
// we just use TWO variables and walk forward.
// Like a caterpillar — only remembers the last two steps,
// throws away everything else.
//
// Example:
//   Input  → arr = [3, 5, 4, 3]
//   Output → arr = [2, 5, 3, 2]
//   Because fib(3)=2, fib(5)=5, fib(4)=3, fib(3)=2
//
// ═══════════════════════════════════════════════════════════════════
//                        HOW DOES fib() WORK?
// ═══════════════════════════════════════════════════════════════════
//
// Instead of asking helpers (recursion) or using a notebook (memo),
// we just BUILD the answer from the ground up using two variables.
//
// Think of it like walking up stairs:
//   You only need to remember the last TWO steps to find the next one.
//   Once you take the next step, the oldest one is forgotten forever.
//
// TWO VARIABLES doing all the work:
//   prev2 = value TWO steps behind  (starts at fib(0) = 0)
//   prev1 = value ONE step behind   (starts at fib(1) = 1)
//   curr  = current step being computed
//
// DRY RUN for fibonacciVal(5):
//
//   Start  →  prev2=0  prev1=1
//
//   i=2 →  curr = 1+0 = 1   prev2=1  prev1=1
//              [fib(0)  fib(1)  fib(2)]
//                              ↑ curr
//
//   i=3 →  curr = 1+1 = 2   prev2=1  prev1=2
//              [fib(1)  fib(2)  fib(3)]
//                              ↑ curr
//
//   i=4 →  curr = 2+1 = 3   prev2=2  prev1=3
//              [fib(2)  fib(3)  fib(4)]
//                              ↑ curr
//
//   i=5 →  curr = 3+2 = 5   prev2=3  prev1=5
//              [fib(3)  fib(4)  fib(5)]
//                              ↑ curr
//
//   return prev1 = 5  ✓
//
// NO recursion. NO map. Just two variables sliding forward like a window.
//
// ═══════════════════════════════════════════════════════════════════
//                  HOW DOES getTransformedArray() WORK?
// ═══════════════════════════════════════════════════════════════════
//
// DRY RUN with arr = [3, 5, 4, 3], n = 4:
//
//   Start  →  arr = [3, 5, 4, 3]
//
//   i=0: arr[0]=3 → fibonacciVal(3)
//        prev2=0,prev1=1 → i=2: curr=1 → i=3: curr=2 → return 2
//        arr = [2, 5, 4, 3]
//
//   i=1: arr[1]=5 → fibonacciVal(5)
//        prev2=0,prev1=1 → i=2→i=3→i=4→i=5 → return 5
//        arr = [2, 5, 4, 3]
//
//   i=2: arr[2]=4 → fibonacciVal(4)
//        prev2=0,prev1=1 → i=2→i=3→i=4 → return 3
//        arr = [2, 5, 3, 3]
//
//   i=3: arr[3]=3 → fibonacciVal(3)
//        prev2=0,prev1=1 → i=2→i=3 → return 2
//        arr = [2, 5, 3, 2]
//
//   Final  →  arr = [2, 5, 3, 2]  ✓
//
// ⚠️  NOTE: Unlike memoization, this version recomputes fib(3) fully
//     when it appears the second time. No memory is shared between calls.
//     But it still wins on SPACE because no map is ever created!
//
// ═══════════════════════════════════════════════════════════════════
//                          TIME COMPLEXITY
// ═══════════════════════════════════════════════════════════════════
//
//  fibonacciVal(n)        → O(n)
//  ┌─────────────────────────────────────────────────────────────┐
//  │  One loop from 2 to n. Each step does one addition.        │
//  │  No branching. No recursion. No repeated work.             │
//  │                                                            │
//  │  Example: fib(5)                                           │
//  │    Loop runs at i=2,3,4,5 → exactly 4 steps               │
//  │    For fib(n) → always exactly (n-1) steps                 │
//  └─────────────────────────────────────────────────────────────┘
//
//  getTransformedArray()  → O(n × M)  where M = biggest number
//  ┌─────────────────────────────────────────────────────────────┐
//  │  Loop visits n elements.                                   │
//  │  Each element calls fib() which costs O(that value).       │
//  │  No answers are saved between calls — each is fresh.       │
//  │                                                            │
//  │  Example: arr = [3, 5, 4, 3]                               │
//  │    fib(3) →  2 steps                                       │
//  │    fib(5) →  4 steps                                       │
//  │    fib(4) →  3 steps                                       │
//  │    fib(3) →  2 steps  (recomputed! no memory saved)        │
//  │    Total  → 11 steps                                       │
//  │                                                            │
//  │  ⚠️  Memoization was O(n + M) — better for arrays with     │
//  │     repeated numbers. This version trades time for space.  │
//  └─────────────────────────────────────────────────────────────┘
//
// ═══════════════════════════════════════════════════════════════════
//                         SPACE COMPLEXITY
// ═══════════════════════════════════════════════════════════════════
//
//  fibonacciVal(n)        → O(1)  ← THE BIG WIN
//  ┌─────────────────────────────────────────────────────────────┐
//  │  Only 3 variables ever exist: prev2, prev1, curr           │
//  │  No map. No call stack. No recursion.                      │
//  │  Same 3 variables are reused for EVERY step.               │
//  │                                                            │
//  │  Example: fib(5) uses exactly 3 variables                  │
//  │           fib(500) also uses exactly 3 variables           │
//  │           n does not change the memory used → O(1)         │
//  └─────────────────────────────────────────────────────────────┘
//
//  getTransformedArray()  → O(1)
//  ┌─────────────────────────────────────────────────────────────┐
//  │  We do NOT make a new array. Same array is edited.         │
//  │  fib() uses O(1) space each call, no leftover memory.      │
//  │  The loop variable i is 1 extra variable — still O(1).     │
//  │                                                            │
//  │  Compare all 3 versions:                                   │
//  │    Plain recursion  → O(n)  call stack                     │
//  │    Memoization      → O(n)  map + call stack               │
//  │    Bottom-up loop   → O(1)  just 3 variables  ← winner     │
//  └─────────────────────────────────────────────────────────────┘
//
// ═══════════════════════════════════════════════════════════════════
