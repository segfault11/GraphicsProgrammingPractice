#include "MeshRenderer.h"
#include <iostream>
#include "Framework/APP/Application.h"

//------------------------------------------------------------------------------
// DEFINITION OF THE GLSL PROGRAM
//------------------------------------------------------------------------------

class MeshProgram : public GL::Program
{
public:
    MeshProgram();
    ~MeshProgram();

    void SetMaterial(const Obj::Material& mat);
    void SetCamera(const APP::Camera& cam);
};

MeshProgram::MeshProgram()
{
    this->AttachShader("MeshVS.h", GL_VERTEX_SHADER);
    this->AttachShader("MeshVS.h", GL_FRAGMENT_SHADER);
    this->BindAttribLocation(0, "Position");
    this->BindFragDataLocation(0, "FragColor");
    this->Compile();
}

MeshProgram::~MeshProgram()
{

}

void MeshProgram::SetMaterial(const Obj::Material& mat)
{

}

void MeshProgram::SetCamera(const APP::Camera& cam)
{

}

//------------------------------------------------------------------------------
// DEFINITION OF A MATERIAL GROUP
//------------------------------------------------------------------------------

class MaterialGroup
{
    // MaterialGroup is a utility class that stores GL geometry for a certain
    // material, and renders it given a GLSL program.
public:
    void SetMaterial(const Obj::Material& material);
    void AddPosition(const Math::Vector3F& position);
    void AddTexCoord(const Math::Vector2F& texCoord);
    void AddNormal(const Math::Vector3F& normal);
    void Upload();
    void Draw();

private:
    std::vector<Math::Vector3F> positions;
    std::vector<Math::Vector2F> texCoords;
    std::vector<Math::Vector3F> normals;
    Obj::Material material;
};

void MaterialGroup::SetMaterial(const Obj::Material& material)
{
    this->material = material;
}

void MaterialGroup::AddPosition(const Math::Vector3F& position)
{
    this->positions.push_back(position);
}

void MaterialGroup::AddTexCoord(const Math::Vector2F& texCoord)
{
    this->texCoords.push_back(texCoord);
}

void MaterialGroup::AddNormal(const Math::Vector3F& normal)
{
    this->AddNormal(normal);
}
//------------------------------------------------------------------------------
//  DEFINITION OF THE IMPLEMENTATION CLASS
//------------------------------------------------------------------------------

class MeshRenderer::RealMeshRenderer
{
public:
    RealMeshRenderer(const std::string& filename);
    ~RealMeshRenderer();

    void Draw();

private:
    // groups the .obj geometry into its material group
    void group(const Obj::File& obj);

    MaterialGroup* matGroups;
    MeshProgram program;
    unsigned int numMaterials;
};

MeshRenderer::RealMeshRenderer::RealMeshRenderer(const std::string& filename)
{
    // create the GLSL program


    // load the .obj file
    const Obj::File* file = Obj::Load(filename);
    ERROR_ASSERT(file != NULL)

    // group the geometry by their material
    matGroups = new MaterialGroup[file->Materials.size()];



    Obj::Release(&file);
}

MeshRenderer::RealMeshRenderer::~RealMeshRenderer()
{
    delete[] matGroups;
}

void MeshRenderer::RealMeshRenderer::group(const Obj::File& obj)
{
    // set the materials for each group
    for (unsigned int i = 0; i < obj.Materials.size(); i++)
    {
        this->matGroups[i].SetMaterial(obj.Materials[i]);
    }

    for (unsigned int i = 0; obj.Objects.size(); i++)
    {
        for (unsigned int j = 0; obj.Objects[i].Groups.size(); j++)
        {
            for (unsigned int k = 0; obj.Objects[i].Groups[k].Faces.size(); k++)
            {
                const Obj::Face& f = obj.Objects[i].Groups[k].Faces[k];

                // check the material index of the face
                unsigned int matIdx = f.MaterialIndex;

                // add geometry to the group
                for (unsigned int u = 0; u < 3; u++)
                {
                    this->matGroups[matIdx].AddPosition(
                        obj.Positions[f.PositionIndices[u]]
                    );

                    this->matGroups[matIdx].AddTexCoord(
                        obj.TexCoords[f.TexCoordsIndices[u]]
                    );

                    this->matGroups[matIdx].AddNormal(
                        obj.Normals[f.NormalIndices[u]]
                    );
                }
            }
        }
    }
}

//------------------------------------------------------------------------------
// PUBLIC DEFINITIONS OF THE MESH RENDERER
//------------------------------------------------------------------------------

MeshRenderer::MeshRenderer(const std::string& filename)
{
    this->meshRenderer = new RealMeshRenderer(filename);
}

MeshRenderer::~MeshRenderer()
{
    delete this->meshRenderer;
}

void MeshRenderer::Draw()
{

}

void MeshRenderer::OnCameraUpdate()
{

}
