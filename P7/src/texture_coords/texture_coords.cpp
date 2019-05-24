
#define _USE_MATH_DEFINES

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

//Stores values for each defined vertex
struct Vertex{
    double x;
    double y;
    double z;

    Vertex(double _x, double _y, double _z) : x(_x), y(_y), z(_z){}

    //Used for t calculations
    double dot(Vertex& other){
        return ((x * other.x) + (y * other.y) + (z * other.z));
    }
};

//Stores values for each defined face
struct Face{
    Vertex* v1;
    Vertex* v2;
    Vertex* v3;

    Face(Vertex* _v1, Vertex* _v2, Vertex* _v3) : v1(_v1), v2(_v2), v3(_v3){}
};

//Stores s and t values for all verteces in each face
struct TextureCoords{
    double s1;
    double s2;
    double s3;
    double t1;
    double t2;
    double t3;
};

void readFile(std::ifstream&, std::vector<Vertex*>&, std::vector<Face*>&);
void writeFile(std::ifstream&, std::ofstream&, std::vector<TextureCoords>&);

//Adjusts s value depending on the quadrant
inline double fixS(Vertex& point, double s){
    if(point.x > 0.0 && point.z > 0){
        return s;
    } else if(point.z > 0.0 && point.x < 0.0){
        return s + 1.0;
    } else{
        return s + 0.5;
    }
}

//If this is called, you're bad
[[noreturn]] inline void usage(const char *name){
	std::cout << "Usage: " << name << " <input_file> <output_file>" << std::endl;
	exit(EXIT_FAILURE);
}

int main(const int argc, const char** argv){
    if(argc < 2){
        std::cerr << "Error: Too few arguments." << std::endl;
        usage(argv[0]);
    }

    std::ifstream inFile(argv[1]);
    std::ofstream outFile(argv[2], std::ios::binary | std::ios::out);

    if(!inFile){
        std::cerr << "Error: Bad input file: " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }
    if(!outFile){
        std::cerr << "Error: Bad output file: " << argv[2] << std::endl;
        return EXIT_FAILURE;
    }

    //Create storage
    std::vector<Vertex*> verteces;
    std::vector<Face*> faces;

    //Read the file
    readFile(inFile, verteces, faces);

    //Create storage for s and t
    std::vector<TextureCoords> coords(faces.size());

    //Calculate s and t for all faces
    for(size_t i = 0; i < faces.size(); ++i){
        double p1 = sqrt(faces[i]->v1->dot(*faces[i]->v1));
        double p2 = sqrt(faces[i]->v2->dot(*faces[i]->v2));
        double p3 = sqrt(faces[i]->v3->dot(*faces[i]->v3));

        double theta1 = acos(faces[i]->v1->y / p1);
        double theta2 = acos(faces[i]->v2->y / p2);
        double theta3 = acos(faces[i]->v3->y / p3);

        coords[i].t1 = 1.0 - (theta1 / M_PI);
        coords[i].t2 = 1.0 - (theta2 / M_PI);
        coords[i].t3 = 1.0 - (theta3 / M_PI);

        double phi1 = atan(faces[i]->v1->x / faces[i]->v1->z);
        double phi2 = atan(faces[i]->v2->x / faces[i]->v2->z);
        double phi3 = atan(faces[i]->v3->x / faces[i]->v3->z);

        coords[i].s1 = fixS(*faces[i]->v1, (phi1 / (2.0 * M_PI)));
        coords[i].s2 = fixS(*faces[i]->v2, (phi2 / (2.0 * M_PI)));
        coords[i].s3 = fixS(*faces[i]->v3, (phi3 / (2.0 * M_PI)));
    }

    //Reset inFile to beginning of file for copying
    inFile.clear();
    inFile.seekg(0, std::ios::beg);

    //Copy input file and append new values
    writeFile(inFile, outFile, coords);

    //Close and leave
    inFile.close();
    outFile.close();

    return 0;
}

void readFile(std::ifstream& inFile, std::vector<Vertex*>& verteces, std::vector<Face*>& faces){
    std::string line;

    getline(inFile, line);

    while(!inFile.eof()){
        if(line.find("v") == 0){
            //Parse the line to get what we want
            std::vector<std::string> tokens;
            std::stringstream sstream(line);
            std::string item;

            while(getline(sstream, item, ' ')){
                tokens.push_back(item);
            }

            double x = atof(tokens[1].c_str());
            double y = atof(tokens[2].c_str());
            double z = atof(tokens[3].c_str());

            //Store it
            verteces.push_back(new Vertex(x, y, z));
        }else if(line.find("f") == 0){
            //Parse line to get what we want
            std::vector<std::string> tokens;
            std::stringstream sstream(line);
            std::string item;

            while(getline(sstream, item, ' ')){
                tokens.push_back(item);
            }

            int v1 = atoi(tokens[1].c_str());
            int v2 = atoi(tokens[2].c_str());
            int v3 = atoi(tokens[3].c_str());

            //Store it
            faces.push_back(new Face(verteces[v1-1], verteces[v2-1], verteces[v3-1]));
        }

        getline(inFile, line, '\n');
    }
}

void writeFile(std::ifstream& inFile, std::ofstream& outFile, std::vector<TextureCoords>& coords){
    std::string line;

    //Copy input file to output file
    getline(inFile, line, '\n');
    while(!inFile.eof()){
        if(line.find("end") == 0)
            break;
        
        outFile << line << std::endl;

        getline(inFile, line, '\n');
    }

    //Append new s and t data to the end
    for(size_t i = 0; i < coords.size(); ++i){
        outFile << "vt " << coords[i].s1 << " " << coords[i].t1
                << " " << coords[i].s2 << " " << coords[i].t2
                << " " << coords[i].s3 << " " << coords[i].t3
                << std::endl;
    }

    //Mark end of file
    outFile << "end of file" << std::endl;
}
