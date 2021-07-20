add_executable(${PROJECT_NAME}
        main.cpp
        image.cpp
        random.cpp

        hittables/sphere.cpp
        hittables/rect.cpp
        hittables/box.cpp

        materials/diffuse_material.cpp
        materials/metal_material.cpp
        materials/glass_material.cpp
        materials/light_material.cpp

        tracing/world.cpp
        tracing/path_tracer.cpp

        realtime/shader.cpp
        realtime/quad_shader.cpp
        realtime/quad.cpp
        realtime/texture.cpp
        realtime/interactive_input.cpp
        realtime/interactive_camera.cpp
        realtime/interactive_renderer.cpp
        realtime/imgui_funcs.cpp)

target_precompile_headers(${PROJECT_NAME} PRIVATE <glm/glm.hpp>)

target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_link_libraries(${PROJECT_NAME} PRIVATE glad glfw glm imgui stb Taskflow)