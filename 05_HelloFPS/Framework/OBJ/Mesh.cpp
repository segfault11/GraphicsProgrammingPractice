#include "Mesh.h"
#include "../Error/Error.h"
#include <iostream>
#include <sstream>
//------------------------------------------------------------------------------
OBJ::Mesh::Mesh(unsigned int numVertices)
: 
    positions_(numVertices), 
    texCoords_(numVertices), 
    normals_(numVertices),
    numVertices_(numVertices)
{

}
//------------------------------------------------------------------------------
OBJ::Mesh::~Mesh()
{

}
//------------------------------------------------------------------------------
void OBJ::Mesh::SetPosition(unsigned int i, const Math::Vector3F& position)
{
    if (i >= positions_.size())
    {
        ERROR_WARNING("Index out of Bounds.")
        return;
    }

    positions_[i] = position;
}    
//------------------------------------------------------------------------------
void OBJ::Mesh::SetTexCoord(unsigned int i, const Math::Vector2F& texCoord)
{
    if (i >= texCoords_.size())
    {
        ERROR_WARNING("Index out of Bounds.")
        return;
    }
    texCoords_[i] = texCoord;
}
//------------------------------------------------------------------------------
void OBJ::Mesh::SetNormal(unsigned int i, const Math::Vector3F& normal)
{
    if (i >= normals_.size())
    {
        ERROR_WARNING("Index out of Bounds.")
        return;
    }

    normals_[i] = normal;
}
//------------------------------------------------------------------------------
void OBJ::Mesh::Dump() const 
{
    std::cout << "#Positions " << positions_.size() << std::endl;
    std::cout << "#TexCoords " << texCoords_.size() << std::endl;
    std::cout << "#Normals " << normals_.size() << std::endl;
    std::cout << std::endl;
    std::cout << "Positions: " << std::endl;

    for (unsigned int i = 0; i < positions_.size(); i++)
    {
        std::cout << "\t" << positions_[i].ToString() << std::endl;
    }

    std::cout << "Normals: " << std::endl;

    for (unsigned int i = 0; i < normals_.size(); i++)
    {
        std::cout << "\t" << normals_[i].ToString() << std::endl;
    }

    std::cout << "Texture Coordinates: " << std::endl;

    for (unsigned int i = 0; i < texCoords_.size(); i++)
    {
        std::cout << "\t" << texCoords_[i].ToString() << std::endl;
    }

    unsigned int size = sizeof(Math::Vector3F)*2*
        sizeof(Math::Vector2F)*positions_.size();
    std::cout << "Size im Memory " << size/(1024*1024.0f) << " MB" << std::endl;
}
//------------------------------------------------------------------------------
