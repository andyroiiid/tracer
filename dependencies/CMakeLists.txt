add_subdirectory(glad EXCLUDE_FROM_ALL)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw EXCLUDE_FROM_ALL)

add_subdirectory(glm EXCLUDE_FROM_ALL)

add_subdirectory(imgui EXCLUDE_FROM_ALL)

add_subdirectory(stb EXCLUDE_FROM_ALL)

add_subdirectory(taskflow EXCLUDE_FROM_ALL)