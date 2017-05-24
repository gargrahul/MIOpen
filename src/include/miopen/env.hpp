#ifndef GUARD_MIOPEN_ENV_HPP
#define GUARD_MIOPEN_ENV_HPP

#include <cstdlib>
#include <cstring>

namespace miopen {

/// \todo Rework: Case-insensitive string compare, ODR, (?) move to .cpp

// Declare a cached environment variable
#define MIOPEN_DECLARE_ENV_VAR(x) struct x { static const char* value() { return #x; }};

/*
 * Returns false if a feature-controlling environment variable is defined
 * and set to something which disables a feature.
 */
inline bool IsEnvvarValueDisabled(const char* name)
{
    const auto value_env_p = std::getenv(name);
    return value_env_p != nullptr && 
         ( std::strcmp(value_env_p, "disable") == 0
        || std::strcmp(value_env_p, "disabled") == 0
        || std::strcmp(value_env_p, "0") == 0
        || std::strcmp(value_env_p, "no") == 0
        || std::strcmp(value_env_p, "false") == 0 );
}

inline bool IsEnvvarValueEnabled(const char* name)
{
    const auto value_env_p = std::getenv(name);
    return value_env_p != nullptr && 
         ( std::strcmp(value_env_p, "enable") == 0
        || std::strcmp(value_env_p, "enabled") == 0
        || std::strcmp(value_env_p, "1") == 0
        || std::strcmp(value_env_p, "yes") == 0
        || std::strcmp(value_env_p, "true") == 0 );
}

template<class T>
inline const char * GetStringEnv(T)
{
    static const char * result = std::getenv(T::value());
    return result;
}

template<class T>
inline bool IsEnabled(T)
{
    static const bool result = miopen::IsEnvvarValueEnabled(T::value());
    return result;
}

template<class T>
inline bool IsDisabled(T)
{
    static const bool result = miopen::IsEnvvarValueDisabled(T::value());
    return result;
}
} // namespace miopen

#endif
