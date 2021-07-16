add_executable(${PROJECT_NAME} main.cpp image.cpp sphere.cpp random.cpp diffuse_material.cpp metal_material.cpp glass_material.cpp world.cpp world.h)

target_precompile_headers(${PROJECT_NAME} PRIVATE <glm/glm.hpp>)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_link_libraries(${PROJECT_NAME} PRIVATE glm stb)