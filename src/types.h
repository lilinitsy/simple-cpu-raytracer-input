#ifndef TYPES_H
#define TYPES_H

#include <vector>

/* Define basic datatypes that will be read in.
 * We only need a few, because basically everything
 * resides in 3D space, so everything is defined
 * either as a vector, or in terms of vectors.
 * More complicated types or aliases, such as colours,
 * could also be defined, but would add to the complexity.
*/

struct vec3
{
	float x;
	float y;
	float z;
};

struct Sphere
{
	vec3 position;
	float radius;
};

struct Scene
{
	std::vector<Sphere> spheres;
	vec3 eye_position;
	vec3 viewdirection;
	vec3 updir;
	float vfov;
	float width;
	float height;
	vec3 bkgcolour;
};


#endif