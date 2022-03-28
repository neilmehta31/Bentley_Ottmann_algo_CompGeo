#include <bits/stdc++.h>
#include <fstream>
#include "event_queue.h"
#include "handleEventPoint.h"

int main()
{
    EventQueue eq;
    ifstream fin;
    // ofstream fout;

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
    // for(auto it:lseg){
    //     cout<<it.pstart.x<<it.pstart.y<<endl;
    //     cout<<it.pend.x<<it.pend.y<<endl;
    // }

    // Find intersections!
    eventNode *eventQueueRoot = NULL;
    for (int i = 0; i < lseg.size(); i++)
    {
        eventQueueRoot = eq.insert(eventQueueRoot, lseg[i].pstart.x, lseg[i].pstart.y, 1, lseg[i]); // last parameter for checking if it is upper or not.
        eventQueueRoot = eq.insert(eventQueueRoot, lseg[i].pend.x, lseg[i].pend.y, 0, lseg[i]);
    }

    eq.inOrder(eventQueueRoot);

    while (!eq.isEmpty(eventQueueRoot))
    {
        eventNode *p = eq.getnextEventPoint(eventQueueRoot);
        // cout<<p->X<<" "<<p->Y<<endl;
        point pnt;
        pnt.x = p->X;
        pnt.y = p->Y;
        handleEventPoint(pnt);
        eventQueueRoot = eq.deleteNode(eventQueueRoot, p->X, p->Y);
    }

    // fout.open("intersection_points.txt");

    // for (int i=0; i<intersection_points.size(); i++) {
    // 	fout<<intersection_points[i].x<<" "<<intersection_points[i].y<<endl;
    // }

    // fout.close();

    return 0;
}