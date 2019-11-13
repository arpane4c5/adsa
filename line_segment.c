//Program to find whether two line segments intersect or not

#include<stdio.h>
#include<stdlib.h>

typedef struct Point2D
{
	float x;
	float y;
}Point2D;

float min(float, float);
float max(float, float);
int direction(Point2D, Point2D, Point2D);		//find direction of P3 w.r.t. line segment (P1, P2)
int on_segment(Point2D, Point2D, Point2D);		//check whether P3 which is collinear actually lies on the segment (P1, P2)
int segments_intersect(Point2D, Point2D, Point2D, Point2D); 	// find whether the segments intersect or not

void main()
{
	Point2D p1, p2, p3, p4;
	int res = -1;
	printf("Program to find whether two line segments (p1,p2) and (p3,p4) intersect or not.\n");
	printf("Enter the points : \n");
	printf("P1 (x,y) : ");
	scanf("%f %f", &p1.x, &p1.y);
	printf("P2 (x,y) : ");
	scanf("%f %f", &p2.x, &p2.y);
	printf("P3 (x,y) : ");
	scanf("%f %f", &p3.x, &p3.y);
	printf("P4 (x,y) : ");
	scanf("%f %f", &p4.x, &p4.y);

	res = segments_intersect(p1, p2, p3, p4);

	if(res == 1)
		printf("Segments Intersect!! \n");
	else
		printf("Segments do not intersect !!\n");

}

float min(float a, float b)
{
	return (a < b) ? a : b;
}

float max(float a, float b)
{
	return (a > b) ? a : b;
}

// Considering p1 as origin, find whether p3 is lying clockwise (+ve det) or anti-clockwise (-ve det) to p2
//  (p2 - p1) and (p3 - p1) are two line segments that form the parallelogram (find cross product)
int direction(Point2D p1, Point2D p2, Point2D p3)
{
	return ((p2.x - p1.x) * (p3.y - p1.y)) - ((p3.x - p1.x) * (p2.y - p1.y)) ;
}

int on_segment(Point2D p1, Point2D p2, Point2D p3)
{
	if ((min(p1.x, p2.x) <= p3.x && p3.x <= max(p1.x, p2.x)) && (min(p1.y, p2.y) <= p3.y && p3.y <= max(p1.y, p2.y)))
		return 1;
	else
		return 0;
}

int segments_intersect(Point2D p1, Point2D p2, Point2D p3, Point2D p4)
{
	float d1, d2, d3, d4;

	// find direction of p1 w.r.t. (p3, p4) segment
	d1 = direction(p3, p4, p1);
	// find direction of p2 w.r.t. (p3, p4) segment
	d2 = direction(p3, p4, p2);
	// find direction of p3 w.r.t. (p1, p2) segment
	d3 = direction(p1, p2, p3);
	// find direction of p4 w.r.t. (p1, p2) segment
	d4 = direction(p1, p2, p4);

	// if p1, p2 straddles (p3,p4) and p3, p4 straddles (p1,p2)
	if(((d1<0 && d2>0) || (d1>0 && d2<0)) && 
		((d3<0 && d4>0) || (d3>0 && d4<0)))
		return 1; 	//True, segments intersect each other
	else if (d1 == 0 && on_segment(p3, p4, p1))
		return 2;	//True, on the line
	else if (d2 == 0 && on_segment(p3, p4, p2))
		return 2;	//True, on the line
	else if (d3 == 0 && on_segment(p1, p2, p3))
		return 2;	//True, on the line
	else if (d4 == 0 && on_segment(p1, p2, p4))
		return 2;	//True, on the line
	else 
		return 0;

}