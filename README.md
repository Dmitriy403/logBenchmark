logBenchmark
============

Benchmark c++ loggers. Now only [google-glog] [1] and [Poco::Logger] [2]. Benchmark only logging to file.

You should have not very old version of Poco (we need poco_warning_f1 and other poco_XXX_fX macroses). If u haven't - you can build it from sources in separate directory.

Build:
 
    cd build
    cmake -DCMAKE_BUILD_TYPE=RELEASE -G "Unix Makefiles" CMakeLists.txt


Build with custom poco root directory (for example - /home/poco):

    cd build
    cmake -DCMAKE_BUILD_TYPE=RELEASE -DPOCO_ROOT="/home/poco" -G "Unix Makefiles" CMakeLists.txt

In this benchmark we use only one logger per file. For _glog_ only INFO. By default glog make for each severity level file and wrote to that file all messages with severity level >= file original severity level (i.e. in xxx.INFO we got all messages with all severity levels). But in reality there must be not many messages with severity >INFO if all works fine, so we can call it close to reality benchmark _(for those who curious what happened if glog got equal and huge amount of INFO, WARNING and ERROR log messages - logging drastically slow down, but it's not probable scenario for good application in production)_.

[1]: http://code.google.com/p/google-glog   "glog"
[2]: http://pocoproject.org/    "Poco Logger"
