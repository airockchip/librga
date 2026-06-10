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
#define LOG_TAG "rga_cfa_a2_demo"

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
    char *src_buf, *dst_buf, *pre_comps_buf, *next_comps_buf;
    int src_buf_size, dst_buf_size, comps_buf_size;

    rga_buffer_t src_img, dst_img, pre_comps_img, next_comps_img;
    rga_buffer_handle_t src_handle, dst_handle, pre_comps_handle, next_comps_handle;
    im_cfa_t cfa;

    memset(&src_img, 0, sizeof(src_img));
    memset(&dst_img, 0, sizeof(dst_img));
    memset(&pre_comps_img, 0, sizeof(pre_comps_img));
    memset(&next_comps_img, 0, sizeof(next_comps_img));
    memset(&cfa, 0, sizeof(cfa));

    src_width = 1280;
    src_height = 720;
    src_format = RK_FORMAT_RGBA_8888;

    dst_width = 1280;
    dst_height = 720;
    dst_format = RK_FORMAT_Y1;

    src_buf_size = src_width * src_height * get_bpp_from_format(src_format);
    dst_buf_size = dst_width * dst_height * get_bpp_from_format(dst_format);
    comps_buf_size = dst_buf_size;

    src_buf = (char *)malloc(src_buf_size);
    dst_buf = (char *)malloc(dst_buf_size);
    pre_comps_buf = (char *)malloc(comps_buf_size);
    next_comps_buf = (char *)malloc(comps_buf_size);

    /* fill image data */
    if (0 != read_image_from_file(src_buf, LOCAL_FILE_PATH, src_width, src_height, src_format, 0)) {
        printf("src image read err\n");
        draw_rgba(src_buf, src_width, src_height);
    }
    memset(dst_buf, 0x11, dst_buf_size);
    memset(pre_comps_buf, 0x22, comps_buf_size);
    memset(next_comps_buf, 0x33, comps_buf_size);

    src_handle = importbuffer_virtualaddr(src_buf, src_buf_size);
    dst_handle = importbuffer_virtualaddr(dst_buf, dst_buf_size);
    pre_comps_handle = importbuffer_virtualaddr(pre_comps_buf, comps_buf_size);
    next_comps_handle = importbuffer_virtualaddr(next_comps_buf, comps_buf_size);
    if (src_handle == 0 || dst_handle == 0 || pre_comps_handle == 0 || next_comps_handle == 0) {
        printf("importbuffer failed!\n");
        goto release_buffer;
    }

    src_img = wrapbuffer_handle(src_handle, src_width, src_height, src_format);
    dst_img = wrapbuffer_handle(dst_handle, dst_width, dst_height, dst_format);
    pre_comps_img = wrapbuffer_handle(pre_comps_handle, dst_width, dst_height, dst_format);
    next_comps_img = wrapbuffer_handle(next_comps_handle, dst_width, dst_height, dst_format);

    /* config cfa */
    cfa.type = IM_CFA_TYPE_A2;
    cfa.pattern = IM_CFA_PATTERN_3x3_RGBGBRBRG;

    cfa.saturation_gain = 64; //[0, 128], default 64
    cfa.sharpen_gain = 32; //[0, 128], default 32

    cfa.filter = 0;
    cfa.filter |= IM_CFA_FILTER_MEDIAN; //remove falsecolor effect
    if (cfa.sharpen_gain < 64)
        cfa.filter |= IM_CFA_FILTER_HIGH_PASS;

    cfa.dither = 0;
    cfa.dither |= IM_CFA_DITHER_FLAG_ENABLE;

    cfa.a2_modulate = IM_CFA_A2_MODULATE_LPS | IM_CFA_A2_MODULATE_HPS | IM_CFA_A2_MODULATE_ERR;
    cfa.comps_level = 64; //[0, 128], default 64

    ret = imcheck(src_img, dst_img, {}, {});
    if (IM_STATUS_NOERROR != ret) {
        printf("%d, check error! %s", __LINE__, imStrError((IM_STATUS)ret));
        return -1;
    }

    /*
     * Convert src to Y1 and get compesation(t-1) image.
        src_img  ==> t-1_comps_img
        --------------    --------------
        |            |    |            |
        |  src_img   | => |  Y1 t-1    |
        |            |    |compesation |
        --------------    --------------
     */
    ret = imcfa(src_img, pre_comps_img, {}, {}, &cfa);
    if (ret == IM_STATUS_SUCCESS) {
        printf("%s running success!\n", LOG_TAG);
    } else {
        printf("%s running failed, %s\n", LOG_TAG, imStrError((IM_STATUS)ret));
        goto release_buffer;
    }

    write_image_to_file(pre_comps_buf, LOCAL_FILE_PATH, dst_width, dst_height, dst_format, 10);

    /*
     * Refer to the t-1 frame toConvert src to Y1 and get compesation(t) image.
        src_img         ====> dst_img
                        |  |
        t-1_comps_img  =|  => t_comps_img
        --------------      --------------
        |            |      |            |
        |  src_img   | ===> |     Y1     |
        |            | | |  |            |
        -------------- | |  --------------
        -------------- | |  --------------
        |            | | |  |            |
        |    Y1 t-1  | = => |    Y1 t    |
        |compesation |      |compesation |
        --------------      --------------

     */
    ret = imcfa(src_img, dst_img, pre_comps_img, next_comps_img, &cfa);
    if (ret == IM_STATUS_SUCCESS) {
        printf("%s running success!\n", LOG_TAG);
    } else {
        printf("%s running failed, %s\n", LOG_TAG, imStrError((IM_STATUS)ret));
        goto release_buffer;
    }

    write_image_to_file(dst_buf, LOCAL_FILE_PATH, dst_width, dst_height, dst_format, 0);
    write_image_to_file(next_comps_buf, LOCAL_FILE_PATH, dst_width, dst_height, dst_format, 1);

release_buffer:
    if (src_handle)
        releasebuffer_handle(src_handle);
    if (dst_handle)
        releasebuffer_handle(dst_handle);
    if (pre_comps_handle)
        releasebuffer_handle(pre_comps_handle);
    if (next_comps_handle)
        releasebuffer_handle(next_comps_handle);

    if (src_buf)
        free(src_buf);
    if (dst_buf)
        free(dst_buf);
    if (pre_comps_buf)
        free(pre_comps_buf);
    if (next_comps_buf)
        free(next_comps_buf);

    return ret;
}
