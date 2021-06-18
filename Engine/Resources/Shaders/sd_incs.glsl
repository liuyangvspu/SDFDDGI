
float sdInter(float distA, float distB) {
    return max(distA, distB);
}

float sdUnion(float distA, float distB) {
    return min(distA, distB);
}

float sdDiff(float distA, float distB) {
    return max(distA, -distB);
}
float smoothMin(float da, float db, float k){
	float h = max(k - abs(da - db), 0.) / k;
    return min(da, db) - h*h*h*k*1./6.;

}
float sdBox( vec3 p, vec3 pos, vec3 b ){
    p -= pos;
  vec3 q = abs(p) - b;
  return length(max(q,0.0)) + min(max(q.x,max(q.y,q.z)),0.0);
}


float sdHexPrism( vec3 p, vec3 pos, vec2 h ){
  const vec3 k = vec3(-0.8660254, 0.5, 0.57735);
  p -= pos;
  p = abs(p);
  p.xy -= 2.0*min(dot(k.xy, p.xy), 0.0)*k.xy;
  vec2 d = vec2(
       length(p.xy-vec2(clamp(p.x,-k.z*h.x,k.z*h.x), h.x))*sign(p.y-h.x),
       p.z-h.y );
  return min(max(d.x,d.y),0.0) + length(max(d,0.0));
}
float sdCapsule( vec3 p, vec3 a, vec3 b, float r){
	vec3 ab = b - a;
    vec3 ap = p - a;
    float t = dot(ap, ab) / dot(ab,ab);
    t = clamp(t, 0., 1.);
    vec3 c = a + (t * ab);
    return length(p -c) - r;
    
    
}
float sdSphere( vec3 point, Sphere sphere ){
	return length(point - sphere.position) - sphere.radius;
}

float sdTorus( vec3 p, vec3 pos, vec2 r ){
    p -= pos;
	float x = length(p.xz) - r.x;
	return length(vec2(x, p.y)) - r.y;
}

#include "march_dist.glsl"