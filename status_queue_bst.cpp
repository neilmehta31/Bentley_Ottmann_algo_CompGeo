#include <bits/stdc++.h>
#include "utils.h"
using namespace std;

class statusQueueNode {
public:
    segment seg;
    statusQueueNode *left, *right;
    int ht;

    statusQueueNode(segment seg) {
        this->seg = seg;
        left = right = NULL;
        ht = 1;
    }
};

int compare (segment const &s1, segment const &s2)
{
    if(s1.pstart.x < s2.pstart.x)
        return -1;
    if(s1.pstart.x > s2.pstart.x)
        return 1;
    if(s1.pend.x < s2.pend.x)
        return -1;
    if(s1.pend.x > s2.pend.x)
        return 1;
    return 0;
}
 

int height(statusQueueNode *node) {
    return (node == NULL)? 0: node->ht;
}

statusQueueNode *leftRotate(statusQueueNode *node)
{
    statusQueueNode *right = node->right;
    statusQueueNode *right_left = right->left;

    right->left = node;
    node->right = right_left;

    node->ht = 1 + max(height(node->left), height(node->right));
    right->ht = 1 + max(height(right->left), height(right->right));

    return right;
}

statusQueueNode *rightRotate(statusQueueNode *node)
{
    statusQueueNode *left = node->left;
    statusQueueNode *left_right = left->right;

    left->right = node;
    node->left = left_right;
    
    node->ht = 1 + max(height(node->left), height(node->right));
    left->ht = 1 + max(height(left->left), height(left->right));
    
    return left;
}

int getBalance(statusQueueNode *node) {
    return (node == NULL)? 0: height(node->left) - height(node->right);
}

