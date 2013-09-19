/*!
** A triangle mesh.
**    
** @since 2013-09-07 
*/
#ifndef MESH_H__
#define MESH_H__

#include <vector>
#include "../Math/Vector3.h"
#include "../Math/Vector2.h"

namespace OBJ
{
    class Mesh
    {
    public:
        Mesh(unsigned int numVertices);
        ~Mesh();

        void SetPosition(unsigned int i, const Math::Vector3F& position);
        void SetTexCoord(unsigned int i, const Math::Vector2F& texCoord);
        void SetNormal(unsigned int i, const Math::Vector3F& normal);

        unsigned int GetNumVertices() const {return numVertices_;}
        const float* GetPositionData() const {return reinterpret_cast<const float*>(positions_.data());}

        void Dump() const;

    private:
        std::vector<Math::Vector3F> positions_;
        std::vector<Math::Vector2F> texCoords_;
        std::vector<Math::Vector3F> normals_;
        unsigned int numVertices_;
    };
}

#endif /* end of include guard: MESH_H__ */