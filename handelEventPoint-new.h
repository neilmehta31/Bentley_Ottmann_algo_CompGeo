#include <float.h>
#include "status_queue_bst.h"
#include "findnewevent.h"

vector<point> intersections;

vector<segment> unionvector(vector<segment> a, vector<segment> b)
{
    vector<segment> uni;
    for (auto seg : a) {
        uni.push_back(seg);
    }
    for (auto segb : b) {
        bool uniq = true;
        for (auto segu : uni) {
            if (segb.pstart.x == segu.pstart.x && segb.pstart.y == segu.pstart.y && segb.pend.x == segu.pend.x && segb.pend.y == segu.pend.y) {
                uniq = false;
            }
        }
        if(uniq) {
            uni.push_back(segb);
        }
    }
    return uni;
}

void handleEventPoint(statusQueueNode* sqnode, eventNode *evntnode, StatusQueue sq)
{
    
    // vector<segment> LUC_P;
    // LUC_P = unionvector(evntnode->L,unionvector(evntnode->C,evntnode->U));
    
    // point pnt;
    // pnt.x = evntnode->X;
    // pnt.y = evntnode->Y;   
    
    // if (LUC_P.size() > 1) {
    //     intersections.push_back(pnt);
    // }

    // vector<segment> LC_P;
    // LC_P = unionvector(evntnode->L,evntnode->C);
    // for (auto lc_seg : LC_P) {
    //     sqnode = sq.deleteNode(sqnode,lc_seg);
    // }

    // vector<segment> UC_P;
    // UC_P = unionvector(evntnode->U,evntnode->C);
    // for(auto uc_seg: UC_P){
    //     sq.insert(sqnode,uc_seg);
    // }

    // for (auto a:UC_P){
    //     cout<<a.pstart.x<<endl;
    // }
    // cout<<"\thELleo\n";
    
    // if(UC_P.size()==0){
    //     segment sl,sr;//sl and sr be the left and right neighbors of p in StatusQueue.
    //     vector<statusQueueNode *> p_neighbours;//0 for left neighbour and 1 for right neighbour.
    //     // statusQueueNode* seg = getRightmostval(sqnode);
    //     segment seg = evntnode->s;
    //     statusQueueNode* segpointer = sq.getAddress(sqnode,seg);
    //     p_neighbours = sq.getNeighbors(sqnode,segpointer);
    //     sl = p_neighbours[0]->seg;
    //     sr = p_neighbours[1]->seg;
    //     cout<<"sl, sr : "<<sl<<", "<<sr<<endl;
    //     cout<<"if statement of handle Event point";
    //     // if(sl)
    //     findnewEvent(sl,sr,pnt);
    // }
    // else{
    //     segment sdash,sdoubledash;
    //     double min_x = DBL_MAX;
    //     double max_x = DBL_MIN;
    //     for(auto uc_seg:UC_P){
    //         if(min_x > uc_seg.pstart.x){
    //             min_x = uc_seg.pstart.x;
    //             sdash = uc_seg;
    //         }
    //         if(min_x > uc_seg.pend.x){
    //             min_x = uc_seg.pend.x;
    //             sdash = uc_seg;
    //         }
    //         if(max_x < uc_seg.pstart.x){
    //             max_x = uc_seg.pstart.x;
    //             sdoubledash = uc_seg;
    //         }
    //         if(max_x < uc_seg.pend.x){
    //             max_x = uc_seg.pend.x;
    //             sdoubledash = uc_seg;
    //         }
    //     }
    //     vector<statusQueueNode *> sdash_neighbours,sdoubledash_neighbours;//0 for left neighbour and 1 for right neighbour.
    //     segment sl_dash,sr_doubledash;
    //     statusQueueNode* segpointer = sq.getAddress(sqnode,sdash);
    //     sdash_neighbours = sq.getNeighbors(sqnode,segpointer);
    //     sl_dash = sdash_neighbours[0]->seg;
    //     // findnewEvent(sl_dash,sdash,pnt);
    //     // cout<<"hello from else of handel Event point";
        
    //     segpointer = sq.getAddress(sqnode,sdoubledash);
    //     sdoubledash_neighbours = sq.getNeighbors(sqnode,segpointer);
    //     sr_doubledash = sdoubledash_neighbours[1]->seg;
    //     // findnewEvent(sdoubledash,sr_doubledash,pnt);
    // }
}