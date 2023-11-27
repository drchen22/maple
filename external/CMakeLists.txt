set(third_party_folder "external")


if(NOT TARGET imgui)
    include(imgui.cmake)
    set_target_properties(imgui PROPERTIES FOLDER ${third_party_folder}/imgui)
endif()

if(NOT TARGET glfw)
    option(GLFW_BUILD_EXAMPLES "" OFF)
    option(GLFW_BUILD_TESTS "" OFF)
    option(GLFW_BUILD_DOCS "" OFF)
    option(GLFW_INSTALL "" OFF)
    add_subdirectory(glfw)
    set_target_properties(glfw PROPERTIES FOLDER ${third_party_folder}/glfw)
    set_target_properties(update_mappings PROPERTIES FOLDER ${third_party_folder}/glfw)
endif()

if(NOT TARGET glm)
    option(BUILD_TESTING "" OFF)
    add_subdirectory(glm)
endif()

if(NOT TARGET glad)
    add_subdirectory(glad)
    set_target_properties(glad PROPERTIES FOLDER ${third_party_folder}/glad)
endif()