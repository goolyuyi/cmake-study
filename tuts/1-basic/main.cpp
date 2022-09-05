#include <iostream>
#include <sqlite3.h>
#include <uv.h>
#include <boost/filesystem.hpp>

int main(int argc, char *argv[]) {
    std::cout << "Hello CMake!" << std::endl;

    //test sqlite3 lib
    std::cout << sqlite3_libversion() << std::endl;

    //test libuv
    uv_loop_t *loop = uv_default_loop();
    uv_run(loop, UV_RUN_DEFAULT);
    std::cout << "Hello CMake!" << std::endl;
    uv_loop_close(loop);

    //test boost
    auto p = boost::filesystem::path{"ff"};
    std::cout << absolute(p) << std::endl;

    return 0;
}