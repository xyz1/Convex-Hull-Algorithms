#include<bits/stdc++.h>
#include "primitives.h"
#define ull unsigned long long
#define ll long long
#define ff first
#define ss second
#define pb push_back
#define ins insert
#define mp make_pair

using namespace std;

/** class GrahamScan 
*	brief The class has the algorithm to generate a convex hull using Graham's Algorithm
*/
class GrahamScan {
	public: 
	
/** brief GrahamScanHull - Outputs the convex hull given a set of points 
*	\param	arr The vector of input points
*	\return	The vector of the points contained in the Convex Hull of the given set of points
*/
	static vector<point> GrahamScanHull(vector<point> arr)
	{
		if(arr.size()<3)
			return arr;
		pair<point,int> low=primitives::getFirstPoint(arr);     /**< lowest leftmost point must always be there in the Convex Hull */
		fp=low.ff;
		swap(arr[0],arr[low.ss]);
		sort(arr.begin()+1,arr.end(),primitives::compare);      /// sort all points based on polar angle with lowest leftmost point
		vector<point> narr;
		narr.pb(fp);
		for(int i=1;i<arr.size();i++)
		{
			while(i<arr.size()-1 && primitives::orientation(fp,arr[i],arr[i+1])==0)   /// if multiple points with same angle keep only furthest one
			    i++;
			narr.pb(arr[i]);
		}
		stack<point> s;				/**< Points are pushed in order into this stack and checked for their orientation */
		s.push(narr[0]);
		s.push(narr[1]);
		s.push(narr[2]);
		for(int i=3;i<narr.size();i++)
		{
			while(s.size()>1 && primitives::orientation(primitives::nextToTop(s),s.top(),narr[i])!=1)     /// check the orientation after insertion of new point
			    s.pop();
			s.push(narr[i]);
		}
		vector<point> hull;			/**< Contains the points in the convex hull */
		while(!s.empty())           /// contents of stack have the convex hull
		{
			hull.pb(s.top());
			s.pop();
		}
		return hull;
	}
};
/** class JarvisMarch
*	brief The class has the algorithm to generate a convex hull using Jarvis March Algorithm
*/
class JarvisMarch {
	public: 

/** brief JarvisHull - Outputs the convex hull given a set of points  using Jarvis' Algorithm
*	\param	arr The vector of input points
*	\return	The vector of the points contained in the Convex Hull of the given set of points
*/	
	static vector<point> JarvisHull(vector<point> arr)
	{
		if(arr.size()<3)
		    return arr;
		int id=0;
		for(int i=0;i<arr.size();i++)
		    if(arr[i].x<arr[id].x)
		        id=i;
		vector<point> ret;				/**< The vector which would contain all the points in the convex hull */
		int i=id,j;
		do
		{
		    ret.pb(arr[i]);
		    j=(i+1)%arr.size();
		    for(int k=0;k<arr.size();k++)
		    {
		        if(primitives::orientation(arr[i],arr[k],arr[j])==1)
		            j=k;
		    }
		    i=j;
		}while(i!=id);
		return ret;
	}
};


/** class AndrewAlgo
*	brief The class has the algorithms used to generate a convex hull using Andrew's Incremental Algorithm
*/
class AndrewAlgo {
	public: 
	
/** brief compareAndrew - Determines the left point between the two points
*	\param	a The first point
	\param 	b	The second point
*	\return	1 is returned if the first point is to the left of the second point
*				Else, 2 is returned
*/	
	static bool compareAndrew(point a,point b)
	{
		if(a.x<b.x) return 1;
		if(a.x>b.x) return 0;
		return a.y<b.y;
	}
/** brief getUpperHull - Outputs the points present in the upper hull from a given set of points from left to right
*	\param	arr The vector of input points
*	\return	The vector of the points present in the Upper Hull
*/	
	static vector<point> getUpperHull(vector<point> arr)
	{
		stack<point> s;
		s.push(arr[0]);
		s.push(arr[1]);
		for(int i=2;i<arr.size();i++)
		{
		    while(s.size()>1 && primitives::orientation(primitives::nextToTop(s),s.top(),arr[i])!=2){
		        s.pop();
		    }
		    s.push(arr[i]);
		}
		vector<point> ret;
		while(!s.empty())
		{
		    point x=s.top();
		    ret.pb(s.top());
		    s.pop();
		}
		return ret;
	}
	
/** brief AndrewHull - Outputs the convex hull given a set of points  using Andrew's Incremental Algorithm
*	\param	arr The vector of input points
*	\return	The vector of the points contained in the Convex Hull of the given set of points
*/
	static vector<point> AndrewHull(vector<point> arr)
	{
		if(arr.size()<3)
		    return arr;
		sort(arr.begin(),arr.end(),compareAndrew);
		vector<point> upperhull=getUpperHull(arr);
		reverse(arr.begin(),arr.end());
		vector<point> lowerhull=getUpperHull(arr);			/**< The lower hull is generated by reversing the points in the set and running them on the function UpperHull */
		vector<point> ret(upperhull.begin(),upperhull.end());
		for(int i=1;i<lowerhull.size()-1;i++)
		    ret.pb(lowerhull[i]);
		return ret;
	}
	
}; 
