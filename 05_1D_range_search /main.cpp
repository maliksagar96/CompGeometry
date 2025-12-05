#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

struct Node {

  Node(int val):val(val), left(nullptr), right(nullptr){}
  Node(int val, Node *left, Node *right):val(val), left(left), right(right) {}
  int val;
  Node *left, *right;

  //Returns true for a leaf
  bool isLeaf(Node *node) {
    return ((node->left == nullptr) && (node->right == nullptr));
  };
};

Node *BalancedBST(vector<int> &points, int l, int r) {
  if (l >= r) return nullptr;

  int mid = (l + r) / 2;
  Node *node = new Node(points[mid]);

  node->left = BalancedBST(points, l, mid);
  node->right = BalancedBST(points, mid+1, r);

  return node;
}

void printBFS(Node *node) {

  if(!node) return;

  queue<Node*> q;
  q.push(node);

  while(!q.empty()) {
    Node *n = q.front();  
    cout<<n->val<<endl;
    q.pop();

    if(n->left != nullptr) q.push(n->left);
    if(n->right != nullptr) q.push(n->right);
  }

}

void printDFS(Node *node) {
  if(!node) return;

  printDFS(node->left);
  cout<<node->val<<endl;
  printDFS(node->right);

}

Node* buildBottomUp(const vector<int> &a) {
  int n = a.size();
  if(n == 0) return nullptr;

  // step 1: make all leaves
  vector<Node*> level;
  for(int x : a) level.push_back(new Node(x));

  // step 2: repeatedly build parent level
  while(level.size() > 1) {
    vector<Node*> next;

    for(int i = 0; i < (int)level.size(); i += 2) {
      if(i + 1 == (int)level.size()) {
        // odd element → move up directly
        next.push_back(level[i]);
      } else {
        // create parent whose left is level[i]
        // and right is level[i+1]
        int parentVal = level[i]->val;  // “highest in left subtree”
        Node *p = new Node(parentVal);
        p->left  = level[i];
        p->right = level[i+1];
        next.push_back(p);
      }
    }

    level = next;
  }

  return level[0]; // root
}

int main() {

  // vector<int> inputPoints = {5, 1, 6, 4, 7, 12, 10, 15, 20, 31, 22, 44, 30, 18};
  // vector<int> inputPoints = {1,2,3,4,5,6,7,8,9,10,11};
  // vector<int> inputPoints = {1,3,5,7};
  vector<int> inputPoints = {3,10, 19, 23, 30, 37, 49, 59, 62, 70, 80, 100, 105};

  sort(inputPoints.begin(), inputPoints.end());

  int sz = inputPoints.size();
  int mid = sz/2;

  //Defining root
  // Node *root = BalancedBST(inputPoints, 0, sz);
  Node *root = buildBottomUp(inputPoints);

  printDFS(root);

}