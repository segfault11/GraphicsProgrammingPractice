/*!
** @file TmpMesh.h
**    
** Declaration of a triangle mesh in .obj format
**
** @since 2013-09-01 
*/
#ifndef TMPMESH_H__
#define TMPMESH_H__

#include <vector>
#include "../Math/Vector3.h"
#include "../Math/Vector2.h"

namespace OBJ
{
    /*!
    ** Stores vertex, normal and texture data for one mesh as specified in an 
    ** .obj file in distinct arrays.
    ** Also stores indices to vertex, normal and texture data in distinct arrays
    **    
    ** @since 2013-09-01
    */
    class TmpMesh
    {
    public:
        TmpMesh(){};
        ~TmpMesh(){};

        void AddPosition(const Math::Vector3F& position);
        void AddTextureCoordinate(const Math::Vector2F& textureCoordinate);
        void AddNormal(const Math::Vector3F& normal);

        void AddPositionIndices(const Math::Tuple3UI& positionIndices);
        void AddTextureCoordinateIndices(
            const Math::Tuple3UI& textureCoordinatesIndices
        );
        void AddNormalIndices(const Math::Tuple3UI& normalIndices);
        
        const Math::Vector3F& GetPosition(unsigned int i) const;
        const Math::Vector3F& GetNormal(unsigned int i) const;
        const Math::Vector2F& GetTextureCoordinate(unsigned int i) const;
        const Math::Tuple3UI& GetPositionIndices(unsigned int i) const;
        const Math::Tuple3UI& GetTextureCoordinateIndices(unsigned int i) const;
        const Math::Tuple3UI& GetNormalIndices(unsigned int i) const;

        unsigned int GetNumPositions() const {return positions_.size();}
        unsigned int GetNumTexCoords() const {return textureCoordinates_.size();}
        unsigned int GetNumFaces() const {return positionIndices_.size();}

        bool HasTexCoords() const;
        bool HasNormals() const;
        bool IsValid() const;

        void Dump() const;

    private:
        std::vector<Math::Vector3F> positions_;
        std::vector<Math::Vector3F> normals_;
        std::vector<Math::Vector2F> textureCoordinates_;
        std::vector<Math::Tuple3UI> positionIndices_;
        std::vector<Math::Tuple3UI> textureCoordinateIndices_;
        std::vector<Math::Tuple3UI> normalIndices_;
    };
    
}

#endif /* end of include guard: TMPMESH_H__ */