statusQueueNode* insert(statusQueueNode* node, segment s)
{
    if (node == NULL)
        return new statusQueueNode(s);
    
    int compared_val = compare(s, node->seg);
    if (compared_val < 0)
        node->left = insert(node->left, s);
    else if (compared_val > 0)
        node->right = insert(node->right, s);
    else
        return node;

    node->ht = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1) {
        if(compare(s, node->left->seg) > 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        else
            return rightRotate(node);
    }

    if (balance < -1) {
        if(compare(s, node->right->seg) < 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        else 
            return leftRotate(node);
    }
    
    return node;
}

statusQueueNode* getInorderSuccessor(statusQueueNode* node)
{
    statusQueueNode* curr = node;

    while (curr->left)
        curr = curr->left;

    return curr;
}

statusQueueNode* deleteNode(statusQueueNode* root, segment s)
{
    if (root == NULL)
        return root;

    int compared_val = compare(s, root->seg);
    if (compared_val < 0)
        root->left = deleteNode(root->left, s);

    else if(compared_val > 0)
        root->right = deleteNode(root->right, s);

    else {
        if(root->left == NULL) {
            statusQueueNode* temp = root->right;
            free(root);
            root = temp;
        }
        else if(root->right == NULL) {
            statusQueueNode* temp = root->left;
            free(root);
            root = temp;
        }
        else {
            statusQueueNode* inorderSuccessor = getInorderSuccessor(root->right);
            (*root).seg.pstart.x = (*inorderSuccessor).seg.pstart.x;
            (*root).seg.pstart.y = (*inorderSuccessor).seg.pstart.y;
            (*root).seg.pend.x = (*inorderSuccessor).seg.pend.x;
            (*root).seg.pend.y = (*inorderSuccessor).seg.pend.y;

            root->right = deleteNode(root->right, inorderSuccessor->seg);
        }
    }

    if (root == NULL)
        return root;
    
    root->ht = 1 + max(height(root->left), height(root->right));
    
    int balance = getBalance(root);
    
    if (balance > 1) {
        if(getBalance(root->left) >= 0)
            return rightRotate(root);  
        else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }

    if (balance < -1) {
        if(getBalance(root->right) <= 0)
            return leftRotate(root);
        else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
        
    return root;
}

statusQueueNode* getMinValue(statusQueueNode* node)
{
    statusQueueNode* current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

statusQueueNode* getMaxValue(statusQueueNode* node)
{
    statusQueueNode* current = node;
    while (current->right != NULL) {
        current = current->right;
    }
    return current;
} 

statusQueueNode* getLeftNeighbor(statusQueueNode* root, statusQueueNode n)
{
    if (n.left != NULL)
        return getMaxValue(n.left);
    
 
    statusQueueNode* succ = NULL;

    while (root != NULL) {
        int compare_val = compare(n.seg, root->seg);
        if (compare_val < 0)
        {
            succ = root;
            root = root->left;
        }
        else if (compare_val > 0)
            root = root->right;
        else
            break;
    }
 
    return succ;
}

statusQueueNode* getRightNeighbor(statusQueueNode* root, statusQueueNode* n)
{
    if (n->right != NULL)
        return getMinValue(n->right);
 
    statusQueueNode* succ = NULL;

    while (root != NULL) {
        int compare_val = compare(n->seg, root->seg);
        if (compare_val < 0)
        {
            succ = root;
            root = root->left;
        }
        else if (compare_val > 0)
            root = root->right;
        else
            break;
    }
    
    return succ;
}

void inOrder(statusQueueNode *root) {
    if(root == NULL)
        return;
        
    inOrder(root->left);
    cout <<"("<< (*root).seg.pstart.x <<","<< (*root).seg.pstart.y <<" "<< (*root).seg.pend.x <<","<<(*root).seg.pend.y <<") ";
    inOrder(root->right);
}

// vector<statusQueueNode*> getNeighbors(statusQueueNode* root, segment s) 
// {
//     vector<statusQueueNode*> res;

//     // res.push_back(getLeftNeighbor(root, s));
//     res.push_back(getRightNeighbor(root, s));

//     return res;
// }

statusQueueNode* getAddress(statusQueueNode* root, segment seg) {
    if(root == NULL)
        return NULL;
    int compare_val = compare(root->seg, seg);
    if(compare_val < 0) 
        return getAddress(root->right, seg);
    else if(compare_val > 0) 
        return getAddress(root->left, seg);
    else
        return root;
}

int main()
{
    statusQueueNode* root = NULL;

    ifstream fin;
	// ofstream fout;
	
	double x1, y1, x2, y2;
	fin.open("input.txt");

	vector<segment> lseg; //Line segments array

	while (!fin.eof()) {
		fin>>x1>>y1>>x2>>y2;
        point p1;
        point p2;
    	segment s;

        p1.x = x1; p1.y = y1;
        p2.x = x2; p2.y = y2;
        if(y1>y2){
            s.pstart = p1;
            s.pend = p2;
        }else if(y1==y2){
            if(x1<x2){
                s.pstart = p1;
                s.pend = p2;
            }else{
                s.pstart = p2;
                s.pend = p1;
            }
        }else{
            s.pstart = p2;
            s.pend = p1;
        }
        lseg.push_back(s);
	}
	fin.close();

    // now the segment is lseg[i]!!


    // segment s2= {1, 0, 1, 1};
    // segment s3= {0, 0, 2, 1};
    for(auto seg: lseg) {
        root = insert(root, seg);
    }

    // inOrder(root); 
    // cout << endl;

    // root = deleteNode(root, lseg[1]);

    segment s
    statusQueueNode* seg = getAddress(root, seg);
    cout << getRightNeighbor(root, seg);

    // vector<statusQueueNode*> neighbors = getNeighbors(root, lseg[2]);
    
    // for(auto neighbor: neighbors) {
    //     cout << neighbor <<" ";
    //      cout <<"("<< (*neighbor).seg.pstart.x; 
    // <<","<< (*neighbor).seg.pstart.y <<" "<< (*neighbor).seg.pend.x <<","<<(*neighbor).seg.pend.y <<") ";   
    // }

    // root = insert(root, s1);
    // root = insert(root, s2);
    // root = insert(root, s3);
    // inOrder(root); 
    // cout << endl;
}