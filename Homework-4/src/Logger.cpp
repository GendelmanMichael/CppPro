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

char *ToLowerCase(char *inp)
{
    int i = 0;
    while (inp[i] != '\0')
    {
        inp[i] += (inp[i] >= 'A' && inp[i] <= 'Z') ? 32 : 0;
        i++;
    }
    return inp;
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        std::string type(ToLowerCase(argv[1]));

        if (type == "console")
        {
            Logger::instance().set_sink(SinkType::CONSOLE);
        }
        else if (type == "file")
        {
            Logger::instance().set_sink(SinkType::FILE);
        }
        else if (type == "none")
        {
            Logger::instance().set_sink(SinkType::NONE);
        }
        else
        {
            std::cout << "Unknown logger type please chose CONSOLE or  FILE or NONE)" << std::endl;
            return 0;
        }

        Logger::instance().log("Test message");

        return 0;
    }
    std::cout << "Please add type of logger after program call (CONSOLE, FILE, NONE)" << std::endl;
    return 0;
}