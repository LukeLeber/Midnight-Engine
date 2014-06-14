#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "BuildConstraints.hpp"
#include "Matrix.hpp"
#include "Shader.hpp"

/**
 * A wrapper class for a GLSL program.  Programs may not be copy-constructed 
 * or copy-assigned, but may be move-constructed and move-assigned.  Programs 
 * are linked upon construction, failing with an exception upon error.  This 
 * means that invalid program objects will never exist.  Unfortunately, this 
 * also means that programs may not have shaders added or removed from them 
 * after construction, nor are they able to be re-linked.
 * 
 */
class Program
{

    /// The implementation provided handle to this Program    
    GLuint handle;

  public:

    /**
     * Constructs a Program from the provided variable-length list of shared Shaders
     * 
     * @param first the first shared Shader
     * 
     * @param shaders the remaining shared Shaders
     * 
     * @throws LinkingError if an error occurs while linking this Program
     * 
     * @throws ResourceException if the implementation fails to create this Program
     * 
     */
    template<typename... E>
    explicit Program(std::shared_ptr<Shader> first, E&&... shaders);

    /**
     * Constructs a Program from the provided variable-length list of Shaders
     * 
     * @param first the first Shader
     * 
     * @param shaders the remaining Shaders
     * 
     * @throws LinkingError if an error occurs while linking this Program
     * 
     * @throws ResourceException if the implementation fails to create this Program
     * 
     */
    template<typename... E>
    explicit Program(Shader&& first, E&&... shaders);

    /**
     * Constructs a Program from the provided variable-length list of Shaders
     * 
     * @param first the first Shader
     * 
     * @param shaders the remaining Shaders
     * 
     * @throws LinkingError if an error occurs while linking this Program
     * 
     * @throws ResourceException if the implementation fails to create this Program
     * 
     */
    template<typename... E>
    explicit Program(Shader& first, E&... shaders);

    /**
     * Constructs a Program from the provided initializer list
     * 
     * @param shaders an initializer_list containing pointers to the shaders to create this Program with
     * 
     * @throws LinkingError if an error occurs while linking this Program
     * 
     * @throws ResourceException if the implementation fails to create this Program
     * 
     */
    explicit Program(const std::initializer_list<Shader*>& shaders);

    /**
     * Programs are not copy-constructible
     * 
     */
    Program(const Program&) = delete;

    /**
     * Programs are not copy-assignable
     * 
     */
    Program& operator=(const Program&) = delete;

    /**
     * Move-constructs this Program based on the provided one
     * 
     * @param other the program that is being moved
     * 
     */
    Program(Program&& other);

    /**
     * Move-assigns this Program based on the provided one
     * 
     * @param other the program that is being moved
     * 
     * @return *this
     * 
     */
    Program& operator=(Program&& other);

    /**
     * Binds this Program to the current context
     * 
     */
    void bind();

    /**
     * Unbinds this Program from the current context
     * 
     */
    void unbind();

    /**
     * Sets the specified uniform to the provided value(s)
     * 
     * @param uniformID the uniform to set
     * 
     * @param tuples the value(s) to set
     * 
     * @throws UniformMismatchException if the provided arguments do not match the type in the program
     * 
     */
    template<typename... E>
    void setUniform(const std::string& uniformID, E&&... tuples);
    
    /**
     * Sets the specified matrix uniform to the provided value
     * 
     * @param uniformID the uniform to set
     * 
     * @param matrix the Matrix to set
     * 
     * @throws UniformMismatchException if the provided arguments do not match the type in the program
     * 
     */
    template<typename T, std::size_t Rows, std::size_t Columns>
    void setMatrixUniform(const std::string& uniformID, const midnight::Matrix<T, Rows, Columns>& matrix);
};

#include "Program.inl"

#endif
