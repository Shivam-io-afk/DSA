# Array vs Linked List

This document highlights the differences between **Array** and **Linked List** in programming.

---

## 1. Structure
- **Array**:
  - A collection of elements stored in **contiguous memory locations**.
  - Each element can be accessed using its index.
- **Linked List**:
  - A collection of nodes where each node contains the data and a **pointer** to the next node.
  - Nodes are stored in **non-contiguous memory locations**.

---

## 2. Memory Allocation
- **Array**:
  - Uses **static memory allocation** (fixed size at compile time) or **dynamic memory allocation**.
  - Has a fixed size in static arrays.
- **Linked List**:
  - Uses **dynamic memory allocation**.
  - Size can grow or shrink dynamically as needed.

---

## 3. Access Time
- **Array**:
  - **O(1)** (constant time) for accessing elements by index due to contiguous memory storage.
- **Linked List**:
  - **O(n)** (linear time) for accessing elements, as traversal is required to reach a specific node.

---

## 4. Insertion and Deletion
- **Array**:
  - Insertion or deletion requires **shifting elements**, making it **O(n)** in time complexity.
  - Not efficient for frequent insertions or deletions.
- **Linked List**:
  - Insertion and deletion are faster, requiring **O(1)** (if the node pointer is already available).
  - Traversal to locate a node (if needed) takes **O(n)**.

---

## 5. Memory Usage
- **Array**:
  - Uses less memory overhead since it stores only the data elements.
- **Linked List**:
  - Requires extra memory for the pointer(s) in each node.
  - May lead to memory fragmentation due to non-contiguous storage.

---

## 6. Flexibility
- **Array**:
  - Fixed size in static arrays.
  - Resizing requires copying elements to a new memory block (in dynamic arrays).
- **Linked List**:
  - Highly flexible; size can easily change with insertions and deletions.

---

## 7. Traversal
- **Array**:
  - Easy to traverse using indices.
- **Linked List**:
  - Requires pointer navigation, which can be more complex and slower.

---

## 8. Variants
- **Array**:
  - Variants include one-dimensional, multi-dimensional (2D, 3D, etc.), and dynamic arrays (e.g., vectors in C++, ArrayList in Java).
- **Linked List**:
  - Variants include singly linked lists, doubly linked lists, and circular linked lists.

---

## Summary Table

| Feature             | Array                  | Linked List             |
|----------------------|------------------------|-------------------------|
| **Memory**           | Contiguous             | Non-contiguous          |
| **Access Time**      | O(1)                  | O(n)                   |
| **Insertion/Deletion** | O(n) (due to shifting) | O(1) (if node is known) |
| **Resizing**         | Requires reallocation  | Dynamic resizing        |
| **Memory Overhead**  | Less                   | More (due to pointers)  |

---

## When to Use?
- Use **Arrays** when:
  - You need frequent direct access to elements.
  - The number of elements is fixed or known in advance.
- Use **Linked Lists** when:
  - Frequent insertions and deletions are required.
  - The total size of data is unknown or variable.
