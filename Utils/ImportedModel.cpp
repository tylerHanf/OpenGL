#include <stdio.h>
#include <vector>
#include <iostream>
#include "ImportedModel.h"
#include "Importer.h"

/*
 * Constructor
 */
ImportedModel::ImportedModel(const char* filename) {
        Importer import;
        import.readFile(filename);
        vertices = import.getVertices();
        texels = import.getTexels();
        normals = import.getNormals();
	numVertices = vertices.size()/3;
}

/*
 * Prints values of all vertices at corresponding indices
 * (for debugging purposes)
 */
void ImportedModel::printVertices() {
	printf("Triangle Verts: \n");
        for (int i=0; i < vertices.size(); i++) {
                printf("Index: %d, Value: %f\n", i, vertices.at(i));
        }

	printf("Texture Verts:\n");
        for (int k=0; k < texels.size(); k++) {
                printf("Index: %d, Value: %f\n", k, texels.at(k));
        }

	printf("Normal Verts:\n");
        for (int j=0; j < normals.size(); j++) {
                printf("Index: %d, Value: %f\n", j, normals.at(j));
        }
}
