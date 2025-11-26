## 🧩 Some Computational Geometry Problems

<details> <summary><strong>Problem 1 — Convex Hull</strong></summary> <br>

Imagine a bunch of nails randomly hammered into a wooden board. Now stretch a rubber band, loop it around all the nails, and let go.
It snaps into place around the **outermost nails** — forming a neat, tight boundary.

That boundary is the **convex hull**.
It’s the smallest wrap-around shape that contains all the points, without any dents or inward folds.
Simple idea, beautiful geometry ✨

---

## 🪓 Brute Force Solution

The brute force way?
Pick every pair of points, draw a line, and check if all other points lie on one side of it.
The logic is simple — the speed is *not*.

* Picking every pair → **O(n²)**
* Checking all other points → **O(n)**
* Total → **O(n³)**

This is **damn slow** 😅
So…

## ⚡ Let’s speed this up 🔥

### **1) Incremental Approach**

A faster method is to build the hull step by step.

#### **Algorithm**

1. **Sort** the points by `x` (and by `y` if `x` is the same).
2. Add the first two sorted points to the hull.
3. Add a third point that's not collinear with the first two.
4. Now loop over all points:

   * Add a point to the hull.
   * Check if the **last 3 points make a left turn**.

     * How to check this?
       Compute the **cross product** of the last two segments.

       * Cross product **> 0** → right turn
       * Cross product **< 0** → left turn
   * If it's a left turn, remove the middle point.
   * Repeat until the hull is convex again.

This builds the **upper hull** smoothly.

#### Example:

```cpp
vector<Point> inputPoints = {
  {0, 0},
  {1, 1},
  {2, 0},
  {3, 1}
};
```

