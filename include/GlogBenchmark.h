#pragma once
#include "Benchmark.h"

#include <string>


namespace LogBenchmark {

class GlogBenchmark:public Benchmark {
    private:
        void SimpleLogString(std::string message, size_t cnt);

    public:
        GlogBenchmark();
        ~GlogBenchmark();

        BenchmarkResults BenchmarkAll(std::string message, size_t cnt);
};

}

