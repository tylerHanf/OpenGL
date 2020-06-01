#ifndef IMPORTED_MODEL_H
#define IMPORTED_MODEL_H

#include <vector>
#include "Importer.h"

/*
 * Holds data for imported .OBJ model
 */
class ImportedModel {
        public:
			std::vector<float> vertices;
			std::vector<float> texels;
			std::vector<float> normals;
			int numVertices;

			ImportedModel(const char* filename);
			void printVertices(void);
};

#endif
