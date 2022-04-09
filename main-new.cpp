#include "event_queue.h"
#include "handelEventPoint-new.h"

int main()
{
    EventQueue eq;
    StatusQueue sq;
    ifstream fin;
    ofstream fout;
    clock_t start,end;

    double x1, y1, x2, y2;
    fin.open("testcases.txt");
    vector<segment> lseg;

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

    start = clock();
    eventNode *eventQueueRoot = NULL;
    statusQueueNode* statusQueueRoot = NULL;

    for (int i = 0; i < lseg.size(); i++) {  
        eventQueueRoot = eq.insert(eventQueueRoot, lseg[i].pstart.x, lseg[i].pstart.y, 1, 0, lseg[i]); // 1,0 for p on upper endpoint of the segment
        eventQueueRoot = eq.insert(eventQueueRoot, lseg[i].pend.x,   lseg[i].pend.y,   0, 1, lseg[i]); // 0,1 for p on lower endpoint of the segment
    }

    eventNode *temp = eventQueueRoot;

    while (!eq.isEmpty(temp) || temp != NULL) {
        eventNode *p = eq.getnextEventPoint(temp);
        double xi = p->X, yi = p->Y;

        void** returnVal = handleEventPoint(statusQueueRoot, p, sq, eq, temp);
        statusQueueRoot = (statusQueueNode*)returnVal[0];
        temp = (eventNode*)returnVal[1];
        temp = eq.deleteNode(temp, xi, yi);
    }
    end = clock();

    if(intersection_points.size()){
    fout.open("output.txt");
    cout<<"Intersection Points: "<<endl;
    for(auto it:intersection_points){
        cout<<" ("<<it.first.first<<","<<it.first.second<<")\n";
        fout<<it.first.first<<" "<<it.first.second<<endl;
    }
    }else{
        cout<<"No Intersection Points Detected."<<endl;
    }
    
    cout<<"\n\n";

    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed 
         << time_taken << setprecision(5);
    cout << " sec " << endl;

    fout.close();

    return 0;
}