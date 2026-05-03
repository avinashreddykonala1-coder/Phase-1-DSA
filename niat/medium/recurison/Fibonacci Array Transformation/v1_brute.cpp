#include <bits/stdc++.h>
using namespace std;

class solution {
public:

    int fibonacciVal(int n) {

        // STOP SIGN #1: position 0 always has value 0. Just return it.
        if (n == 0) {
            return 0;
        }

        // STOP SIGN #2: position 1 always has value 1. Just return it.
        if (n == 1) {
            return 1;
        }

        // For everything else: answer = (one step back) + (two steps back)
        // e.g. fib(5) = fib(4) + fib(3) = 3 + 2 = 5
        return fibonacciVal(n - 1) + fibonacciVal(n - 2);
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
//                        WHAT DOES THIS CODE DO?
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
// Example:
//   Input  → arr = [3, 5, 1]
//   Output → arr = [2, 5, 1]
//   Because fib(3)=2, fib(5)=5, fib(1)=1
//
// ═══════════════════════════════════════════════════════════════════
//                         HOW DOES fib() WORK?
// ═══════════════════════════════════════════════════════════════════
//
// Think of it like a helper asking other helpers:
//   You forget fib(5), so you ask two friends:
//     "what is fib(4)?" and "what is fib(3)?"
//   Each friend also forgets, so they ask their own friends.
//   This keeps going until someone hits fib(0) or fib(1)
//   — those two ALWAYS know the answer (0 and 1).
//   Then everyone passes answers back up the chain.
//
// DRY RUN for fibonacciVal(4):
//
//   fib(4)
//   ├── fib(3)
//   │   ├── fib(2)
//   │   │   ├── fib(1) → returns 1  ✓ (base case)
//   │   │   └── fib(0) → returns 0  ✓ (base case)
//   │   │   fib(2) = 1 + 0 = 1
//   │   └── fib(1) → returns 1  ✓ (base case)
//   │   fib(3) = 1 + 1 = 2
//   └── fib(2)
//       ├── fib(1) → returns 1  ✓ (base case)
//       └── fib(0) → returns 0  ✓ (base case)
//       fib(2) = 1 + 0 = 1
//   fib(4) = 2 + 1 = 3  ✓
//
// ⚠️  PROBLEM: fib(2) was solved TWICE! This is wasted work.
//     Fix later: save answers in a table (memoization)
//     so we never solve the same problem twice.
//
// ═══════════════════════════════════════════════════════════════════
//                    HOW DOES getTransformedArray() WORK?
// ═══════════════════════════════════════════════════════════════════
//
// DRY RUN with arr = [3, 5, 1], n = 3:
//
//   Start  →  arr = [3, 5, 1]
//
//   i = 0: arr[0] = 3 → fib(3) = 2  →  arr = [2, 5, 1]
//   i = 1: arr[1] = 5 → fib(5) = 5  →  arr = [2, 5, 1]
//   i = 2: arr[2] = 1 → fib(1) = 1  →  arr = [2, 5, 1]
//
//   Final  →  arr = [2, 5, 1]  ✓
//
// ═══════════════════════════════════════════════════════════════════
//                          TIME COMPLEXITY
// ═══════════════════════════════════════════════════════════════════
//
//  fibonacciVal(n)        → O(2^n)
//  ┌─────────────────────────────────────────────────────────────┐
//  │  Every call splits into 2 more calls.                      │
//  │  For n=5  → ~30  calls total                               │
//  │  For n=10 → ~1000 calls total                              │
//  │  Doubles with every step. Very slow for large numbers!     │
//  └─────────────────────────────────────────────────────────────┘
//
//  getTransformedArray()  → O(n × 2^max(arr))
//  ┌─────────────────────────────────────────────────────────────┐
//  │  Loop runs n times (once per element).                     │
//  │  Each element calls fib() which costs 2^(that value).      │
//  │                                                            │
//  │  Example: arr = [3, 5, 1]                                  │
//  │    fib(3) →  8 calls                                       │
//  │    fib(5) → 30 calls                                       │
//  │    fib(1) →  1 call                                        │
//  │    Total  → 39 calls                                       │
//  └─────────────────────────────────────────────────────────────┘
//
// ═══════════════════════════════════════════════════════════════════
//                         SPACE COMPLEXITY
// ═══════════════════════════════════════════════════════════════════
//
//  fibonacciVal(n)        → O(n)
//  ┌─────────────────────────────────────────────────────────────┐
//  │  The call stack grows one level at a time going down.      │
//  │  Deepest it ever goes = n levels.                          │
//  │  fib(4) → fib(3) → fib(2) → fib(1) = 4 levels deep       │
//  └─────────────────────────────────────────────────────────────┘
//
//  getTransformedArray()  → O(max(arr))
//  ┌─────────────────────────────────────────────────────────────┐
//  │  We do NOT make a new array. Same array is edited.         │
//  │  Only extra memory = the fib() call stack.                 │
//  │  Call stack goes as deep as the biggest number in array.   │
//  │                                                            │
//  │  Example: arr = [3, 5, 1]                                  │
//  │  Biggest number = 5                                        │
//  │  Stack goes 5 levels deep at most → O(max(arr))            │
//  └─────────────────────────────────────────────────────────────┘
//
// ═══════════════════════════════════════════════════════════════════
