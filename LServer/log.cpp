#ifndef __LSERVER_LOG_H__
#define __LSERVER_LOG_H__

#include <string>
#include <cstdint>

namespace LServer
{
    class LogEvent
    {
    public:
        typedef std::shared_ptr<LogEvent> ptr;
        LogEvent();

    private:
        const char *m_file = nullptr; // 文件名
        int32_t m_line = 0;           // 行号
        uint32_t m_elapse = 0;        // 程序启动开始到现在的毫秒数
        int32_t m_threadId = 0;       // 线程 Id
        uint32_t m_fiberId = 0;       // 协程 Id
        std::string m_content;        // 消息
        uint64_t m_time;              // 时间戳
    };

    // 日志级别类
    class LogLevel
    {
    public:
        // 日志级别
        enum Level
        {
            DEBUG = 1,
            INFO = 2,
            WARN = 3,
            ERROR = 4,
            FATAL = 5
        };
    };

    // 日志格式器
    class LogFormatter
    {
    public:
        typedef std::shared_ptr<LogFormatter> ptr;
        std::string format(LogEvent::ptr event);

    private:
    };

    // 日志输出
    class LogAppender
    {
    public:
        typedef std::shared_ptr<LogAppender> ptr;
        virtual ~LogAppender() {}
        void log(LogLevel::Level level, LogEvent::ptr event);

    private:
        LogLevel::Level m_level;
    };

    // 日志器
    class Logger
    {
    public:
        typedef std::shared_ptr<Logger> ptr;

        Logger(const std::string &name = "root");

        void log(LogLevel::Level level, LogEvent::ptr event);

    private:
        std::string m_name;
        LogLevel::Level m_level;
        LogAppender::ptr p;
    };

    // 输出到控制台的 Appender
    class StdoutLogAppender : public LogAppender
    {
    };

    // 定义输出到文件的 Appender
    class FileLogAppender : public LogAppender
    {
    };

}

#endif

/**
 * g++ log.cpp, 编译 + 链接
 *  1. 编译阶段：把 log.cpp 编译为目标文件。
 *  2. 链接阶段：默认尝试生成可执行文件，并寻找入口函数 main()。
 *
 * g++ -c log.cpp, 只编译, 不连接
 */