#include "utils.h"

class eventNode
{
public:
    double X, Y;
    int ht;
    eventNode *left, *right;
    segment s;
    int upperEndpoint, lowerEndpoint;
    vector<segment> U;
    vector<segment> L;
    vector<segment> C;

    eventNode(double X, double Y, int upperEndpoint, int lowerEndpoint, segment seg)
    {
        this->X = X;
        this->Y = Y;
        this->upperEndpoint = upperEndpoint;
        this->lowerEndpoint = lowerEndpoint;
        this->s = seg;
        ht = 1;
        left = right = NULL;
    }
};