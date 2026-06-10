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
#define LOG_TAG "rga_cfa_bsch_demo"

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

#define LOCAL_FILE_PATH "/data"

int main() {
    int ret = 0;
    int src_width, src_height, src_format;
    int dst_width, dst_height, dst_format;
    int lut_width, lut_height, lut_format;
    char *src_buf, *dst_buf, *lut_buf;
    char bcsh_table[256];
    int src_buf_size, dst_buf_size, lut_buf_size;

    rga_buffer_t src_img, dst_img, lut_img;
    rga_buffer_handle_t src_handle, dst_handle, lut_handle;
    im_cfa_t cfa;

    memset(&src_img, 0, sizeof(src_img));
    memset(&dst_img, 0, sizeof(dst_img));
    memset(&lut_img, 0, sizeof(lut_img));
    memset(&cfa, 0, sizeof(cfa));

    src_width = 1280;
    src_height = 720;
    src_format = RK_FORMAT_YCbCr_400;

    dst_width = 1280;
    dst_height = 720;
    dst_format = RK_FORMAT_Y8;

    /* 0~256 color LUT*/
    lut_width = 16;
    lut_height = 16;
    lut_format = RK_FORMAT_RGBA_8888;

    src_buf_size = src_width * src_height * get_bpp_from_format(src_format);
    dst_buf_size = dst_width * dst_height * get_bpp_from_format(dst_format);
    lut_buf_size = lut_width * lut_height * get_bpp_from_format(lut_format);

    src_buf = (char *)malloc(src_buf_size);
    dst_buf = (char *)malloc(dst_buf_size);
    lut_buf = (char *)malloc(lut_buf_size);

    /* fill image data */
    if (0 != read_image_from_file(src_buf, LOCAL_FILE_PATH, src_width, src_height, src_format, 0)) {
        printf("src image read err, a color scale image from 0~255 will be drawn using the CPU.\n");
        for (int i = 0; i < 256; i++) {
            memset(src_buf + i * src_width * src_height / 256, i, src_width * src_height / 256);
        }
    }
    memset(dst_buf, 0x00, dst_buf_size);

    /* generate BCSH LUT table */
    for (int i = 0; i < 256; i++) {
        bcsh_table[i] = i;
    }

    /* generate RKCFA LUT table */
    for (int i = 0; i < 256 / 4; i++) {
        lut_buf[i * 8 + 0] = bcsh_table[i * 4 + 0];
        lut_buf[i * 8 + 1] = bcsh_table[i * 4 + 1];
        lut_buf[i * 8 + 2] = bcsh_table[i * 4 + 2];
        lut_buf[i * 8 + 3] = bcsh_table[i * 4 + 3];

        lut_buf[i * 8 + 4] = bcsh_table[i * 4 + 0];
        lut_buf[i * 8 + 5] = bcsh_table[i * 4 + 1];
        lut_buf[i * 8 + 6] = bcsh_table[i * 4 + 2];
        lut_buf[i * 8 + 7] = bcsh_table[i * 4 + 3];
    }

    src_handle = importbuffer_virtualaddr(src_buf, src_buf_size);
    dst_handle = importbuffer_virtualaddr(dst_buf, dst_buf_size);
    lut_handle = importbuffer_virtualaddr(lut_buf, lut_buf_size);
    if (src_handle == 0 || dst_handle == 0 || lut_handle == 0) {
        printf("importbuffer failed!\n");
        goto release_buffer;
    }

    src_img = wrapbuffer_handle(src_handle, src_width, src_height, src_format);
    dst_img = wrapbuffer_handle(dst_handle, dst_width, dst_height, dst_format);
    lut_img = wrapbuffer_handle(lut_handle, lut_width, lut_height, lut_format);

    /* config cfa */
    cfa.type = IM_CFA_TYPE_DEFAULT;
    cfa.pattern = IM_CFA_PATTERN_GRAY;

    cfa.dither = 0;
    cfa.dither |= IM_CFA_DITHER_FLAG_CLEAR_LOW_4BITS;

    cfa.bcsh_en = true;

    /*
     * Convert src to Y8 and enable BCSH LUT.
        src_img  => dst_img
                 |
        BCSH LUT =
        --------------    --------------
        |            |    |            |
        |  src_img   | => |     Y8     |
        |            | |  |            |
        -------------- |  --------------
        -------------- |
        |            | |
        |  BCSH LUT  | =
        |            |
        --------------
     */

    ret = imcheck(src_img, dst_img, {}, {});
    if (IM_STATUS_NOERROR != ret) {
        printf("%d, check error! %s", __LINE__, imStrError((IM_STATUS)ret));
        return -1;
    }

    ret = imcfa(src_img, dst_img, lut_img, {}, {}, &cfa);
    if (ret == IM_STATUS_SUCCESS) {
        printf("%s running success!\n", LOG_TAG);
    } else {
        printf("%s running failed, %s\n", LOG_TAG, imStrError((IM_STATUS)ret));
        goto release_buffer;
    }

    write_image_to_file(dst_buf, LOCAL_FILE_PATH, dst_width, dst_height, dst_format, 0);
    write_image_to_file(lut_buf, LOCAL_FILE_PATH, lut_width, lut_height, lut_format, 1);

release_buffer:
    if (src_handle)
        releasebuffer_handle(src_handle);
    if (dst_handle)
        releasebuffer_handle(dst_handle);
    if (lut_handle)
        releasebuffer_handle(lut_handle);

    if (src_buf)
        free(src_buf);
    if (dst_buf)
        free(dst_buf);
    if (lut_buf)
        free(lut_buf);

    return ret;
}
