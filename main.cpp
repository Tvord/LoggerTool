//
// Created by tokareva on 29.09.2021.
//

#include "LoggingTool.h"

int main(int argc, char** argv) {
    //LoggingTool::setLogLevel(LogLevel::Info);
    //LoggingTool::setLogPath("test.log");
    //LoggingTool::init(LogLevel::Debug, "test.log");
    LoggingTool::Info("Information");
    LoggingTool::Error("ERR");
    LoggingTool::Debug("Debug message");
    //LoggingTool::deinit();
    return 0;
}