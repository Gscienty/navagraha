cmake_minimum_required(VERSION 2.8.8)

project (navagraha)

set (NAVAGRAHA_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (CMAKE_COMPILER_IS_GNUCXX)

    add_compile_options(-std=c++11)
    message(STATUS "optional: -std=c++11")

    add_compile_options(-Wall)
    message(STATUS "optional: -Wall")

endif (CMAKE_COMPILER_IS_GNUCXX)

link_libraries(curl tar git2)

include_directories(${NAVAGRAHA_INCLUDE})

aux_source_directory(${PROJECT_SOURCE_DIR}/extensions NAVAGRAHA_EXTENSIONS)
aux_source_directory(${PROJECT_SOURCE_DIR}/http_client NAVAGRAHA_HTTP_CLIENT)
aux_source_directory(${PROJECT_SOURCE_DIR}/kubeent NAVAGRAHA_KUBEENT)
aux_source_directory(${PROJECT_SOURCE_DIR}/kube_api NAVAGRAHA_KUBE_API)
aux_source_directory(${PROJECT_SOURCE_DIR}/dockerent NAVAGRAHA_DOCKERENT)
aux_source_directory(${PROJECT_SOURCE_DIR}/docker_api NAVAGRAHA_DOCKER_API)
aux_source_directory(${PROJECT_SOURCE_DIR}/cli_arg NAVAGRAHA_CLI_ARG)
aux_source_directory(${PROJECT_SOURCE_DIR}/cli NAVAGRAHA_CLI)
aux_source_directory(${PROJECT_SOURCE_DIR}/git NAVAGRAHA_GIT)
aux_source_directory(${PROJECT_SOURCE_DIR}/process NAVAGRAHA_PROCESS)

add_subdirectory(${PROJECT_SOURCE_DIR}/cli)
add_subdirectory(${PROJECT_SOURCE_DIR}/jni)
