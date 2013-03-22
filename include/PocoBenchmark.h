#pragma once
#include "Benchmark.h"

#include <string>

namespace Poco { class Logger; }

namespace LogBenchmark {

class PocoBenchmark:public Benchmark {
    private:
        Poco::Logger& logger_;
        std::string   loggerName_;

        void MacroDebugOnly(std::string message, size_t cnt);

        void LoggerMethodLogString(std::string message, size_t cnt);
        void LogToStream(std::string message, size_t cnt);

        void MacroRef(std::string message, size_t cnt);
        void MacroRefWithIntParam(std::string message, size_t cnt);
        void MacroRefWithStringParam(std::string message, size_t cnt);
        void MacroRefWithFloatParam(std::string message, size_t cnt);
        void MacroRefErrFmt(std::string message, size_t cnt);

        void MacroGet(std::string message, size_t cnt);
        void MacroGetWithIntParam(std::string message, size_t cnt);
        void MacroGetWithStringParam(std::string message, size_t cnt);
        void MacroGetWithFloatParam(std::string message, size_t cnt);
        void MacroGetErrFmt(std::string message, size_t cnt);

    public:
        PocoBenchmark(Poco::Logger& logRef,std::string loggerName);
        ~PocoBenchmark();

        BenchmarkResults BenchmarkAll(std::string message, size_t cnt);
};

}

