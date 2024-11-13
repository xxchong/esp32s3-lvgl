file(GLOB_RECURSE SOURCES 
    "src/*.cpp" 
    "src/*.c"
)
set(INCLUDE_DIRS
    "inc"
    "inc/apps"
    "inc/Aliot"
    "inc/Udp"
    "inc/Audio"
)
idf_component_register(SRCS "main.c" ${SOURCES}
                    INCLUDE_DIRS ${INCLUDE_DIRS}    
                    )