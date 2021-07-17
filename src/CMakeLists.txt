add_executable(${PROJECT_NAME}
        main.cpp
        image.cpp
        sphere.cpp
        random.cpp
        diffuse_material.cpp
        metal_material.cpp
        glass_material.cpp
        world.cpp
        path_tracer.cpp
        shader.cpp
        quad_shader.cpp
        quad.cpp
        texture.cpp)

target_precompile_headers(${PROJECT_NAME} PRIVATE <glm/glm.hpp>)

target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_link_libraries(${PROJECT_NAME} PRIVATE glad glfw glm stb opengl32)