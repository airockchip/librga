/*
 * Copyright (C) 2022  Rockchip Electronics Co., Ltd.
 * Authors:
 *     YuQiaowei <cerf.yu@rock-chips.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_NDEBUG 0
#undef LOG_TAG
#define LOG_TAG "rga_copy_drm_fourcc_demo"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <linux/stddef.h>

#include "RgaUtils.h"
#include "im2d.hpp"
#include "utils.h"

#include "drm_fourcc.h"

#define LOCAL_FILE_PATH "/data"

int main() {
    int ret = 0;
    uint32_t src_width, src_height, src_format;
    uint32_t dst_width, dst_height, dst_format;
    uint64_t src_modifier, dst_modifier;
    char *src_buf, *dst_buf;
    int src_buf_size, dst_buf_size;

    rga_buffer_t src_img, dst_img;
    rga_buffer_handle_t src_handle, dst_handle;

    memset(&src_img, 0, sizeof(src_img));
    memset(&dst_img, 0, sizeof(dst_img));

    src_width = 1280;
    src_height = 720;
    src_format = DRM_FORMAT_ABGR8888;
    src_modifier = 0;

    dst_width = 1280;
    dst_height = 720;
    dst_format = DRM_FORMAT_ABGR8888;
    dst_modifier = 0;
    // dst_modifier = DRM_FORMAT_MOD_ARM_AFBC(AFBC_FORMAT_MOD_BLOCK_SIZE_32x8 | AFBC_FORMAT_MOD_SPLIT);

    src_buf_size = src_width * src_height * 4;
    dst_buf_size = dst_width * dst_height * 4;
    dst_buf_size = dst_buf_size * 1.5;

    src_buf = (char *)malloc(src_buf_size);
    dst_buf = (char *)malloc(dst_buf_size);

    /* fill image data */
    memset(src_buf, 0xff, src_buf_size);
    memset(dst_buf, 0x80, dst_buf_size);

    src_handle = importbuffer_virtualaddr(src_buf, src_buf_size);
    dst_handle = importbuffer_virtualaddr(dst_buf, dst_buf_size);
    if (src_handle == 0 || dst_handle == 0) {
        printf("importbuffer failed!\n");
        goto release_buffer;
    }

    src_img = wrapbuffer_handle(src_handle, src_width, src_height,
                                src_format, src_modifier,
                                src_width, src_height);
    dst_img = wrapbuffer_handle(dst_handle, dst_width, dst_height,
                                dst_format, dst_modifier,
                                dst_width, dst_height);
    if (src_img.handle == 0 || dst_img.handle == 0) {
        printf("wrapbuffer failed! %s\n", imStrError());
        goto release_buffer;
    }

    /*
     * Copy the src image to the dst buffer.
        --------------        --------------
        |            |        |            |
        |  src_image |   =>   |  dst_image |
        |            |        |            |
        --------------        --------------
     */

    ret = imcheck(src_img, dst_img, {}, {});
    if (IM_STATUS_NOERROR != ret) {
        printf("%d, check error! %s", __LINE__, imStrError((IM_STATUS)ret));
        goto release_buffer;
    }

    ret = imcopy(src_img, dst_img);
    if (ret == IM_STATUS_SUCCESS) {
        printf("%s running success!\n", LOG_TAG);
    } else {
        printf("%s running failed, %s\n", LOG_TAG, imStrError((IM_STATUS)ret));
        goto release_buffer;
    }

	printf("output [0x%x, 0x%x, 0x%x, 0x%x]\n", dst_buf[0], dst_buf[1], dst_buf[2], dst_buf[3]);

release_buffer:
    if (src_handle)
        releasebuffer_handle(src_handle);
    if (dst_handle)
        releasebuffer_handle(dst_handle);

    if (src_buf)
        free(src_buf);
    if (dst_buf)
        free(dst_buf);

    return ret;
}
