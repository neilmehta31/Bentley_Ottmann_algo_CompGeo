#include <bits/stdc++.h>
#include "eventnode.h"
#include "helper.h"
using namespace std;

class EventQueue
{
public:
    int height(eventNode *node)
    {
        return (node == NULL) ? 0 : node->ht;
    }

public:
    eventNode *getnextEventPoint(eventNode *node)
    {
        int nodecorrect = helper();
        while (node->right != NULL)
        {
            node = node->right;
        }
        return node;
    }

public:
    bool isEmpty(eventNode *node)
    {
        if (node == NULL)
        {
            return true;
        }
        return false;
    }

private:
    int getBalance(eventNode *node)
    {
        return (node == NULL) ? 0 : height(node->left) - height(node->right);
    }

private:
    eventNode *leftRotate(eventNode *node)
    {
        eventNode *right = node->right;
        eventNode *right_left = right->left;

        right->left = node;
        node->right = right_left;

        node->ht = 1 + max(height(node->left), height(node->right));
        right->ht = 1 + max(height(right->left), height(right->right));

        return right;
    }

private:
    eventNode *rightRotate(eventNode *node)
    {
        eventNode *left = node->left;
        eventNode *left_right = left->right;

        left->right = node;
        node->left = left_right;

        node->ht = 1 + max(height(node->left), height(node->right));
        left->ht = 1 + max(height(left->left), height(left->right));

        return left;
    }
private:
    bool liesOn(point p, segment s){
        if(((p.y-s.pstart.y)/(p.x - s.pstart.x))==((p.y-s.pend.y)/(p.x - s.pend.x))){ //If slope is equal on both the sides then point lies on the line segment
            return true;
        }
        return false;
    }

public:
    eventNode *insert(eventNode *node, double X, double Y, int upperEndpoint, int lowerEndpoint, segment s)
    {
        if (node == NULL){
            // cout <<"NULL"<<endl;
            eventNode *eventnode = new eventNode(X, Y, upperEndpoint, lowerEndpoint, s);
            return eventnode;
        }
        // cout << node->X <<" "<< node->Y << "  ";
        if (Y < node->Y || (Y == node->Y && X > node->X)) {
            // cout << "Left\n";
            node->left = insert(node->left, X, Y, upperEndpoint,lowerEndpoint, s);
        }
        else if (Y > node->Y || (Y == node->Y && X < node->X)) {
            // cout << "Right\n";
            node->right = insert(node->right, X, Y, upperEndpoint,lowerEndpoint, s);
        }
        else if (Y==node->Y && X==node->X && (node->s.pstart.x!= s.pstart.x || node->s.pstart.y!= s.pstart.y || node->s.pend.x!= s.pend.x || node->s.pend.y!= s.pend.y))
            node->left = insert(node->left,X, Y, upperEndpoint,lowerEndpoint, s);
        else
            return node;

        node->ht = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1)
        {
            if (Y > node->left->Y || (Y == node->left->Y && X < node->left->X))
            {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
            else
                return rightRotate(node);
        }

        if (balance < -1)
        {
            if (Y < node->right->Y || (Y == node->right->Y && X > node->right->X))
            {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
            else
                return leftRotate(node);
        }

        return node;
    }

public:
    void inOrder(eventNode *root)
    {
        if (root == NULL)
            return;

        inOrder(root->left);
        cout << "(" << root->X << " " << root->Y << ") ";
        inOrder(root->right);
    }

public:
    void levelOrder(eventNode *root)
    {
        queue<eventNode *> que;
        if(root)
            que.push(root);

        while (!que.empty())
        {
            eventNode *curr = que.front();
            que.pop();
            cout << "(" << curr->X << " " << curr->Y << ") ";

            if (curr->left)
                que.push(curr->left);
            if (curr->right)
                que.push(curr->right);
        }

        cout << endl;
    }

public:
    eventNode *getInorderSuccessor(eventNode *node)
    {
        eventNode *curr = node;

        while (curr->left)
            curr = curr->left;

        return curr;
    }

public:
        eventNode *deleteNode(eventNode *root, double X, double Y)
    {
        if (root == NULL)
            return root;
        
        // cout << root->X <<" "<< root->Y <<" | " << X<<" "<< Y << endl;

        if (root->Y > Y || (Y == root->Y && root->X < X)) {
            // cout << "1" << endl;
            root->left = deleteNode(root->left, X, Y);
        }

        else if (root->Y < Y || (Y == root->Y && root->X > X)) {
            // cout << "2" << endl;
            root->right = deleteNode(root->right, X, Y);
        }
        
        else
        {
            // cout << "Yaay" << endl;
            if (root->left == NULL)
            {
                eventNode *temp = root->right;
                free(root);
                root = temp;
            }
            else if (root->right == NULL)
            {
                eventNode *temp = root->left;
                free(root);
                root = temp;
            }
            else
            {
                eventNode *inorderSuccessor = getInorderSuccessor(root->right);
                root->X = inorderSuccessor->X;
                root->Y = inorderSuccessor->Y;
                root->right = deleteNode(root->right, inorderSuccessor->X, inorderSuccessor->Y);
            }
        }
        root = NULL;
        if (root == NULL)
            return root;

        root->ht = 1 + max(height(root->left), height(root->right));

        int balance = getBalance(root);

        if (balance > 1)
        {
            if (getBalance(root->left) >= 0)
                return rightRotate(root);
            else
            {
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }
        }

        if (balance < -1)
        {
            if (getBalance(root->right) <= 0)
                return leftRotate(root);
            else
            {
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }
        }

        return root;
    }
};

// int main() {
// 	eventNode *root = NULL;
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