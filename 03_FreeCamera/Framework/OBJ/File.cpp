#include "File.h"
#include <fstream>
#include <sstream>
#include <cstdio>
#include "../Error/Error.h"
#include <iostream>
#include <cstdlib>
//------------------------------------------------------------------------------
static void processLine(
    OBJ::TmpMesh& mesh, 
    const char* line, 
    const std::string& filename
);
static void convert(
    OBJ::Mesh& mesh,
    const OBJ::TmpMesh& tmpMesh 
);
//------------------------------------------------------------------------------
OBJ::File::File(const char* filename)
: filename_(filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {   
        ERROR_WARNING("Could not open .obj file.");
        return;
    }

    std::string line;

    TmpMesh mesh;

    while (file.good())
    {
        std::getline(file, line);
        processLine(mesh, line.c_str(), filename_);
    }

    file.close();

    if (!mesh.IsValid())
    {
        ERROR_WARNING("Extracted mesh was not valid");
        return;
    }

    mesh_ = new Mesh(mesh.GetNumFaces()*3);

    convert(*mesh_, mesh);
}
//------------------------------------------------------------------------------
OBJ::File::~File(){}
//------------------------------------------------------------------------------
void processLine(
    OBJ::TmpMesh& mesh, 
    const char* line, 
    const std::string& filename
)
{
    float x, y, z;

    // scan for vertex position
    if (std::sscanf(line, "v %f %f %f", &x, &y, &z) == 3)
    {
        mesh.AddPosition(Math::Vector3F(x, y, z));
        return;
    }

    // scan for vertex texture coordinates
    if (std::sscanf(line, "vt %f %f", &x, &y) == 2)
    {
        mesh.AddTextureCoordinate(Math::Vector2F(x, y));
        return;
    }

    // scan for vertex normals
    if (std::sscanf(line, "vn %f %f %f", &x, &y, &z) == 3)
    {
        mesh.AddNormal(Math::Vector3F(x, y, z));
        return;
    }

    Math::Tuple3UI positionIndices;
    Math::Tuple3UI textureCoordinateIndices;
    Math::Tuple3UI normalIndices;

    // scan for face indices (position)
    unsigned int n;
    n = std::sscanf(
            line, 
            "f %u %u %u", 
            &positionIndices[0], 
            &positionIndices[1], 
            &positionIndices[1]
        );

    if ( n == 3)
    {
        mesh.AddPositionIndices(positionIndices);
        return;
    }

    n = std::sscanf(
            line, 
            "f %u// %u// %u//", 
            &positionIndices[0], 
            &positionIndices[1], 
            &positionIndices[1]
        );

    if (n == 3)
    {
        mesh.AddPositionIndices(positionIndices);
        return;
    }

    // scan for face indices (position, texture)
    n = std::sscanf(
            line, 
            "f %u/%u %u/%u %u/%u", 
            &positionIndices[0], 
            &textureCoordinateIndices[0], 
            &positionIndices[1], 
            &textureCoordinateIndices[1],
            &positionIndices[2],
            &textureCoordinateIndices[2]
        );

    if (n == 6)
    {
        mesh.AddPositionIndices(positionIndices);
        mesh.AddTextureCoordinateIndices(textureCoordinateIndices);
        return;
    }

    n = std::sscanf(
            line, 
            "f %u/%u/ %u/%u/ %u/%u/",
            &positionIndices[0], 
            &textureCoordinateIndices[0], 
            &positionIndices[1], 
            &textureCoordinateIndices[1],
            &positionIndices[2],
            &textureCoordinateIndices[2]
        );

    if (n == 6)
    {
        mesh.AddPositionIndices(positionIndices);
        mesh.AddTextureCoordinateIndices(textureCoordinateIndices);
        return;
    }

    // scan for faces indices (position, normals)  
    n = std::sscanf(
            line, 
            "f %u//%u %u//%u %u//%u", 
            &positionIndices[0], 
            &normalIndices[0], 
            &positionIndices[1], 
            &normalIndices[1],
            &positionIndices[2],
            &normalIndices[2]
        );

    if (n == 6)
    {
        mesh.AddPositionIndices(positionIndices);
        mesh.AddNormalIndices(normalIndices);
        return;
    }

    // scan for face indices (geometry, texture, normals)  
    n = std::sscanf(
            line, 
            "f %u/%u/%u %u/%u/%u %u/%u/%u", 
            &positionIndices[0], 
            &textureCoordinateIndices[0], 
            &normalIndices[0], 
            &positionIndices[1],
            &textureCoordinateIndices[1],
            &normalIndices[1],
            &positionIndices[2],
            &textureCoordinateIndices[2],
            &normalIndices[2]
        );

    if (n == 9)
    {
        mesh.AddPositionIndices(positionIndices);
        mesh.AddTextureCoordinateIndices(textureCoordinateIndices);
        mesh.AddNormalIndices(normalIndices);
        return;
    }

    std::stringstream s;
    s << "For file " << filename << " the following line was ignored: " << line;
    ERROR_WARNING(s.str().c_str());
}
//------------------------------------------------------------------------------
void convert(OBJ::Mesh& mesh, const OBJ::TmpMesh& tmpMesh)
{
    for (unsigned int i = 0; i < tmpMesh.GetNumFaces(); i++)
    {
        Math::Tuple3UI posIdx = tmpMesh.GetPositionIndices(i);

        // substract -1 to reference the data arrays correctly (.obj indices 
        // start with 1 not 0)
        posIdx[0] -= 1;
        posIdx[1] -= 1;
        posIdx[2] -= 1;

        // copy positions
        for (unsigned int j = 0; j < 3; j++)
        {
            const Math::Vector3F& pos = tmpMesh.GetPosition(posIdx[j]);
            mesh.SetPosition(3*i + j, pos);
        }

        // copy normals if they exist
        if (tmpMesh.HasNormals())
        {
            Math::Tuple3UI nrmIdx = tmpMesh.GetNormalIndices(i);
            nrmIdx[0] -= 1;
            nrmIdx[1] -= 1;
            nrmIdx[2] -= 1;

            for (unsigned int j = 0; j < 3; j++)
            {
                const Math::Vector3F& nrm = tmpMesh.GetNormal(nrmIdx[j]);
                mesh.SetNormal(3*i + j, nrm);
            }            
        }

        // copy texture coords if they exist
        if (tmpMesh.HasTexCoords())
        {
            Math::Tuple3UI tcIdx = tmpMesh.GetTextureCoordinateIndices(i);
            tcIdx[0] -= 1;
            tcIdx[1] -= 1;
            tcIdx[2] -= 1;

            for (unsigned int j = 0; j < 3; j++)
            {
                const Math::Vector2F& tc = tmpMesh.GetTextureCoordinate(
                        tcIdx[j]
                    );
                mesh.SetTexCoord(3*i + j, tc);
            }            
        }
    }
}
//------------------------------------------------------------------------------
