#include <fstream>
#include "event_queue.h"
#include "handelEventPoint-new.h"

int main()
{
    EventQueue eq;
    StatusQueue sq;
    ifstream fin;
    ofstream fout;

    double x1, y1, x2, y2;
    fin.open("input.txt");

    vector<segment> lseg; // Line segments array

    while (!fin.eof())
    {
        fin >> x1 >> y1 >> x2 >> y2;
        point p1;
        point p2;
        segment s;

        p1.x = x1;
        p1.y = y1;
        p2.x = x2;
        p2.y = y2;
        if (y1 > y2)
        {
            s.pstart = p1;
            s.pend = p2;
        }
        else if (y1 == y2)
        {
            if (x1 < x2)
            {
                s.pstart = p1;
                s.pend = p2;
            }
            else
            {
                s.pstart = p2;
                s.pend = p1;
            }
        }
        else
        {
            s.pstart = p2;
            s.pend = p1;
        }
        lseg.push_back(s);
    }
    fin.close();

    point p_ = {.x = 10, .y = -1};
    point p = findnewEvent(lseg[1], lseg[0], p_);
    if(!(p.x == FLT_MAX && p.y == FLT_MAX)) {
        // add event
    }
    // cout << p.x <<" "<< p.y << endl;

                    // for(auto it: lseg){
                    //     cout<<it.pstart.x <<" "<< it.pstart.y <<", "<< it.pend.x <<" "<< it.pend.y << endl;
                    // }

    // Find intersections!
    // eventNode *eventQueueRoot = NULL;
    // statusQueueNode* statusQueueRoot = NULL;

    // for (int i = 0; i < lseg.size(); i++) {  
    //     eventQueueRoot = eq.insert(eventQueueRoot, lseg[i].pstart.x, lseg[i].pstart.y, 1, 0, lseg[i]); // 1,0 for p on upper endpoint of the segment
    //     eventQueueRoot = eq.insert(eventQueueRoot, lseg[i].pend.x,   lseg[i].pend.y,   0, 1, lseg[i]); // 0,1 for p on lower endpoint of the segment
    // }
    // eq.inOrder(eventQueueRoot);

                    // for(auto seg: lseg) {
                    //     statusQueueRoot = sq.insert(statusQueueRoot, seg);
                    // }
                    // sq.inOrder(statusQueueRoot);

    // eventNode *temp = eventQueueRoot;
    // while (!eq.isEmpty(temp)) {
    //     eventNode *p = eq.getnextEventPoint(temp);
    //     // cout<<p->X<<" "<<p->Y<<endl;
    //     // handleEventPoint(statusQueueRoot, p, sq);
    //     temp = eq.deleteNode(temp, p->X, p->Y);
    // }

    // fout.open("intersection_points.txt");

    // for (int i=0; i<intersection_points.size(); i++) {
    // 	fout<<intersection_points[i].x<<" "<<intersection_points[i].y<<endl;
    // }

    // fout.close();

    return 0;
}