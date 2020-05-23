#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>

class ImportedModel{
	std::vector<float> vertices;
	std::vector<float> texels;
	std::vector<float> normals;

	public:
		ImportedModel(const char* filename);
		void printVertices(void);

};

class Importer {
	//Init
	std::vector<float> vertices;
	std::vector<float> texels;
	std::vector<float> normals;

	//Finals
	std::vector<float> triVerts;
	std::vector<float> textCoords;
	std::vector<float> norms;

	public:
		void readFile(const char* filename);
		std::vector<float> getVertices(void);
		std::vector<float> getTexels(void);
		std::vector<float> getNormals(void);
};

/*
 * Constructor
 */
ImportedModel::ImportedModel(const char* filename) {
	Importer Import;
	Import.readFile(filename);
	vertices = Import.getVertices();
	texels = Import.getTexels();
	normals = Import.getNormals();
}

void ImportedModel::printVertices() {
	std::cout << "Triangle Verts: " << std::endl;
	for (int i=0; i < vertices.size(); i++) {
		printf("Index: %d, Value: %f\n", i, vertices.at(i));
	}

	std::cout << "Texture Verts: " << std::endl;
	for (int k=0; k < texels.size(); k++) {
		printf("Index: %d, Value: %f\n", k, texels.at(k));
	}

	std::cout << "Normal Verts: " << std::endl;
	for (int j=0; j < normals.size(); j++) {
		printf("Index: %d, Value: %f\n", j, normals.at(j));
	}
}

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
					//Get to start of vertex (OBJ indice starts at 1)
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

int main() {
	ImportedModel model("cube.obj");
	model.printVertices();
	return 0;
}
