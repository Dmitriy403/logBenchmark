logBenchmark
============

Benchmark c++ loggers. Now only [google-glog] [1] and [Poco::Logger] [2]. Benchmark only logging to file.

Build with custom poco install (for ex in /home/poco):
cd build
cmake -DCMAKE_BUILD_TYPE=RELEASE -DPOCO_PATH="/home/poco" -DPOCO_LIB_PATH="/home/poco/lib/Linux/i686" -G "Unix Makefiles" CMakeLists.txt

[1]: http://code.google.com/p/google-glog   "glog"
[2]: http://pocoproject.org/    "Poco Logger"
