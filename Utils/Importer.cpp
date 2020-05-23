#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>
#include "Importer.h"

/*
 * Get vertices
 */
std::vector<float> Importer::getVertices() {
	return triVerts;
}

/*
 * Get texture coordinates
 */
std::vector<float> Importer::getTexels() {
	return textCoords;
}

/*
 * get normal coordinates
 */
std::vector<float> Importer::getNormals() {
	return norms;
}

/*
 * Read data from .OBJ file
 * Must push initial data into respective initial vectors
 * 	in order to get correct final data per triangle index
 *
 * Currently only handles triangles with vertex, texture, and normal indices
 */
void Importer::readFile(const char* filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cout << "Could not open file." << std::endl;
	}

	std::string line, seg;
	float x, y, z;
	int i, vIndex, tIndex, nIndex, endIndex;
	std::istringstream input;
	while (std::getline(file, line)) {
			if (line[0] == 'v' && line[1] == 't') {
			      line.erase(0, 3);
			      sscanf(line.c_str(), "%f %f", &x, &y);
			      texels.push_back(x);
			      texels.push_back(y);
			}

			else if (line[0] == 'v' && line[1] == 'n') {
				line.erase(0, 3);
				sscanf(line.c_str(), "%f %f %f", &x, &y, &z);
				normals.push_back(x);
				normals.push_back(y);
				normals.push_back(z);
			}

			else if (line[0] == 'v') {
				line.erase(0, 2);
				sscanf(line.c_str(), "%f %f %f", &x, &y, &z);
				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);
			}
			
			else if (line[0] == 'f') {
				line.erase(0, 2);
				input.str(line.c_str());
				while (std::getline(input, seg, ' ')) {
					sscanf(seg.c_str(), "%d %*c %d %*c %d", &vIndex, &tIndex, &nIndex);
					//Get to start of vertex (OBJ index starts at 1)
					vIndex = (vIndex-1)*3;
					tIndex = (tIndex-1)*2;
					nIndex = (nIndex-1)*3;

					//Push Vertices
					triVerts.push_back(vertices[vIndex]);
					triVerts.push_back(vertices[vIndex+1]);
					triVerts.push_back(vertices[vIndex+2]);

					//Push Texutres
					textCoords.push_back(texels[tIndex]);
					textCoords.push_back(texels[tIndex+1]);

					//Push Normals
					norms.push_back(normals[nIndex]);
					norms.push_back(normals[nIndex+1]);
				}
				input.clear();
			}

			else {
				continue;
			}
	}
	file.close();
}
