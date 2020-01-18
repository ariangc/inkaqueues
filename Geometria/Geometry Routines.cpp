// C++ routines for computational geometry

const ld INF = 1e100;
const ld EPS = 1e-12;
const ld PI = acos(-1);

struct PT { 
  ld x, y; 
  PT() {}
  PT(ld x, ld y) : x(x), y(y) {}
  PT(const PT &p) : x(p.x), y(p.y)   {}
  PT operator + (const PT &p)  const { return PT(x+p.x, y+p.y); }
  PT operator - (const PT &p)  const { return PT(x-p.x, y-p.y); }
  PT operator * (ld c)    const { return PT(x*c,   y*c  ); }
  PT operator / (ld c)    const { return PT(x/c,   y/c  ); }
};

ld dot(PT p, PT q)    { return p.x*q.x+p.y*q.y; }
ld norm(PT p) { return sqrt(dot(p,p)); }
ld dist2(PT p, PT q)   { return dot(p-q,p-q); }
ld cross(PT p, PT q)   { return p.x*q.y-p.y*q.x; }

ld angle(PT p){
   ld res = acos(p.x / norm(p));   
   if (p.y > 0) return res;
   else return 2*PI - res;
}

// rotate a point CCW or CW around the origin
PT RotateCCW90(PT p)   { return PT(-p.y,p.x); }
PT RotateCW90(PT p)   { return PT(p.y,-p.x); }
PT RotateCCW(PT p, ld t) { 
  return PT(p.x*cos(t)-p.y*sin(t), p.x*sin(t)+p.y*cos(t)); 
}

// project point c onto line through a and b
// assuming a != b
PT ProjectPointLine(PT a, PT b, PT c) {
  return a + (b-a)*dot(c-a, b-a)/dot(b-a, b-a);
}

// project point c onto line segment through a and b
PT ProjectPointSegment(PT a, PT b, PT c) {
  ld r = dot(b-a,b-a);
  if (fabs(r) < EPS) return a;
  r = dot(c-a, b-a)/r;
  if (r < 0) return a;
  if (r > 1) return b;
  return a + (b-a)*r;
}

// distance from c to segment between a and b
ld DistancePointSegment(PT a, PT b, PT c) {
  return sqrt(dist2(c, ProjectPointSegment(a, b, c)));
}

// distance between point (x,y,z) and plane ax+by+cz=d
ld DistancePointPlane(ld x, ld y, ld z,
            ld a, ld b, ld c, ld d)
{
  return fabs(a*x+b*y+c*z-d)/sqrt(a*a+b*b+c*c);
}

// Whethes lines (a,b), (c,d) are parallel/collinear
bool LinesParallel(PT a, PT b, PT c, PT d) { 
  return fabs(cross(b-a, c-d)) < EPS; 
}
bool LinesCollinear(PT a, PT b, PT c, PT d) { 
  return LinesParallel(a, b, c, d)
     && fabs(cross(a-b, a-c)) < EPS
     && fabs(cross(c-d, c-a)) < EPS; 
}

// determine if line segment from a to b intersects with 
// line segment from c to d
bool SegmentsIntersect(PT a, PT b, PT c, PT d) {
   if (LinesCollinear(a, b, c, d)) {
      if (dist2(a, c) < EPS || dist2(a, d) < EPS ||
         dist2(b, c) < EPS || dist2(b, d) < EPS) return true;
      if (dot(c-a, c-b) > 0 && dot(d-a, d-b) > 0 && 
          dot(c-b, d-b) > 0) return false;
      return true;
  }
  if (cross(d-a, b-a) * cross(c-a, b-a) > 0) return false;
  if (cross(a-c, d-c) * cross(b-c, d-c) > 0) return false;
  return true;
}

// compute intersection of line passing through a and b
// with line passing through c and d, assuming that unique
// intersection exists; for segment intersection, check if
// segments intersect first
PT ComputeLineIntersection(PT a, PT b, PT c, PT d) {
  b=b-a; d=c-d; c=c-a;
  assert(dot(b, b) > EPS && dot(d, d) > EPS);
  return a + b*cross(c, d)/cross(b, d);
}

// compute center of circle given three points
PT ComputeCircleCenter(PT a, PT b, PT c) {
  b=(a+b)/2;
  c=(a+c)/2;
  return ComputeLineIntersection(b, b+RotateCW90(a-b), c, c+RotateCW90(a-c));
}

