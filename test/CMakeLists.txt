# 添加 doctest 预处理宏
add_definitions(-D DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN)

# 添加 fmt 预处理宏
add_definitions(-D FMT_HEADER_ONLY)

add_executable(test_fmt test_fmt.cpp)
target_include_directories(test_fmt 
PUBLIC
    ${CMAKE_SOURCE_DIR}/vendor
)

add_executable(test_spdlog test_spdlog.cpp)
target_include_directories(test_spdlog 
PUBLIC
    ${CMAKE_SOURCE_DIR}/vendor
)

add_executable(test-logger test_logger.cpp)
target_link_libraries(test-logger
PUBLIC
    zel-win
)

add_executable(test-ini test_ini.cpp)
target_link_libraries(test-ini
PUBLIC
    zel-win
)

add_executable(test-xml test_xml.cpp)
target_link_libraries(test-xml
PUBLIC
    zel-win
)

add_executable(test-json test_json.cpp)
target_link_libraries(test-json
PUBLIC
    zel-win
)

add_executable(test-serialize test_serialize.cpp)
target_link_libraries(test-serialize
PUBLIC
    zel-win
)

add_executable(test-interpreter test_interpreter.cpp)
target_link_libraries(test-interpreter
PUBLIC
    zel-win
)

add_executable(test-thread test-thread/test_thread.cpp test-thread/task/write_num.hpp)
target_link_libraries(test-thread
PUBLIC
    zel-win
)



