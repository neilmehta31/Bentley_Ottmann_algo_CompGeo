#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include "segment_val.h"

using namespace std;
vector<pair<pair<double,double>,pair<Segment,Segment>>> intersection_points;

void printSegment(Segment* r)
{
    if(r == NULL) cout << "NULL\t";
    else
     cout << "(" << r->beg.first << "," << r->beg.second << ")"  << " " << "(" << r->end.first << "," << r->end.second << ")  ";       
}
bool get_line_intersection(Segment *p, Segment *q, double *i_x, double *i_y)
  {
    double p0_x = p->beg.first;
    double p0_y = p->beg.second;
    double p1_x = p->end.first;
    double p1_y = p->end.second;

    double p2_x = q->beg.first;
    double p2_y = q->beg.second;
    double p3_x = q->end.first;
    double p3_y = q->end.second;

    double s1_x, s1_y, s2_x, s2_y;
    s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
    s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

    double s, t;
    //cout<<(-s2_x * s1_y + s1_x * s2_y);
    s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
    t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        //cout<<"Collision detected ";
        if (i_x != NULL)
            *i_x = p0_x + (t * s1_x);
        if (i_y != NULL)
            *i_y = p0_y + (t * s1_y);
        return true;
    }

    return false; // No collision
  }
int helper()
{
    time_t start,end;
    time(&start);
    vector<Segment*> segments;
    fstream newfile;
    newfile.open("testcases.txt",ios::in); 
    if (newfile.is_open()){                                //mechanism to take input from a text file for testing purposes 
        string tp;
        while(getline(newfile, tp)){ 
            vector <string> tokens;
        
            stringstream check1(tp);
            
            string intermediate;
            while(getline(check1, intermediate, ' '))
            {
                tokens.push_back(intermediate);
            }
            double x1 = std::stod(tokens[0]);
            double y1 = std::stod(tokens[1]);
            double x2 = std::stod(tokens[2]);
            double y2 = std::stod(tokens[3]); 
            segments.push_back(new Segment(make_pair(x1,y1),make_pair(x2,y2)));
        }
        newfile.close(); //close the file object.
    }
    for(unsigned int i = 0; i < segments.size()-1; i++)
    {
        for(unsigned j =i+1; j<segments.size(); j++)
        {
            double *i_x=(double*) malloc(sizeof(double));
            double *i_y=(double*) malloc(sizeof(double));
            if(get_line_intersection(segments[i],segments[j],i_x,i_y))
            {
                pair<double,double> point = make_pair(*i_x,*i_y);
                pair<Segment,Segment> forSeg = make_pair(*segments[i],*segments[j]);
                intersection_points.push_back(make_pair(point,forSeg));
            }
        }
    }
    time(&start);
    
    return 1;
}