#include <bits/stdc++.h>
#include "Eventnode.h"
using namespace std;

class EventQueue {
public:
    int height(Node *node) {
        return (node == NULL)? 0: node->ht;
    }

public:
    Node* getnextEventPoint(Node* node){
        while(node->right!=NULL){
            node = node->right;
        }
        return node;
    }

public:
    bool isEmpty(Node *node){
        if(node==NULL){
            return true;
        }
        return false;
    }

private:
    int getBalance(Node *node) {
        return (node == NULL)? 0: height(node->left) - height(node->right);
    }

private:
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

private:
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

public:
    Node* insert(Node* node, double X, double Y,int upper)
    {
        if (node == NULL)
            return new Node(X, Y);
        
        if (Y < node->Y || (Y == node->Y && X > node->X))
            node->left = insert(node->left, X, Y);
        else if (Y > node->Y || (Y == node->Y && X < node->X))
            node->right = insert(node->right, X, Y);
        else
            return node;

        node->ht = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1) {
            if(Y > node->left->Y || (Y == node->left->Y && X < node->left->X)) {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
            else
                return rightRotate(node);
        }

        if (balance < -1) {
            if(Y < node->right->Y || (Y == node->right->Y && X > node->right->X)) {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
            else 
                return leftRotate(node);
        }
        
        return node;
    }

public:
    void inOrder(Node *root) 
    {
        if(root == NULL)
            return;
            
        inOrder(root->left);
        cout <<"("<< root->X <<" "<< root->Y << ") ";
        inOrder(root->right);
    }

public:
    void levelOrder(Node* root) {
        queue<Node*> que;
        que.push(root);

        while(!que.empty()) {
            Node* curr = que.front();
            que.pop();
            cout <<"("<< curr->X <<" "<< curr->Y << ") ";

            if(curr->left)
                que.push(curr->left);
            if(curr->right)
                que.push(curr->right);
        }
        
        cout << endl;
    }
public:
    Node* getInorderSuccessor(Node* node)
    {
        Node* curr = node;

        while (curr->left)
            curr = curr->left;
    
        return curr;
    }

public:
    Node* deleteNode(Node* root, int X, int Y)
    {
        if (root == NULL)
            return root;

        if (Y < root->Y || (Y == root->Y && X > root->X))
            root->left = deleteNode(root->left, X, Y);

        else if(Y > root->Y || (Y == root->Y && X < root->X))
            root->right = deleteNode(root->right, X, Y);

        else {
            if(root->left == NULL) {
                Node* temp = root->right;
                free(root);
                root = temp;
            }
            else if(root->right == NULL) {
                Node* temp = root->left;
                free(root);
                root = temp;
            }
            else {
                Node* inorderSuccessor = getInorderSuccessor(root->right);
                root->X = inorderSuccessor->X;
                root->Y = inorderSuccessor->Y;
                root->right = deleteNode(root->right, inorderSuccessor->X, inorderSuccessor->Y);
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
};

// int main() {
// 	Node *root = NULL;
// 	EventQueue eq;
//     root = eq.insert(root, 1, 10);
//     root = eq.insert(root, 1, 20);
//     root = eq.insert(root, 2, 20);
//     root = eq.insert(root, 0, 20);
//     root = eq.insert(root, 2, 40);
//     root = eq.insert(root, 2, 50);
//     root = eq.insert(root, 3, 25);
    
//     eq.levelOrder(root);
//     eq.inOrder(root);
//     cout << endl;
    
//     root = eq.deleteNode(root, 2, 40);

//     eq.levelOrder(root);
//     eq.inOrder(root);
//     cout << endl;
    
//     root = eq.deleteNode(root, 3, 25);

//     eq.levelOrder(root);
//     eq.inOrder(root);
//     cout << endl;
    
//     root = eq.deleteNode(root, 1, 10);

//     eq.levelOrder(root);
//     eq.inOrder(root);
//     cout << endl;
    
//     root = eq.deleteNode(root, 2, 50);

//     eq.levelOrder(root);
//     eq.inOrder(root);
//     cout << endl;
     
//     return 0;
// }