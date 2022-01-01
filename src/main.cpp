// Name of program mainreturn.cpp
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// Code Specific Header Files(s)
#include "..\include\logger.hpp"

using namespace std;
using namespace Log;

std::string domain;
std::string clients;
std::string logFileName;

// Create the object pointer for Logger Class
Logger* pLogger = NULL;

static void show_usage(std::string name) {
    std::cerr << "Usage: " << name << " <option(s)>\n"
              << "Options:\n"
              << "\t-h,--help\tShow this help message\n"
              << "\t-d,--domain\tSpecify the current domain\n"
              << "\t-c,--clients\tSpecify the path to list with all clients\n"
              << "\n"
              << "Logging:\n"
              << "\t-l,--logfile\tSpecify the (path) name to the logFile\n"
              << "\t--nolog\t\tDisable log\n"
              << "\t--debug\t\tEnable debugging only on console window\n"
              << std::endl;
}

Logger* log(int argc, char** argv) {
    bool debug = false;
    bool debugOnly = false;
    bool nolog = false;
    std::string logFileName;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

		if ((arg == "-l") || (arg == "--logfile")){
            logFileName = argv[i+1];
        } else if (arg == "--nolog") {
            nolog = true;
        }  else if (arg == "--debug") {
            debug = true;
        }
    }

    if (!logFileName.empty()) {
        pLogger = Logger::setLogFileName(logFileName);
    }
    if (nolog) {
        LOG_INFO("Logging are disabled");
        pLogger->disableLog();
    }
    if (debug){
        pLogger->enableBothLogging();
        LOG_INFO("Enable debugging only on console window");
    }

    return Logger::getInstance();
}

void checkArgv(int argc, char** argv){
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

		if ((arg == "-h") || (arg == "--help")) {
            show_usage(argv[i]);
        } else if ((arg == "-d") || (arg == "--domain")) {
			domain = argv[i+1];
        } else if ((arg == "-c") || (arg == "--clients")) {
			clients = argv[i+1];
        } 
    }
}

int main(int argc, char** argv) {
    pLogger = log(argc, argv);
    LOG_BUFFER("####### Programm start #######");
    checkArgv(argc, argv);
   
    if (argc < 2) {
        LOG_ERROR("No Arguments found!\n\t\t\t\tUse '-h' for show usage");
        return 1;
    }  
   
    LOG_ERROR("Message Logged using Direct Interface, Log level: LOG_ERROR");
    LOG_ALARM("Message Logged using Direct Interface, Log level: LOG_ALARM");
    LOG_ALWAYS("Message Logged using Direct Interface, Log level: LOG_ALWAYS");
    LOG_INFO("Message Logged using Direct Interface, Log level: LOG_INFO");
    LOG_BUFFER("Message Logged using Direct Interface, Log level: LOG_BUFFER");
    LOG_TRACE("Message Logged using Direct Interface, Log level: LOG_TRACE");
    LOG_DEBUG("Message Logged using Direct Interface, Log level: LOG_DEBUG");

    LOG_BUFFER("####### Programm exit #######");
    return 0;
}