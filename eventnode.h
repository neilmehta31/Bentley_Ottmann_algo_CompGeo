#include "utils.h"

class eventNode
{
public:
    double X, Y, ht;
    eventNode *left, *right;
    segment s;
    int upperEndpoint;
    vector<segment> U;
    vector<segment> L;
    vector<segment> C;

    eventNode(double X, double Y, int upperEndpoint, segment seg)
    {
        this->X = X;
        this->Y = Y;
        this->upperEndpoint = upperEndpoint;
        this->s = seg;
        ht = 1;
        left = right = NULL;
    }
};