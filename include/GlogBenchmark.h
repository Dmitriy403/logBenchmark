#pragma once
#include "Benchmark.h"

#include <string>


namespace LogBenchmark {

class GlogBenchmark:public Benchmark {
    private:
        void SimpleLogString(std::string message, size_t cnt);
        void LogWithInt(std::string message, size_t cnt);
        void LogWithString(std::string message, size_t cnt);
        void LogWithFloat(std::string message, size_t cnt);


    public:
        GlogBenchmark();
        ~GlogBenchmark();

        BenchmarkResults BenchmarkAll(std::string message, size_t cnt);
};

}

