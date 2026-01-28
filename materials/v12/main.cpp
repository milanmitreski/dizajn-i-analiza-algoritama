#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct Point2D {
    int x, y;
};

struct Vector2D {
    int x, y;
};

Vector2D vector2D(const Point2D& A, const Point2D& B) {
    return Vector2D{x: B.x-A.x, y: B.y-A.y};    
}

Vector2D vector2D(const Point2D& A) {
    return vector2D(Point2D{x:0, y:0}, A);
}

double norm2D(Vector2D& v) {
    double dx = 1.0*v.x, dy = 1.0*v.y;
    return sqrt(dx*dx + dy*dy);
}

int dot_prod2D(const Vector2D& v, const Vector2D& u) {
    return v.x*u.x + v.y*u.y;
}

int vec_prod2D(const Vector2D& v, const Vector2D& u) {
    return v.x*u.y - v.y*u.x;
}

bool colinear2D(const Point2D& A, const Point2D& B, const Point2D& M) {
    Vector2D MA = vector2D(M, A), MB = vector2D(M, B);
    return vec_prod2D(MA, MB) == 0;
}

bool in_segment2D(const Point2D& A, const Point2D& B, const Point2D& M) {
    return colinear2D(A, B, M) &&
        min(A.x, B.x) <= M.x && M.x <= max(A.x, B.x) &&
        min(A.y, B.y) <= M.y && M.y <= max(A.y, B.y);
}

double area2D(const Point2D& A, const Point2D& B, const Point2D& C) {
    Vector2D AB = vector2D(A, B), AC = vector2D(A, C);
    return abs(1.0*vec_prod2D(AB, AC))/2.0;
}

double line_distance2D(const Point2D& A, const Point2D& B, const Point2D& C) {
    Vector2D AB = vector2D(A, B), AC = vector2D(A, C);
    return 1.0*vec_prod2D(AB, AC)/norm2D(AB);
}

enum Orientation2D {POSITIVE=1, COLINEAR=0, NEGATIVE=-1};

Orientation2D orientation2D(const Point2D& A, const Point2D& B, const Point2D& C) {
    int d = vec_prod2D(vector2D(A,B), vector2D(A,C));
    if(d > 0)
        return POSITIVE;
    else if(d < 0)
        return NEGATIVE;
    else
        return COLINEAR;
}

bool same_side2D(const Point2D& A, const Point2D& B, const Point2D& M, const Point2D& N) {
    return orientation2D(A, B, M) == orientation2D(A, B, N);
}

bool in_open_triangle2D(const Point2D& T, const Point2D& A, const Point2D& B, const Point2D& C) {
    Orientation2D o1 = orientation2D(A, B, T),
                  o2 = orientation2D(B, C, T),
                  o3 = orientation2D(C, A, T);
    return o1 == o2 && o2 == o3;
}

bool in_closed_triangle2D(const Point2D& T, const Point2D& A, const Point2D& B, const Point2D& C) {
    Orientation2D o1 = orientation2D(A, B, T),
                  o2 = orientation2D(B, C, T),
                  o3 = orientation2D(C, A, T);
    if(o1 == 0 && in_segment2D(A, B, T)) return true;
    if(o2 == 0 && in_segment2D(B, C, T)) return true;
    if(o3 == 0 && in_segment2D(C, A, T)) return true;
    return o1 == o2 && o2 == o3;

}

bool segment_insersects_line2D(const Point2D& A, const Point2D& B, const Point2D& C, const Point2D& D) {
    return orientation2D(A, B, C) * orientation2D(A, B, D) <= 0;
}

bool segments_intersect2D(const Point2D& A, const Point2D& B, const Point2D& C, const Point2D& D) {
    return segment_insersects_line2D(A, B, C, D) &&
           segment_insersects_line2D(C, D, A, B) &&
           max(A.x, B.x) >= min(C.x, D.x) && max(C.x, D.x) >= min(A.x, B.x) &&
           max(A.y, B.y) >= min(C.y, D.y) && max(C.y, D.y) >= min(A.y, B.y);
}

typedef vector<Point2D> Polygon2D;

void polygon2D(Polygon2D& points) {
    auto max = max_element(begin(points), end(points),
                            [](const Point2D& P1, const Point2D& P2) {
                                return P1.x < P2.x || (P1.x == P2.x && P1.y > P2. y);
                            });
    swap(*begin(points), *max);
    const Point2D& P0 = points[0];

    sort(next(begin(points)), end(points),
            [&P0](const Point2D& P1, const Point2D& P2) {
                Orientation2D o = orientation2D(P0, P1, P2);
                Vector2D P0P1 = vector2D(P0,P1), P0P2 = vector2D(P0, P2);
                if(o == COLINEAR) return norm2D(P0P1) <= norm2D(P0P2);
                return o == POSITIVE;
            });

    auto it = prev(end(points));
    while(orientation2D(*prev(it), *it, P0) == COLINEAR)
        it = prev(it);
    reverse(it, end(points));
}

bool point_in_convex_polygon2D(const Polygon2D& points, const Point2D Q, int i, int j) {
    if(j - i == 1)
        return in_closed_triangle2D(Q, points[0], points[i], points[j]);
    
    int m = i + (j - i) / 2;
    if(orientation2D(points[0], points[m], Q) == Orientation2D::POSITIVE)
        return point_in_convex_polygon2D(points, Q, m, j);
    else
        return point_in_convex_polygon2D(points, Q, i, m);
}

bool point_in_convex_polygon2D(const Polygon2D& points, const Point2D Q) {
    return point_in_convex_polygon2D(points, Q, 1, points.size()-1);
}

Polygon2D convex_hull_graham2D(Polygon2D& points) {
    auto max = max_element(begin(points), end(points),
                            [](const Point2D& P1, const Point2D& P2) {
                                return P1.x < P2.x || (P1.x == P2.x && P1.y > P2. y);
                            });
    swap(*begin(points), *max);
    const Point2D& P0 = points[0];

    sort(next(begin(points)), end(points),
            [&P0](const Point2D& P1, const Point2D& P2) {
                Orientation2D o = orientation2D(P0, P1, P2);
                Vector2D P0P1 = vector2D(P0,P1), P0P2 = vector2D(P0, P2);
                if(o == COLINEAR) return norm2D(P0P1) <= norm2D(P0P2);
                return o == POSITIVE;
            });

    Polygon2D convex_hull;
    convex_hull.push_back(points[0]);
    convex_hull.push_back(points[1]);
    for(int i = 2; i < points.size(); i++) {
        while(convex_hull.size() > 2 && 
                orientation2D(convex_hull[convex_hull.size()-2], 
                    convex_hull[convex_hull.size()-1], 
                    points[i]) != Orientation2D::POSITIVE)
            convex_hull.pop_back();
        convex_hull.push_back(points[i]);
    }

    return convex_hull;
}

int main() {
    /* THE END :) */
}