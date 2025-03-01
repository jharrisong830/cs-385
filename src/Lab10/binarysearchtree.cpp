#include <iostream>
#include <limits>
#include <queue>
#include <algorithm> // for max
using namespace std;

struct Node {
	Node *parent, *left, *right;
	int depth, data;

	Node(int depth, int data) :
		parent{nullptr}, left{nullptr}, right{nullptr},
		depth{depth}, data(data) { }

	Node(Node *parent, int depth, int data) :
		parent{parent}, left{nullptr}, right{nullptr},
		depth{depth}, data{data} { }
};

// O(tree height) (and the tree height is O(n))
Node* insert_helper(Node **proot, int x, Node *parent, int depth) {
	if(*proot == nullptr) {
		return *proot = new Node(parent, depth, x);
	}
	if((*proot)->data == x) {
		return nullptr;
	}
	if(x < (*proot)->data) {
		return insert_helper(&(*proot)->left, x, *proot, depth + 1);
	} else {
		return insert_helper(&(*proot)->right, x, *proot, depth + 1);
	}
}

Node* insert(Node **proot, int x) {
	return insert_helper(proot, x, nullptr, 0);
}

// Θ(n)
void display_sideways(Node *node) {
	if(node != nullptr) {
		display_sideways(node->right);
		if(node->depth == 0) {
			cout << "-> ";
		} else {
			cout << "   ";
		}
		for(int i = 0; i < node->depth; ++i) {
			cout << "   ";
		}
		cout << node->data << endl;
		display_sideways(node->left);
	}
}

// O(tree height) (and the tree height is O(n))
Node* find(Node *root, int x) {
	if(root == nullptr) {
		return nullptr;
	}
	if(root->data == x) {
		return root;
	}
	if(x < root->data) {
		return find(root->left, x);
	} else {
		return find(root->right, x);
	}
}

// Sum all integers in the BST
// Θ(n)
int sum(Node *root) {
	if(root == nullptr) {
		return 0;
	} else {
		return root->data + sum(root->left) + sum(root->right);
	}
}

// Θ(n)
void decrement_depths(Node *root) {
	if(root) {
		root->depth--;
		decrement_depths(root->left);
		decrement_depths(root->right);
	}
}

// Deletes and returns as result the minimum node in the non-empty tree.
// Since the tree is non-empty, such minimum node must exist.
// This code is similar to findMin except that we do not have to test
// the Null case since we know that the tree is non-empty.
// O(tree height) (and the tree height is O(n))
Node *delete_min(Node **proot) {
	if((*proot)->left == nullptr) {
		// root is the minimum node, remove it from the tree and return it
		Node *min = *proot;
		decrement_depths((*proot)->right);
		*proot = (*proot)->right;
		return min;
	} else {
		// Keep moving down-left
		return delete_min(&(*proot)->left);
	}
}

// O(tree height) (and the tree height is O(n))
bool delete_node(Node **proot, int x){
	if(*proot == nullptr) {
		// Cannot find x, deletion fails
		return false;
	}
	if((*proot)->data == x) {
		// Case 1: the node is a leaf
		// Note: this case is in fact a special case of the next one (case 2-a
		// or case 2-b) so this code could be merged with the next case.
		// We keep this case separate here for clarity.
		if((*proot)->left == nullptr && (*proot)->right == nullptr) {
			delete *proot;
			*proot = nullptr;
			return true;
		}
		// Case 2-a: the node has one left child
		if((*proot)->left != nullptr && (*proot)->right == nullptr) {
			Node *tmp = *proot;
			decrement_depths((*proot)->left);
			*proot = (*proot)->left;
			delete tmp;
			return true;
		}
		// Case 2-b: the node has one right child
		if((*proot)->left == nullptr && (*proot)->right != nullptr) {
			Node *tmp = *proot;
			decrement_depths((*proot)->right);
			*proot = (*proot)->right;
			delete tmp;
			return true;
		}
		// Case 3: the node has two children
		// We replace the root with the minimum node in the right subtree
		// (The maximum node in the left subtree would work too.)
		if((*proot)->left != nullptr && (*proot)->right != nullptr) {
			Node *tmp = *proot;
			// Find the smallest node in the right subtree:
			Node *min = delete_min(&(*proot)->right);
			// Replace the root with the min:
			min->parent = (*proot)->parent;
			min->depth = (*proot)->depth;
			min->left = (*proot)->left;
			min->right = (*proot)->right;
			*proot = min;
			delete tmp;
			return true;
		}
	}
	if((*proot)->data > x) {
		return delete_node(&(*proot)->left, x);
	} else {
		return delete_node(&(*proot)->right, x);
	}
}

