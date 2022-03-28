#include "utils.h"

class Node {
public:
    double X, Y, ht;
    Node *left, *right;
    segment s;
    int upperEndpoint;
    
    Node(double X, double Y,int upperEndpoint,segment seg) {
        this->X = X;
        this->Y = Y;
        this->upperEndpoint = upperEndpoint;
        this->s = seg;
        ht = 1;
        left = right = NULL;
    }
};