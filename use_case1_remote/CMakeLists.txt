
#project(use_case1_remote)


file(GLOB_RECURSE SRCS *.cpp)






add_executable(use_case1_remote use_case1_remote.cpp)


target_link_libraries(use_case1_remote  oc::tests_cryptoTools)
target_link_libraries(use_case1_remote  com-psi)
target_link_libraries(use_case1_remote  aby3-ML)
target_link_libraries(use_case1_remote  com-psi_Tests)
target_link_libraries(use_case1_remote  aby3_Tests)








