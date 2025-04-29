#include <iostream>
#include <fstream>
#include <memory>

struct LogSink
{
    virtual void write(const std::string &msg) = 0;
    virtual ~LogSink() = default;
};

enum class SinkType
{
    CONSOLE,
    FILE,
    NONE
};

struct ConsoleSink : public LogSink
{
    void write(const std::string &msg) override
    {
        std::cout << msg << std::endl;
    }
};

struct FileSink : public LogSink
{
    void write(const std::string &msg) override
    {
        std::ofstream logFile("Log.txt", std::ios::app);
        logFile << msg << std::endl;
        logFile.close();
    }
};

struct NullSink : public LogSink
{
    void write(const std::string &msg) override {};
};

class Logger
{
public:
    static Logger &instance()
    {
        static Logger _instance;
        return _instance;
    }

    void set_sink(SinkType type)
    {
        switch (type)
        {
        case SinkType::CONSOLE:
            sink_.reset(new ConsoleSink());
            break;
        case SinkType::FILE:
            sink_.reset(new FileSink());
            break;
        default:
            sink_.reset(new NullSink());
            break;
        }
    }

    void log(const std::string &msg)
    {
        if (sink_ != nullptr)
        {
            sink_->write(msg);
        }
    }

private:
    std::unique_ptr<LogSink> sink_ = nullptr;

    // заборонити стороннє створення обєкту
    Logger() = default;
    Logger(Logger &) = delete;

    // заборонити копіювання/присвоєння
    Logger operator=(Logger &) = delete;
};

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        std::string type(argv[1]);

        if (type == "CONSOLE")
        {
            Logger::instance().set_sink(SinkType::CONSOLE);
        }
        else if (type == "FILE")
        {
            Logger::instance().set_sink(SinkType::FILE);
        }
        else if (type == "NONE")
        {
            Logger::instance().set_sink(SinkType::NONE);
        }
        else
        {
            return 1;
        }

        Logger::instance().log("Test message");

        return 0;
    }
    return 2;
}