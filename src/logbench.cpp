/** Benchmark Poco::Logger and glog.
    Use different methods of logging with Poco::Logger:
     - use formatting or not;
     - use stored reference or call Logger::get every time;
     - use stream logging;
     - use macros or call logger method.

    @author Dmitriy T.
   */
#include "PocoBenchmark.h"
#include "GlogBenchmark.h"

#include "Poco/Logger.h"
#include "Poco/PatternFormatter.h"
#include "Poco/FormattingChannel.h"
#include "Poco/FileChannel.h"

#include "Poco/AutoPtr.h"

#include <glog/logging.h>

#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

using Poco::AutoPtr;
using Poco::FormattingChannel;
using Poco::FileChannel;
using Poco::PatternFormatter;
using Poco::Logger;
using Poco::Message;

using LogBenchmark::BenchmarkResult;
using LogBenchmark::BenchmarkResults;

int main(int argc, char** argv) {
    if (argc!=2) {
        cerr<<"run syntax:"<<endl<<argv[0]<<" C"<<endl<<"where C number of cycles for every method"<<endl;
        return -1;
    }

    string cntS(argv[1]);
    size_t cnt;
    istringstream iss(cntS);
    iss >> cnt;
    if (iss.fail() || iss.bad()) {
        cerr<<"can't convert param to size_t: "<<argv[1]<<endl;
        return -1;
    }

    cout<<"run "<<cnt<<" cycles"<<endl;
    cout<<"all measured in microseconds"<<endl;
    // == Create Poco loggers. 1 with formatting channel and 1 raw
    const string pocoFormattingLogger = "LoggerWithFormatting";
    const string pocoSimpleLogger = "SumpleLogger";
    AutoPtr<PatternFormatter> logFormatter(new PatternFormatter("%Y-%m-%d %H:%M:%S.%c [%P] %U %u:%s:%q:%t"));
    AutoPtr<FormattingChannel> formattingChannel(new FormattingChannel(logFormatter));
    AutoPtr<FileChannel> fileChannel(new FileChannel("./poco_flog.log"));
    fileChannel->setProperty("rotation","100 M");
    fileChannel->setProperty("purgeCount","1");
    fileChannel->setProperty("purgeAge","1 seconds");
    fileChannel->setProperty("rotateOnOpen","true");

    formattingChannel->setChannel(fileChannel);
    formattingChannel->open();

    AutoPtr<FileChannel> fileChannel2(new FileChannel("./poco_log.log"));
    fileChannel2->setProperty("rotation","100 M");
    fileChannel2->setProperty("purgeCount","1");
    fileChannel2->setProperty("purgeAge","1 seconds");
    fileChannel2->setProperty("rotateOnOpen","true");


    Logger::create(pocoFormattingLogger, formattingChannel, Message::PRIO_INFORMATION);
    Logger::create(pocoSimpleLogger, fileChannel2, Message::PRIO_INFORMATION);
    // == End creating Poco loggers

    // == Init GLOG
    google::InitGoogleLogging("benchglog.log");

    LogBenchmark::PocoBenchmark pocoFormattedBenchmark(Logger::get(pocoFormattingLogger),pocoFormattingLogger);
    LogBenchmark::PocoBenchmark pocoSimpleBenchmark(Logger::get(pocoSimpleLogger),pocoSimpleLogger);
    LogBenchmark::GlogBenchmark glogBenchmark;

    BenchmarkResults res;
    res = pocoSimpleBenchmark.BenchmarkAll("test message",cnt);
    cout<<"POCO NOT FORMATTED: "<<endl;
    for (BenchmarkResults::iterator it=res.begin(); it!=res.end(); ++it) {
        cout<<setw(65)<<(*it).first<<" "<<(*it).second<<endl;
    }

    res = pocoFormattedBenchmark.BenchmarkAll("test message",cnt);
    cout<<"POCO FORMATTED: "<<endl;
    for (BenchmarkResults::iterator it=res.begin(); it!=res.end(); ++it) {
        cout<<setw(65)<<(*it).first<<" "<<(*it).second<<endl;
    }

    res = glogBenchmark.BenchmarkAll("test message", cnt);
    cout<<"GLOG"<<endl;
    for (BenchmarkResults::iterator it=res.begin(); it!=res.end(); ++it) {
        cout<<setw(65)<<(*it).first<<" "<<(*it).second<<endl;
    }

    return 0;
}
