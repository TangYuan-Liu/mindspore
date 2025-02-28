set(NORMAL_CMAKE_C_COMPILER ${CMAKE_C_COMPILER})
set(NORMAL_CMAKE_CXX_COMPILER ${CMAKE_CXX_COMPILER})
if(DEFINED ENV{ASCEND_CUSTOM_PATH})
    set(TOOLCHAIN_PATH $ENV{ASCEND_CUSTOM_PATH}/toolkit/toolchain)
else()
    set(TOOLCHAIN_PATH /usr/local/Ascend/toolkit/toolchain)
endif()
set(CMAKE_C_COMPILER ${TOOLCHAIN_PATH}/hcc/bin/aarch64-target-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH}/hcc/bin/aarch64-target-linux-gnu-g++)

if(${CMAKE_HOST_SYSTEM_PROCESSOR} MATCHES "aarch64" AND EXISTS ${CMAKE_C_COMPILER} AND EXISTS ${CMAKE_CXX_COMPILER})
    set(AICPU_PROTO_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/aicpu_op_proto/aicpu_tensor.proto
    )

    ms_protobuf_generate(PROTO_SRCS PROTO_HDRS ${AICPU_PROTO_SRC})

    set(AICPU_SRC
        ${PROTO_SRCS}
        ${CMAKE_CURRENT_SOURCE_DIR}/common/kernel_base.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/common/kernel_log.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/aicpu_sharder/aicpu_async_event.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/aicpu_sharder/aicpu_context.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/aicpu_sharder/aicpu_pulse.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/aicpu_sharder/aicpu_sharder.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/random_choice_with_mask_kernels.cc
    )

    add_library(aicpu_kernels SHARED
        ${AICPU_SRC}
    )

    target_compile_options(aicpu_kernels PRIVATE
        -march=armv8-a
        -O2
        -fvisibility-inlines-hidden
        -fvisibility=hidden
        -fno-strict-aliasing
        -fno-common
    )

    target_link_libraries(aicpu_kernels PRIVATE
        -ldl
        -shared
        PUBLIC
        ${SECUREC_LIBRARY}
        -Wl,--whole-archive
        -Wl,--no-whole-archive
        -Wl,-Bsymbolic
        -rdynamic
        mindspore::protobuf
        -pthread
    )

    set(INSTALL_LIBRARY_DIR lib)
    install(TARGETS aicpu_kernels OPTIONAL
        EXPORT aicpu_kernels-targets
        LIBRARY DESTINATION ${INSTALL_LIBRARY_DIR}
    )

endif()

set(CMAKE_C_COMPILER ${NORMAL_CMAKE_C_COMPILER})
set(CMAKE_CXX_COMPILER ${NORMAL_CMAKE_CXX_COMPILER})
