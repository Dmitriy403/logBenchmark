#include "GlogBenchmark.h"

#include <glog/logging.h>
#include <utility>
#include <functional>

using namespace std;

namespace LogBenchmark {

GlogBenchmark::GlogBenchmark() {
}

GlogBenchmark::~GlogBenchmark() {}

void GlogBenchmark::SimpleLogString(std::string message, size_t cnt) {
    for (size_t i=0; i<cnt; ++i) {
        DLOG(INFO)<<message;
        LOG(INFO)<<message;
        LOG(INFO)<<message;
    }
}

BenchmarkResults GlogBenchmark::BenchmarkAll(string message, size_t cnt) {
    BenchmarkResults ret;
    ret.push_back(
            make_pair(
                "Call logger with string message",
                runBench( bind(&GlogBenchmark::SimpleLogString,*this,message,cnt) )
                )
            );

    return ret;
}

} //ns
