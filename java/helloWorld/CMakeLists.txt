cmake_minimum_required (VERSION 3.0)

find_package(Java REQUIRED)
include(UseJava)

enable_testing()

project (helloWorld NONE)

# set(CMAKE_JAVA_COMPILE_FLAGS "-source" "1.6" "-target" "1.6")
set(CMAKE_JAVA_INCLUDE_PATH "external-packages/*")
set(CLASSDIR "sources/mypackage/*")

add_jar(${PROJECT_NAME} sources/mypackage/Main.java)
# get_target_property(_jarFile ${PROJECT_NAME} JAR_FILE)
# get_target_property(_classDir ${PROJECT_NAME} CLASSDIR)



message(STATUS "Jar file ${_jarFile}")
message(STATUS "Class compiled to ${_classDir}")

add_test(NAME TestHelloWorld COMMAND ${Java_JAVA_EXECUTABLE} -cp ${_jarFile} HelloWorld)