#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>

#include "types.h"


Scene parse_scene(std::string inputfile)
{
	Scene scene;

	// Open the inputstream (comes from <fstream>) to
	std::ifstream inputstream(inputfile, std::ios::in | std::ios::binary);

	// Thanks to Linden Killam for a lot of this
	if(!inputstream.is_open())
	{
		fprintf(stderr, "Could not open input stream with inputfile %s\n", inputfile.c_str());
		exit(-1);
	}

	/* Loop through each line C++'s built-in function
	 * from the standard library, std::getline.
	 * Much like in the C version, this should be done in
	 * a loop.
	 * 
	 * Will also need to make a string to store the cmd in.
	*/
	std::string cmd;

	/* Even though it's called getline, using it this way reads in single words. 
	 * We will be going through the whole line per iteration though, due
	 * to the way we're reading in the streams.
	 * 
	 * See cppstrinput.cpp for the stinrgstream method reading entire lines at once.
	 * It's more "elegant" and "proper" but this is a hack that works.
	*/
	while(std::getline(inputstream, cmd, ' '))
	{
		/* The first word in a line is stored in line EXCEPT for the last newline char.
		 * There are two ways around this: The way demonstrated, and using stringstreams.
		 * I'll prefer this way so that we don't have to explicitly parse strings.
		*/

		if(cmd == "sphere")
		{
			vec3 p;
			float r;

			/* Read in the words from the stream.
			 * This stream doesn't read them in as strings,
			 * but will operate on them as whatever types
			 * that are being read in are.
			*/
			inputstream >> p.x >> p.y >> p.z >> r;
			Sphere sphere = {
				.position = p,
				.radius	  = r,
			};

			scene.spheres.push_back(sphere);
			printf("Sphere (Position: %f %f %f)\t(Radius: %f)\n",
				   sphere.position.x, sphere.position.y, sphere.position.z, sphere.radius);
		}

		else if(cmd == "eye")
		{
			vec3 eye;
			
			inputstream >> eye.x >> eye.y >> eye.z;
			scene.eye_position = eye;
			printf("Eye position: %f %f %f\n", scene.eye_position.x, scene.eye_position.y, scene.eye_position.z);
		}

		else if(cmd == "viewdir")
		{
			vec3 viewdir;
			inputstream >> viewdir.x >> viewdir.y >> viewdir.z;
			scene.viewdirection = viewdir;
						printf("Viewdir: %f %f %f\n", scene.viewdirection.x, scene.viewdirection.y, scene.viewdirection.z);
		}

		else if(cmd == "updir")
		{
			vec3 updir;
			inputstream >> updir.x >> updir.y >> updir.z;
			scene.updir = updir;
			printf("updir: %f %f %f\n", scene.updir.x, scene.updir.y, scene.updir.z);		
		}

		else if(cmd == "vfov")
		{
			float vfov;
			inputstream >> vfov;
			scene.vfov = vfov;
			printf("vfov: %f\n", scene.vfov);
		}

		/* Now advance to the last "word" which is the newline character.
		 * This is necessary because with the loop we have that's reading in,
		 * it delimits based only on spaces, not newlines.
		*/
		std::getline(inputstream, cmd, '\n');
	}

	// Safety, make sure to close the input stream
	inputstream.close();

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
