namespace midnight
{
    
    inline Mesh::Mesh(const std::vector<Vertex32F>& vertices, const std::vector<midnight::Material>& materials, const std::vector<midnight::Mesh::Renderable>& renderables) : 
        vertices(vertices), materials(materials), meshes(renderables)
    {
        
    }



    inline std::ostream& operator<<(std::ostream& stream, const Mesh& /*mesh*/)
    {
        // TODO: implement after finalizing class
        return stream;
    }


    inline std::ostream& operator<<(std::ostream& stream, Mesh&& /*mesh*/)
    {
        // TODO: implement after finalizing class
        return stream;
    }


    inline std::istream& operator>>(std::istream& stream, Mesh& /*mesh*/)
    {
        // TODO: implement after finalizing class
        return stream;
    }
}