// Θ(n)
void delete_bst(Node *root) {
	if(root != nullptr) {
		delete_bst(root->left);
		delete_bst(root->right);
		delete root;
	}
}

// Create a balanced BST from a sorted array.
// Θ(n)
Node* create_bst_helper(int data[], int low, int high, Node *parent, int depth) {
	if(low > high) {
		return nullptr;
	}
	int mid = low + (high - low) / 2;
	Node *new_node = new Node(parent, depth, data[mid]);
	new_node->left = create_bst_helper(data, low, mid - 1, new_node, depth + 1);
	new_node->right = create_bst_helper(data, mid + 1, high, new_node, depth + 1);
	return new_node;
}

Node* create_bst(int data[], int length) {
	return create_bst_helper(data, 0, length - 1, nullptr, 0);
}

/* We need min and max to ensure that the binary search tree property
   is respected by the tree: data values in the tree must increase
   from left to right.  For example, in the tree:
         5
       /   \
      3     6
    /   \
   2     4
   we need to make sure that 4 is bigger than 3 but also less than 5.
   O(n)
 */
bool is_bst_helper(Node *root, int min, int max) {
	if(root == nullptr) {
		return true;
	}
	if(root->data <= min || root->data >= max) {
		return false;
	}
	return is_bst_helper(root->left, min, root->data) &&
			is_bst_helper(root->right, root->data, max);
}

bool is_bst(Node *tree) {
	return is_bst_helper(tree, std::numeric_limits<int>::min(),
			std::numeric_limits<int>::max());
}

// O(tree height)
Node* lowest_common_ancestor(Node *p, Node *q) {
	if(p == nullptr || q == nullptr) {
		return nullptr;
	}
	if(p == q) {
		return p;
	}
	if(p->depth > q->depth) {
		return lowest_common_ancestor(p->parent, q);
	}
	if(p->depth < q->depth) {
		return lowest_common_ancestor(p, q->parent);
	}
	return lowest_common_ancestor(p->parent, q->parent);
}

// Similar to breadth-first search in a graph. Note that this algorithm is
// not recursive because we need to count all the nodes at the same depth
// in many different parts of the tree at the same time.
// Θ(n)
int max_width(Node *root) {
	if(root == nullptr) {
		return 0;
	}
	int max_width = 0;
	queue<Node*> q;
	q.push(root);

	// Every time around the while loop, the queue contains all the nodes
	// at the current depth, starting from the depth of the root.
	while(!q.empty()) {
		int width = q.size(); // width of current level
		max_width = max(max_width, width);
		// Remove from the queue all the nodes from the current level and add
		// all their children (if any) to get all the nodes for the next level.
		for(int i = 0; i < width; i++) {
			Node *current = q.front();
			q.pop();
			if(current->left != nullptr) {
				q.push(current->left);
			}
			if(current->right != nullptr) {
				q.push(current->right);
			}
		}
	}
	return max_width;
}

// Find the node with the smallest value (so the leftmost node).
// O(tree height)
Node* find_min(Node *root) {
	if(root == nullptr) {
		return nullptr;
	}
	if(root->left == nullptr) {
		return root;
	} else {
		// Keep moving down-left
		return find_min(root->left);
	}
}

/* Finds the successor of a node: the node containing the value which
   is the next higher one relative to the value in the argument node.
         7
       /   \
      3     9
    /   \
   1     5
   For example 5 is the successor of 3 and 7 is the successor of 5.
   O(tree height)
 */
