#include <Engine/src/Utils/Logger.h>

int main(){

    LOG("LOG {} w/ {}.", "logger", 1234);
    DEBUG("DEBUG {} w/ {}.", "logger", 1234);
    WARN("WARN {} w/ {}.", "logger", 1234);
    ERROR("ERROR {} w/ {}.", "logger", 1234);
    FATAL("FATAL {} w/ {}.", "logger", 1234);

}