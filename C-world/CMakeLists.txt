set(PROJECT_NAME C-world)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "C-world.h"
    "Defs.h"
    "pch.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Header_Files__Engine
    "AssetManager.h"
    "GameEngine.h"
    "InputManager.h"
    "LTexture.h"
)
source_group("Header Files\\Engine" FILES ${Header_Files__Engine})

set(Header_Files__Entity
    "Actor.h"
    "Entity.h"
)
source_group("Header Files\\Entity" FILES ${Header_Files__Entity})

set(Header_Files__External
    "external/FastNoise-master/FastNoise.h"
)
source_group("Header Files\\External" FILES ${Header_Files__External})

set(Header_Files__GameStates
    "GameState.h"
    "IntroState.h"
    "PlayState.h"
)
source_group("Header Files\\GameStates" FILES ${Header_Files__GameStates})

set(Header_Files__Map
    "Camera.h"
    "Map.h"
    "RegularMap.h"
    "Tile.h"
)
source_group("Header Files\\Map" FILES ${Header_Files__Map})

set(Header_Files__UI
    "UI.h"
)
source_group("Header Files\\UI" FILES ${Header_Files__UI})

set(Header_Files__UI__Elements
    "UI_BasicBox.h"
    "UI_Button.h"
    "UI_MoveHandle.h"
    "UI_Text.h"
    "UIElement.h"
)
source_group("Header Files\\UI\\Elements" FILES ${Header_Files__UI__Elements})

set(Source_Files
    "C-world.cpp"
    "pch.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__Engine
    "AssetManager.cpp"
    "GameEngine.cpp"
    "InputManager.cpp"
    "LTexture.cpp"
)
source_group("Source Files\\Engine" FILES ${Source_Files__Engine})

set(Source_Files__Entity
    "Actor.cpp"
    "Entity.cpp"
)
source_group("Source Files\\Entity" FILES ${Source_Files__Entity})

set(Source_Files__External
    "external/FastNoise-master/FastNoise.cpp"
    "external/pugixml-1.10/src/pugixml.cpp"
)
source_group("Source Files\\External" FILES ${Source_Files__External})

set(Source_Files__GameStates
    "IntroState.cpp"
    "PlayState.cpp"
)
source_group("Source Files\\GameStates" FILES ${Source_Files__GameStates})

set(Source_Files__Map
    "Camera.cpp"
    "RegularMap.cpp"
    "Tile.cpp"
)
source_group("Source Files\\Map" FILES ${Source_Files__Map})

set(Source_Files__UI
    "UI.cpp"
)
source_group("Source Files\\UI" FILES ${Source_Files__UI})

set(Source_Files__UI__Elements
    "UI_BasicBox.cpp"
    "UI_Button.cpp"
    "UI_MoveHandle.cpp"
    "UI_Text.cpp"
    "UIElement.cpp"
)
source_group("Source Files\\UI\\Elements" FILES ${Source_Files__UI__Elements})

set(ALL_FILES
    ${Header_Files}
    ${Header_Files__Engine}
    ${Header_Files__Entity}
    ${Header_Files__External}
    ${Header_Files__GameStates}
    ${Header_Files__Map}
    ${Header_Files__UI}
    ${Header_Files__UI__Elements}
    ${Source_Files}
    ${Source_Files__Engine}
    ${Source_Files__Entity}
    ${Source_Files__External}
    ${Source_Files__GameStates}
    ${Source_Files__Map}
    ${Source_Files__UI}
    ${Source_Files__UI__Elements}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

add_precompiled_header(${PROJECT_NAME} "pch.h" "pch.cpp")

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE Cworld)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
endif()
################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "_CONSOLE;"
        "UNICODE;"
        "_UNICODE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "WIN32;"
        "_CONSOLE;"
        "UNICODE;"
        "_UNICODE"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                /Gy
            >
            /permissive-;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                /Gy
            >
            /permissive-;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /INCREMENTAL
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            /DEBUG;
            /SUBSYSTEM:CONSOLE
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /INCREMENTAL
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            /DEBUG;
            /SUBSYSTEM:CONSOLE
        )
    endif()
endif()

################################################################################
# Dependencies
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$<$<CONFIG:Debug>:"
            "SDL2_gfx"
        ">"
        "SDL2;"
        "SDL2main;"
        "SDL2_image;"
        "SDL2_ttf"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "SDL2;"
        "SDL2main;"
        "SDL2_image;"
        "SDL2_ttf"
    )
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

