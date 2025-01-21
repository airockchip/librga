/*
 * Copyright (C) 2024  Rockchip Electronics Co., Ltd.
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
#define LOG_TAG "rga_gauss_demo"

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
#include "dma_alloc.h"

#define LOCAL_FILE_PATH "/data"

int main() {
    int ret = 0;
    int src_width, src_height, src_format;
    int dst_width, dst_height, dst_format;
    char *src_buf, *dst_buf;
    int src_dma_fd, dst_dma_fd;
    int src_buf_size, dst_buf_size;

    rga_buffer_t src_img, dst_img;
    rga_buffer_handle_t src_handle, dst_handle;
    im_handle_param_t src_param;
    im_handle_param_t dst_param;

    memset(&src_img, 0, sizeof(src_img));
    memset(&dst_img, 0, sizeof(dst_img));

    src_width = 1280;
    src_height = 720;
    src_format = RK_FORMAT_RGBA_8888;

    dst_width = 1280;
    dst_height = 720;
    dst_format = RK_FORMAT_RGBA_8888;

    src_buf_size = src_width * src_height * get_bpp_from_format(src_format);
    dst_buf_size = dst_width * dst_height * get_bpp_from_format(dst_format);

    src_param = {(uint32_t)src_width, (uint32_t)src_height, (uint32_t)src_format};
    dst_param = {(uint32_t)dst_width, (uint32_t)dst_height, (uint32_t)dst_format};

    /* Allocate dma_buf from CMA, return dma_fd and virtual address */
    ret = dma_buf_alloc(DMA_HEAP_DMA32_UNCACHED_PATH, src_buf_size, &src_dma_fd, (void **)&src_buf);
    if (ret < 0) {
        printf("alloc src CMA buffer failed!\n");
        return -1;
    }

    ret = dma_buf_alloc(DMA_HEAP_DMA32_UNCACHED_PATH, dst_buf_size, &dst_dma_fd, (void **)&dst_buf);
    if (ret < 0) {
        printf("alloc dst CMA buffer failed!\n");
        dma_buf_free(src_buf_size, &src_dma_fd, src_buf);
        return -1;
    }

    /* fill image data */
    if (0 != read_image_from_file(src_buf, LOCAL_FILE_PATH, src_width, src_height, src_format, 0)) {
        printf("src image read err\n");
        draw_rgba(src_buf, src_width, src_height);
    }
    memset(dst_buf, 0x80, dst_buf_size);

    src_handle = importbuffer_fd(src_dma_fd, &src_param);
    dst_handle = importbuffer_fd(dst_dma_fd, &dst_param);
    if (src_handle == 0 || dst_handle == 0) {
        printf("import dma_fd error!\n");
        ret = -1;
        goto release_buffer;
    }

    src_img = wrapbuffer_handle(src_handle, src_width, src_height, src_format);
    dst_img = wrapbuffer_handle(dst_handle, dst_width, dst_height, dst_format);

    /*
     * After performing Gaussian blur on the source data, output it to the target buffer.
        --------------        --------------
        |            | guass  |            |
        |  src_image |   =>   |   result   |
        |            |        |            |
        --------------        --------------
     */

    imsetOpacity(&src_img, 0xff);

    ret = imcheck(src_img, dst_img, (im_rect){}, (im_rect){});
    if (IM_STATUS_NOERROR != ret) {
        printf("%d, check error! %s", __LINE__, imStrError((IM_STATUS)ret));
        return -1;
    }

    ret = imgaussianBlur(src_img, dst_img, 3, 3, 1);
    if (ret == IM_STATUS_SUCCESS) {
        printf("%s running success!\n", LOG_TAG);
    } else {
        printf("%s running failed, %s\n", LOG_TAG, imStrError((IM_STATUS)ret));
        goto release_buffer;
    }

	printf("output [0x%x, 0x%x, 0x%x, 0x%x]\n", dst_buf[0], dst_buf[1], dst_buf[2], dst_buf[3]);
    write_image_to_file(dst_buf, LOCAL_FILE_PATH, dst_width, dst_height, dst_format, 0);

release_buffer:
    if (src_handle)
        releasebuffer_handle(src_handle);
    if (dst_handle)
        releasebuffer_handle(dst_handle);

    if (src_buf)
        dma_buf_free(src_buf_size, &src_dma_fd, src_buf);
    if (dst_buf)
        dma_buf_free(dst_buf_size, &dst_dma_fd, dst_buf);

    return ret;
}
