
find_package(BISON)
find_package(FLEX)

# Treat all Bison warnings as error and must be resolved.
set(BISON_COMPILE_FLAGS "--warnings=error")
set(FLEX_COMPILE_FLAGS "")

# Enabled debug output in debug build
if((CMAKE_BUILD_TYPE STREQUAL "Debug") OR (CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo") )
    set(BISON_COMPILE_FLAGS "${BISON_COMPILE_FLAGS} -v -t")
    set(FLEX_COMPILE_FLAGS "${FLEX_COMPILE_FLAGS} -d -T -v")
endif()

BISON_TARGET(SyntaxParser syntax.y ${CMAKE_CURRENT_SOURCE_DIR}/syntax-parser.c COMPILE_FLAGS "${BISON_COMPILE_FLAGS}")
FLEX_TARGET(LexicalScanner lexical.l ${CMAKE_CURRENT_SOURCE_DIR}/lexical-scanner.c COMPILE_FLAGS "${FLEX_COMPILE_FLAGS}" )
ADD_FLEX_BISON_DEPENDENCY(LexicalScanner SyntaxParser)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} PROJECT_SOURCE_FILES)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCE_FILES}
    ${BISON_SyntaxParser_OUTPUTS}
    ${FLEX_LexicalScanner_OUTPUTS}
)
