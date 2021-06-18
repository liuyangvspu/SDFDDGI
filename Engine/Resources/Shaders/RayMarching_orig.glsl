#version 460
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec4 o_color;
layout(location = 0) out vec4 outColor;
uniform float u_time;

struct Ray{
	vec3 origin;
    vec3 direction;
};

struct Sphere{
	vec3 position;
    float radius;
    vec3 color;
    
};
    
struct RayHit{
	float dist;
    vec3 color;
};
    
Ray getRay(vec2 uv, vec3 cameraPosition, vec3 lookAt, float zoom){
	Ray ray;
    ray.origin = cameraPosition;
    
    vec3 front = normalize(lookAt - ray.origin);
    vec3 right = cross(vec3(0., 1., 0.), front);
    vec3 up = cross(front, right);
    vec3 center = ray.origin + front * zoom;
    vec3 intersectionPointOfScreen = center + uv.x * right + uv.y * up;
    ray.direction = normalize(intersectionPointOfScreen - ray.origin);
    return ray;
}

#define MAX_MARCH_STEPS 128
#define SURFACE_HIT_DISTANCE 0.004
#define MAX_DISTANCE_MARCHABLE 1024.

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
RayHit getMarchDistance(vec3 point){
    Sphere spheres[4];
    int i = 0;
    spheres[i].position = vec3(0., 3., 11.); spheres[i++].radius = 2.;
    spheres[i].position = vec3(2. * cos(u_time), 3., 11.); spheres[i++].radius = 1.;
    spheres[i].position = vec3(2. * -cos(u_time), 3., 11.); spheres[i++].radius = 1.;
    spheres[i].position = vec3(7., 1.25 + 2.*(sin(u_time*1.5f)), 10.); spheres[i++].radius = 1.;
    
    const int modelCount = 11;
    RayHit rayHits[modelCount];
    rayHits[10].dist = sdHexPrism(point, vec3(-2., 2., 2.), vec2(.5, .25));rayHits[10].color = vec3(1., 1., 0.);
    rayHits[0].dist = sdSphere(point, spheres[0]);rayHits[0].color = vec3(0., 0., 1.);
    rayHits[1].dist = sdSphere(point, spheres[1]);rayHits[1].color =  vec3(0., 0., 1.);
    rayHits[2].dist = sdSphere(point, spheres[2]);rayHits[2].color =  vec3(0., 0., 1.);
    rayHits[3].dist = sdSphere(point, spheres[3]);rayHits[3].color =  vec3(1., 0., 0.);
    rayHits[4].dist = sdCapsule(point, vec3(-20., 5. * abs(sin(u_time * 3.)) + 1., 30.), vec3(-15., 5. * abs(cos(u_time * 3.)) + 1., 35.), 1.);
    rayHits[4].color =  vec3(1., 0., 1.);
    vec3 moving = vec3(0., 0.5, 3.);
    vec3 moving2 = vec3(0., 0.5, 3.);
    moving.xz += vec2(sin(u_time), cos(u_time));
    moving2.xz -= vec2(sin(u_time), cos(u_time));
    rayHits[5].dist = sdCapsule(point,vec3(0., 1.5, 3.),moving, .12);rayHits[5].color =  vec3(0., 1., 0.);
    rayHits[6].dist = sdCapsule(point,vec3(0., 1.5, 3.),moving2, .12);rayHits[6].color =  vec3(0., 1., 0.);
    rayHits[7].dist = sdTorus(point,  vec3(0., .5, 3.), vec2(1., .5));rayHits[7].color =  vec3(0., 1., 0.);
    rayHits[8].dist = sdBox(point,  vec3(7., 1., 10.), vec3(1., 1., 1.));rayHits[8].color =  vec3(1., 0., 0.);
    rayHits[9].dist = point.y;rayHits[9].color =  vec3(1., 1., 1.);
    float distanceFromPlane = point.y;
    float capDist = sdCapsule(point, vec3(-10., 1., 10.), vec3(-9.75, 1., 15.), 1.);
   
    int minValueIndex = 0;
    float minValue = rayHits[minValueIndex].dist;
    RayHit rayHit; rayHit.dist = minValue; rayHit.color = rayHits[minValueIndex].color;
    for(int k = 0; k < modelCount; k++){
        float compareValue = rayHits[k].dist;
        if(compareValue < rayHits[minValueIndex].dist){
            minValueIndex = k;

        }
    		minValue = smoothMin(minValue, compareValue, 0.64);
        
    }
	rayHit.color = rayHits[minValueIndex].color;
    rayHit.dist = minValue;
    
    return rayHit;
}




