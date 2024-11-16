#include <fstream>
#include <iostream>

#include <observer.h>

void ConsoleObserver::notify(const std::string &message) {
    std::cout << message << std::endl;
}

FileObserver::FileObserver(const std::string &filename) : _log_file_name(filename) {}

void FileObserver::notify(const std::string &message) {
    auto log = std::ofstream(_log_file_name);
    log << message << std::endl;
    log.close();
}
