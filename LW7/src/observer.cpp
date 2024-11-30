#include <fstream>
#include <iostream>
#include <utility>

#include <observer.h>
#include <mutex.h>

void ConsoleObserver::handle_event(const std::string &message) {
    std::lock_guard lock(stdout_mtx);
    std::cout << message << std::endl;
}

FileObserver::FileObserver(std::string filename) : _log_file_name(std::move(filename)) {}

void FileObserver::handle_event(const std::string &message) {
    std::lock_guard lock(file_mutex);
    auto log = std::ofstream(_log_file_name, std::ios::app);
    log << message << std::endl;
    log.close();
}