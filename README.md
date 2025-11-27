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
</details>

<details><summary><strong>Problem 3 — Ray Tracing</strong></summary><br>

Ever wondered how your GPU figures out whether a ray of light hits a triangle in a 3D scene?

It’s basically asking:

**“If I shoot a laser from point A in direction B… does it smack into this triangle?”**

Turns out—yes, there’s math for that 😄
Enter one of the coolest little formulas in computer graphics…

---

## 🎯 Ray–Triangle Intersection (a.k.a. “Did we hit it?”)

A ray in 3D is just:

**L(t) = p₀ + t·v₀**
→ starting point + direction × constant

A triangle can be described as:

**T(u, v) = A + u(B − A) + v(C − A)**
with the rules:
`u ≥ 0`,
`v ≥ 0`,
`u + v ≤ 1`
(meaning the point lies inside the triangle).

To find the intersection, we simply set **L = T** and solve for *(t, u, v)*.

Simple?
Yes.
Fast?
…not quite.

---

## ⚡ The Möller–Trumbore Magic

In their legendary paper
**“Fast, Minimum Storage Ray–Triangle Intersection”**
Tomas Möller and Ben Trumbore took the slow algebraic mess and turned it into a **blazingly fast**, branch-friendly algorithm.

How?
By cleverly rearranging Cramer's rule and using cross/dot products like ninjas 🥷✨

### 🧠 The Algorithm in Super-Brief:

1. Compute triangle edges:
   `e1 = B − A`
   `e2 = C − A`
2. Use a cross product to detect if the ray is **parallel** (early reject).
3. Solve for barycentric coordinates **u** and **v**.
4. Check if the point is inside the triangle (`u ≥ 0`, `v ≥ 0`, `u + v ≤ 1`).
5. Solve for **t** → gives you the intersection point on the ray.

Fast, clean, and still used everywhere in real-time graphics today.
A true classic.

---

## 📂 Relevant Code

The full implementation lives in the folder:
**`03_ray_tracing`**

Dive in and play with it — it’s one of the most satisfying algorithms in computational geometry!

</details>
