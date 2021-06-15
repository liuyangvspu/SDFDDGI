python populate_cmake_src_deps.py
if not exist "build" mkdir build
cd build
cmake -G "MinGW Makefiles" ..
make