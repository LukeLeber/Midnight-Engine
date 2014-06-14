inline midnight::glsl::CompilationError::CompilationError(const std::string& message, const std::string& shaderSource) noexcept :
midnight::GLException(message),
shaderSource(shaderSource)
{

}

inline const std::string& midnight::glsl::CompilationError::getShaderSource() const noexcept
{
    return shaderSource;
}
