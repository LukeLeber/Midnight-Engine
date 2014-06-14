#ifndef MATERIAL_HPP
#    define MATERIAL_HPP

#    include <iostream>

#    include "Color.hpp"

namespace midnight
{

/**
 * An enumeration of all possible lighting configurations for a Material
 * 
 */
enum LightingMode
{
    NO_LIGHTING, /** No lighting should be used */
    AMBIENT, /** Ambient lighting should be used */
    DIFFUSE, /** Diffuse lighting should be used */
    EMISSIVE, /** Emissive lighting should be used */
    SPECULAR, /** Specular lighting should be used */
    AMBIENT_AND_DIFFUSE, /** Ambient and Diffuse lighting should be used */
    AMBIENT_AND_EMISSIVE, /** Ambient and Emissive lighting should be used */
    AMBIENT_AND_SPECULAR, /** Ambient and Specular lighting should be used */
    AMBIENT_AND_DIFFUSE_AND_EMISSIVE, /** Ambient, Diffuse, and Emissive lighting should be used */
    AMBIENT_AND_DIFFUSE_AND_SPECULAR, /** Ambient, Diffuse, and Specular lighting should be used */
    AMBIENT_AND_EMISSIVE_AND_SPECULAR, /** Ambient, Emissive, and Specular lighting should be used */
    DIFFUSE_AND_EMISSIVE, /** Diffuse and Emissive lighting should be used */
    DIFFUSE_AND_SPECULAR, /** Diffuse and Specular lighting should be used */
    DIFFUSE_AND_EMISSIVE_AND_SPECULAR, /** Diffuse, Emissive, and Specular lighting should be used */
    EMISSIVE_AND_SPECULAR, /** Emissive and Specular lighting should be used */
    ALL_LIGHTING, /** All lighting should be used*/
};

/**
 * An enumeration of all possible face culling configurations for a Material
 * 
 */
enum CullingMode
{
    NO_CULLING, /** No culling should be performed */
    CULL_FRONT_FACES, /** Front faces should be culled */
    CULL_BACK_FACES, /** Back faces should be culled*/
    CULL_ALL_FACES /** All faces should be culled */
};

class Material;

}

/**
 * Inserts the provided Material into the provided output stream
 * 
 * @param stream the output stream to write to
 * 
 * @param material the Material to write
 * 
 * @return the provided output stream
 * 
 */
std::ostream& operator<<(std::ostream& stream, const midnight::Material& material);

/**
 * Inserts the provided Material into the provided output stream
 * 
 * @param stream the output stream to write to
 * 
 * @param material the Material to write
 * 
 * @return the provided output stream
 * 
 * @note [optimization] this method should be preferred when the provided Material is not used by the calling method
 * 
 */
std::ostream& operator<<(std::ostream& stream, midnight::Material&& material);

/**
 * Extracts a Material from the provided input stream
 * 
 * @param stream the input stream to read from
 * 
 * @param material the Material to populate with the extracted data
 * 
 * @return the provided input stream
 * 
 */
std::istream& operator>>(std::istream& stream, midnight::Material& material);

namespace midnight
{

/**
 * TODO: Class Desc. Docs
 */
class Material
{
    
    friend std::ostream& operator<<(std::ostream&, const Material&);
    friend std::ostream& operator<<(std::ostream&, Material&&);
    friend std::istream& operator>>(std::istream&, Material&);

    /// The lighting mode used by this Material
    LightingMode lightingMode;

    /// The culling mode used by this Material
    CullingMode cullingMode;

    /// Should this Material auto-normalize non-unit vectors?
    bool autoNormalize;

    /// The ambience of this Material
    Color<float, 4> ambience;

    /// The diffusion of this Material
    Color<float, 4> diffusion;

    /// The emission of this Material
    Color<float, 4> emission;

    /// The specularity of this Material
    Color<float, 4> specularity;

  public:

    // TODO: docs after finalizing API
    Material(
            LightingMode lightingMode = LightingMode::ALL_LIGHTING,
            CullingMode cullingMode = CullingMode::NO_CULLING,
            bool autoNormalize = true,
            Color<float, 4> ambience = (Color<float, 4>()),
            Color<float, 4> diffusion = (Color<float, 4>()),
            Color<float, 4> emission = (Color<float, 4>()),
            Color<float, 4> specularity = (Color<float, 4>()));

    /**
     * Sets the lighting mode of this Material
     * 
     * @param newMode the new lighting mode to set
     * 
     * @return *this
     * 
     */
    Material& setLightingMode(LightingMode newMode) noexcept;

    /**
     * Retrieves the lighting mode of this Material
     * 
     * @return the lighting mode of this Material
     * 
     */
    LightingMode getLightingMode() const noexcept;

    /**
     * Sets the culling mode of this Material
     * 
     * @param newMode the new culling mode to set
     * 
     * @return *this
     * 
     */
    Material& setCullingMode(CullingMode newMode) noexcept;

    /**
     * Retrieves the culling mode of this Material
     * 
     * @return the culling mode of this Material
     * 
     */
    CullingMode getCullingMode() const noexcept;

    /**
     * Sets the auto-normalization state of this Material
     * 
     * @param enabled should auto-normalization be enabled?
     * 
     * @return *this
     * 
     */
    Material& setAutoNormalization(bool enabled) noexcept;

    /**
     * Should this Material auto-normalize itself?
     * 
     * @return true if auto-normalization is enabled, otherwise false
     * 
     */
    bool autoNormalizes() const noexcept;

    /**
     * Retrieves the ambient color of this Material
     * 
     * @return the ambient color of this Material
     * 
     */
    const Color<float, 4>& getAmbience() const noexcept;

    /**
     * Retrieves the ambient color of this Material
     * 
     * @return the ambient color of this Material
     * 
     */
    Color<float, 4>& getAmbience() noexcept;

    /**
     * Retrieves the diffuse color of this Material
     * 
     * @return the diffuse color of this Material
     * 
     */
    const Color<float, 4>& getDiffusion() const noexcept;

    /**
     * Retrieves the diffuse color of this Material
     * 
     * @return the diffuse color of this Material
     * 
     */
    Color<float, 4>& getDiffusion() noexcept;

    /**
     * Retrieves the emissive color of this Material
     * 
     * @return the emissive color of this Material
     * 
     */
    const Color<float, 4>& getEmission() const noexcept;

    /**
     * Retrieves the emissive color of this Material
     * 
     * @return the emissive color of this Material
     * 
     */
    Color<float, 4>& getEmission() noexcept;

    /**
     * Retrieves the specular color of this Material
     * 
     * @return the specular color of this Material+
     * 
     */
    const Color<float, 4>& getSpecularity() const noexcept;

    /**
     * Retrieves the specular color of this Material
     * 
     * @return the specular color of this Material
     * 
     */
    Color<float, 4>& getSpecularity() noexcept;

};

}

#include "Material.inl"

#endif