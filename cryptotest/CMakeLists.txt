cmake_minimum_required(VERSION 3.10)
include(GNUInstallDirs)

set(APP_NAME "cryptotest")

project(${APP_NAME})
project(${PROJECT_NAME} VERSION ${SVERSION} DESCRIPTION "libMantids crypto helper library testing")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

file(GLOB_RECURSE EDV_INCLUDE_FILES "src/*.h*")
file(GLOB_RECURSE EDV_SOURCE_FILES "src/*.c*")
file(GLOB_RECURSE EDV_INCLUDE_FILES2 "src/*/*.h*")
file(GLOB_RECURSE EDV_SOURCE_FILES2 "src/*/*.c*")

configure_file(src/config.h.in ${${APP_NAME}_SOURCE_DIR}/src/config.h)

add_executable( ${APP_NAME} ${EDV_INCLUDE_FILES} ${EDV_SOURCE_FILES} ${EDV_INCLUDE_FILES2} ${EDV_SOURCE_FILES2} )

install( TARGETS ${APP_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} )

if (EXTRAPREFIX)
    target_include_directories(${APP_NAME} PUBLIC ${EXTRAPREFIX}/include)
    target_link_libraries(${APP_NAME} "-L${EXTRAPREFIX}/lib")
    target_link_libraries(${APP_NAME} "-L${EXTRAPREFIX}/lib64")
endif()


if (CMAKE_INSTALL_PREFIX)
    target_include_directories(${APP_NAME} PUBLIC ${CMAKE_INSTALL_PREFIX}/include)
    target_include_directories(${APP_NAME} PUBLIC ${CMAKE_INSTALL_PREFIX}/usr/include)
    target_link_libraries(${APP_NAME} "-L${CMAKE_INSTALL_PREFIX}/lib")
    target_link_libraries(${APP_NAME} "-L${CMAKE_INSTALL_PREFIX}/lib64")
endif()

target_link_libraries(${APP_NAME} "-lmdz_thr_mutex")
target_link_libraries(${APP_NAME} "-lmdz_thr_safecontainers")
target_link_libraries(${APP_NAME} "-lmdz_thr_threads")
target_link_libraries(${APP_NAME} "-lmdz_prg_service")
target_link_libraries(${APP_NAME} "-lmdz_prg_logs")
target_link_libraries(${APP_NAME} "-lmdz_mem_vars")
target_link_libraries(${APP_NAME} "-lmdz_hlp_functions")

#target_link_libraries(${APP_NAME} "-lsqlite3")


option(SSLRHEL7 "OpenSSL 1.1 For Red Hat 7.x provided by EPEL" OFF)
find_package(PkgConfig REQUIRED)
if (SSLRHEL7)
    pkg_check_modules(OPENSSL REQUIRED libssl11)
else()
    pkg_check_modules(OPENSSL REQUIRED libssl)
endif()
target_include_directories(${APP_NAME} PUBLIC ${OPENSSL_INCLUDE_DIRS})
target_compile_options(${APP_NAME} PUBLIC ${OPENSSL_CFLAGS_OTHER})
target_link_libraries(${APP_NAME} ${OPENSSL_STATIC_LDFLAGS})

target_link_libraries(${APP_NAME} "-lpthread")


if (WIN32)
    target_link_libraries(${APP_NAME} "-lboost_regex-mt")
else()
    target_link_libraries(${APP_NAME} "-lboost_regex")
endif()



find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})
target_include_directories(${APP_NAME} PUBLIC ${JSONCPP_INCLUDE_DIRS})
target_link_libraries(${APP_NAME} ${JSONCPP_LIBRARIES})
