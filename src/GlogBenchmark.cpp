#include "GlogBenchmark.h"

#include <glog/logging.h>
#include <utility>
#include <functional>

using namespace std;

namespace LogBenchmark {

GlogBenchmark::GlogBenchmark() {
}

GlogBenchmark::~GlogBenchmark() {}

void GlogBenchmark::LogDebugOnlyString(std::string message, size_t cnt) {
    for (size_t i=0; i<cnt; ++i) {
        DLOG(INFO)<<message;
        DLOG(INFO)<<message;
        DLOG(INFO)<<message;
    }
}

void GlogBenchmark::SimpleLogString(std::string message, size_t cnt) {
    for (size_t i=0; i<cnt; ++i) {
        DLOG(INFO)<<message;
        LOG(INFO)<<message;
        LOG(INFO)<<message;
    }
}

void GlogBenchmark::LogWithInt(std::string message, size_t cnt) {
    int param;
    param = 1;
    for (size_t i=0; i<cnt; ++i) {
        DLOG(INFO)<<message<<param;
        LOG(INFO)<<message<<param;
        LOG(INFO)<<message<<param;
    }

}

void GlogBenchmark::LogWithString(std::string message, size_t cnt) {
    string param;
    param = "a";
    for (size_t i=0; i<cnt; ++i) {
        DLOG(INFO)<<message<<param;
        LOG(INFO)<<message<<param;
        LOG(INFO)<<message<<param;
    }
}

void GlogBenchmark::LogWithFloat(std::string message, size_t cnt) {
    float param;
    param = 1.23f;
    for (size_t i=0; i<cnt; ++i) {
        DLOG(INFO)<<message<<param;
        LOG(INFO)<<message<<param;
        LOG(INFO)<<message<<param;
    }
}

BenchmarkResults GlogBenchmark::BenchmarkAll(string message, size_t cnt) {
    BenchmarkResults ret;

    ret.push_back(
            make_pair(
                "Call logger with debug only level with string message",
                runBench( bind(&GlogBenchmark::LogDebugOnlyString,this,message,cnt) )
                )
            );

    ret.push_back(
            make_pair(
                "Call logger with string message",
                runBench( bind(&GlogBenchmark::SimpleLogString,this,message,cnt) )
                )
            );
    ret.push_back(
            make_pair(
                "Call logger with string message with 1 int param",
                runBench( bind(&GlogBenchmark::LogWithInt,this,message,cnt) )
                )
            );
    ret.push_back(
            make_pair(
                "Call logger with string message with 1 string param",
                runBench( bind(&GlogBenchmark::LogWithString,this,message,cnt) )
                )
            );
    ret.push_back(
            make_pair(
                "Call logger with string message with 1 float param",
                runBench( bind(&GlogBenchmark::LogWithFloat,this,message,cnt) )
                )
            );

    return ret;
}

} //ns
