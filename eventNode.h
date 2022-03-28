class Node {
public:
    double X, Y, ht;
    Node *left, *right;
    segment s;
    int upperEndpoint;
    
    Node(double X, double Y,int upperEndpoint,segment seg) {
        this->X = X;
        this->Y = Y;
        if(upperEndpoint){
            this->s = seg;
        }else{
            this->s = NULL;
        }
        ht = 1;
        left = right = NULL;
    }
};