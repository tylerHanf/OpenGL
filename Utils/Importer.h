#ifndef IMPORTER_H
#define IMPORTER_H

#include <vector>
#include <string>

/*
 * Handles import of data from .OBJ file to ImportedModel class
 */
class Importer {
 	//Init Vectors
        std::vector<float> vertices;
        std::vector<float> texels;
        std::vector<float> normals;

        //Final Vectors
        std::vector<float> triVerts;
        std::vector<float> textCoords;
        std::vector<float> norms;
        std::string texturePath;

	public:
                //Reads in various data from .obj file
		void readFile(const char* filename);
                //Gets the filepath of the texture associated with the object
                std::string getTextureName(std::string mtl_name);
		std::vector<float> getVertices(void);
		std::vector<float> getTexels(void);
		std::vector<float> getNormals(void);
                std::string getTexturePath(void);
};

#endif
