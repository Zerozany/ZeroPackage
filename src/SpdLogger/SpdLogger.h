_Pragma("once");
#include <memory>
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

class PACKAGE_DLL SpdLogger
{
public:
    static auto instance() noexcept -> SpdLogger*;

    ~SpdLogger() noexcept;

public:
    static auto init(const std::string& _logPath, std::size_t _logNum = 3) noexcept -> void;

private:
    explicit(true) SpdLogger();

private:
    inline static std::shared_ptr<spdlog::logger> m_LoggerInstance{nullptr};
};
