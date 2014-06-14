#ifndef SHADER_HPP
#    define SHADER_HPP

/// Puke if clang is not used
static_assert(__clang__, "Your compiler is not supported.");

#    include <string>

#    include "Platform.hpp"

/**
 * An encapsulation of a GLSL shader (https://www.opengl.org/wiki/GLSL_Core_Language)
 * 
 * Various built-in types of Shaders are provided as template aliases including:
 * <ul>
 *  <li>VertexShader</li>
 *  <li>TessControlShader</li>
 *  <li>TessEvaluationShader</li>
 *  <li>GeometryShader</li>
 *  <li>FragmentShader</li>
 * </ul>
 * 
 * More built-in types shall be added to this API as the opengl specification evolves
 * 
 */
class Shader
{
  public:

    /**
     * Constructs a Shader with the provided source
     * 
     * @param source the source code of this GLSL program
     * 
     * @throw ResourceException if the implementation fails to create a GLSL shader program
     * 
     * @throw CompilationError if the implementation fails to compile the provided source code
     * 
     */
    explicit Shader(const std::string& source);

    /**
     * Copy-constructs a Shader based on the provided one
     * 
     * @param other the Shader to copy
     * 
     * @throws ResourceException if the implementation fails to create a GLSL shader program
     * 
     * @throws CompilationError if the implementation fails to compile the provided source code
     * 
     */
    Shader(const Shader& other) = default;

    /**
     * Copy-assigns this Shader based on the provided one
     * 
     * @param other the Shader to copy
     * 
     * @return *this
     * 
     * @throws ResourceException if the implementation fails to create a GLSL shader program
     * 
     * @throws CompilationError if the implementation fails to compile the provided source code
     * 
     */
    Shader& operator=(const Shader& other) = default;

    /**
     * Move-constructs this Shader based on the provided one
     * 
     * @param other the Shader to move
     * 
     */
    Shader(Shader&& other) noexcept = default;

    /**
     * Move-assigns this Shader based on the provided one
     * 
     * @param other the Shader to move
     * 
     * @return *this
     * 
     */
    Shader& operator=(Shader&& other) noexcept = default;

    /**
     * Retrieves an implementation defined handle to this Shader
     * 
     * @return an implementation defined handle to this Shader
     * 
     */
    virtual GLuint getHandle() const noexcept = 0;

    /**
     * Retreives the source code of this GLSL program
     * 
     * @return the source code of this GLSL program
     * 
     */
    virtual const std::string& getSource() const noexcept = 0;

    /**
     * Unregisters this GLSL program from the underlying implementation
     * 
     */
    virtual ~Shader() noexcept = default;
};

#    include <iostream>
#    include <memory>

namespace ShaderIO
{
    /**
     * Loads a shader of the provided type from the provided stream
     * 
     * @param stream the stream to load a shader from
     * 
     * @return a shader loaded from the provided stream
     * 
     * @throws CompilationError if the shader could not be compiled
     * 
     * @throws ResourceException if the implementation fails to create a GLSL shader program
     * 
     */
    template<typename T>
    T loadFromStream(std::istream& stream);

    /**
     * Loads a shader of the provided type from the provided file
     * 
     * @param fileName the name of the file from which to load a shader
     * 
     * @return a shader loaded from the provided file
     * 
     * @throws CompilationError if the shader could not be compiled
     * 
     * @throws ResourceException if the provided file could not be opened for reading
     * 
     * @throws ResourceException if the implementation fails to create a GLSL shader program
     * 
     */
    template<typename T>
    T loadFromFile(const std::string& fileName);

    /**
     * Loads a shared pointer to a shader of the provided type from the provided stream
     * 
     * @param stream the stream to load a shader from
     * 
     * @return a shared pointer to a shader of the provided type
     * 
     * @throws CompilationError if the shader could not be compiled
     * 
     * @throws ResourceException if the implementation fails to create a GLSL shader program
     * 
     */
    template<typename T>
    std::shared_ptr<T> loadSharedFromStream(std::istream& stream);

    /**
     * Loads a shared pointer to a shader of the provided type from the provided file
     * 
     * @param fileName the name of the file from which to load a shader
     * 
     * @return a shared pointer to a shader of the provided type
     * 
     * @throws CompilationError if the shader could not be compiled
     * 
     * @throws ResourceException if the provided file could not be opened for reading
     * 
     * @throws ResourceException if the implementation fails to create a GLSL shader program
     * 
     */
    template<typename T>
    std::shared_ptr<T> loadSharedFromFile(const std::string& fileName);
}

#    include "Shader.inl"

using VertexShader = detail::ShaderImpl<GL_VERTEX_SHADER>; /** A wrapper class for a GLSL Vertex Shader */
using TessControlShader = detail::ShaderImpl<GL_TESS_CONTROL_SHADER>; /** A wrapper class for a GLSL Tesselation control Shader */
using TessEvaluationShader = detail::ShaderImpl<GL_TESS_EVALUATION_SHADER>; /** A wrapper class for a GLSL Tesselation Evaluation Shader */
using GeometryShader = detail::ShaderImpl<GL_GEOMETRY_SHADER>; /** A wrapper class for a GLSL Geometry Shader */
using FragmentShader = detail::ShaderImpl<GL_FRAGMENT_SHADER>; /** A wrapper class for a GLSL Fragment Shader */

#endif
