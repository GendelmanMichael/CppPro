#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <memory>
#include <string>
#include <functional>

std::string ToLowerCase(std::string inp)
{
    int i = 0;
    while (inp[i] != '\0')
    {
        inp[i] += (inp[i] >= 'A' && inp[i] <= 'Z') ? 32 : 0;
        i++;
    }
    return inp;
}

class INumberFilter
{
public:
    virtual bool keep(int number) = 0;
};

class EvenFilter : public INumberFilter
{
public:
    bool keep(int number) override
    {
        return number % 2 == 0;
    }
};

class OddFilter : public INumberFilter
{
public:
    bool keep(int number) override
    {
        return number % 2 == 1;
    }
};

class GtFilter : public INumberFilter
{
public:
    GtFilter(int t) : threshold(t) {}

    bool keep(int number) override
    {
        return number > threshold;
    }

private:
    int threshold;
};

class IRegistry
{
    virtual std::unique_ptr<INumberFilter> create(std::string type) = 0;
};

class FilterFactoryRegistry : public IRegistry
{
public:
    static FilterFactoryRegistry &instance()
    {
        static FilterFactoryRegistry reg;
        return reg;
    }

    void register_factory(const std::string &type, std::function<std::unique_ptr<INumberFilter>(int)> f)
    {
        this->registry[type] = f;
    }

    std::unique_ptr<INumberFilter> create(std::string ftype) override
    {
        std::string type = ftype;
        int tr = 0;
        if (ftype.substr(0, 2) == "gt")
        {
            type = "gt";
            size_t skip(2);
            tr = std::stoi(ftype.substr(2));
        }
        if (this->registry.find(type) != this->registry.end())
        {
            auto func = this->registry[type];
            return func(tr);
        }
        return nullptr;
    }

private:
    std::map<std::string, std::function<std::unique_ptr<INumberFilter>(int)>> registry;

    FilterFactoryRegistry() = default;
    FilterFactoryRegistry(const FilterFactoryRegistry &other) = delete;
    FilterFactoryRegistry &operator=(const FilterFactoryRegistry &other) = delete;
};

class INumberReader
{
public:
    virtual std::vector<int> parse() = 0;
};

class NumberReader : public INumberReader
{
public:
    NumberReader(std::string f) : fileName(f) {}
    std::vector<int> parse()
    {
        std::vector<int> numbers;

        std::ifstream ifs(fileName);
        if (ifs.is_open())
        {
            int num;
            while (ifs >> num)
            {
                numbers.push_back(num);
            }
        }
        return numbers;
    }

private:
    std::string fileName;
};

class NumberReaderFactory
{
public:
    static NumberReaderFactory instance()
    {
        static NumberReaderFactory factory;
        return factory;
    }

    std::unique_ptr<INumberReader> create(std::string arg)
    {
        return std::make_unique<NumberReader>(arg);
    }
};

class INUmberObserver
{
public:
    virtual void on_number(int) = 0;
    virtual void on_finish() = 0;
};

class PrintObserver : public INUmberObserver
{
public:
    void on_number(int num) override
    {
        std::cout << num << " Passed" << std::endl;
    }
    void on_finish() override {}
};

class CountObserver : public INUmberObserver
{
public:
    void on_number(int num) override
    {
        count++;
    }
    void on_finish() override
    {
        std::cout << "Total numbers passed: " << count << std::endl;
    }

private:
    int count = 0;
};

class NumberProcessor
{
public:
    NumberProcessor(std::unique_ptr<INumberReader> r, std::unique_ptr<INumberFilter> f, std::vector<INUmberObserver *> &os)
    {
        reader = std::move(r);
        filter = std::move(f);
        observers = os;
    }

    bool run()
    {
        std::vector<int> numbers = reader->parse();

        if (numbers.empty())
        {
            return false;
        }

        for (int num : numbers)
        {
            if (filter->keep(num))
            {
                for (INUmberObserver *observer : observers)
                {
                    observer->on_number(num);
                }
            }
        }
        for (INUmberObserver *observer : observers)
        {
            observer->on_finish();
        }
        return true;
    }

private:
    std::unique_ptr<INumberReader> reader;
    std::unique_ptr<INumberFilter> filter;
    std::vector<INUmberObserver *> observers;
};

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Wrong argument number!!!" << std::endl;
        return 1;
    }

    FilterFactoryRegistry &filterRegistry = FilterFactoryRegistry::instance();
    filterRegistry.register_factory("even", [](int tr)
                                    { return std::make_unique<EvenFilter>(); });
    filterRegistry.register_factory("odd", [](int tr)
                                    { return std::make_unique<OddFilter>(); });
    filterRegistry.register_factory("gt", [](int tr)
                                    { return std::make_unique<GtFilter>(tr); });

    std::unique_ptr<INumberFilter> filter = filterRegistry.create(ToLowerCase(argv[1]));

    if (!filter)
    {
        std::cerr << "Wrong filter type!!!" << std::endl;
        return 2;
    }

    std::unique_ptr<INumberReader> reader = NumberReaderFactory::instance().create(ToLowerCase(argv[2]));

    std::vector<INUmberObserver *> observers;
    PrintObserver pObserv;
    CountObserver cObserv;
    observers.push_back(&pObserv);
    observers.push_back(&cObserv);

    NumberProcessor processor(std::move(reader), std::move(filter), observers);

    if (!processor.run())
    {
        std::cerr << "Wrong file name!!!" << std::endl;
        return 3;
    }

    return 0;
}
