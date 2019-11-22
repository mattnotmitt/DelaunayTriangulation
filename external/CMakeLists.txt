include(ExternalProject)
ExternalProject_Add(catch2-src
        URL https://github.com/catchorg/Catch2/releases/download/v1.12.2/catch.hpp
        URL_HASH SHA512=d2cf8b2fe95aae061a7771a0e1b7135583595d1f36dfc8d5e4d10e101ab58f6fac9d260f77c5760906c24aa402d7433aa82b5d6a0ca6b3ad91092dc5cc2d9c22
        DOWNLOAD_DIR ${CMAKE_SOURCE_DIR}/external/catch2
        DOWNLOAD_NO_EXTRACT false
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        LOG_DOWNLOAD ON
        )

add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE catch2)
add_dependencies(Catch catch2-src)