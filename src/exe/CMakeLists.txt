
# KuriePlot
add_executable(KuriePlot KuriePlot.cxx)
target_link_libraries(KuriePlot ToolBox TritiumRooFit )
add_custom_command(TARGET KuriePlot
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:KuriePlot> ${PROJECT_SOURCE_DIR}/bin/KuriePlot)
