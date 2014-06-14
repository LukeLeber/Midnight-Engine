/**
 * This file is protected under the KILLGPL License.
 * 
 * For more information visit www.midnightengine.com/license
 *  
 * @version 1.1
 *      1/22/2014 - initial draft
 *      3/26/2014 - API & Documentation Enhancement
 * 
 * @since 1.0
 * 
 * @author Luke A. Leber <LukeLeber@gmail.com>
 * 
 */
#include "Platform.hpp"

namespace midnight
{

/// @internal
/// A bit hacky, reinterpret_casting and all, but we're dealing with an archaic C-API...
/// glGetError can fail with GL_INVALID_OPERATION in the (deprecated) fixed function pipeline,
/// but we're not using it, so it can be safely ignored.  Likewise, gluErrorString had better not 
/// fail since we're directly feeding it a value that the opengl implementation generates!
inline GLException::GLException(const std::string& message) noexcept : 
    std::runtime_error(message),
    freezeFrameData(reinterpret_cast<const char*>(gluErrorString(glGetError())))
{

}

inline const std::string& GLException::getFreezeFrameData() const noexcept
{
    return freezeFrameData;
}

}
