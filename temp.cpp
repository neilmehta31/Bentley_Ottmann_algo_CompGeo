#include <bits/stdc++.h>
#include "utils.h"
#include "event_queue.h"
#include <fstream>
#include <string>
using namespace std;


int main(){
    EventQueue eq;
    ifstream fin;
	ofstream fout;
	
	double x1, y1, x2, y2;
	fin.open("input.txt");

	vector<segment> lseg; //Line segments array

	while (!fin.eof()) {
		fin>>x1>>y1>>x2>>y2;
        point p1;
        point p2;
    	segment s;

        p1.x = x1; p1.y = y1;
        p2.x = x2; p2.y = y2;
        if(y1>=y2){
            s.pstart = p1;
            s.pend = p2;
        }else{
            s.pstart = p2;
            s.pend = p1;
        }
        lseg.push_back(s);
	}
	fin.close();
    
    Node *eventQueueRoot = NULL;
    for(int i=0;i<lseg.size();i++){
        eventQueueRoot = eq.insert(eventQueueRoot,lseg[i].pstart.x,lseg[i].pstart.y);
        eventQueueRoot = eq.insert(eventQueueRoot,lseg[i].pend.x,lseg[i].pend.y);
    }
    eq.levelOrder(eventQueueRoot);
    // while(!eq.isEmpty(eventQueueRoot)){
        
    // }
	// fout.open("intersection_points.txt");
	
	// for (int i=0; i<intersection_points.size(); i++) {
	// 	fout<<intersection_points[i].x<<" "<<intersection_points[i].y<<endl;
	// }
	
	// fout.close();
    return 0;
}