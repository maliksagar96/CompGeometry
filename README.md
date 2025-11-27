## 🧩 Some Computational Geometry Problems

## 🟦 Problem 1 — Convex Hull

<details><summary><strong>Wrapping a rubber band around your data 📦✨</strong></summary><br>

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

## 🔦 Problem 3 — Ray Tracing

<details><summary><strong>Teaching light how to behave 🌈💡</strong></summary><br>

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


## 🧲 Problem 4 — Closest Pair of Points

<details><summary><strong>Who’s the closest pair in the room?</strong></summary><br>

Imagine you’re hosting a big party 🎉
There are *n* people scattered all across the room (each with coordinates x, y, z — fancy 3D party!).

Your job?

👉 **Find the two people standing closest to each other.**
No cheating. No “just eyeballing it.”
We need the actual minimum Euclidean distance.

Sounds simple, right?

Well…

---

## 🪓 Brute Force? More like Brutal Force

The simplest (and dumbest) plan:

1. Take every person.
2. Compare them with every other person.
3. Compute all distances.
4. Cry when `n = 10,000` because this is **O(n²)**.

This is like saying:

> “Let me ask every pair of people if they’re best friends.”

Fun for small parties.
Disaster for concerts. 😭

---

## ⚡ Divide and Conquer to the Rescue 🚀

Instead of checking everything, let’s use some **algorithmic Jedi magic**.

### Step 1 — Sort by X

Line everyone up from left to right.
No chaos. No elbows.

### Step 2 — Split the room

Cut the room into two halves.

Left side 👈
Right side 👉

And recursively find:

* Closest pair on the left
* Closest pair on the right

Pick the better one.

So far so good. But wait…

---

## 🧠 The Sneaky Part — The Strip Trick

This is where the beauty kicks in 😍

The true closest pair
**might be standing at the border between left and right!**

So we:

1. Build a vertical **strip** around the dividing line.
2. Only include people whose x-coordinate is within `d` of the middle
   (where `d` is the best distance we’ve found so far).
3. Now check distances *only* inside the strip.

Why does this work?

Because geometry says:

> “If two points are closer than d, they must live in that narrow strip.”

So instead of checking thousands, you're checking a tiny handful.

Result?

A glorious **O(n log n)** algorithm 🎉✨

---

## 🧾 Final Takeaway

Closest pair of points isn’t just a problem.
It’s a *story* about:

* Splitting the world
* Checking fewer things
* Letting geometry do the heavy lifting
* And respecting personal space 😄

Efficient, elegant, and surprisingly fun.

</details>

