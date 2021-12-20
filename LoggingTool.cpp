//
// Created by tokareva on 29.09.2021.
//

#include "LoggingTool.h"
#include <QElapsedTimer>
#include <QDebug>
#include <QTextCodec>
#include <QFileInfo>
#include <QDir>

const std::map<LogLevel, QString> LoggingTool::Levels{{LogLevel::Debug, "Debug"},
        {LogLevel::Info, "Info"}, {LogLevel::Warning, "Warning"}, {LogLevel::Error,"Error"}};
QString LoggingTool::logPath{"/etc/psatoolkit/logfile.log"};
LogLevel LoggingTool::currentLevel{LogLevel::Warning};
QSharedPointer<QFile> LoggingTool::file{nullptr};
QSharedPointer<QTextStream> LoggingTool::stream{nullptr};


void LoggingTool::Debug(const QString &message) {
    if (currentLevel == 0)
        LoggingTool::Message(LogLevel::Debug, message);
}

void LoggingTool::Info(const QString &message) {
    if (currentLevel < 2)
        LoggingTool::Message(LogLevel::Info, message);
}

void LoggingTool::Warning(const QString &message) {
    if (currentLevel < 3)
        LoggingTool::Message(LogLevel::Warning, message);
}

void LoggingTool::Error(const QString &message) {
    if (currentLevel < 4)
        LoggingTool::Message(LogLevel::Error, message);
}

void LoggingTool::setLogLevel(LogLevel level) {
    currentLevel = level;
}

void LoggingTool::setLogPath(const QString &path) {
    //! Close file if exist
    logPath = path;
    //! Create new file
}

void LoggingTool::Message(LogLevel level, const QString &message) {
    if (Q_UNLIKELY(!stream)) {
        LoggingTool::init();
    }
    *stream << BuildMessage(level, message);
    stream->flush();
}

QString LoggingTool::BuildMessage(LogLevel level, const QString &message) {
    return QString("[%1] %2: %3\n").arg(QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss"),
                                        Levels.at(level), message);
}

void LoggingTool::init(LogLevel minimalLevel, const QString &path) {
    deleteOldLogs(path);
    currentLevel = minimalLevel;
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));
#if (_QTVERSION == 5)
    file.reset(new QFile(path));
#else
    file = QSharedPointer<QFile>(new QFile(path));
#endif
    if (!file->open(QIODevice::WriteOnly))
        qDebug() << "Something wring with opening logfile: " << path;
#if (_QTVERSION == 5)
    stream.reset(new QTextStream(&*file));
#else
    stream = QSharedPointer<QTextStream>(new QTextStream(&*file));
#endif
    stream->setCodec("UTF-8");
}

void LoggingTool::deleteOldLogs(const QString &path) {
    auto dirParts = path.split('/');
    dirParts.removeLast();
    auto dirPath = dirParts.join("/");
    auto dirInfo = QDir(dirPath);
    for (auto& fileInfo : dirInfo.entryInfoList(QStringList("*.log"))) {
        if (fileInfo.created().daysTo(QDateTime::currentDateTime()) > 7) {
            QFile f(fileInfo.absoluteFilePath());
            f.remove();
        }
    }
}
