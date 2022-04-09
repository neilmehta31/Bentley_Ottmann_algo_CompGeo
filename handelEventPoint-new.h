#include <float.h>
#include "status_queue_bst.h"
#include "findnewevent.h"

vector<point> intersections;

vector<segment> unionvector(vector<segment> a, vector<segment> b)
{
    vector<segment> uni;
    for (auto seg : a)
    {
        uni.push_back(seg);
    }
    for (auto segb : b)
    {
        bool uniq = true;
        for (auto segu : uni)
        {
            if (segb.pstart.x == segu.pstart.x && segb.pstart.y == segu.pstart.y && segb.pend.x == segu.pend.x && segb.pend.y == segu.pend.y)
            {
                uniq = false;
            }
        }
        if (uniq)
        {
            uni.push_back(segb);
        }
    }
    return uni;
}

void **handleEventPoint(statusQueueNode *sqnode, eventNode *evntnode, StatusQueue sq, EventQueue eq, eventNode *root)
{

    point pnt;
    pnt.x = evntnode->X;
    pnt.y = evntnode->Y;
    // cout<<"POINT: "<<pnt.x<<" "<<pnt.y<<endl;

    if(evntnode->upperEndpoint == 1) {
        // cout <<"TOP Pt---------"<<endl;

        // cout << "SQ inorder: ";
        // sq.inOrder(sqnode); cout << endl;

        // insert segment
        sqnode = sq.insert(sqnode, evntnode->s);

        // cout << "SQ inorder: ";
        // sq.inOrder(sqnode); cout << endl;

        // get neighbours
        statusQueueNode *segpointer = sq.getAddress(sqnode, evntnode->s);
        vector<statusQueueNode *>neighbours = sq.getNeighbors(sqnode, segpointer);
        // cout << "Neighbours Start Pt" << endl;
        // cout <<"Segpointer: "<<segpointer << endl;
        
        if(neighbours[0]!=NULL) {
            // cout << "LEFT NEIGHBOUR: ";
            // cout <<"("<<neighbours[0]->seg.pstart.x<<","<<neighbours[0]->seg.pstart.y<<") and ("<<neighbours[0]->seg.pend.x<<","<<neighbours[0]->seg.pend.y<<")"<<endl;
            
            point p = findnewEvent(neighbours[0]->seg, evntnode->s, pnt);
            // cout << "Event Pt: " << p.x <<" "<< p.y << endl;

            if(!(p.x == FLT_MAX && p.y == FLT_MAX)){
                bool present = false;
                root = eq.insert(root, p.x, p.y, 0, 0, neighbours[0]->seg);
                root = eq.insert(root, p.x, p.y, 0, 0, evntnode->s);
                intersections.push_back(p);
            }
        }
        if(neighbours[1]!=NULL) {
            // cout << "RIGHT NEIGHBOUR: ";
            // cout <<"("<<neighbours[1]->seg.pstart.x<<","<<neighbours[1]->seg.pstart.y<<") and ("<<neighbours[1]->seg.pend.x<<","<<neighbours[1]->seg.pend.y<<")"<<endl;
            
            point p = findnewEvent(neighbours[1]->seg, evntnode->s, pnt);
            // cout << "Event Pt: " << p.x <<" "<< p.y << endl;

            // cout << "\n>>EQ Level Order: ";
            // eq.levelOrder(root);
            // cout << ">>EQ inOrder: ";
            // eq.inOrder(root); cout << endl;
            if(!(p.x == FLT_MAX && p.y == FLT_MAX)){
                root = eq.insert(root, p.x, p.y, 0, 0, neighbours[1]->seg);
                root = eq.insert(root, p.x, p.y, 0, 0, evntnode->s);
                intersections.push_back(p);
            }

            // cout << "\n>>>EQ Level Order: ";
            // eq.levelOrder(root);
            // cout << ">>>EQ inOrder: ";
            // eq.inOrder(root); cout << endl;
        }

        // cout << "Neighbours Handled, Done TOP Pt---------\n";
    }

    else if(evntnode->lowerEndpoint == 1) {
        // cout <<"delete"<<endl;
        // cout <<"sq & eq "<< sqnode <<" "<< evntnode->s.pstart.y << endl;
        statusQueueNode *segpointer = sq.getAddress(sqnode, evntnode->s);

        if(segpointer != NULL) {
            // cout << segpointer << endl;
            vector<statusQueueNode *>neighbours = sq.getNeighbors(sqnode, segpointer);

            sqnode = sq.deleteNode(sqnode, evntnode->s);

            if(neighbours[0]!=NULL && neighbours[1]!=NULL) {
                // cout << "New Neighbour while deletion\n";
                point p = findnewEvent(neighbours[0]->seg, neighbours[1]->seg, pnt);

                if(!(p.x == FLT_MAX && p.y == FLT_MAX)) {
                    evntnode = eq.insert(evntnode, p.x, p.y, 0, 0, neighbours[0]->seg);
                    evntnode = eq.insert(evntnode, p.x, p.y, 0, 0, neighbours[1]->seg);    
                    intersections.push_back(p);
                }
            }
        }

    }

    else if(evntnode->lowerEndpoint == 0 && evntnode->upperEndpoint == 0 ) {
        // cout <<"MID Pt"<<endl;
        
        // cout << "SQ inorder before deleting: ";
        // sq.inOrder(sqnode); cout << endl;
        
        sqnode = sq.deleteNode(sqnode, evntnode->s);
        
        // cout << "SQ inorder after deleting: ";
        // sq.inOrder(sqnode); cout << endl;
        
        segment seg_new1;
        seg_new1.pend.x = evntnode->s.pend.x;;
        seg_new1.pend.y = evntnode->s.pend.y;
        seg_new1.pstart.x = pnt.x;
        seg_new1.pstart.y = pnt.y;
        // cout << seg_new1.pstart.x<<","<<seg_new1.pstart.y<<" "<<seg_new1.pend.x<<","<<seg_new1.pend.y<<endl;
        
        sqnode = sq.insert(sqnode, seg_new1);

        // cout << "SQ inorder after inserting: ";
        // sq.inOrder(sqnode); cout << endl;

        // get neighbours
        // cout << "Neighbours Start Pt" << endl;
        // cout << "start\n";
        statusQueueNode *segpointer = sq.getAddress(sqnode, seg_new1);
        // cout << "end\n";

        // cout << "Segment to get neighbour: ";
        // cout << segpointer->seg.pstart.x <<","<< segpointer->seg.pstart.y <<" "<< segpointer->seg.pend.x <<","<< segpointer->seg.pend.y << endl;
        // cout <<"Segpointer: "<<segpointer << endl;
        vector<statusQueueNode *>neighbours = sq.getNeighbors(sqnode, segpointer);
        
        if(neighbours[0]!=NULL) {
            // cout << "LEFT NEIGHBOUR: ";
            // cout <<"("<<neighbours[0]->seg.pstart.x<<","<<neighbours[0]->seg.pstart.y<<") and ("<<neighbours[0]->seg.pend.x<<","<<neighbours[0]->seg.pend.y<<")"<<endl;
            
            point p = findnewEvent(neighbours[0]->seg, seg_new1, pnt);
            // cout << "Event Pt: " << p.x <<" "<< p.y << endl;

            if(!(p.x == FLT_MAX && p.y == FLT_MAX)){
                bool present = false;
                root = eq.insert(root, p.x, p.y, 0, 0, neighbours[0]->seg);
                root = eq.insert(root, p.x, p.y, 0, 0, seg_new1);
                intersections.push_back(p);
            }
        }
        if(neighbours[1]!=NULL) {
            // cout << "RIGHT NEIGHBOUR: ";
            // cout <<"("<<neighbours[1]->seg.pstart.x<<","<<neighbours[1]->seg.pstart.y<<") and ("<<neighbours[1]->seg.pend.x<<","<<neighbours[1]->seg.pend.y<<")"<<endl;
            
            point p = findnewEvent(neighbours[1]->seg, seg_new1, pnt);
            // cout << "Event Pt: " << p.x <<" "<< p.y << endl;

            if(!(p.x == FLT_MAX && p.y == FLT_MAX)){
                root = eq.insert(root, p.x, p.y, 0, 0, neighbours[1]->seg);
                root = eq.insert(root, p.x, p.y, 0, 0, seg_new1);
                intersections.push_back(p);
            }
        }
        

        // cout << "Neighbours Handled, Done TOP Pt---------\n";
    }
    else {
        // cout << "excetion: none of 3" << endl;
    }
    
    void** val = new void*[2];
    val[0] = (void*)sqnode;
    val[1] = (void*)root;
    return val;
}