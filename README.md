logBenchmark
============

Benchmark c++ loggers. For now only [google-glog] [1] and [Poco::Logger] [2]. Benchmark only logging to file.

Use different logging methods (via printf-like macros, via stream, simple logging, formatted logging, debug logging etc.). Every minibenchmark do 3 calls - 1 debug and 2 of other levels. For every logger there _one_  minibenchmark which do 3 debug log calls. Obviously in release build messages with debug log level shouldn't be logged to file.

Build (release):
 
    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=RELEASE -G "Unix Makefiles" ..
    make


In this benchmark we use only one logger per file. For _glog_ only INFO. By default glog make for each severity level file and wrote to that file all messages with severity level >= file original severity level (i.e. in xxx.INFO we got all messages with all severity levels). But in reality there must be not many messages with severity >INFO if all works fine, so we can call it close to reality benchmark _(for those who curious what happened if glog got equal and huge amount of INFO, WARNING and ERROR log messages - logging drastically slow down, but it's not probable scenario for good application in production)_.

[1]: http://code.google.com/p/google-glog   "glog"
[2]: http://pocoproject.org/    "Poco Logger"
