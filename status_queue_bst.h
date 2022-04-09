#include <bits/stdc++.h>
#include "statusnode.h"

using namespace std;

class StatusQueue
{        
private:
    double compare (segment s1, segment s2)
    {
        // if(s1.pstart.x < s2.pstart.x)
        //     return -1;
        // if(s1.pstart.x > s2.pstart.x)
        //     return 1;
        // if(s1.pend.x < s2.pend.x)
        //     return -1;
        // if(s1.pend.x > s2.pend.x)
        //     return 1;
        // return 0;

        double x2 = s2.pend.x;
        double x1 = s2.pstart.x;
        double y2 = s2.pend.y;
        double y1 = s2.pstart.y;

        double xi = ((x2-x1)*(s1.pstart.y-y2)/(y2-y1))+x2;
        // cout <<"x2="<<x2<<" y2="<<y2<<" x1="<<x1<<" y1="<<y1<<endl;
        // cout <<"y="<<s1.pstart.y<<" ";
        // cout <<"X Decider: "<< xi << endl;
        // cout <<"Return: "<<s1.pstart.x-xi << endl;
        return s1.pstart.x-xi;
    }

private:
    int height(statusQueueNode *node) {
        return (node == NULL)? 0: node->ht;
    }
    
private:
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
    
private:
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
    
private:
    int getBalance(statusQueueNode *node) {
        return (node == NULL)? 0: height(node->left) - height(node->right);
    }

public:
    statusQueueNode* insert(statusQueueNode* node, segment s)
    {
        if (node == NULL) {
            // cout << "Inserted\n";
            return new statusQueueNode(s);
        }
        
        double compared_val = compare(s, node->seg);
        // cout << "Compared val: "<< compared_val << endl;
        if (compared_val < 0 || (compared_val == 0 && node->seg.pend.x > s.pend.x)) {
            // cout << "To left\n";
            node->left = insert(node->left, s);
        }
        else if (compared_val > 0 || (compared_val == 0 && node->seg.pend.x < s.pend.x)) {
            // cout << "To right\n";
            node->right = insert(node->right, s);
        }
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
    
private:
    statusQueueNode* getInorderSuccessor(statusQueueNode* node)
    {
        statusQueueNode* curr = node;

        while (curr->left)
            curr = curr->left;

        return curr;
    }

public:
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

private:
    statusQueueNode* getMinValue(statusQueueNode* node)
    {
        statusQueueNode* current = node;
        while (current->left != NULL) {
            current = current->left;
        }
        return current;
    }

private:
    statusQueueNode* getMaxValue(statusQueueNode* node)
    {
        statusQueueNode* current = node;
        while (current->right != NULL) {
            current = current->right;
        }
        return current;
    } 

private:
    statusQueueNode* getLeftNeighbor(statusQueueNode* root, statusQueueNode* n)
    {
        // if(n == NULL)
        //     return NULL;
        if (n->left != NULL)
            return getMaxValue(n->left);
    
        statusQueueNode* pred = root;

        while (root != NULL) {
            double compare_val = compare(n->seg, root->seg);

            if (compare_val < 0)
                root = root->left;
            else if (compare_val > 0) {
                pred = root;
                root = root->right;
            }
            else
                break;
        }
        if(pred != NULL && compare(n->seg, pred->seg) <= 0)
            return NULL;
        return pred;
    }

private:
    statusQueueNode* getRightNeighbor(statusQueueNode* root, statusQueueNode* n)
    {
        // if(n == NULL)
        //     return NULL;
        if (n->right != NULL)
            return getMinValue(n->right);
    
        statusQueueNode* succ = NULL;

        while (root != NULL) {

            double compare_val = compare(n->seg, root->seg);

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
        if(succ != NULL && compare(n->seg, succ->seg) >= 0)
            return NULL;
        return succ;
    }

public:
    void inOrder(statusQueueNode *root) {
        if(root == NULL)
            return;
            
        inOrder(root->left);
        cout <<"("<< (*root).seg.pstart.x <<","<< (*root).seg.pstart.y <<" "<< (*root).seg.pend.x <<","<<(*root).seg.pend.y <<") ";
        inOrder(root->right);
    }

public:
    vector<statusQueueNode*> getNeighbors(statusQueueNode* root, statusQueueNode* s) 
    {
        vector<statusQueueNode*> res;

        res.push_back(getLeftNeighbor(root, s));
        res.push_back(getRightNeighbor(root, s));

        return res;
    }

public:
    statusQueueNode* getAddress(statusQueueNode* root, segment seg) {
        
        if(root == NULL) {
            return root;
        }

        double compared_val = compare(root->seg, seg);
        // cout << root->seg.pstart.x <<","<< root->seg.pstart.y <<" "<<root->seg.pend.x<<","<<root->seg.pend.y<<endl;
        // cout << seg.pstart.x <<","<< seg.pstart.y <<" "<<seg.pend.x<<","<<seg.pend.y<<endl;
        // cout << "compared_val: " << compared_val << endl;
        
        if(compared_val < 0 || (compared_val == 0 && seg.pend.x > root->seg.pend.x)) {
            // cout << "left\n";
            return getAddress(root->left, seg);
        }
        else if(compared_val > 0 || (compared_val == 0 && seg.pend.x < root->seg.pend.x)) {
            // cout << "right\n";
            return getAddress(root->right, seg);
        }
        else {
            // cout << "got it\n";
            return root;
        }

        return root;
    }
};

// int main()
// {
//     statusQueueNode* root = NULL;
//     StatusQueue sq;
//     ifstream fin;
// 	// ofstream fout;
	
// 	double x1, y1, x2, y2;
// 	fin.open("input.txt");

// 	vector<segment> lseg; //Line segments array

// 	while (!fin.eof()) {
// 		fin>>x1>>y1>>x2>>y2;
//         point p1;
//         point p2;
//     	segment s;

//         p1.x = x1; p1.y = y1;
//         p2.x = x2; p2.y = y2;
//         if(y1>y2){
//             s.pstart = p1;
//             s.pend = p2;
//         }else if(y1==y2){
//             if(x1<x2){
//                 s.pstart = p1;
//                 s.pend = p2;
//             }else{
//                 s.pstart = p2;
//                 s.pend = p1;
//             }
//         }else{
//             s.pstart = p2;
//             s.pend = p1;
//         }
//         lseg.push_back(s);
// 	}
// 	fin.close();

//     // now the segment is lseg[i]!!


//     // segment s2= {1, 0, 1, 1};
//     // segment s3= {0, 0, 2, 1};
//     for(auto seg: lseg) {
//         root = sq.insert(root, seg);
//     }

//     // inOrder(root); 
//     // cout << endl;

//     // root = deleteNode(root, lseg[1]);

//     segment s;
//     s.pstart.x = 7;
//     s.pstart.y = 5;
//     s.pend.x = 2;
//     s.pend.y = 4;
//     statusQueueNode* seg = sq.getAddress(root, s);
    
//     vector<statusQueueNode*> neighbors = sq.getNeighbors(root, seg);
    
//     if(neighbors[0] != NULL) {
//         cout <<"Left Neighbour: ";
//         cout <<"("<< (*neighbors[0]).seg.pstart.x <<","<< (*neighbors[0]).seg.pstart.y <<" "<< (*neighbors[0]).seg.pend.x <<","<<(*neighbors[0]).seg.pend.y <<") "; 
//     }
//     if(neighbors[1] != NULL) {
//         cout <<"Right Neighbour: ";
//         cout <<"("<< (*neighbors[1]).seg.pstart.x <<","<< (*neighbors[1]).seg.pstart.y <<" "<< (*neighbors[1]).seg.pend.x <<","<<(*neighbors[1]).seg.pend.y <<") "; 
//     }

//     return 0;
// }