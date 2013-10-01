//------------------------------------------------------------------------------
#include "Object.h"
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <iostream>
//------------------------------------------------------------------------------
#define MAX_NAME_LENGTH 1024
//------------------------------------------------------------------------------
//                         FILE PRIVATE DECLARATIONS
//------------------------------------------------------------------------------
static void readLine(std::string& line, std::ifstream& file);
static void processLine(Obj::File& file, std::string& line);
static bool addObject(Obj::File& file, std::string& line);
static bool addGroup(Obj::File& file, std::string& line);
static bool addPosition(Obj::File& file, std::string& line);
static bool addNormal(Obj::File& file, std::string& line);
static bool addTexCoord(Obj::File& file, std::string& line);
static bool addFace(Obj::File& file, std::string& line);
//------------------------------------------------------------------------------
//                           PUBLIC DEFINITIONS
//------------------------------------------------------------------------------
const Obj::File* Obj::Load(
    const std::string& filename, 
    void (*errorHandler)(const std::string& line, const std::string& errorMsg)
)
{
    std::ifstream file;
    std::string line;
    

    file.open(filename.c_str());

    // check if files could be opened
    if (!file.is_open())
    {
        return NULL;
    }

    // create an .obj file struct to store the files contents
    Obj::File* objFile = new Obj::File();

    // save the name of the file
    objFile->Name = filename;

    // set the first entries of the positions, tex coords and normals to NULL
    objFile->Positions.push_back(Math::Vector3F(0.0f, 0.0f, 0.0f));
    objFile->TexCoords.push_back(Math::Vector2F(0.0f, 0.0f));
    objFile->Normals.push_back(Math::Vector3F(0.0f, 0.0f, 0.0f));


    // fill the struct
    while(file.good())
    {
        readLine(line, file);
        processLine(*objFile, line);
    };

    file.close();

    return objFile;
}
//------------------------------------------------------------------------------
void Obj::ReleaseFile(const Obj::File** file)
{
    delete *file;
    *file = NULL;
}
//------------------------------------------------------------------------------
void Obj::Dump(const Obj::File* file)
{
    std::cout << "Dumping: " << file->Name  << std::endl;
    std::cout << "# Objects " << file->Objects.size() << std::endl;

    for (unsigned int i = 0; i < file->Objects.size(); i++)
    {
        std::cout << "\n\tObject " << i << std::endl;
        std::cout << "\tName: " << file->Objects[i].Name << std::endl;

        for (unsigned int j = 0;  j < file->Objects[i].Groups.size() ; j++)
        {
            std::cout << "\n\t\tGroup " << j << std::endl;
            std::cout << "\t\tName: " << file->Objects[i].Groups[j].Name << std::endl;
            std::cout << "\t\t# Faces: " << file->Objects[i].Groups[j].Faces.size() << std::endl;
            std::cout << "\n\t\tFaces:" << std::endl;

            unsigned int numFaces = file->Objects[i].Groups[j].Faces.size();

            for (unsigned int k = 0; k < numFaces; k++)
            {
                const Obj::Face& f = file->Objects[i].Groups[j].Faces[k];
                const Math::Tuple3UI& p = f.PositionIndices;
                const Math::Tuple3UI& t = f.TexCoordsIndices;
                const Math::Tuple3UI& n = f.NormalIndices;

                std::cout << "\t\t" 
                    << p[0] << "/" << t[0] << "/" << n[0] << " "
                    << p[1] << "/" << t[1] << "/" << n[1] << " "
                    << p[2] << "/" << t[2] << "/" << n[2] << " "
                    << std::endl;
            }
        }
    }

    std::cout << "\n# Positions " << file->Positions.size() << std::endl;
    std::cout << "\nPositions:" << std::endl;

    for (unsigned int i = 0; i < file->Positions.size(); i++)
    {
        const Math::Vector3F& pos = file->Positions[i];
        std::cout << pos[0] << " " << pos[1] << " " << pos[2] << std::endl;
    }


    std::cout << "\n# TexCoords " << file->TexCoords.size() << std::endl;
    std::cout << "\nTexCoords:" << std::endl;

    for (unsigned int i = 0; i < file->TexCoords.size(); i++)
    {
        const Math::Vector2F& tc = file->TexCoords[i];
        std::cout << tc[0] << " "<< tc[1] << std::endl;
    }
    
    std::cout << "\n# Normals " << file->Normals.size() << std::endl;
    std::cout << "\nNormals:" << std::endl;

    for (unsigned int i = 0; i < file->Normals.size(); i++)
    {
        const Math::Vector3F& nrm = file->Normals[i];
        std::cout << nrm[0] << " " << nrm[1] << " " << nrm[2] << std::endl;
    }
}
//------------------------------------------------------------------------------
//                       FILE PRIVATE DEFINITIONS
//------------------------------------------------------------------------------
void readLine(std::string& line, std::ifstream& file)
{
    std::getline(file, line);
}
//------------------------------------------------------------------------------
static void processLine(Obj::File& file, std::string& line)
{
    // TODO: maybe trim lines

    if (line.c_str()[0] == 'o')
    {
        addObject(file, line);
        return;
    }

    if (line.c_str()[0] == 'g')
    {
        addGroup(file, line);
        return;
    }

    if (line.c_str()[0] == 'v' && line.c_str()[1] == 'n')
    {
        addNormal(file, line);
        return;
    }

    if (line.c_str()[0] == 'v' && line.c_str()[1] == 't')
    {
        addTexCoord(file, line);
        return;
    }    

    if (line.c_str()[0] == 'v')
    {
        addPosition(file, line);
        return;
    }

    if (line.c_str()[0] == 'f')
    {
        addFace(file, line);
        return;
    }

}
//------------------------------------------------------------------------------
bool addPosition(Obj::File& file, std::string& line)
{
    Math::Vector3F pos;    
    int n = std::sscanf(line.c_str(), "v %f %f %f", &pos[0], &pos[1], &pos[2]);
    
    if (n != 3)
    {
        return false;
    }

    file.Positions.push_back(pos);

    return true;
}
//------------------------------------------------------------------------------
bool addNormal(Obj::File& file, std::string& line)
{
    Math::Vector3F nrm;
    int n = std::sscanf(line.c_str() , "vn %f %f %f", &nrm[0], &nrm[1], &nrm[2]);

    if (n != 3)
    {
        return false;
    }

    file.Normals.push_back(nrm);

    return true;
}
//------------------------------------------------------------------------------
bool addTexCoord(Obj::File& file, std::string& line)
{
    Math::Vector2F tc;
    int n = std::sscanf(line.c_str() , "vt %f %f", &tc[0], &tc[1]);

    if (n != 2)
    {
        return false;
    }

    file.TexCoords.push_back(tc);

    return true;   
}
//------------------------------------------------------------------------------
bool addFace(Obj::File& file, std::string& line)
{
    // check if an object struct already exists, if not create an "anonymous" 
    // one (i.e. one without a name)
    if (file.Objects.size() == 0)
    {
        Obj::Object o;
        o.Name = std::string("");
        file.Objects.push_back(o);
    }

    // if the current object has no groups add an anonymous group
    if (file.Objects[file.Objects.size() - 1].Groups.size() == 0)
    {
        Obj::Group g;
        g.Name = std::string("");
        file.Objects[file.Objects.size() - 1].Groups.push_back(g);
    }    

    // scan line
    Obj::Face f;

    Math::Tuple3UI& posIds = f.PositionIndices;
    Math::Tuple3UI& tcIds = f.TexCoordsIndices;
    tcIds[0] = 0;
    tcIds[1] = 0;
    tcIds[2] = 0;
    Math::Tuple3UI& nrmIds = f.NormalIndices;
    nrmIds[0] = 0;
    nrmIds[1] = 0;
    nrmIds[2] = 0;

    unsigned int currObj = file.Objects.size() - 1;
    unsigned int currGrp = file.Objects[currObj].Groups.size() - 1;

    // case: f [p] [p] [p]
    int n = std::sscanf(
            line.c_str(), 
            "f %u %u %u", 
            &posIds[0], &posIds[1], &posIds[2]
        );

    if (n == 3)
    {
        file.Objects[currObj].Groups[currGrp].Faces.push_back(f);
        return true;
    }

    // case: f [p]/[tc] [p]/[tc] [p]/[tc]
    n = std::sscanf(
            line.c_str(), 
            "f %u/%u %u/%u %u/%u",
            &posIds[0], &tcIds[0], 
            &posIds[1], &tcIds[1], 
            &posIds[2], &tcIds[2]
        );

    if (n == 6)
    {
        file.Objects[currObj].Groups[currGrp].Faces.push_back(f);
        return true;
    }    

    // case: f [p]//[n] [p]//[n] [p]//[n]
    n = std::sscanf(
            line.c_str(), 
            "f %u//%u %u//%u %u//%u",
            &posIds[0], &nrmIds[0], 
            &posIds[1], &nrmIds[1], 
            &posIds[2], &nrmIds[2]
        );

    if (n == 6)
    {
        file.Objects[currObj].Groups[currGrp].Faces.push_back(f);
        return true;
    }  

    // case: f [p]/[tc]/[n] [p]/[tc]/[n] [p]/[tc]/[n]
    n = std::sscanf(
            line.c_str(), 
            "f %u/%u/%u %u/%u/%u %u/%u/%u",
            &posIds[0], &tcIds[0], &nrmIds[0], 
            &posIds[1], &tcIds[1], &nrmIds[1], 
            &posIds[2], &tcIds[2], &nrmIds[2]
        );

    if (n == 9)
    {
        file.Objects[currObj].Groups[currGrp].Faces.push_back(f);
        return true;
    }  


    return false;
}
//------------------------------------------------------------------------------
bool addObject(Obj::File& file, std::string& line)
{
    // ADDS AN OBJECT TO THE FILE STRUCTURE, RETURNS FALSE IF NO NAME COULD
    // BE FOUND
    char name[MAX_NAME_LENGTH];

    int n = std::sscanf(line.c_str(), "o %s", name);

    if (n != 1)
    {
        return false;
    }

    Obj::Object newObject;
    newObject.Name = name;
    file.Objects.push_back(newObject);

    return true;
}
//------------------------------------------------------------------------------
bool addGroup(Obj::File& file, std::string& line)
{
    char name[MAX_NAME_LENGTH];
    int n = std::sscanf(line.c_str(), "g %s", name);

    if (n != 1)
    {
        return false;
    }

    // if currently no object exists, add an anonymous one
    if (file.Objects.size() == 0)
    {
        Obj::Object o;
        o.Name = std::string("");
    }

    // add a group to the current object
    Obj::Group g;
    g.Name = std::string(name);

    file.Objects[file.Objects.size() - 1].Groups.push_back(g);

    return true;
}
//------------------------------------------------------------------------------
