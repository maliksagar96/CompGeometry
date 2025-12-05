#include <bits/stdc++.h>
using namespace std;

// An event for the sweep line algorithm
class Event {
public:
    int x, y;
    bool isLeft;
    int index;
    Event(int x, int y, bool l, int i) {
        this->x = x;
        this->y = y;
        this->isLeft = l;
        this->index = i;
    }

    // Order events Primarily by y-coordinate, then by x-coordinate
    //This is required otherwise the events can't be arranged in a set according to y-axis.
    bool operator<(const Event &e) const {
        if (y == e.y)
            return x < e.x;
        return y < e.y;
    }
};

// Given three collinear points p, q, r 
// the function checks if point 
// q lies on line segment 'pr'
bool onSegment(vector<int> p, vector<int> q, vector<int> r) {
    if (q[0] <= max(p[0], r[0]) && q[0] >= min(p[0], r[0]) &&
        q[1] <= max(p[1], r[1]) && q[1] >= min(p[1], r[1]))
        return true;
    return false;
}

// To find orientation of ordered triplet (p, q, r).
// Returns 0 if collinear, 1 if clockwise, 2 if counterclockwise.
int orientation(vector<int> p, vector<int> q, vector<int> r) {
    int val = (q[1] - p[1]) * (r[0] - q[0]) -
              (q[0] - p[0]) * (r[1] - q[1]);

     // collinear
    if (val == 0)
        return 0;
    
    // clock- or counterclockwise
    return (val > 0) ? 1 : 2; 
}

// to find if two segments intersect
bool doIntersect(vector<vector<int>> s1, vector<vector<int>> s2) {
    vector<int> p1 = s1[0], q1 = s1[1], p2 = s2[0], q2 = s2[1];

    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    // Special cases
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}

// Returns the predecessor iterator in set s.
set<Event>::iterator pred(set<Event> &s, set<Event>::iterator it) {
    return it == s.begin() ? s.end() : --it;
}

// Returns the successor iterator in set s.
set<Event>::iterator succ(set<Event> &s, set<Event>::iterator it) {
    return ++it;
}

// Returns the number of intersections found between segments.
int isIntersect(vector<vector<vector<int>>> &lines) {

    // To avoid duplicate intersection reports.
    unordered_map<string, int> mp;  

    vector<Event> events;
    int n = lines.size();
    for (int i = 0; i < n; ++i) {

        // Create events for the left and right endpoints.
        events.push_back(Event(lines[i][0][0], lines[i][0][1], true, i));
        events.push_back(Event(lines[i][1][0], lines[i][1][1], false, i));
    }

    // Sort events according to x-coordinate.
    sort(events.begin(), events.end(), [](Event &e1, Event &e2) {
        return e1.x < e2.x;
    });

    // Set for storing active segments.
    set<Event> active;
    int ans = 0;

    // Process all events.
    for (int i = 0; i < 2 * n; i++) {
        Event curr = events[i];
        int index = curr.index;

        if (curr.isLeft) {

            // For the left endpoint, get neighbors in the active set.
            auto next = active.lower_bound(curr);
            auto prev = pred(active, next);

            // Check for intersection with the next segment.
            if (next != active.end() && doIntersect(lines[next->index], lines[index])) {
                string key = to_string(next->index + 1) + " " + to_string(index + 1);
                if (mp.count(key) == 0) {
                    mp[key]++;
                    ans++;
                }
            }

            // Check for intersection with the previous segment.
            if (prev != active.end() && doIntersect(lines[prev->index], lines[index])) {
                string key = to_string(prev->index + 1) + " " + to_string(index + 1);
                if (mp.count(key) == 0) {
                    mp[key]++;
                    ans++;
                }
            }

            // To avoid counting duplicates if the same segment is both neighbor.
            if (prev != active.end() && next != active.end() && next->index == prev->index)
                ans--;

            active.insert(curr);
        } 
        
        else {

            // For the right endpoint, find the matching left endpoint in the active set.
            auto it = active.find(Event(lines[index][0][0], lines[index][0][1], true, index));
            auto next = succ(active, it);
            auto prev = pred(active, it);

            // If both neighbors exist, check if they intersect.
            if (next != active.end() && prev != active.end()) {
                string key1 = to_string(next->index + 1) + " " + to_string(prev->index + 1);
                string key2 = to_string(prev->index + 1) + " " + to_string(next->index + 1);
                if (mp.count(key1) == 0 && mp.count(key2) == 0 && doIntersect(lines[prev->index], lines[next->index]))
                  ans++;
                mp[key1]++;
            }

            // Remove the segment from the active set.
            active.erase(it);
        }
    }

    // Report all intersecting pairs.
    for (auto &pr : mp) {
        cout << "Line: " << pr.first << "\n";
    }
    return ans;
}

int main() {
    vector<vector<vector<int>>> lines = {
        { {1, 5}, {4, 5} },
        { {2, 5}, {10, 1} },
        { {3, 2}, {10, 3} },
        { {6, 4}, {9, 4} },
        { {7, 1}, {8, 1} }
    };
    cout << isIntersect(lines);
    return 0;
}