#pragma once
#include <string>
#include <vector>
#include <functional>
#include <chrono>
#include <ratio>

namespace LogBenchmark {

typedef std::pair<std::string, long> BenchmarkResult;
typedef std::vector<BenchmarkResult> BenchmarkResults;

class Benchmark {
    protected:
        template<typename Func>
        long runBench(Func method);
    public:
        virtual ~Benchmark()=0;

        virtual BenchmarkResults BenchmarkAll(std::string message, size_t cnt)=0;

};

template<typename Func>
long Benchmark::runBench(Func method) {
    std::chrono::high_resolution_clock::time_point tpStart,tpEnd;

    tpStart = std::chrono::high_resolution_clock::now();
    method();
    tpEnd = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::duration<long, std::micro> >(tpEnd-tpStart).count();
}

} //ns
