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

statusQueueNode *handleEventPoint(statusQueueNode *sqnode, eventNode *evntnode, StatusQueue sq, EventQueue eq)
{
    vector<segment> LUC_P;
    LUC_P = unionvector(evntnode->L, unionvector(evntnode->C, evntnode->U));
    for(auto a:LUC_P){
        cout<<"segment in LUC_P :("<<a.pstart.x<<","<<a.pstart.y<<") and ("<<a.pend.x<<","<<a.pend.y<<")"<<endl;
    }
    point pnt;
    pnt.x = evntnode->X;
    pnt.y = evntnode->Y;
    cout<<"POINT=>"<<pnt.x<<pnt.y<<endl;
    // cout<<LUC_P.size()<<endl;
    if (LUC_P.size() > 1)
    {
        intersections.push_back(pnt);
    }
    
    vector<segment> LC_P;
    LC_P = unionvector(evntnode->L, evntnode->C);
    for (auto lc_seg : LC_P)
    {
        cout<<"segment in LC_P :("<<lc_seg.pstart.x<<","<<lc_seg.pstart.y<<") and ("<<lc_seg.pend.x<<","<<lc_seg.pend.y<<")"<<endl;
        sqnode = sq.deleteNode(sqnode, lc_seg);
        // cout<<"deleted node"<<endl;
    }

    vector<segment> UC_P;
    UC_P = unionvector(evntnode->U, evntnode->C);

    for (auto uc_seg : UC_P)
    {
        sqnode = sq.insert(sqnode, uc_seg);
    }
    sq.inOrder(sqnode);
    // cout<<"sqnode before= "<< sqnode << endl;

    // for (auto a:UC_P){
    //     cout<<a.pstart.x<<endl;
    // }
    // cout<<"\thELleo\n";
    cout<<"UC_P.size() = "<<UC_P.size()<<endl;
    if (UC_P.size() == 0){
        
        segment sl, sr;                         // sl and sr be the left and right neighbors of p in StatusQueue.
        vector<statusQueueNode *> p_neighbours; // 0 for left neighbour and 1 for right neighbour.
        segment seg = evntnode->s;

        cout <<"("<< seg.pstart.x <<","<< seg.pstart.y <<" "<< seg.pend.x <<","<<seg.pend.y <<") "; 

        statusQueueNode *segpointer = sq.getAddress(sqnode, seg);        
        cout<<"seg_ptr: "<< segpointer << endl;
        p_neighbours = sq.getNeighbors(sqnode, segpointer);

        if(!(p_neighbours[0] == NULL && p_neighbours[1] == NULL)) {
            sl = p_neighbours[0]->seg;
            sr = p_neighbours[1]->seg;
            point p = findnewEvent(sl, sr, pnt);
            if(!(p.x == FLT_MAX && p.y == FLT_MAX)) {
                evntnode = eq.insert(evntnode, p.x, p.y, 0, 0, seg); // 0,0 for p on C of segment
            }
        }
        // int right=0;
        // for(auto neighbour:p_neighbours){

        //     if(neighbour!=NULL){
        //         if(right==0)
        //             {sl = p_neighbours[0]->seg;}
        //         else
        //             {sr = p_neighbours[1]->seg;}
        //     }

        //     if(sl!=NULL || sr!=NULL){
        //         point p = findnewEvent(sl, sr, pnt);
        //             if(!(p.x == FLT_MAX && p.y == FLT_MAX)) {
        //                 evntnode = eq.insert(evntnode, p.x, p.y, 0, 0, seg); // 0,0 for p on C of segment
        //             }
        //     }
        //     right++;
        // }
        
        // findnewEvent(sl, sr, pnt);
    }else{

        segment sdash, sdoubledash, sl_dash, sr_doubledash;

        double min_x = DBL_MAX;
        double max_x = DBL_MIN;
        for (auto uc_seg : UC_P)
        {
            if (min_x > uc_seg.pstart.x)
            {
                min_x = uc_seg.pstart.x;
                sdash = uc_seg;
            }
            if (min_x > uc_seg.pend.x)
            {
                min_x = uc_seg.pend.x;
                sdash = uc_seg;
            }
            if (max_x < uc_seg.pstart.x)
            {
                max_x = uc_seg.pstart.x;
                sdoubledash = uc_seg;
            }
            if (max_x < uc_seg.pend.x)
            {
                max_x = uc_seg.pend.x;
                sdoubledash = uc_seg;
            }
        }
        cout<<"min_x = "<<min_x<<", max_x = "<<max_x<<endl;
        vector<statusQueueNode *> sdash_neighbours, sdoubledash_neighbours; // 0 for left neighbour and 1 for right neighbour.
        
        statusQueueNode *segpointer = sq.getAddress(sqnode, sdash);

        cout << "segpointer"<< segpointer <<endl;
        sdash_neighbours = sq.getNeighbors(sqnode, segpointer);
        for(auto n:sdash_neighbours){
            if(n==NULL){
                cout<<"NULL val in get neighbours ";
            }
            else 
                cout<<"segment = ("<<n->seg.pstart.x<<","<<n->seg.pstart.y<<endl;
        }
        if(sdash_neighbours[0] != NULL) {
            sl_dash = sdash_neighbours[0]->seg;
            cout<<"left neighbour : "<<sl_dash.pstart.x<<sl_dash.pstart.y<<endl;
            // findnewEvent(sl_dash, sdash, pnt);
            point p = findnewEvent(sl_dash, sdash, pnt);

            if(!(p.x == FLT_MAX && p.y == FLT_MAX)) {
                // segment seg_new1,seg_new2;
                // seg_new1.pstart.x = p.x;
                // seg_new1.pstart.y = p.y;
                // seg_new1.pend.x = sdash.pend.x;
                // seg_new1.pend.y = sdash.pend.y;

                // seg_new2.pstart.x = p.x;
                // seg_new2.pstart.y = p.y;
                // seg_new2.pend.x = sl_dash.pend.x;
                // seg_new2.pend.y = sl_dash.pend.y;

                // evntnode = sq.deleteNode(sqnode,sdash);
                // evntnode = sq.deleteNode(sqnode,sl_dash);
                // evntnode = eq.insert(evntnode, p.x, p.y, 0, 0, sl_dash); // 0,0 for p on C of segment
                evntnode = eq.insert(evntnode, p.x, p.y, 0, 0, sdash); 
                intersections.push_back(p);
            }
        }
        
        segpointer = sq.getAddress(sqnode, sdoubledash);
        sdoubledash_neighbours = sq.getNeighbors(sqnode, segpointer);
        if(sdoubledash_neighbours[1] != NULL) 
        {
            sr_doubledash = sdoubledash_neighbours[1]->seg;
            point p = findnewEvent(sdoubledash, sr_doubledash, pnt);

            // point p = findnewEvent(lseg[1], lseg[0], p_);
            if(!(p.x == FLT_MAX && p.y == FLT_MAX)) {
                // segment seg_new1,seg_new2;
                // seg_new1.pstart.x = p.x;
                // seg_new1.pstart.y = p.y;
                // seg_new1.pend.x = sdoubledash.pend.x;
                // seg_new1.pend.y = sdoubledash.pend.y;

                // seg_new2.pstart.x = p.x;
                // seg_new2.pstart.y = p.y;
                // seg_new2.pend.x = sr_doubledash.pend.x;
                // seg_new2.pend.y = sr_doubledash.pend.y;

                // evntnode = sq.deleteNode(sqnode,sdoubledash);
                // evntnode = sq.deleteNode(sqnode,sr_doubledash);
                // evntnode = eq.insert(evntnode, p.x, p.y, 0, 0, seg_new1); // 0,0 for p on C of segment
                evntnode = eq.insert(evntnode, p.x, p.y, 0, 0, sdoubledash); // 0,0 for p on C of segment
                intersections.push_back(p);
            }
        }
    }
    cout<<"\n\n\n"<<endl;
    return sqnode;
}