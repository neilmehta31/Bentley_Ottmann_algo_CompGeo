#include <bits/stdc++.h>
#include "node.h"
using namespace std;

int height(Node *node) {
    return (node == NULL)? 0: node->ht;
}

int getBalance(Node *node) {
    return (node == NULL)? 0: height(node->left) - height(node->right);
}

Node *leftRotate(Node *node)
{
    Node *right = node->right;
    Node *right_left = right->left;

    right->left = node;
    node->right = right_left;

    node->ht = 1 + max(height(node->left), height(node->right));
    right->ht = 1 + max(height(right->left), height(right->right));

    return right;
}

Node *rightRotate(Node *node)
{
    Node *left = node->left;
    Node *left_right = left->right;

    left->right = node;
    node->left = left_right;
    
    node->ht = 1 + max(height(node->left), height(node->right));
    left->ht = 1 + max(height(left->left), height(left->right));
    
    return left;
}

Node* insert(Node* node, int X, int Y)
{
    if (node == NULL) {
        Node* curr = new Node(X, Y);
        curr->left = new Node(X, Y);
        curr->ht = 2;
        return curr;
    }
    
    if (X < node->X)
        node->left = insert(node->left, X, Y);
    else if (X > node->X)
        node->right = insert(node->right, X, Y);
    else
        return node;

    node->ht = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);
    
    if (balance > 1)
        return rightRotate(node);

    if (balance < -1)
        return leftRotate(node);
    
    return node;
}

void inOrder(Node *root) 
{
    if(root == NULL)
        return;
        
    inOrder(root->left);
    cout <<"("<< root->X <<" "<< root->Y << ") ";
    inOrder(root->right);
}

void levelOrder(Node* root) {
    queue<Node*> que;
    que.push(root);

    while(!que.empty()) {
        int n = que.size();
        while(n--) {
            Node* curr = que.front();
            que.pop();
            cout <<"("<< curr->X <<" "<< curr->Y << ") ";

            if(curr->left)
                que.push(curr->left);
            if(curr->right)
                que.push(curr->right);
        }
        cout <<"   ";
    }
    
    cout << endl;
}

Node* getInorderSuccessor(Node* node)
{
    Node* curr = node;

    while (curr->left)
        curr = curr->left;
 
    return curr;
}

bool isLeaf(Node* node) {
    return (node->left == NULL && node->right == NULL);
}

Node* deleteNode(Node* root, int X, int Y)
{
    if (root == NULL)
        return root;

    if (Y < root->Y || (Y == root->Y && X > root->X) || (Y == root->Y && X == root->X && !isLeaf(root)))
        root->left = deleteNode(root->left, X, Y);

    else if(Y > root->Y || (Y == root->Y && X < root->X))
        root->right = deleteNode(root->right, X, Y);
    
    else {
        free(root);
        return NULL;
    }

    if(root->X == X && root->Y == Y) {
        if(root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
    }

//     else {
//         if(root->left == NULL) {
//             Node* temp = root->right;
//             free(root);
//             root = temp;
//         }
//         else if(root->right == NULL) {
//             Node* temp = root->left;
//             free(root);
//             root = temp;
//         }
//         else {
//             Node* inorderSuccessor = getInorderSuccessor(root->right);
//             root->X = inorderSuccessor->X;
//             root->Y = inorderSuccessor->Y;
//             root->right = deleteNode(root->right, inorderSuccessor->X, inorderSuccessor->Y);
//         }
//     }
 
//     if (root == NULL)
//         return root;
    
//     root->ht = 1 + max(height(root->left), height(root->right));
    
//     int balance = getBalance(root);
//     cout << "yoo";
//     if (balance > 1) {
//         if(X > root->left->X)
//             return rightRotate(root);  
//         else {
//             root->left = leftRotate(root->left);
//             return rightRotate(root);
//         }
//     }
//     cout << "yoo";

//     if (balance < -1) {
//         cout << "yoo";
//         if(root->left->right) {
//             Node* temp = root->left;
//             root->left = temp->right;
//             temp->right = root;
//             return root;
//         }
//         else {
//             Node* temp = root->left;
//             temp->right = root;
//             root->left = NULL;
//             return temp;
//         }
//     }
        
    return root;
}

int main() {
	Node *root = NULL;
	
    root = insert(root, -1, 10);
    root = insert(root, 0, 20);
    root = insert(root, 2, 20); cout << endl;
    root = insert(root, 3, 20);
    root = insert(root, 5, 40);
    root = insert(root, 1, 50);
    root = insert(root, 6, 25);

    levelOrder(root);
    inOrder(root);
    cout << endl;

    
    root = deleteNode(root, 5, 40);

    levelOrder(root);
    inOrder(root);
    cout << endl;
    
    // root = deleteNode(root, 3, 25);

    // levelOrder(root);
    // inOrder(root);
    // cout << endl;
    
    // root = deleteNode(root, 1, 10);

    // levelOrder(root);
    // inOrder(root);
    // cout << endl;
    
    // root = deleteNode(root, 2, 50);

    // levelOrder(root);
    // inOrder(root);
    // cout << endl;
     
    return 0;
}