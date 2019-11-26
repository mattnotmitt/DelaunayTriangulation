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

ExternalProject_Add(eigen3-src
        URL http://bitbucket.org/eigen/eigen/get/3.3.7.tar.gz
        URL_HASH SHA512=34cf600914cce719d61511577ef9cd26fbdcb7a6fad1d0ab8396f98b887fac6a5577d3967e84a8f56225cc50de38f3b91f34f447d14312028383e32b34ea1972
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/eigen3
        LOG_DOWNLOAD ON
        )