// determine if point is in a possibly non-convex polygon 
// (by William Randolph Franklin); returns 1 for strictly
// interior points, 0 for strictly exterior points, and 0 or 1
// for the remaining points. Note that it is possible to
// convert this into an *exact* test using integer arithmetic
// by taking care of the division appropriately (making sure 
// to deal with signs properly) and then by writing exact
// tests for checking point on polygon boundary
bool PointInPolygon(const vector<PT> &p, PT q) {
  bool c = 0;
  for (int i = 0; i < p.size(); i++){
   int j = (i+1)%p.size();
   if (((p[i].y <= q.y && q.y < p[j].y) || 
     (p[j].y <= q.y && q.y < p[i].y)) &&
     q.x < p[i].x + (p[j].x - p[i].x) *(q.y - p[i].y) / 
      (p[j].y - p[i].y))
     c = !c;
  }
  return c;
}

// determine if point is on the boundary of a polygon
bool PointOnPolygon(const vector<PT> &p, PT q) {
  for (int i = 0; i < p.size(); i++){
   if (dist2(ProjectPointSegment(p[i], p[(i+1)%p.size()], q), q) < EPS)
     return true;
  }
  
  return false;
}

// compute intersection of line through points a and b with
// circle centered at c with radius r > 0
vector<PT> CircleLineIntersection(PT a, PT b, PT c, ld r) {
  vector<PT> ret;
  b = b-a;
  a = a-c;
  ld A = dot(b, b);
  ld B = dot(a, b);
  ld C = dot(a, a) - r*r;
  ld D = B*B - A*C;
  if (D < -EPS) return ret;
  ret.push_back(c+a+b*(-B+sqrt(D+EPS))/A);
  if (D > EPS)
   ret.push_back(c+a+b*(-B-sqrt(D))/A);
  return ret;
}

// compute intersection of circle centered at a with radius r
// with circle centered at b with radius R
vector<PT> CircleCircleInter(PT a, PT b, ld r, ld R) {
  vector<PT> ret(0);
  ld d = sqrt(dist2(a, b));
  if (d > r+R + EPS || d+min(r, R) + EPS < max(r, R)) return ret;
  ld x = (d*d-R*R+r*r)/(2*d);
  ld y = sqrt(r*r-x*x);
  PT v = (b-a)/d;
  ret.push_back(a+v*x + RotateCCW90(v)*y);
  if (y > 0)
   ret.push_back(a+v*x - RotateCCW90(v)*y);
  return ret;
}

// Area or centroid of a (possibly nonconvex) polygon, 
// assuming the coordinates are listed in a clockwise or
// counterclockwise order.  Note that the centroid is often
// known as the "center of gravity" or "center of mass".
ld ComputeSignedArea(const vector<PT> &p) {
  ld area = 0;
  for(int i = 0; i < p.size(); i++) {
   int j = (i+1) % p.size();
   area += p[i].x*p[j].y - p[j].x*p[i].y;
  }
  return area / 2.0;
}

ld ComputeArea(const vector<PT> &p) {
  return fabs(ComputeSignedArea(p));
}

PT ComputeCentroid(const vector<PT> &p) {
  PT c(0,0);
  ld scale = 6.0 * ComputeSignedArea(p);
  for (int i = 0; i < p.size(); i++){
   int j = (i+1) % p.size();
   c = c + (p[i]+p[j])*(p[i].x*p[j].y - p[j].x*p[i].y);
  }
  return c / scale;
}

// Whether or not a given (CW or CCW) polygon is simple
bool IsSimple(const vector<PT> &p) {
  for (int i = 0; i < p.size(); i++) {
   for (int k = i+1; k < p.size(); k++) {
     int j = (i+1) % p.size();
     int l = (k+1) % p.size();
     if (i == l || j == k) continue;
     if (SegmentsIntersect(p[i], p[j], p[k], p[l])) 
      return false;
   }
  }
  return true;
}

// Computes the circumcenter of a Triangle PQR
PT circumcenter(PT p, PT q, PT r) {
   PT a = p-r, b = q-r;
   PT c = PT(dot(a, (p + r)) / 2, dot(b, (q + r)) / 2);
   return PT(dot(c, RotateCW90(PT(a.y, b.y))), 
      dot(PT(a.x, b.x), RotateCW90(c))) / dot(a, RotateCW90(b));
}