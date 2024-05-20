#pragma  once
#include <chrono>
#include <ctime>
#include <fstream>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;


class Logger {
public:
  enum class Level {
    ERROR = 0,
    WARNING,
    INFO,
    DEBUG,
  };

private:
  ofstream logFile;
  Level currentLevel;

  Logger(const string &filename, Level level = Level::INFO): currentLevel(level) {
    logFile.open(filename, ios::app);
    if (!logFile.is_open()) {
      throw runtime_error("Failed to open log file");
    }
  }

  Logger(const Logger&) = delete;
  Logger &operator=(const Logger&) = delete;

public:
  ~Logger() {
    logFile.close();
  }
  static Logger &getInstance(const string& filename = "logfile.txt") {
    static Logger instance(filename);
    return instance;
  }

  void setLevel(Level level) {
    this->currentLevel = level;
  }

  void log(const string& message, Level level = Level::INFO) {
    if (currentLevel >= level) {
      auto t = chrono::system_clock::now();
      time_t time = chrono::system_clock::to_time_t(t);
      logFile << ctime(&time) << " " << levelToString(level) << ": " << message << '\n';
    }
  }

 private:
  string levelToString(Level level) {
    switch (level) {
      case Level::DEBUG:
        return "DEBUG";
        break;
      case Level::INFO:
        return "INFO";
        break;
      case Level::ERROR:
        return "ERROR";
        break;
      case Level::WARNING:
        return "WARNING";
        break;
    }
  }
};

