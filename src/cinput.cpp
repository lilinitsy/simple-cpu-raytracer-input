#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include "types.h"

/* This version will use a very C style input
 * based on FILE pointers. It will use fopen
 * and C functions to read.
*/


Scene parse_scene(std::string inputfile)
{
	Scene scene;

	/* Use a file pointer to open a stream to the inputfile
	 * "r" means to open the file for reading and only reading
	*/
	FILE *fp = fopen(inputfile.c_str(), "r");

	// Error checking for if the file doesn't exist
	if(fp == NULL)
	{
		fprintf(stderr, "Can't open file %s, exiting now\n", inputfile.c_str());
		exit(-1);
	}

	// Use a fixed max line width. 1024 should do the trick.
	size_t maxlength = 1024;
	char line[maxlength];

	/* Can loop through each line
	 * with fgets on the file pointer.
	 * Doing this within the while loop call
	 * will call fgets each iteration of the loop.
	*/
	while(fgets(line, maxlength, fp))
	{
		/* Line is now a char*, or a char aray.
		 * This means we can either operate on the whole
		 * array with some string methods, or check the
		 * ith element to see what an individual character is.
		 * 
		 * The first thing to do would be to check for comment lines,
		 * denoted by a '#', with single quotes as opposed to double.
		*/
		if(line[0] == '#')
		{
			// Don't need to do anything with the comment, but can still print it.
			printf("Skipping comment: %s\n", line);

			// Continue will skip the rest of this iteration of the loop.
			continue;
		}

		/* The first word in a line should be a keyword.
		 * It won't be uber long, so we can cap the length
		 * and read it as a char array.
		*/
		size_t cmdlength = 128;
		char cmd[cmdlength];

		// Read a contiguous string into cmd, delimited by spaces, with sscanf
		int32_t fields_read = sscanf(line, "%s ", cmd);

		/* sscanf will return the number of arguments filled.
		 * If no arguments are filled, then presumably no
		 * command was read, and we can continue.
		*/
		if(fields_read < 1)
		{
			// Skip the rest of this iteration
			continue;
		}

		/* Now we can do all the string comparisons
		 * This will operate by using the strcmp function,
		 * which will return 0 if two compared strings are the same.
		 * Read the documentation for other return values, which won't
		 * be handled here.
		*/
		if(strcmp(cmd, "sphere") == 0)
		{
			// Declare variables that will be read in
			vec3 p;
			float r;

			/* Format the input with sscanf in the order that
			 * the keyword will be expecting args.
			 * Sphere expects x, y, z, r, and
			 * they'll be floats, so read in %f four times in a row.
			 * Make sure you're reading in the keyword too, since
			 * this operates on the whole line still, even though
			 * we already parsed the first word from the line.
			*/
			sscanf(line, "sphere %f %f %f %f", &p.x, &p.y, &p.z, &r);

			// Now make the sphere and add it to the scene.
			Sphere sphere = {
				.position = p,
				.radius	  = r,
			};

			// Add the sphere to the scene
			scene.spheres.push_back(sphere);

			// Print out the sphere just to make sure that it was read properly.
			printf("Sphere (Position: %f %f %f)\t(Radius: %f)\n",
				   sphere.position.x, sphere.position.y, sphere.position.z, sphere.radius);
		}

		if(strcmp(cmd, "eye") == 0)
		{
			vec3 eye;
			sscanf(line, "eye %f %f %f", &eye.x, &eye.y, &eye.z);
			scene.eye_position = eye;
			printf("Eye position: %f %f %f\n", scene.eye_position.x, scene.eye_position.y, scene.eye_position.z);
		}

		if(strcmp(cmd, "viewdir") == 0)
		{
			vec3 viewdir;
			sscanf(line, "viewdir %f %f %f", &viewdir.x, &viewdir.y, &viewdir.z);
			scene.viewdirection = viewdir;
			printf("Viewdir: %f %f %f\n", scene.viewdirection.x, scene.viewdirection.y, scene.viewdirection.z);
		}

		if(strcmp(cmd, "updir") == 0)
		{
			vec3 updir;
			sscanf(line, "updir %f %f %f", &updir.x, &updir.y, &updir.z);
			scene.updir = updir;
			printf("updir: %f %f %f\n", scene.updir.x, scene.updir.y, scene.updir.z);
		}

		if(strcmp(cmd, "vfov") == 0)
		{
			float vfov;
			sscanf(line, "vfov %f", &vfov);
			scene.vfov = vfov;
			printf("vfov: %f\n", scene.vfov);
		}
	}


	return scene;
}



int main(int argc, char *argv[])
{
	/* First we should check the number of arguments.
	 * This will only take in an input, no output file.
	 * Therefore, there should be only 2 arguments.
	*/

	if(argc != 2)
	{
		fprintf(stderr, "Only the raytracer input file should be passed in! Exiting now!\n");
		exit(-1);
	}

	std::string inputfile_name = argv[1];
	Scene scene				   = parse_scene(inputfile_name);

	return 0;
}
