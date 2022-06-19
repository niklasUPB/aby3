
#project(hello)


file(GLOB_RECURSE SRCS *.cpp)






add_executable(hello hello.cpp)


target_link_libraries(hello oc::tests_cryptoTools)
target_link_libraries(hello com-psi)
target_link_libraries(hello aby3-ML)
target_link_libraries(hello com-psi_Tests)
target_link_libraries(hello aby3_Tests)








