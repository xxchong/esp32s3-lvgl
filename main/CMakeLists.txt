file(GLOB_RECURSE SOURCES 
    "src/*.cpp" 
    "src/*.c"
    "Gui-Guider/custom/*.c"
    "Gui-Guider/generated/*.c"

)
set(INCLUDE_DIRS
    "inc"
    "inc/apps"
    "inc/Aliot"
    "inc/Udp"
    "inc/Audio"
    "inc/AI"
    "Gui-Guider/custom"
    "Gui-Guider/generated"    # 确保这行存在
)
idf_component_register(SRCS "main.c" ${SOURCES}
                    INCLUDE_DIRS ${INCLUDE_DIRS}    
                    )