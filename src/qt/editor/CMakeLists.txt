#--------------------------------------------------------------------
# Inviwo Qt Editor
ivw_project(inviwo-qteditor)

#--------------------------------------------------------------------
# Add MOC files
set(MOC_FILES
    ${IVW_INCLUDE_DIR}/inviwo/qt/editor/consolewidget.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/editor/networkeditor.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/editor/inviwomainwindow.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/editor/globaleventfilter.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/editor/processorlistwidget.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/editor/helpwidget.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/editor/resourcemanagerwidget.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/editor/settingswidget.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/editor/linkdialog/linkdialog.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/editor/linkdialog/linkdialogscene.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/editor/linkdialog/linkdialogprocessorgraphicsitems.h
)

#--------------------------------------------------------------------
# Add header files
set(HEADER_FILES
    ${IVW_INCLUDE_DIR}/inviwo/qt/editor/connectiongraphicsitem.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/editor/editorgrapicsitem.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/editor/inviwoqteditordefine.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/editor/linkdialog/linkdialogcurvegraphicsitems.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/editor/linkdialog/linkdialoggraphicsitems.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/editor/linkdialog/linkdialogpropertygraphicsitems.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/editor/linkdialog/linkdialogview.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/editor/linkgraphicsitem.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/editor/networkeditorobserver.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/editor/networkeditorview.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/editor/processorgraphicsitem.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/editor/processorlinkgraphicsitem.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/editor/processorportgraphicsitem.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/editor/processorpreview.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/editor/processorprogressgraphicsitem.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/editor/processorstatusgraphicsitem.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/editor/undomanager.h
    ${MOC_FILES}
)
ivw_group("Header Files" ${HEADER_FILES})



#--------------------------------------------------------------------
# Add source files
set(SOURCE_FILES
    connectiongraphicsitem.cpp
    consolewidget.cpp
    editorgrapicsitem.cpp
    globaleventfilter.cpp
    helpwidget.cpp
    inviwomainwindow.cpp
    linkdialog/linkdialog.cpp
    linkdialog/linkdialogcurvegraphicsitems.cpp
    linkdialog/linkdialogprocessorgraphicsitems.cpp
    linkdialog/linkdialogpropertygraphicsitems.cpp
    linkdialog/linkdialogscene.cpp
    linkdialog/linkdialogview.cpp
    linkgraphicsitem.cpp
    networkeditor.cpp
    networkeditorview.cpp
    processorgraphicsitem.cpp
    processorlinkgraphicsitem.cpp
    processorlistwidget.cpp
    processorportgraphicsitem.cpp
    processorpreview.cpp
    processorprogressgraphicsitem.cpp
    processorstatusgraphicsitem.cpp
    resourcemanagerwidget.cpp
    settingswidget.cpp
    undomanager.cpp
)
ivw_group("Source Files" ${SOURCE_FILES})

#--------------------------------------------------------------------
# Create library
find_package(Qt5Core QUIET REQUIRED)
ivw_qt_wrap_cpp(MOC_FILES ${MOC_FILES})
source_group("MOC Files" FILES ${MOC_FILES})
add_library(inviwo-qteditor ${SOURCE_FILES} ${MOC_FILES} ${HEADER_FILES})

#--------------------------------------------------------------------
# Define defintions
ivw_define_standard_definitions(IVW_QTEDITOR inviwo-qteditor)
ivw_define_standard_properties(inviwo-qteditor)
ivw_define_qt_definitions()

# Add dependencies to this list
set(IVW_EDITOR_QT_DEPENDS
    Qt5Core
    Qt5Gui
    Qt5Widgets
    Qt5Help
)

foreach(qtarget ${IVW_EDITOR_QT_DEPENDS})
    ivw_add_dependencies(${qtarget})  
    ivw_qt_add_to_install(${qtarget} qt_editor)
endforeach()

foreach(qtarget Qt5Sql Qt5Network)
    ivw_qt_add_to_install(${qtarget} qt_editor)
endforeach()

ivw_add_dependencies(InviwoQtWidgets)

#--------------------------------------------------------------------
# Optimize compilation with pre-compilied headers based on inviwo-core
ivw_compile_optimize_inviwo_core()

#--------------------------------------------------------------------
# Make package (for other projects to find)
ivw_set_cpack_name(qt_editor)
ivw_make_package(InviwoQtEditor inviwo-qteditor)

#--------------------------------------------------------------------
# Generate build info

# make a clean help script
set(build_info_script_list
    "include(${IVW_ROOT_DIR}/cmake/globalutils.cmake)"
    "ivw_generate_build_info(${IVW_CMAKE_TEMPLATES}/inviwo_buildinfo_template.h"
    "    ${CMAKE_BINARY_DIR}/modules/_generated/inviwo_buildinfo.h"
    "    ${IVW_MODULE_DIR} ${IVW_EXTERNAL_MODULES})"
)
string(REPLACE ";" "\n" build_info_script "${build_info_script_list}")
file(WRITE "${IVW_CMAKE_BINARY_MODULE_DIR}/build_info.cmake" ${build_info_script})

# add a target to generate the header file a build time
add_custom_target("inviwo-buildinfo"
    COMMAND ${CMAKE_COMMAND} -P "${IVW_CMAKE_BINARY_MODULE_DIR}/build_info.cmake"
    WORKING_DIRECTORY ${OUTPUT_DIR}
    COMMENT "Generating inviwo build info"
    VERBATIM
)
add_dependencies("inviwo-qteditor" "inviwo-buildinfo")