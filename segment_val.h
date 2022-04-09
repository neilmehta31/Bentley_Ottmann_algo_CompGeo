class Segment
{
  public:
    pair<double,double> beg;
    pair<double,double> end;
    Segment()
    {

    }
    Segment(pair<double,double> a,pair<double,double> b)
    {
      beg=a;
      end=b;
    }
};