//
// Created by tokareva on 29.09.2021.
//

#ifndef LOGGINGTOOL_LOGGINGTOOL_H
#define LOGGINGTOOL_LOGGINGTOOL_H

#include <QString>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <map>
#include <memory>
#include <QSharedPointer>

#ifdef COMPILEDQTVERSION
#define _QTVERSION COMPILEDQTVERSION
#else
#define _QTVERSION 5
#endif

//#if (_QTVERSION == 5)
//
//#else
//#endif

enum LogLevel {
    Debug = 0,
    Info = 1,
    Warning = 2,
    Error = 3
};

class LoggingTool {
public:
    LoggingTool() = default;
    static void init(LogLevel minimalLevel = LogLevel::Warning, const QString& path = "/etc/psatoolkit/logfile.log");
    static void Debug(const QString& message);
    static void Info(const QString& message);
    static void Warning(const QString& message);
    static void Error(const QString& message);
    static void setLogLevel(LogLevel level);
    static void setLogPath(const QString& path);

private:
    static void Message(LogLevel level, const QString& message);
    static LogLevel currentLevel;
    static QString logPath;
    static QSharedPointer<QFile> file;
    static QSharedPointer<QTextStream> stream;
    static const std::map<LogLevel, QString> Levels;
    inline static QString BuildMessage(LogLevel level, const QString& message);
    static void deleteOldLogs(const QString& path);
};


#endif //LOGGINGTOOL_LOGGINGTOOL_H