Node* successor(Node *node) {
	if(node == nullptr) {
		return nullptr;
	}
	// If the node has a right subtree then the successor of the node
	// is the node with the smallest value in the right subtree.
	if(node->right != nullptr) {
		return find_min(node->right);
	}
	// Otherwise we move up the parent links as long as each node is its
	// parent's right child. When a node is the left child of its parent,
	// the parent of that node is the successor of the original node.
	Node *parent = node->parent;
	while(parent != nullptr && node == parent->right) {
		node = parent;
		parent = node->parent;
	}
	// At this point either parent is NULL (so there is no successor)
	// or the original node is the biggest value in the left subtree of
	// parent and therefore parent is the successor of the original node.
	return parent;
}




// LAB 10 CODE

bool find_next_equal_node(Node *t1, Node *t2) {
	cout<<"finding node in t1 equal to "<<t2->data<<endl;
	while(t1!=nullptr) {
		if(t1->data == t2->data) {
			cout<<"found!"<<endl;
			return true;
		}
		t1=successor(t1);
	}
	cout<<"none found!"<<endl;
	return false;
}

bool contains_tree(Node *t1, Node *t2) {
	bool tree=true;
	while(t2->left!=nullptr) {
		t2=t2->left;
	}
	cout<<"leftmost in t2 is "<<t2->data<<endl;
	while(t1->left!=nullptr) {
		t1=t1->left;
	}
	cout<<"leftmost in t1 is "<<t1->data<<endl;
	if(find_next_equal_node(t1, t2)) {
		while(t1->data != t2->data) {
			t1=successor(t1);
		}
	}
	else {
		tree=false;
		cout<<"HAHAHAHHA"<<endl;
	}

	while(tree) {
		if((t1->data == t2->data)) {
			cout<<"nodes = "<<t1->data<<" and "<<t2->data<<", moving on!"<<endl;
			t1=successor(t1);
			t2=successor(t2);
			cout<<"continuing with new successors..."<<endl;
		}
		else if(t1==nullptr && t2==nullptr) {
			cout<<"we've reached the end (return true!)"<<endl;
			break;
		}
		else if(find_next_equal_node(t1, t2)) {
			while(t1->data != t2->data) {
				t1=successor(t1);
			}
		}
		else {
			cout<<"oops! no more equal nodes! (exiting)"<<endl;
			tree=false;
		}
	}

	cout<<"end of function"<<endl;
	if(tree) {
		return true;
	}
	return false;
}

int main(int argc, const char *argv[]) {
	/*Node *bst1 = nullptr;
	insert(&bst1, 3);
	insert(&bst1, 5);
	insert(&bst1, 2);
	display_sideways(bst1);
	cout << endl;
	cout << "finding " << find(bst1, 5)->data << endl;
	cout << "sum is " << sum(bst1) << endl;
	cout << "deleting 3:" << endl << endl;
	delete_node(&bst1, 3);
	display_sideways(bst1);
	cout << endl;
	cout << "deleting 5:" << endl << endl;
	delete_node(&bst1, 5);
	display_sideways(bst1);
	cout << endl;
	delete_bst(bst1);
	bst1 = nullptr;

	int data[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	Node *bst2 = create_bst(data, 15);
	display_sideways(bst2);
	cout << endl << "Is BST? " << (is_bst(bst2) ? "yes" : "no") << endl << endl;

	Node *lca = lowest_common_ancestor(find(bst2, 6), find(bst2, 11));
	cout << "Lowest common ancestor of 6 and 11: " << lca->data << endl << endl;

	cout << "bst2 has a max width of " << max_width(bst2) << endl << endl;

	cout << "successor of 8 is " << successor(find(bst2, 8))->data << endl;
	cout << "successor of 7 is " << successor(find(bst2, 7))->data << endl << endl;

	delete_bst(bst2);*/

	Node *bst1=nullptr;
	insert(&bst1, 5);
	insert(&bst1, 1);
	insert(&bst1, 10);
	insert(&bst1, 9);
	insert(&bst1, 11);
	insert(&bst1, 20);

	Node *bst2=nullptr;
	insert(&bst2, 10);
	insert(&bst2, 9);
	insert(&bst2, 11);
	insert(&bst2, 20);

	display_sideways(bst1);
	cout<<endl<<endl<<endl;
	display_sideways(bst2);

	if(contains_tree(bst1, bst2)) {
		cout<<"True!"<<endl;
	}
	else {
		cout<<"False!"<<endl;
	}
	return 0;
}
