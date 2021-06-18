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
