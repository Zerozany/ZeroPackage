_Pragma("once");
#include <memory>
#ifndef SPDLOG_ACTIVE_LEVEL
    #define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif
#include <spdlog/spdlog.h>

#if defined(_WIN32) && defined(_MSC_VER)
    #ifdef ZEROPACKAGE_BUILDING
        #define PACKAGE_DLL __declspec(dllexport)
    #else
        #define PACKAGE_DLL __declspec(dllimport)
    #endif
#elif defined(__GNUC__) || defined(__clang__)
    #define PACKAGE_DLL __attribute__((visibility("default")))
#else
    #define PACKAGE_DLL
#endif

class PACKAGE_DLL LogManager
{
public:
    static auto instance() noexcept -> LogManager*;

    ~LogManager() noexcept;

public:
    auto init(const std::string& _logPath, std::size_t _logNum = 3) noexcept -> void;

    template <typename... Args>
    auto trace(fmt::format_string<Args...> _fmt, Args&&... _args) noexcept -> void;

    template <typename... Args>
    auto debug(fmt::format_string<Args...> _fmt, Args&&... _args) noexcept -> void;

    template <typename... Args>
    auto info(fmt::format_string<Args...> _fmt, Args&&... _args) noexcept -> void;

    template <typename... Args>
    auto warn(fmt::format_string<Args...> _fmt, Args&&... _args) noexcept -> void;

    template <typename... Args>
    auto error(fmt::format_string<Args...> _fmt, Args&&... _args) noexcept -> void;

    template <typename... Args>
    auto critical(fmt::format_string<Args...> _fmt, Args&&... _args) noexcept -> void;

private:
    explicit(true) LogManager();

private:
    std::shared_ptr<spdlog::logger> m_LoggerInstance{nullptr};
};

template <typename... Args>
inline auto LogManager::trace(fmt::format_string<Args...> _fmt, Args&&... _args) noexcept -> void
{
    if (!m_LoggerInstance)
    {
        return;
    }
    SPDLOG_LOGGER_TRACE(m_LoggerInstance, _fmt, std::forward<Args>(_args)...);
}

template <typename... Args>
inline auto LogManager::debug(fmt::format_string<Args...> _fmt, Args&&... _args) noexcept -> void
{
    if (!m_LoggerInstance)
    {
        return;
    }
    SPDLOG_LOGGER_DEBUG(m_LoggerInstance, _fmt, std::forward<Args>(_args)...);
}

template <typename... Args>
inline auto LogManager::info(fmt::format_string<Args...> _fmt, Args&&... _args) noexcept -> void
{
    if (!m_LoggerInstance)
    {
        return;
    }
    SPDLOG_LOGGER_INFO(m_LoggerInstance, _fmt, std::forward<Args>(_args)...);
}

template <typename... Args>
inline auto LogManager::warn(fmt::format_string<Args...> _fmt, Args&&... _args) noexcept -> void
{
    if (!m_LoggerInstance)
    {
        return;
    }
    SPDLOG_LOGGER_WARN(m_LoggerInstance, _fmt, std::forward<Args>(_args)...);
}

template <typename... Args>
inline auto LogManager::error(fmt::format_string<Args...> _fmt, Args&&... _args) noexcept -> void
{
    if (!m_LoggerInstance)
    {
        return;
    }
    SPDLOG_LOGGER_ERROR(m_LoggerInstance, _fmt, std::forward<Args>(_args)...);
}

template <typename... Args>
inline auto LogManager::critical(fmt::format_string<Args...> _fmt, Args&&... _args) noexcept -> void
{
    if (!m_LoggerInstance)
    {
        return;
    }
    SPDLOG_LOGGER_CRITICAL(m_LoggerInstance, _fmt, std::forward<Args>(_args)...);
}
