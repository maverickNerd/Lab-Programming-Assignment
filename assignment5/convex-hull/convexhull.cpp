#include<iostream>
#include<bits/stdc++.h>

#define ptspair pair<int,int>

using namespace std;

set<ptspair> hull;

int findside(ptspair p1, ptspair p2, ptspair p)
{
    int val=(( p2.first - p1.first )*( p.second - p1.second ))-
            (( p2.second - p1.second )*( p.first - p1.first ));

    if( val > 0 )
    {
        return 1;
    }

    if( val == 0 )
    {
        return 0;
    }

    if( val < 0 )
    {
        return -1;
    }
}

int distance( ptspair p1, ptspair p2, ptspair p )
{
    return abs(( p.second - p1.second )*( p2.first - p1.first )-
                ( p2.second - p1.second )*( p.first - p1.first ));
}

void findhull(ptspair a[], int n, ptspair p1, ptspair p2, int side)
{
    int ind = -1;
    int max_dist = 0;

    for(int i=0; i<n; i++)
    {
        int temp = distance( p1, p2, a[i] );
        if( findside( p1, p2, a[i] ) == side && temp > max_dist )
        {
            ind = i;
            max_dist = temp;
        }
    }

    if( ind == -1 )
    {
        hull.insert( p1 );
        hull.insert( p2 );
        return;
    }

    findhull(a, n, a[ind], p1, -findside( a[ind], p1, p2 ));
    findhull(a, n, a[ind], p2, -findside( a[ind], p2, p1 ));
}

void ptsonhull(ptspair a[], int n)
{
    if(n < 3)
    {
        cout<<"Convex hull not possible\n";
        return;
    }

    int minx = 0,maxx = 0;

    for(int i=0; i<n; i++)
    {
        if( minx > a[i].first )
            minx = a[i].first;

        if( maxx < a[i].first )
            maxx=a[i].first;
    }

    findhull(a, n, a[minx], a[maxx], 1);

    findhull(a, n, a[minx], a[maxx], -1);

    cout<<"The points on the Hull are:\n";

    while(!hull.empty())
    {
        cout<<"("<<( *hull.begin() ).first<<","<<(*hull.begin()).second<<")"<<"\n";

        hull.erase(hull.begin());
    }
}

int main()
{
    int x, y;
    int n=8;
    cout<<"Total input points are 8 \n";

    ptspair points[n] = {{0, 4}, {1, 1}, {2, 2}, {3, 3}, {0, 0}, {1, 4}, {4, 1}, {4, 4}};
    cout << "Initial Points are:\n";
    for (int i=0; i<n; i++) {
       cout << "(" << points[i].first << ',' << points[i].second << ")" << '\n';
    }    
    ptsonhull(points, n);

    return 0;
}
