#include "alalbapch.h"
#include "Model.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
namespace std {
  inline bool operator<(const tinyobj::index_t& a,
    const tinyobj::index_t& b)
  {
    if (a.vertex_index < b.vertex_index) return true;
    if (a.vertex_index > b.vertex_index) return false;

    if (a.normal_index < b.normal_index) return true;
    if (a.normal_index > b.normal_index) return false;

    if (a.texcoord_index < b.texcoord_index) return true;
    if (a.texcoord_index > b.texcoord_index) return false;

    return false;
  }
}

/*! \namespace osc - Optix Siggraph Course */
namespace Alalba {
  void Model::addCube(const vec3f& center, const vec3f& size)
  {
    PING;
    affine3f xfm;
    xfm.p = center - 0.5f * size;
    xfm.l.vx = vec3f(size.x, 0.f, 0.f);
    xfm.l.vy = vec3f(0.f, size.y, 0.f);
    xfm.l.vz = vec3f(0.f, 0.f, size.z);
    addUnitCube(xfm);
  }

  /*! add a unit cube (subject to given xfm matrix) to the current
      triangleMesh */
  void Model::addUnitCube(const affine3f& xfm)
  {
    TriangleMesh* trianglemesh = new TriangleMesh;
    //int firstVertexID = (int)vertex.size();
    trianglemesh->vertex.push_back(xfmPoint(xfm, vec3f(0.f, 0.f, 0.f)));
    trianglemesh->vertex.push_back(xfmPoint(xfm, vec3f(1.f, 0.f, 0.f)));
    trianglemesh->vertex.push_back(xfmPoint(xfm, vec3f(0.f, 1.f, 0.f)));
    trianglemesh->vertex.push_back(xfmPoint(xfm, vec3f(1.f, 1.f, 0.f)));
    trianglemesh->vertex.push_back(xfmPoint(xfm, vec3f(0.f, 0.f, 1.f)));
    trianglemesh->vertex.push_back(xfmPoint(xfm, vec3f(1.f, 0.f, 1.f)));
    trianglemesh->vertex.push_back(xfmPoint(xfm, vec3f(0.f, 1.f, 1.f)));
    trianglemesh->vertex.push_back(xfmPoint(xfm, vec3f(1.f, 1.f, 1.f)));


    int indices[] = { 0,1,3, 2,3,0,
                     5,7,6, 5,6,4,
                     0,4,5, 0,5,1,
                     2,3,7, 2,7,6,
                     1,5,7, 1,7,3,
                     4,0,2, 4,2,6
    };
    for (int i = 0; i < 12; i++)
      trianglemesh->index.push_back( vec3i(indices[3 * i + 0],
        indices[3 * i + 1],
        indices[3 * i + 2]));

    this->meshes.push_back(trianglemesh);
  }

  /*! find vertex with given position, normal, texcoord, and return
      its vertex ID, or, if it doesn't exit, add it to the mesh, and
      its just-created index */
  int addVertex(TriangleMesh* mesh,
    tinyobj::attrib_t& attributes,
    const tinyobj::index_t& idx,
    std::map<tinyobj::index_t, int>& knownVertices)
  {
    if (knownVertices.find(idx) != knownVertices.end())
      return knownVertices[idx];

    const vec3f* vertex_array = (const vec3f*)attributes.vertices.data();
    const vec3f* normal_array = (const vec3f*)attributes.normals.data();
    const vec2f* texcoord_array = (const vec2f*)attributes.texcoords.data();

    int newID = mesh->vertex.size();
    knownVertices[idx] = newID;

    mesh->vertex.push_back(vertex_array[idx.vertex_index]);
    if (idx.normal_index >= 0) {
      while (mesh->normal.size() < mesh->vertex.size())
        mesh->normal.push_back(normal_array[idx.normal_index]);
    }
    if (idx.texcoord_index >= 0) {
      while (mesh->texcoord.size() < mesh->vertex.size())
        mesh->texcoord.push_back(texcoord_array[idx.texcoord_index]);
    }

    // just for sanity's sake:
    if (mesh->texcoord.size() > 0)
      mesh->texcoord.resize(mesh->vertex.size());
    // just for sanity's sake:
    if (mesh->normal.size() > 0)
      mesh->normal.resize(mesh->vertex.size());

    return newID;
  }

  Model* loadOBJ(const std::string& objFile)
  {
    Model* model = new Model;

    const std::string mtlDir
      = objFile.substr(0, objFile.rfind('/') + 1);
    PRINT(mtlDir);

    tinyobj::attrib_t attributes;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err = "";

    bool readOK
      = tinyobj::LoadObj(&attributes,
        &shapes,
        &materials,
        &err,
        &err,
        objFile.c_str(),
        mtlDir.c_str(),
        /* triangulate */true);
    if (!readOK) 
    {
      throw std::runtime_error("Could not read OBJ model from " + objFile + ":" + mtlDir + " : " + err);
    }

    if (materials.empty())
      throw std::runtime_error("could not parse materials ...");

    std::cout << "Done loading obj file - found " << shapes.size() << " shapes with " << materials.size() << " materials" << std::endl;
    
  /// loop over shapes
    for (int shapeID = 0; shapeID < (int)shapes.size(); shapeID++) 
    {
    /// loop over face
      tinyobj::shape_t& shape = shapes[shapeID];
      
      //build a set of material id for eace face 
      std::set<int> materialIDs;
      for (auto faceMatID : shape.mesh.material_ids)
        materialIDs.insert(faceMatID);

      std::map<tinyobj::index_t, int> knownVertices;

      for (int materialID : materialIDs) 
      {
        TriangleMesh* mesh = new TriangleMesh;

        for (int faceID = 0; faceID < shape.mesh.material_ids.size(); faceID++) 
        {
          if (shape.mesh.material_ids[faceID] != materialID) continue;
          tinyobj::index_t idx0 = shape.mesh.indices[3 * faceID + 0];
          tinyobj::index_t idx1 = shape.mesh.indices[3 * faceID + 1];
          tinyobj::index_t idx2 = shape.mesh.indices[3 * faceID + 2];

          vec3i idx(addVertex(mesh, attributes, idx0, knownVertices),
            addVertex(mesh, attributes, idx1, knownVertices),
            addVertex(mesh, attributes, idx2, knownVertices));
          mesh->index.push_back(idx);
          mesh->diffuse = (const vec3f&)materials[materialID].diffuse;
          mesh->diffuse = gdt::randomColor(materialID);
        }

        if (mesh->vertex.empty())
          delete mesh;
        else
          model->meshes.push_back(mesh);
      }
    }

    // of course, you should be using tbb::parallel_for for stuff
    // like this:
    for (auto mesh : model->meshes)
      for (auto vtx : mesh->vertex)
        model->bounds.extend(vtx);

    std::cout << "created a total of " << model->meshes.size() << " meshes" << std::endl;
    return model;
  }
}