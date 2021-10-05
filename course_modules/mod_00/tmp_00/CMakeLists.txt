

add_executable("${PROJECT_NAME}_00_tmp")
target_compile_features("${PROJECT_NAME}_00_tmp" PUBLIC cxx_std_20)
target_sources("${PROJECT_NAME}_00_tmp" PRIVATE "main.cpp" "gnuplot.hpp")

#find_package(ROOT COMPONENTS RooStats)
#message(ROOT_COMPONENTS ${ROOT_COMPONENTS})
#find_package(libpython REQUIRED)
#find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
#target_link_libraries("${PROJECT_NAME}_00_tmp" private libpython)
#target_link_libraries("${PROJECT_NAME}_00_tmp" private python)
#message(PYTHON3_LIBRARIES ${PYTHON_LIBRARIES})
#target_link_libraries("${PROJECT_NAME}_00_tmp" INTERFACE
#  Python3::Python
#  Python3::Module
#)

find_package(matplotlib_cpp REQUIRED)
message(matplotlib_cpp_INCLUDE_DIRS= ${matplotlib_cpp_INCLUDE_DIRS} )
message(matplotlib_cpp_LIBRARIES= ${matplotlib_cpp_LIBRARIES} )
message(matplotlib_cpp_TARGETS= ${matplotlib_cpp_TARGETS} )
message(matplotlib_cpp_VERSION= ${matplotlib_cpp_VERSION} )
target_link_libraries("${PROJECT_NAME}_00_tmp" PRIVATE matplotlib_cpp::matplotlib_cpp)
