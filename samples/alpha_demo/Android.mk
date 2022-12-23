LOCAL_PATH := $(call my-dir)
#======================================================================
#
# alphaTest
#
#======================================================================
include $(CLEAR_VARS)
LOCAL_VENDOR_MODULE := true

LOCAL_CFLAGS += -Wall -Werror -Wunreachable-code

LOCAL_C_INCLUDES += \
    hardware/rockchip/librga \
    hardware/rockchip/librga/include \
    hardware/rockchip/librga/im2d_api

LOCAL_SHARED_LIBRARIES := \
    librga \
    libui

LOCAL_HEADER_LIBRARIES += \
    libgui_headers

LOCAL_SRC_FILES:= \
    src/rga_alpha_demo.cpp

LOCAL_MODULE:= \
    rga_alpha_demo

ifdef TARGET_32_BIT_SURFACEFLINGER
LOCAL_32_BIT_ONLY := true
endif

include $(BUILD_EXECUTABLE)

