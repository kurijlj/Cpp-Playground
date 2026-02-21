# Technical Interview Preparation Guide
## Mid-Level to Senior C++ / Python Developer Positions

*Tailored for developers with medical physics / scientific computing background*

---

## Table of Contents

1. [Interview Process Overview](#1-interview-process-overview)
2. [C++ Core Knowledge](#2-c-core-knowledge)
3. [Python Core Knowledge](#3-python-core-knowledge)
4. [Data Structures & Algorithms](#4-data-structures--algorithms)
5. [System Design](#5-system-design)
6. [Software Engineering Practices](#6-software-engineering-practices)
7. [Domain-Specific Topics](#7-domain-specific-topics)
8. [Behavioral Interview](#8-behavioral-interview)
9. [Preparation Roadmap](#9-preparation-roadmap)
10. [Resources & References](#10-resources--references)

---

## 1. Interview Process Overview

### Typical Interview Stages

| Stage | Duration | Focus |
|-------|----------|-------|
| Phone Screen | 30-45 min | Resume review, basic technical questions |
| Technical Phone/Video | 45-60 min | Coding problem, language knowledge |
| On-site / Virtual Loop | 3-5 hours | Multiple rounds (see below) |
| Final / Team Fit | 30-60 min | Cultural fit, questions for you |

### Common Round Types

- **Coding Round**: Solve 1-2 algorithmic problems (45-60 min)
- **System Design**: Design a system architecture (45-60 min)
- **Language Deep-Dive**: C++ or Python specific questions
- **Domain Knowledge**: For specialized roles (medical software, etc.)
- **Behavioral**: Past experiences, teamwork, conflict resolution

---

## 2. C++ Core Knowledge

### 2.1 Language Fundamentals (Must Know)

#### Memory Management
```cpp
// Stack vs Heap allocation
int stackVar = 10;                    // Stack - automatic lifetime
int* heapVar = new int(10);           // Heap - manual management
auto smartPtr = std::make_unique<int>(10);  // Heap - RAII managed

// Rule of Zero/Three/Five
class Resource {
    std::unique_ptr<int[]> data;
public:
    // Rule of Zero: let smart pointers handle everything
    Resource(size_t size) : data(std::make_unique<int[]>(size)) {}
    // No destructor, copy/move constructors needed!
};
```

**Key Topics:**
- Stack vs heap, allocation/deallocation costs
- RAII (Resource Acquisition Is Initialization)
- Smart pointers: `unique_ptr`, `shared_ptr`, `weak_ptr`
- Memory leaks, dangling pointers, double-free
- Rule of Zero/Three/Five
- Move semantics and perfect forwarding

#### Object-Oriented Programming
```cpp
// Polymorphism and virtual functions
class Shape {
public:
    virtual ~Shape() = default;           // Virtual destructor!
    virtual double area() const = 0;      // Pure virtual
    virtual void draw() const { /* default impl */ }
};

class Circle : public Shape {
    double radius;
public:
    double area() const override { return 3.14159 * radius * radius; }
};
```

**Key Topics:**
- Inheritance (public, protected, private)
- Virtual functions, vtable, virtual destructor
- Abstract classes and interfaces
- Multiple inheritance, diamond problem, virtual inheritance
- Composition vs inheritance
- SOLID principles (see Section 6)

#### Modern C++ Features (C++11/14/17)

```cpp
// C++11
auto x = 42;                              // Type deduction
std::vector<int> v = {1, 2, 3};           // Initializer lists
for (const auto& item : v) { }            // Range-based for
auto lambda = [](int x) { return x * 2; };// Lambdas
std::thread t([]{ /* work */ });          // Threading

// C++14
auto lambda14 = [](auto x) { return x * 2; };  // Generic lambdas
auto func() { return 42; }                      // Return type deduction

// C++17
if (auto it = map.find(key); it != map.end()) { }  // Init in if
auto [key, value] = *mapIterator;                   // Structured bindings
std::optional<int> maybeValue;                      // Optional
std::variant<int, string> either;                   // Type-safe union
std::filesystem::path p = "/home/user";             // Filesystem
```

**C++17 Features You Should Know:**
- `std::optional`, `std::variant`, `std::any`
- `std::string_view`
- Structured bindings
- `if constexpr`
- Fold expressions
- `std::filesystem`
- Parallel STL algorithms

### 2.2 STL and Standard Library

#### Containers
| Container | Access | Insert/Delete | Use Case |
|-----------|--------|---------------|----------|
| `vector` | O(1) | O(n) / O(1) amortized end | Default choice |
| `deque` | O(1) | O(1) both ends | Queue with random access |
| `list` | O(n) | O(1) with iterator | Frequent mid-insertion |
| `map` | O(log n) | O(log n) | Sorted key-value |
| `unordered_map` | O(1) avg | O(1) avg | Fast key-value lookup |
| `set` | O(log n) | O(log n) | Sorted unique elements |
| `priority_queue` | O(1) top | O(log n) | Heap operations |

#### Algorithms
```cpp
#include <algorithm>
#include <numeric>

std::vector<int> v = {3, 1, 4, 1, 5, 9};

// Sorting
std::sort(v.begin(), v.end());
std::sort(v.begin(), v.end(), std::greater<int>());  // Descending

// Searching
auto it = std::find(v.begin(), v.end(), 4);
auto it2 = std::lower_bound(v.begin(), v.end(), 4);  // Binary search

// Transforming
std::transform(v.begin(), v.end(), v.begin(), [](int x) { return x * 2; });

// Accumulating
int sum = std::accumulate(v.begin(), v.end(), 0);

// Removing (erase-remove idiom)
v.erase(std::remove_if(v.begin(), v.end(), [](int x) { return x < 3; }), v.end());
```

### 2.3 Concurrency

```cpp
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <atomic>

// Basic threading
std::thread t([](){ /* work */ });
t.join();  // or t.detach();

// Mutex and lock
std::mutex mtx;
{
    std::lock_guard<std::mutex> lock(mtx);  // RAII lock
    // critical section
}

// Condition variable
std::condition_variable cv;
std::unique_lock<std::mutex> lock(mtx);
cv.wait(lock, []{ return ready; });

// Async/Future
auto future = std::async(std::launch::async, [](){ return 42; });
int result = future.get();

// Atomics
std::atomic<int> counter{0};
counter.fetch_add(1, std::memory_order_relaxed);
```

**Key Topics:**
- Thread creation and lifecycle
- Mutex, lock_guard, unique_lock
- Deadlock prevention (lock ordering, std::lock)
- Condition variables
- std::async, std::future, std::promise
- Atomic operations and memory ordering
- Thread-safe data structures

### 2.4 Common C++ Interview Questions

1. **What is the difference between `new`/`delete` and `malloc`/`free`?**
2. **Explain virtual destructor and when it's needed.**
3. **What is the diamond problem? How does virtual inheritance solve it?**
4. **Difference between `unique_ptr` and `shared_ptr`?**
5. **What is move semantics? When is it beneficial?**
6. **Explain RAII. Why is it important?**
7. **What happens if an exception is thrown in a constructor?**
8. **Difference between `std::map` and `std::unordered_map`?**
9. **What is a lambda capture? Difference between `[=]` and `[&]`?**
10. **How would you implement a thread-safe singleton?**

---

## 3. Python Core Knowledge

### 3.1 Language Fundamentals

#### Data Structures
```python
# Lists (dynamic arrays)
lst = [1, 2, 3]
lst.append(4)           # O(1) amortized
lst.insert(0, 0)        # O(n)
lst.pop()               # O(1)
lst.pop(0)              # O(n)

# Dictionaries (hash maps)
d = {'a': 1, 'b': 2}
d['c'] = 3              # O(1) average
del d['a']              # O(1) average
'b' in d                # O(1) average

# Sets
s = {1, 2, 3}
s.add(4)                # O(1) average
s.remove(1)             # O(1) average
s1 & s2                 # Intersection
s1 | s2                 # Union

# Collections module
from collections import defaultdict, Counter, deque, namedtuple
counter = Counter(['a', 'b', 'a'])  # {'a': 2, 'b': 1}
dd = defaultdict(list)
dq = deque([1, 2, 3])              # O(1) both ends
```

#### Object-Oriented Python
```python
from abc import ABC, abstractmethod
from dataclasses import dataclass
from typing import Protocol

# Abstract base class
class Shape(ABC):
    @abstractmethod
    def area(self) -> float:
        pass

# Inheritance
class Circle(Shape):
    def __init__(self, radius: float):
        self._radius = radius  # Convention: single underscore = protected
    
    @property
    def radius(self) -> float:
        return self._radius
    
    def area(self) -> float:
        return 3.14159 * self._radius ** 2

# Dataclasses (Python 3.7+)
@dataclass
class Point:
    x: float
    y: float
    
    def distance_from_origin(self) -> float:
        return (self.x**2 + self.y**2) ** 0.5

# Protocols (structural subtyping, Python 3.8+)
class Drawable(Protocol):
    def draw(self) -> None: ...
```

#### Decorators and Context Managers
```python
# Decorator
def timer(func):
    import time
    def wrapper(*args, **kwargs):
        start = time.time()
        result = func(*args, **kwargs)
        print(f"{func.__name__} took {time.time() - start:.2f}s")
        return result
    return wrapper

@timer
def slow_function():
    import time
    time.sleep(1)

# Context manager
class FileManager:
    def __init__(self, filename, mode):
        self.filename = filename
        self.mode = mode
    
    def __enter__(self):
        self.file = open(self.filename, self.mode)
        return self.file
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        self.file.close()
        return False  # Don't suppress exceptions

# Or using contextlib
from contextlib import contextmanager

@contextmanager
def file_manager(filename, mode):
    f = open(filename, mode)
    try:
        yield f
    finally:
        f.close()
```

#### Generators and Iterators
```python
# Generator function
def fibonacci(n):
    a, b = 0, 1
    for _ in range(n):
        yield a
        a, b = b, a + b

# Generator expression
squares = (x**2 for x in range(10))

# Iterator protocol
class Counter:
    def __init__(self, max_val):
        self.max_val = max_val
        self.current = 0
    
    def __iter__(self):
        return self
    
    def __next__(self):
        if self.current >= self.max_val:
            raise StopIteration
        self.current += 1
        return self.current
```

### 3.2 Type Hints (Python 3.5+)

```python
from typing import List, Dict, Optional, Union, Callable, TypeVar, Generic

def greet(name: str) -> str:
    return f"Hello, {name}"

def process_items(items: List[int]) -> Dict[str, int]:
    return {"sum": sum(items), "count": len(items)}

def maybe_parse(s: str) -> Optional[int]:  # int | None
    try:
        return int(s)
    except ValueError:
        return None

# Generic types
T = TypeVar('T')

class Stack(Generic[T]):
    def __init__(self) -> None:
        self._items: List[T] = []
    
    def push(self, item: T) -> None:
        self._items.append(item)
    
    def pop(self) -> T:
        return self._items.pop()
```

### 3.3 Concurrency in Python

```python
# Threading (for I/O-bound tasks)
import threading

def worker(name):
    print(f"Worker {name} starting")

threads = [threading.Thread(target=worker, args=(i,)) for i in range(5)]
for t in threads:
    t.start()
for t in threads:
    t.join()

# Multiprocessing (for CPU-bound tasks, bypasses GIL)
from multiprocessing import Pool

def square(x):
    return x ** 2

with Pool(4) as p:
    results = p.map(square, range(10))

# Async/Await (for I/O-bound, single-threaded concurrency)
import asyncio

async def fetch_data(url):
    await asyncio.sleep(1)  # Simulating I/O
    return f"Data from {url}"

async def main():
    tasks = [fetch_data(f"url{i}") for i in range(3)]
    results = await asyncio.gather(*tasks)

asyncio.run(main())
```

**Key Concept: GIL (Global Interpreter Lock)**
- CPython has a GIL that prevents true parallel execution of Python bytecode
- Threading is good for I/O-bound tasks (network, file operations)
- Multiprocessing is needed for CPU-bound parallelism
- Async/await is for concurrent I/O without threads

### 3.4 Common Python Interview Questions

1. **What is the GIL? How does it affect multithreading?**
2. **Difference between `is` and `==`?**
3. **What are `*args` and `**kwargs`?**
4. **How does Python manage memory? What is garbage collection?**
5. **Explain list comprehension vs generator expression.**
6. **What is a decorator? Write a simple caching decorator.**
7. **Difference between `@staticmethod` and `@classmethod`?**
8. **What are dunder (magic) methods? Give examples.**
9. **How do you handle exceptions in Python?**
10. **What is the difference between shallow and deep copy?**

---

## 4. Data Structures & Algorithms

### 4.1 Essential Data Structures

| Data Structure | Operations | Time Complexity | Common Uses |
|----------------|------------|-----------------|-------------|
| Array/Vector | Access, Insert, Delete | O(1), O(n), O(n) | Sequential data |
| Linked List | Access, Insert, Delete | O(n), O(1), O(1) | Frequent insertions |
| Hash Table | Search, Insert, Delete | O(1) avg | Fast lookup |
| Binary Search Tree | Search, Insert, Delete | O(log n) avg | Sorted data |
| Heap | Find min/max, Insert, Delete | O(1), O(log n), O(log n) | Priority queue |
| Graph | Varies by representation | - | Networks, relationships |
| Trie | Search, Insert | O(m) where m=key length | Prefix matching |

### 4.2 Algorithm Patterns

#### Two Pointers
```cpp
// Find pair with target sum in sorted array
bool twoSum(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left < right) {
        int sum = nums[left] + nums[right];
        if (sum == target) return true;
        else if (sum < target) left++;
        else right--;
    }
    return false;
}
```

#### Sliding Window
```cpp
// Maximum sum subarray of size k
int maxSumSubarray(vector<int>& nums, int k) {
    int windowSum = 0, maxSum = 0;
    for (int i = 0; i < nums.size(); i++) {
        windowSum += nums[i];
        if (i >= k - 1) {
            maxSum = max(maxSum, windowSum);
            windowSum -= nums[i - k + 1];
        }
    }
    return maxSum;
}
```

#### Binary Search
```cpp
// Find target or insertion point
int binarySearch(vector<int>& nums, int target) {
    int left = 0, right = nums.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) left = mid + 1;
        else right = mid;
    }
    return left;
}
```

#### DFS and BFS
```cpp
// DFS for graph traversal
void dfs(vector<vector<int>>& graph, int node, vector<bool>& visited) {
    visited[node] = true;
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(graph, neighbor, visited);
        }
    }
}

// BFS for shortest path (unweighted)
int bfs(vector<vector<int>>& graph, int start, int end) {
    queue<int> q;
    vector<int> dist(graph.size(), -1);
    q.push(start);
    dist[start] = 0;
    
    while (!q.empty()) {
        int node = q.front(); q.pop();
        if (node == end) return dist[node];
        
        for (int neighbor : graph[node]) {
            if (dist[neighbor] == -1) {
                dist[neighbor] = dist[node] + 1;
                q.push(neighbor);
            }
        }
    }
    return -1;
}
```

#### Dynamic Programming
```cpp
// Classic: Longest Common Subsequence
int lcs(string& s1, string& s2) {
    int m = s1.size(), n = s2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    return dp[m][n];
}
```

### 4.3 Complexity Analysis

**Big O Cheat Sheet:**

| Complexity | Name | Example |
|------------|------|---------|
| O(1) | Constant | Hash table lookup |
| O(log n) | Logarithmic | Binary search |
| O(n) | Linear | Array traversal |
| O(n log n) | Linearithmic | Merge sort, heap sort |
| O(n²) | Quadratic | Nested loops, bubble sort |
| O(2^n) | Exponential | Recursive Fibonacci |
| O(n!) | Factorial | Generating permutations |

**Space Complexity Considerations:**
- In-place algorithms vs extra space
- Recursive call stack
- Data structure overhead

---

## 5. System Design

### 5.1 System Design Process

1. **Clarify Requirements** (5 min)
   - Functional requirements (what the system does)
   - Non-functional requirements (scale, latency, availability)
   - Constraints and assumptions

2. **High-Level Design** (10 min)
   - Draw main components
   - Define APIs
   - Data flow

3. **Deep Dive** (20 min)
   - Database schema
   - Scaling strategies
   - Caching
   - Message queues

4. **Address Trade-offs** (10 min)
   - CAP theorem considerations
   - Consistency vs availability
   - Cost vs performance

### 5.2 Key Concepts

#### Scaling
- **Vertical scaling**: More powerful machine
- **Horizontal scaling**: More machines
- **Load balancing**: Distribute traffic (round-robin, least connections)
- **Database sharding**: Partition data across multiple databases
- **Replication**: Master-slave, master-master

#### Caching
- **Cache-aside**: Application manages cache
- **Write-through**: Write to cache and DB simultaneously
- **Write-back**: Write to cache, async write to DB
- **TTL (Time-to-Live)**: Expiration strategy
- **Cache invalidation**: Hardest problem in CS!

#### Databases
- **SQL**: ACID, structured data, complex queries
- **NoSQL**: Flexible schema, horizontal scaling
  - Document (MongoDB)
  - Key-value (Redis)
  - Column-family (Cassandra)
  - Graph (Neo4j)

#### Message Queues
- Decouple services
- Handle traffic spikes
- Enable async processing
- Examples: RabbitMQ, Kafka, AWS SQS

### 5.3 Common System Design Questions

For mid-level positions, expect simplified versions:

1. **Design a URL shortener** (like bit.ly)
2. **Design a rate limiter**
3. **Design a cache system**
4. **Design a task scheduler**
5. **Design a file storage service**

For medical software domain:
- Design a DICOM image storage and retrieval system
- Design a treatment planning workflow system
- Design a real-time dose monitoring system

---

## 6. Software Engineering Practices

### 6.1 SOLID Principles

| Principle | Description | C++ Example |
|-----------|-------------|-------------|
| **S**ingle Responsibility | One reason to change | Separate file I/O from parsing |
| **O**pen/Closed | Open for extension, closed for modification | Use virtual functions |
| **L**iskov Substitution | Subtypes must be substitutable | Square shouldn't inherit Rectangle |
| **I**nterface Segregation | Clients shouldn't depend on unused interfaces | Split large interfaces |
| **D**ependency Inversion | Depend on abstractions | Inject interfaces, not concrete classes |

### 6.2 Design Patterns

**Creational:**
- **Singleton**: Single instance (use sparingly!)
- **Factory**: Create objects without specifying exact class
- **Builder**: Construct complex objects step by step

**Structural:**
- **Adapter**: Convert interface to another
- **Decorator**: Add responsibilities dynamically
- **Facade**: Simplified interface to subsystem

**Behavioral:**
- **Observer**: Notify dependents of state changes
- **Strategy**: Interchangeable algorithms
- **Command**: Encapsulate request as object

### 6.3 Testing

```cpp
// GoogleTest example
#include <gtest/gtest.h>

class CalculatorTest : public ::testing::Test {
protected:
    Calculator calc;
};

TEST_F(CalculatorTest, AddPositiveNumbers) {
    EXPECT_EQ(calc.add(2, 3), 5);
}

TEST_F(CalculatorTest, AddNegativeNumbers) {
    EXPECT_EQ(calc.add(-2, -3), -5);
}

// Test-Driven Development (TDD) cycle:
// 1. Write failing test
// 2. Write minimal code to pass
// 3. Refactor
```

```python
# pytest example
import pytest

class TestCalculator:
    def test_add_positive(self):
        calc = Calculator()
        assert calc.add(2, 3) == 5
    
    def test_add_negative(self):
        calc = Calculator()
        assert calc.add(-2, -3) == -5
    
    @pytest.mark.parametrize("a,b,expected", [
        (1, 2, 3),
        (0, 0, 0),
        (-1, 1, 0),
    ])
    def test_add_parametrized(self, a, b, expected):
        calc = Calculator()
        assert calc.add(a, b) == expected
```

### 6.4 Build Systems & CI/CD

**CMake Best Practices:**
```cmake
cmake_minimum_required(VERSION 3.16)
project(MyProject VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Modern target-based approach
add_library(mylib src/mylib.cpp)
target_include_directories(mylib PUBLIC include)
target_compile_features(mylib PUBLIC cxx_std_17)

# FetchContent for dependencies
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Tests
enable_testing()
add_executable(tests tests/test_main.cpp)
target_link_libraries(tests mylib GTest::gtest_main)
add_test(NAME MyTests COMMAND tests)
```

### 6.5 Version Control (Git)

```bash
# Feature branch workflow
git checkout -b feature/new-feature
git add .
git commit -m "Add new feature"
git push origin feature/new-feature
# Create pull request

# Useful commands
git rebase -i HEAD~3      # Interactive rebase last 3 commits
git cherry-pick <hash>    # Apply specific commit
git stash                 # Temporarily store changes
git bisect                # Find bug-introducing commit
```

---

## 7. Domain-Specific Topics

### 7.1 Medical Imaging & DICOM

Given your background, be prepared to discuss:

- **DICOM structure**: Patient → Study → Series → Instance
- **Common DICOM tags**: PatientID, StudyInstanceUID, Modality, PixelData
- **Image processing**: Windowing, resampling, registration
- **ITK/VTK**: Pipeline architecture, filters, visualization
- **Regulatory considerations**: FDA, CE marking, IEC 62304

### 7.2 Scientific Computing

- **Numerical precision**: Float vs double, accumulation errors
- **Linear algebra**: Matrix operations, eigenvalues, SVD
- **Optimization**: Gradient descent, convex optimization
- **Parallel computing**: OpenMP, MPI, GPU computing

---

## 8. Behavioral Interview

### 8.1 STAR Method

- **S**ituation: Set the context
- **T**ask: Describe your responsibility
- **A**ction: Explain what you did
- **R**esult: Share the outcome

### 8.2 Common Questions

Prepare 2-3 stories for each category:

**Technical Leadership:**
- Tell me about a technically challenging project you led.
- Describe a time you had to make a difficult technical decision.
- How do you approach code reviews?

**Teamwork:**
- Describe a conflict with a colleague and how you resolved it.
- Tell me about a time you helped mentor someone.
- How do you handle disagreements about technical approaches?

**Problem Solving:**
- Tell me about a difficult bug you debugged.
- Describe a time you had to learn a new technology quickly.
- How do you handle tight deadlines?

### 8.3 Your Unique Value Proposition

Prepare to articulate:
- Bridge between medical physics domain and software engineering
- Experience with regulated medical software development
- Hands-on experience with ITK, VTK, DICOM
- Understanding of clinical workflows and user needs

---

## 9. Preparation Roadmap

### Phase 1: Foundation Review (Weeks 1-2)

**Week 1: C++ Deep Dive**
- [ ] Review modern C++ features (C++11/14/17)
- [ ] Practice memory management concepts
- [ ] Study STL containers and algorithms
- [ ] Review concurrency primitives

**Week 2: Python Deep Dive**
- [ ] Review Python OOP and design patterns
- [ ] Study decorators, generators, context managers
- [ ] Review type hints and best practices
- [ ] Study async/await and multiprocessing

### Phase 2: Data Structures & Algorithms (Weeks 3-6)

**Daily Practice:**
- Solve 1-2 LeetCode problems daily
- Focus on Medium difficulty
- Practice in both C++ and Python

**Weekly Focus:**
- Week 3: Arrays, Strings, Hash Tables
- Week 4: Linked Lists, Trees, Graphs
- Week 5: Dynamic Programming, Backtracking
- Week 6: System Design basics

### Phase 3: Interview Practice (Weeks 7-8)

**Mock Interviews:**
- Practice with peers or platforms (Pramp, interviewing.io)
- Time yourself (45 minutes per problem)
- Practice thinking aloud

**System Design:**
- Study 2-3 classic system design problems
- Practice drawing diagrams
- Prepare domain-specific examples

### Daily Schedule Template

| Time | Activity |
|------|----------|
| Morning (1h) | LeetCode problem + review |
| Lunch (30m) | Read technical article/documentation |
| Evening (1h) | Concept review or mock interview |

---

## 10. Resources & References

### Books

**C++:**
- "Effective Modern C++" - Scott Meyers
- "C++ Concurrency in Action" - Anthony Williams
- "The C++ Programming Language" - Bjarne Stroustrup

**Python:**
- "Fluent Python" - Luciano Ramalho
- "Python Cookbook" - David Beazley
- "Effective Python" - Brett Slatkin

**Algorithms:**
- "Introduction to Algorithms" (CLRS)
- "Cracking the Coding Interview" - Gayle McDowell
- "Elements of Programming Interviews" (C++ or Python version)

**System Design:**
- "Designing Data-Intensive Applications" - Martin Kleppmann
- "System Design Interview" - Alex Xu

### Online Platforms

**Coding Practice:**
- LeetCode (https://leetcode.com) - Primary recommendation
- HackerRank (https://hackerrank.com)
- CodeSignal (https://codesignal.com)

**Learning:**
- CppCon YouTube channel (C++ conference talks)
- C++ Weekly with Jason Turner (YouTube)
- Real Python (https://realpython.com)

**Mock Interviews:**
- Pramp (https://pramp.com) - Free peer mock interviews
- interviewing.io - Practice with engineers

### Documentation

- C++ Reference: https://en.cppreference.com
- Python Docs: https://docs.python.org/3/
- CMake Documentation: https://cmake.org/documentation/
- GoogleTest: https://google.github.io/googletest/

### YouTube Channels

- **CppCon**: Conference talks on modern C++
- **Back To Back SWE**: Algorithm explanations
- **NeetCode**: LeetCode problem walkthroughs
- **Gaurav Sen**: System design concepts

---

## Quick Reference Card

### C++ Interview Essentials
```
□ Smart pointers (unique_ptr, shared_ptr, weak_ptr)
□ Move semantics and perfect forwarding
□ Virtual functions and polymorphism
□ RAII and exception safety
□ STL containers and their complexities
□ Concurrency (mutex, condition_variable, atomic)
□ Modern features (auto, lambdas, structured bindings)
```

### Python Interview Essentials
```
□ Data structures (list, dict, set, deque)
□ OOP (inheritance, properties, dunder methods)
□ Decorators and context managers
□ Generators and iterators
□ GIL and concurrency options
□ Type hints
□ List comprehensions vs generators
```

### Algorithm Patterns
```
□ Two pointers
□ Sliding window
□ Binary search
□ BFS/DFS
□ Dynamic programming
□ Recursion with memoization
□ Greedy algorithms
```

---

*Good luck with your interview preparation!*
