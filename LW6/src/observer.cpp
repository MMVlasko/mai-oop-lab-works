#include <fstream>
#include <iostream>
#include <utility>

#include <observer.h>

void ConsoleObserver::handle_event(const std::string &message) {
    std::cout << message << std::endl;
}

FileObserver::FileObserver(std::string filename) : _log_file_name(std::move(filename)) {}

void FileObserver::handle_event(const std::string &message) {
    auto log = std::ofstream(_log_file_name);
    log << message << std::endl;
    log.close();
}