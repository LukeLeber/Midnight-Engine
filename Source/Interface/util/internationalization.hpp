#ifndef INTERNATIONALIZATION_HPP
#    define INTERNATIONALIZATION_HPP

#    include <unordered_map>

#    include "dynamic_assert.hpp"

class Strings
{
    static std::unordered_map<std::string, std::wstring> strings;

    static const std::wstring KEY_NOT_FOUND;

  public:

    static const std::wstring& getString(const std::string& key)
    {
        auto iter = strings.find(key);
        if(iter != strings.end())
        {
            return iter->second;
        }
        dynamic_assert(iter != strings.end(), "string key: \"" << key << "\" was not found");
        return KEY_NOT_FOUND;
    }

};

std::unordered_map<std::string, std::wstring> Strings::strings;

const std::wstring Strings::KEY_NOT_FOUND(L"null");


#endif