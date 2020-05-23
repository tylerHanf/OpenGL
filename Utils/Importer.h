#ifndef IMPORTER_H
#define IMPORTER_H

#include <vector>

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

	public:
		void readFile(const char* filename);
		std::vector<float> getVertices(void);
		std::vector<float> getTexels(void);
		std::vector<float> getNormals(void);
};

#endif
