set(TARGET exchange)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/)

add_executable(${TARGET} main.cpp Order.cpp Exchange.cpp)

target_link_libraries(${TARGET} PRIVATE cpprest nlohmann_json::nlohmann_json)
