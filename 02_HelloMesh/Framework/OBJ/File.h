/*!
** @file File.h
**
** Declaration of an .obj file.
**
** @since 2013-09-01 
*/
#ifndef FILE_H__
#define FILE_H__

#include <string>
#include "TmpMesh.h"
#include "Mesh.h"

namespace OBJ
{
    /*!
    ** Stores an .obj file.
    **    
    ** @since 2013-09-01 
    */
    class File
    {
    public:

        /*!
        ** Loads an .obj file.
        **
        ** @param filename Filename of the .obj file.
        ** @since 2013-09-01 
        */
        File(const char* filename);
        ~File();

        const Mesh& GetMesh() const {return *mesh_;}
    
    private:
        std::string filename_;
        Mesh* mesh_;
    };

}

#endif /* end of include guard: FILE_H__ */