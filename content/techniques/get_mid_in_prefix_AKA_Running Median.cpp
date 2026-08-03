/*
 * RUNNING PERCENTILE / MEDIAN (Two Priority Queues)
 * -------------------------------------------------
 * max_heap: stores the smaller P% of elements. Top is the answer.
 * min_heap: stores the larger (1-P)% of elements.
 * 
 * GENERAL RULE FOR ANY PERCENTILE (e.g., P = 0.90 for 90th percentile):
 * 1. Push 'num' to the correct heap (compare with max_heap.top()).
 * 2. int expected_left = ceil(total_elements * P);
 * 3. Rebalance using while loops:
 *    while(max_heap.size() > expected_left) { 
 *        min_heap.push(max_heap.top()); max_heap.pop(); 
 *    }
 *    while(max_heap.size() < expected_left && !min_heap.empty()) { 
 *        max_heap.push(min_heap.top()); min_heap.pop(); 
 *    }
 * 4. The answer is always: max_heap.top()
 * -------------------------------------------------
 * BELOW IS THE FAST IMPLEMENTATION FOR RUNNING MEDIAN (P = 0.50):
 */

priority_queue<int> max_heap; 
// for small numbers (returns the greatest)

priority_queue<int, vector<int>, greater<int>> min_heap; 
// for large numbers (returns the smallest)

// 1. Adding num to your current window
int num; // Assume this is your input
if (max_heap.empty() || num <= max_heap.top()) {
    max_heap.push(num);
} else {
    min_heap.push(num);
}

// 2. Rebalancing (Specific for Median 50/50 split)
if (max_heap.size() > min_heap.size() + 1) {
    min_heap.push(max_heap.top());
    max_heap.pop();
} else if (min_heap.size() > max_heap.size()) {
    max_heap.push(min_heap.top());
    min_heap.pop();
}

// 3. Find the median
double ans;
if (max_heap.size() == min_heap.size()) {
    // for even size
    ans = (max_heap.top() + min_heap.top()) / 2.0; 
} else {
    // for odd size (max_heap always holds the extra element)
    ans = max_heap.top();
}

/*
 * U can also do it using Binary Lifting And Fenwick Tree (See it in DataStructures chapter)
 */
