#include "TmpMesh.h"
#include <iostream>
#include "../Error/Error.h"
//------------------------------------------------------------------------------
void OBJ::TmpMesh::AddPosition(const Math::Vector3F& position)
{
    positions_.push_back(position);
}
//------------------------------------------------------------------------------
void OBJ::TmpMesh::AddTextureCoordinate(const Math::Vector2F& textureCoordinate)
{
    textureCoordinates_.push_back(textureCoordinate);
}
//------------------------------------------------------------------------------
void OBJ::TmpMesh::AddNormal(const Math::Vector3F& normal)
{
    normals_.push_back(normal);
}
//------------------------------------------------------------------------------
void OBJ::TmpMesh::AddPositionIndices(
    const Math::Tuple3UI& positionIndices
)
{
    positionIndices_.push_back(positionIndices);
}
//------------------------------------------------------------------------------
void OBJ::TmpMesh::AddTextureCoordinateIndices(
   const Math::Tuple3UI& textureCoordinatesIndices
)
{
    textureCoordinateIndices_.push_back(textureCoordinatesIndices);
}
//------------------------------------------------------------------------------
void OBJ::TmpMesh::AddNormalIndices(
    const Math::Tuple3UI& normalIndices
)
{
    normalIndices_.push_back(normalIndices);
}
//------------------------------------------------------------------------------
void OBJ::TmpMesh::Dump() const
{
    std::cout << "#positions: " << positions_.size() << std::endl;

    std::cout << "Positions:";
    for (unsigned int i = 0; i < positions_.size(); i++)
    {
        std::cout << "v " << positions_[i].ToString() << std::endl;
    }

    std::cout << "\n\nTexture Coordinates:";
    for (unsigned int i = 0; i < textureCoordinates_.size(); i++)
    {        
        std::cout << "vt "<< textureCoordinates_[i].ToString() << std::endl;
    }    

    std::cout << "\n\nNormals:";
    for (unsigned int i = 0; i < normals_.size(); i++)
    {
        std::cout << "vn" << normals_[i].ToString() << std::endl;
    }

    // std::cout << "\n\nFaces:";

    // // bool hasSameSize = 
    // //     (positionIndexArray_.size() == textureCoordinateIndexArray_.size() &&
    // //     positionIndexArray_.size() == normalIndexArray_.size());

    // // if(!hasSameSize)
    // // {
    // //     std::cout << "Could not print faces because of different sizes in the index array";
    // //     return;
    // // }

    for (unsigned int i = 0; i < positionIndices_.size(); i++)
    {
        const Math::Tuple3UI& facePosition = positionIndices_[i];
        //const Math::Tuple3UI& faceTC = textureCoordinateIndices_[i];
        const Math::Tuple3UI& faceNormal = normalIndices_[i];

        std::cout << facePosition[0] << "//" << faceNormal[0] << " " 
                  << facePosition[1] << "//" << faceNormal[1] << " " 
                  << facePosition[2] << "//" << faceNormal[2] << std::endl;
    }

    std::cout << "\n\n";
}
//------------------------------------------------------------------------------
bool OBJ::TmpMesh::IsValid() const
{
    bool isValid = true;

    if (normalIndices_.size() > 0)
    {
        isValid = (normalIndices_.size() == positionIndices_.size());
    }

    if (textureCoordinateIndices_.size() > 0)
    {
        isValid = (textureCoordinateIndices_.size() == positionIndices_.size());
    }

    return isValid;
}
//------------------------------------------------------------------------------
bool OBJ::TmpMesh::HasTexCoords() const
{
    return textureCoordinateIndices_.size() > 0;
}
//------------------------------------------------------------------------------
bool OBJ::TmpMesh::HasNormals() const
{
    return normalIndices_.size() > 0;
}
//------------------------------------------------------------------------------
const Math::Vector3F& OBJ::TmpMesh::GetPosition(unsigned int i) const
{    
    ERROR_ASSERT(i < positions_.size())

    return positions_[i];
}
//------------------------------------------------------------------------------
const Math::Vector3F& OBJ::TmpMesh::GetNormal(unsigned int i) const
{
    ERROR_ASSERT(i < normals_.size())

    return normals_[i];
}
//------------------------------------------------------------------------------
const Math::Vector2F& OBJ::TmpMesh::GetTextureCoordinate(unsigned int i) const
{
    ERROR_ASSERT(i < textureCoordinates_.size())

    return textureCoordinates_[i];
}
//------------------------------------------------------------------------------
const Math::Tuple3UI& OBJ::TmpMesh::GetPositionIndices(unsigned int i) const
{
    ERROR_ASSERT(i < positionIndices_.size())

    return positionIndices_[i];
}
//------------------------------------------------------------------------------        
const Math::Tuple3UI& OBJ::TmpMesh::GetTextureCoordinateIndices(unsigned int i) const
{
    ERROR_ASSERT(i < textureCoordinateIndices_.size())
 
    return textureCoordinateIndices_[i];
}
//------------------------------------------------------------------------------        
const Math::Tuple3UI& OBJ::TmpMesh::GetNormalIndices(unsigned int i) const
{
    ERROR_ASSERT(i < normalIndices_.size())

    return normalIndices_[i];
}
//------------------------------------------------------------------------------        