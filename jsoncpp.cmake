include(ExternalProject)

ExternalProject_Add(jsoncpp
   GIT_REPOSITORY     https://github.com/open-source-parsers/jsoncpp
   GIT_TAG            b063cf4
   CONFIGURE_COMMAND  true
   BUILD_COMMAND      true
   INSTALL_COMMAND    true
)

ExternalProject_Get_Property(jsoncpp source_dir)

set (JSONCPP_SRC_FILE "${source_dir}/dist/jsoncpp.cpp")

add_custom_command(OUTPUT ${JSONCPP_SRC_FILE}
                   COMMAND python amalgamate.py
                   WORKING_DIRECTORY ${source_dir}
                   DEPENDS jsoncpp
)

set (JSONCPP_INC_DIR "${source_dir}/dist")

include_directories(${JSONCPP_INC_DIR})
