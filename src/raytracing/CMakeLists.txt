file(GLOB_RECURSE raytracing_files PROJECT_SOURCE_DIR
  "*.h"
  "*.cpp"
#  "lib/*.hpp"
#  "lib/*.cpp"
)

include_directories("${PROJECT_SOURCE_DIR}/src")

add_executable(raytracing ${raytracing_files})
target_compile_definitions(raytracing PUBLIC BUILD_PROD)