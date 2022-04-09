
point findnewEvent(segment sl, segment sr, point p_){
    double a1 = sl.pend.y - sl.pstart.y;
	double b1 = sl.pstart.x - sl.pend.x;
	double c1 = a1 * (sl.pstart.x) + b1 * (sl.pstart.y);

    double a2 = sr.pend.y - sr.pstart.y;
	double b2 = sr.pstart.x - sr.pend.x;
	double c2 = a2 * (sr.pstart.x) + b2 * (sr.pstart.y);

    double determinant = a1 * b2 - a2 * b1;

	point p = {.x=FLT_MAX, .y=FLT_MAX};

    if (determinant != 0)
	{
		double x = (b2 * c1 - b1 * c2) / determinant;
		double y = (a1 * c2 - a2 * c1) / determinant;

        if(y >= max(sl.pend.y, sr.pend.y) && y <= min(sl.pstart.y, sr.pstart.y) && (y<=p_.y)) {
			p.x = x;
			p.y = y;
		}
	}
	return p;
}