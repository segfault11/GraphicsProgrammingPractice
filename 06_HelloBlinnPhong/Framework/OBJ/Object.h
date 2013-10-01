/*!
** A simple loader for .obj files. Supports only triangle meshes.
**
** Some remarks:
** - [Positions], [TexCoords] & [Normals] in the [File]-class have all a 
**   null vector as first element.
** - A face always also stores indices to tex coordinates and normal coordinates 
**   , if these do not exist in the .obj file the tex coords and normal  
**   coordinates are set to null tuples and reference the null vectors in the
**   [File]'s data arrays (see first remark).
**    
** @since 2013-09-27 
*/
/*
    TODO's:
        - Read Materials
        - Specify what materials should be supported
        - Triangulate Quads if they appear in the obj file.
        - Implement "the error handling"
*/
#ifndef OBJECT_H__
#define OBJECT_H__
 
#include <string>
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include <vector>

namespace Obj
{

    /*!
    ** Stores the material for each face.
    */
    class Material
    {
    public:
        std::string Name;

        Math::Vector3F Ka;
        Math::Vector3F Kd;
        Math::Vector3F Ks;
    };

    /*!
    ** Stores a face, that is a triangle.
    */
    class Face
    {
    public:
        Math::Tuple3UI PositionIndices; 
        Math::Tuple3UI TexCoordsIndices; 
        Math::Tuple3UI NormalIndices;
        unsigned int MaterialIndex; 
    };

    /*!
    ** Stores the name of the group and its faces
    */
    class Group
    {
    public:
        std::string Name;
        std::vector<Face> Faces;
    };

    /*!
    ** Stores an Object
    */
    class Object
    {
    public:
        std::string Name;
        std::vector<Group> Groups;
    };

    /*!
    ** A description of an .obj file
    */
    class File
    {
    public:
        std::string Name;
        std::vector<Math::Vector3F> Positions;
        std::vector<Math::Vector2F> TexCoords;
        std::vector<Math::Vector3F> Normals;

        std::vector<Material> Materials;
        std::vector<Object> Objects;
    };


    const File* Load(
        const std::string& filename
    );
        
    const File* Load(
        const std::string& filename, 
        void (*errorHandler)(const std::string& line, const std::string& errorMsg)
    );

    void ReleaseFile(const File** file);

    void Dump(const File* file);

}

 
#endif /* end of include guard: OBJECT_H__ */