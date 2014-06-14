namespace midnight
{
    inline Material::Material(
            LightingMode lightingMode,
            CullingMode cullingMode,
            bool autoNormalize,
            Color<float, 4> ambience,
            Color<float, 4> diffusion,
            Color<float, 4> emission,
            Color<float, 4> specularity) :
    lightingMode(lightingMode),
    cullingMode(cullingMode),
    autoNormalize(autoNormalize),
    ambience(ambience),
    diffusion(diffusion),
    emission(emission),
    specularity(specularity)
    {

    }

    inline Material& Material::setLightingMode(LightingMode newMode) noexcept
    {
        this->lightingMode = newMode;
        return *this;
    }

    inline LightingMode Material::getLightingMode() const noexcept
    {
        return this->lightingMode;
    }

    inline Material& Material::setCullingMode(CullingMode newMode) noexcept
    {
        this->cullingMode = newMode;
        return *this;
    }

    inline CullingMode Material::getCullingMode() const noexcept
    {
        return this->cullingMode;
    }

    inline Material& Material::setAutoNormalization(bool enabled) noexcept
    {
        this->autoNormalize = enabled;
        return *this;
    }

    inline bool Material::autoNormalizes() const noexcept
    {
        return this->autoNormalize;
    }

    inline const Color<float, 4>& Material::getAmbience() const noexcept
    {
        return this->ambience;
    }

    inline Color<float, 4>& Material::getAmbience() noexcept
    {
        return this->ambience;
    }

    inline const Color<float, 4>& Material::getDiffusion() const noexcept
    {
        return this->diffusion;
    }

    inline Color<float, 4>& Material::getDiffusion() noexcept
    {
        return this->diffusion;
    }

    inline const Color<float, 4>& Material::getEmission() const noexcept
    {
        return this->emission;
    }

    inline Color<float, 4>& Material::getEmission() noexcept
    {
        return this->emission;
    }

    inline const Color<float, 4>& Material::getSpecularity() const noexcept
    {
        return this->specularity;
    }

    inline Color<float, 4>& Material::getSpecularity() noexcept
    {
        return this->specularity;
    }

    inline std::ostream& operator<<(std::ostream& stream, const Material& /*material*/)
    {
        // TODO: implement after finalizing class
        return stream;
    }

    inline std::ostream& operator<<(std::ostream& stream, Material&& /*material*/)
    {
        // TODO: implement after finalizing class
        return stream;
    }

    inline std::istream& operator>>(std::istream& stream, Material& /*material*/)
    {
        // TODO: implement after finalizing class
        return stream;
    }
}
