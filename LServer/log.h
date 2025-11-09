#ifndef __LSERVER_LOG_H__
#define __LSERVER_LOG_H__

#include <string>
#include <cstdint>
#include <list>

namespace LServer
{
    // 日志事件类
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

        void debug(LogEvent::ptr event);
        void info(LogEvent::ptr event);
        void warn(LogEvent::ptr event);
        void error(LogEvent::ptr event);
        void fatal(LogEvent::ptr event);

        void addAppender(LogAppender::ptr appender);
        void delAppender(LogAppender::ptr appender);
        LogLevel::Level getLevel() const { return m_level; }
        void setLevel(LogLevel::Level val) { m_level = val; }

    private:
        std::string m_name;                      // 日志名称
        LogLevel::Level m_level;                 // 日志级别, 只有满足该日志级别的日志才会被输出
        std::list<LogAppender::ptr> m_appenders; // Appender 集合，是一个列表
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
 * 一、g++ -c 只编译不链接
 * g++ log.cpp, 编译 + 链接
 *  1. 编译阶段：把 log.cpp 编译为目标文件。
 *  2. 链接阶段：默认尝试生成可执行文件，并寻找入口函数 main()。
 *
 * g++ -c log.cpp, 只编译, 不连接
 *
 *
 * 二、vector 和 list
 * vector 和 list 的区别:
 * - std::vector, 动态数组（连续内存）,元素在内存中是连续的
 * - std::list, 双向链表, 每个节点分散分布，通过指针链接
 *
 *
 * 三、智能指针: 无需手动 new 和 delete
 * std::shared_ptr<LogEvent> ptr;
 *
 *
 *
 * 四、常量成员函数
 * LogLevel::Level getLevel() const { return m_level; }
 * 这个函数不会修改档当前对象的成员变量
 *
 *
 */
