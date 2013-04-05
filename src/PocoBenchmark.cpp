#include "PocoBenchmark.h"

#include "Poco/Logger.h"
#include "Poco/LogStream.h"

#include <utility>
#include <functional>

using namespace std;
using Poco::Logger;
using Poco::LogStream;

namespace LogBenchmark {

PocoBenchmark::PocoBenchmark(Poco::Logger& logRef,std::string loggerName):logger_(logRef),loggerName_(loggerName) {
}

PocoBenchmark::~PocoBenchmark() {}

void PocoBenchmark::MacroDebugOnly(std::string message, size_t cnt) {
    for (size_t i=0; i<cnt; ++i) {
        poco_debug(logger_,message);
        poco_debug(logger_,message);
        poco_debug(logger_,message);
    }
}

void PocoBenchmark::LoggerMethodLogString(std::string message, size_t cnt) {
    for (size_t i=0; i<cnt; ++i) {
        logger_.debug(message);
        logger_.information(message);
        logger_.error(message);
    }
}

void PocoBenchmark::LogToStream(std::string message, size_t cnt) {
    LogStream lstr(Logger::get(loggerName_));
    for (size_t i=0; i<cnt; ++i) {
        lstr.debug()<<message<<std::endl;
        lstr.information()<<message<<std::endl;
        lstr.error()<<message<<std::endl;
    }
}

void PocoBenchmark::MacroRef(std::string message, size_t cnt) {
    for (size_t i=0; i<cnt; ++i) {
        poco_debug(logger_,message);
        poco_information(logger_,message);
        poco_error(logger_,message);
    }
}

void PocoBenchmark::MacroRefWithIntParam(std::string message, size_t cnt) {
    string pattern = message+" %d";
    for (size_t i=0; i<cnt; ++i) {
        poco_debug_f1(logger_, pattern, 1);
        poco_information_f1(logger_, pattern, 1);
        poco_error_f1(logger_, pattern, 1);
    }
}

void PocoBenchmark::MacroRefWithStringParam(std::string message, size_t cnt) {
    string param;
    param = "a";
    string pattern = message+" %s";
    for (size_t i=0; i<cnt; ++i) {
        poco_debug_f1(logger_, pattern, param);
        poco_information_f1(logger_, pattern, param);
        poco_error_f1(logger_, pattern, param);
    }
}

void PocoBenchmark::MacroRefWithFloatParam(std::string message, size_t cnt) {
    string pattern = message+" %f";
    for (size_t i=0; i<cnt; ++i) {
        poco_debug_f1(logger_, pattern, 1.23);
        poco_information_f1(logger_, pattern, 1.23);
        poco_error_f1(logger_, pattern, 1.23);
    }
}

void PocoBenchmark::MacroRefErrFmt(std::string message, size_t cnt) {
    string pattern = message+" %s";
    for (size_t i=0; i<cnt; ++i) {
        poco_debug_f1(logger_, pattern, 1.23);
        poco_information_f1(logger_, pattern, 1.23);
        poco_error_f1(logger_, pattern, 1.23);
    }
}

void PocoBenchmark::MacroGet(std::string message, size_t cnt) {
    for (size_t i=0; i<cnt; ++i) {
        poco_debug(Logger::get(loggerName_),message);
        poco_information(Logger::get(loggerName_),message);
        poco_error(Logger::get(loggerName_),message);
    }
}

void PocoBenchmark::MacroGetWithIntParam(std::string message, size_t cnt) {
    string pattern = message+" %d";
    for (size_t i=0; i<cnt; ++i) {
        poco_debug_f1(Logger::get(loggerName_), pattern, 1);
        poco_information_f1(Logger::get(loggerName_), pattern, 1);
        poco_error_f1(Logger::get(loggerName_), pattern, 1);
    }
}

void PocoBenchmark::MacroGetWithStringParam(std::string message, size_t cnt) {
    string param;
    param = "a";
    string pattern = message+" %s";
    for (size_t i=0; i<cnt; ++i) {
        poco_debug_f1(Logger::get(loggerName_), pattern, param);
        poco_information_f1(Logger::get(loggerName_), pattern, param);
        poco_error_f1(Logger::get(loggerName_), pattern, param);
    }
}

void PocoBenchmark::MacroGetWithFloatParam(std::string message, size_t cnt) {
    string pattern = message+" %f";
    for (size_t i=0; i<cnt; ++i) {
        poco_debug_f1(Logger::get(loggerName_), pattern, 1.23);
        poco_information_f1(Logger::get(loggerName_), pattern, 1.23);
        poco_error_f1(Logger::get(loggerName_), pattern, 1.23);
    }
}

void PocoBenchmark::MacroGetErrFmt(std::string message, size_t cnt) {
    string pattern = message+" %s";
    for (size_t i=0; i<cnt; ++i) {
        poco_debug_f1(Logger::get(loggerName_), pattern, 1.23);
        poco_information_f1(Logger::get(loggerName_), pattern, 1.23);
        poco_error_f1(Logger::get(loggerName_), pattern, 1.23);
    }
}

BenchmarkResults PocoBenchmark::BenchmarkAll(string message, size_t cnt) {
    BenchmarkResults ret;

    ret.push_back(
            make_pair(
                "Call only macro with debug level with string message",
                runBench( bind(&PocoBenchmark::MacroDebugOnly, this, message, cnt) )
                )
            );

    ret.push_back(
            make_pair(
                "Call logger method with string message",
                runBench( bind(&PocoBenchmark::LoggerMethodLogString, this, message, cnt) )
                )
            );

    ret.push_back(
            make_pair(
                "Log to stream with string message",
                runBench( bind(&PocoBenchmark::LogToStream, this, message, cnt) )
                )
            );

    ret.push_back(
            make_pair(
                "Macro poco_XXX with reference to logger",
                runBench( bind(&PocoBenchmark::MacroRef, this, message, cnt) )
                )
            );
    ret.push_back(
            make_pair(
                "Macro poco_XXX with reference to logger and 1 int param",
                runBench( bind(&PocoBenchmark::MacroRefWithIntParam, this, message, cnt) )
                )
            );
    ret.push_back(
            make_pair(
                "Macro poco_XXX with reference to logger and 1 string param",
                runBench( bind(&PocoBenchmark::MacroRefWithStringParam, this, message, cnt) )
                )
            );
    ret.push_back(
            make_pair(
                "Macro poco_XXX with reference to logger and 1 float param",
                runBench( bind(&PocoBenchmark::MacroRefWithFloatParam, this, message, cnt) )
                )
            );
    ret.push_back(
            make_pair(
                "Macro poco_XXX with reference to logger and 1 [ERRFMT] param",
                runBench( bind(&PocoBenchmark::MacroRefErrFmt, this, message, cnt) )
                )
            );


    ret.push_back(
            make_pair(
                "Macro poco_XXX with Logger::get call",
                runBench( bind(&PocoBenchmark::MacroGet, this, message, cnt) )
                )
            );
    ret.push_back(
            make_pair(
                "Macro poco_XXX with Logger::get call and 1 int param",
                runBench( bind(&PocoBenchmark::MacroGetWithIntParam, this, message, cnt) )
                )
            );
    ret.push_back(
            make_pair(
                "Macro poco_XXX with Logger::get call and 1 string param",
                runBench( bind(&PocoBenchmark::MacroGetWithStringParam, this, message, cnt) )
                )
            );
    ret.push_back(
            make_pair(
                "Macro poco_XXX with Logger::get call and 1 float param",
                runBench( bind(&PocoBenchmark::MacroGetWithFloatParam, this, message, cnt) )
                )
            );
    ret.push_back(
            make_pair(
                "Macro poco_XXX with Logger::get call and 1 [ERRFMT] param",
                runBench( bind(&PocoBenchmark::MacroGetErrFmt, this, message, cnt) )
                )
            );

    return ret;
}

} //ns
