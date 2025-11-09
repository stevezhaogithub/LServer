#include "log.h"

namespace LServer
{
    Logger::Logger(const std::string &name) : m_name(name)
    {
    }

    void log(LogLevel::Level level, LogEvent::ptr event)
    {
        if (level >= m_level)
        {
            for (auto &i : m_appenders)
            {
                i->log(level, event);
            }
        }
    }

    void debug(LogEvent::ptr event)
    {
        log(LogLevel::DEBUG, event);
    }
    void info(LogEvent::ptr event)
    {
        log(LogLevel::INFO, event);
    }
    void warn(LogEvent::ptr event)
    {
        log(LogLevel::WARN, event);
    }
    void error(LogEvent::ptr event)
    {
        log(LogLevel::ERROR, event);
    }
    void fatal(LogEvent::ptr event)
    {
        log(LogLevel::FATAL, event);
    }

    void Logger::addAppender(LogAppender::ptr appender)
    {
        m_appenders.push_back(appender);
    }
    void Logger::delAppender(LogAppender::ptr appender)
    {
        for (auto it = m_appenders.begin(); it != m_appenders.end(); ++it)
        {
            if (*it == appender)
            {
                m_appenders.erase(it);
                break;
            }
        }
    }
}

/**
 *
 *
 * 一、成员初始化列表
 * Logger::Logger(const std::string &name) : m_name(name){}
 *
 *
 *
 *
 *
 *
 */