project(MoUtils LANGUAGES CXX)


set(IncludePaths

)

file(GLOB UtilsSourceFiles
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/ExportHeader/utils.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/*/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*/*/*.cpp
)

message(STATUS "Utils Source Files: ${UtilsSourceFiles}")

add_library(${PROJECT_NAME} STATIC ${UtilsSourceFiles})
add_library(Mortis::Utils ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/ExportHeader

	${CMAKE_CURRENT_SOURCE_DIR}/Base/APi
	${CMAKE_CURRENT_SOURCE_DIR}/Base/Concept
	${CMAKE_CURRENT_SOURCE_DIR}/Base/Template
	${CMAKE_CURRENT_SOURCE_DIR}/Base/Type

	${CMAKE_CURRENT_SOURCE_DIR}/Containers/BoundedQueue
	${CMAKE_CURRENT_SOURCE_DIR}/Containers/PipeExecutor
	${CMAKE_CURRENT_SOURCE_DIR}/Containers/ScopeWrapper
	${CMAKE_CURRENT_SOURCE_DIR}/Containers/ThreadPool
)

target_precompile_headers(${PROJECT_NAME} 
	PRIVATE 
	${CMAKE_CURRENT_SOURCE_DIR}/ExportHeader/utils.hpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC
	nlohmann_json
	spdlog::spdlog_header_only
	magic_enum
	concurrentqueue
	sigslot
)