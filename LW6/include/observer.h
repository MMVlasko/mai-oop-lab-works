#pragma once

#include <string>

class Observer {
    public:
        Observer() = default;

        Observer(const Observer &other) = default;

        Observer(Observer &&other) = default;

        Observer &operator=(const Observer &other) = default;

        Observer &operator=(Observer &&other) = default;

        virtual ~Observer() = default;

        virtual void notify(const std::string &message) {};
};

class ConsoleObserver : public Observer {
    public:
        using Observer::Observer;

        void notify(const std::string &message) override;
};

class FileObserver : public Observer {
    std::string _log_file_name;

    public:
        using Observer::Observer;

        explicit FileObserver(const std::string &filename);

        void notify(const std::string &message) override;

};