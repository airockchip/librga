SET(TOOLCHAIN_HOME "/home/yqw/workspace/linux/common/prebuilts/gcc/linux-x86/arm/gcc-arm-none-eabi-10-2020-q4-major-x86_64-linux")
SET(TOOLCHAIN_NAME "arm-none-eabi")

SET(RTT_DEVICE_FLAGS " -mcpu=cortex-a7 -mfloat-abi=hard -mfpu=vfpv4 -marm -ffast-math")

# this is required
SET(CMAKE_SYSTEM_NAME Generic)


# specify the cross compiler
SET(CMAKE_C_COMPILER ${TOOLCHAIN_HOME}/bin/${TOOLCHAIN_NAME}-gcc)
SET(CMAKE_CXX_COMPILER ${TOOLCHAIN_HOME}/bin/${TOOLCHAIN_NAME}-g++)
set(CMAKE_LINKER ${TOOLCHAIN_HOME}/bin/${TOOLCHAIN_NAME}-ld)
set(CMAKE_AR ${TOOLCHAIN_HOME}/bin/${TOOLCHAIN_NAME}-ar)
set(CMAKE_RANLIB ${TOOLCHAIN_HOME}/bin/${TOOLCHAIN_NAME}-ranlib)
set(CMAKE_STRIP ${TOOLCHAIN_HOME}/bin/${TOOLCHAIN_NAME}-strip)

add_compile_options(-mcpu=cortex-a7 -mfloat-abi=hard -mfpu=vfpv4 -marm -ffast-math)
set(DEVICE_FLAGS "-mcpu=cortex-a7 -mfloat-abi=hard -mfpu=vfpv4 -marm -ffast-math")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -Wall -g -Wno-stringop-truncation")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g -Wno-stringop-truncation")

set(ARM_LINKER_FLAGS "${DEVICE_FLAGS} -lm -lgcc -lc -nostartfiles -Wl,--gc-sections,-Map=rtthread.map,-cref,-u,system_vectors")
set(CMAKE_SHARED_LINKER_FLAGS "${ARM_LINKER_FLAGS} ${CMAKE_SHARED_LINKER_FLAGS}")
set(CMAKE_MODULE_LINKER_FLAGS "${ARM_LINKER_FLAGS} ${CMAKE_MODULE_LINKER_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS    "${ARM_LINKER_FLAGS} ${CMAKE_EXE_LINKER_FLAGS}")

# where is the target environment
SET(CMAKE_FIND_ROOT_PATH  ${TOOLCHAIN_HOME})

# search for programs in the build host directories (not necessary)
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
