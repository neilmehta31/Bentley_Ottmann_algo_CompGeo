
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