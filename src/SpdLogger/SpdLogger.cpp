#include "SpdLogger.h"
#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <vector>
#include <print>

#if defined(__ANDROID__)
    #include <spdlog/sinks/android_sink.h>
#endif

static constexpr std::size_t LOGSIZE{1024 * 1024 * 5};

auto SpdLogger::instance() noexcept -> SpdLogger*
{
    static SpdLogger* zeroLogger{new SpdLogger{}};
    return zeroLogger;
}

SpdLogger::SpdLogger()
{
}

SpdLogger::~SpdLogger() noexcept
{
    spdlog::shutdown();
    m_LoggerInstance.reset();
}

auto SpdLogger::init(const std::string& _logPath, std::size_t _logNum) noexcept -> void
{
    try
    {
        spdlog::init_thread_pool(8192, 1);
        // 控制台 sink：输出所有等级（仅打印，不写文件）
        std::vector<spdlog::sink_ptr> sinks{};
#if defined(_WIN32)
        // Windows: 控制台 sink
        auto consoleSink{std::make_shared<spdlog::sinks::stdout_color_sink_mt>()};
        consoleSink.get()->set_level(spdlog::level::trace);
        sinks.push_back(consoleSink);
#elif defined(__ANDROID__)
        // Android: logcat sink
        auto androidSink{std::make_shared<spdlog::sinks::android_sink_mt>()};
        androidSink.get()->set_level(spdlog::level::trace);
        sinks.push_back(androidSink);
#endif
        // 文件 sink：只写 warn 以上等级日志（自动轮转）
        auto fileSink{std::make_shared<spdlog::sinks::rotating_file_sink_mt>(_logPath, LOGSIZE, _logNum)};
        fileSink->set_level(spdlog::level::warn);
        sinks.push_back(fileSink);

        m_LoggerInstance = std::make_shared<spdlog::async_logger>("SpdLogger", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
        m_LoggerInstance->flush_on(spdlog::level::trace);
        spdlog::register_logger(m_LoggerInstance);
        spdlog::set_default_logger(m_LoggerInstance);
        spdlog::set_pattern("[%Y-%m-%d %H:%M:%S]%^ [%s:%#][%l]: %v%$");
    }
    catch (const std::exception& _e)
    {
        std::println("Failed to enable the logging function:{}", _e.what());
    }
}

auto SpdLogger::set_level(const spdlog::level::level_enum& _level) noexcept -> void
{
    m_LoggerInstance->set_level(_level);
}