vec3 getNormal(vec3 point){
	vec2 change = vec2(0.01, 0.);
    RayHit rayHit = getMarchDistance(point);
    vec3 normal = vec3(rayHit.dist - getMarchDistance(point - change.xyy).dist,rayHit.dist - getMarchDistance(point - change.yxy).dist,
                       rayHit.dist - getMarchDistance(point - change.yyx).dist);
    return normalize(normal);

}



RayHit rayMarch(Ray ray){
 	RayHit rayHit;rayHit.dist = 0.;
    for(int i = 0; i < MAX_MARCH_STEPS; i++){
    	vec3 pointMarchingFrom = ray.origin + rayHit.dist * ray.direction;
        RayHit distanceToNextMarch = getMarchDistance(pointMarchingFrom);
        rayHit.dist += distanceToNextMarch.dist;
        rayHit.color = distanceToNextMarch.color;

        if(distanceToNextMarch.dist < SURFACE_HIT_DISTANCE || rayHit.dist > MAX_DISTANCE_MARCHABLE) break;
    
    }
    return rayHit;
    
}
    


float getLight(vec3 point){
    vec3 lightPosition = vec3(0, 4, -3);lightPosition.xz += vec2(sin(u_time), cos(u_time));
    vec3 lightVector = normalize(lightPosition - point);
    vec3 normal = getNormal(point);
    float dif = clamp(dot(normal, lightVector), 0., 1.);
    
    Ray pointToLightRay; pointToLightRay.origin = point + normal * SURFACE_HIT_DISTANCE * 2.; pointToLightRay.direction = normalize(lightPosition - point);
    float distToLight = rayMarch(pointToLightRay).dist;
    if(distToLight < length(lightPosition - point)) dif *= 0.05;
	return dif ;
}

vec3 phongContribForLight(vec3 k_d, vec3 k_s, float alpha, vec3 p, vec3 eye,
                          vec3 lightPos, vec3 lightIntensity) {
    vec3 N = getNormal(p);
    vec3 L = normalize(lightPos - p);
    vec3 V = normalize(eye - p);
    vec3 R = normalize(reflect(-L, N));
    
    float dotLN = clamp(dot(L, N),0.,1.); 
    float dotRV = dot(R, V);
    
    if (dotLN < 0.0) return vec3(0.0, 0.0, 0.0);
    if (dotRV < 0.0)  return lightIntensity * (k_d * dotLN);

    return lightIntensity * (k_d * dotLN + k_s * pow(dotRV, alpha));
}
vec3 phongIllumination(vec3 k_a, vec3 k_d, vec3 k_s, float alpha, vec3 p, vec3 eye) {
    const vec3 ambientLight = 0.5 * vec3(1.0, 1.0, 1.0);
    vec3 color = ambientLight * k_a;
    
    vec3 light1Pos = vec3(4.0 * sin(u_time),
                          2.0,
                          4.0 * cos(u_time));
    vec3 light1Intensity = vec3(0.4, 0.4, 0.4);
    
    color += phongContribForLight(k_d, k_s, alpha, p, eye,
                                  light1Pos,
                                  light1Intensity);
    
    vec3 light2Pos = vec3(2.0 * sin(0.37 * u_time),
                          2.0 * cos(0.37 * u_time),
                          9.0);
    vec3 light2Intensity = vec3(0.4, 0.4, 0.4);
    
    color += phongContribForLight(k_d, k_s, alpha, p, eye,
                                  light2Pos,
                                  light2Intensity);    
    return color;
}


vec2 iResolution = vec2(640, 480);
void main(){
    vec2 uv = (gl_FragCoord.xy - 0.5 * iResolution.xy)/iResolution.y;
    uv.y = uv.y;
	vec3 resultingColor = vec3(0);
    
    Ray cameraRay;
    vec3 cameraPos = vec3(0., 3., -5.);vec3 lookAt = vec3(0., 2.5, 0.); float zoom = 1.;
    cameraRay = getRay(uv, cameraPos, lookAt, zoom);
    
    
    RayHit rayMarch = rayMarch(cameraRay);
    
    vec3 point = cameraRay.origin + (cameraRay.direction * rayMarch.dist);
    vec3 K_a = vec3(0.005);
    vec3 K_s = vec3(1., .1, .1);
    float shininess = 3.;
    
    vec3 color = phongIllumination(K_a, rayMarch.color, K_s, shininess, point, cameraRay.origin);
    //resultingColor = getNormal(point); //for visualizing normals
    outColor =  vec4(color, o_color.a);
}