
# KuriePlot
add_executable(KuriePlot KuriePlot.cxx)
target_link_libraries(KuriePlot ToolBox TritiumPdf )
add_custom_command(TARGET KuriePlot
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:KuriePlot> ${PROJECT_SOURCE_DIR}/bin/KuriePlot)

# PhaseI_KryptonLineFitter
add_executable(PhaseI_KryptonLineFitter PhaseI_KryptonLineFitter.cxx)
target_link_libraries(PhaseI_KryptonLineFitter KryptonPdf PdfFactory )
add_custom_command(TARGET PhaseI_KryptonLineFitter
                    POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:PhaseI_KryptonLineFitter> ${PROJECT_SOURCE_DIR}/bin/PhaseI_KryptonLineFitter)
