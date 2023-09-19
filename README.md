## librga

RGA (Raster Graphic Acceleration Unit)是一个独立的2D硬件加速器，可用于加速点/线绘制，执行图像缩放、旋转、bitBlt、alpha混合等常见的2D图形操作。本仓库代码实现了RGA用户空间驱动，并提供了一系列2D图形操作API。

### 版本说明

#### RGA API

- 当前预编译仓库API版本：1.10.0

- 获取源码方式：

  - 同步SDK

    - Android SDK

      ```
      <SDK_path>/hardware/rockchip/librga
      ```

    - 通用Linux SDK

      ```
      <SDK_path>/external/linux-rga
      ```

  - 百度网盘

    可通过以下链接选择对应版本驱动源码更新至SDK对应目录下，或独立编译使用。

    https://eyun.baidu.com/s/3jJ9Aiz0

#### 驱动版本适配：

- 详细的驱动版本查询方法可以查看 [Rockchip_Developer_Guide_RGA_CN](docs/Rockchip_Developer_Guide_RGA_CN.md) —— **版本说明章节**

  常用命令如下：

  - 使用默认使能CONFIG_ROCKCHIP_RGA_DEBUG_FS编译选项的kernel。

  ```shell
  cat /sys/kernel/debug/rkrga/driver_version
  ```

  - 使能ROCKCHIP_RGA_PROC_FS编译选项的kernel。

  ```shell
  cat /proc/rkrga/driver_version
  ```

- 当前API版本适配以下驱动：

  - RGA multicore Device Driver
    - 该版本驱动所有版本均支持获取版本号，最低适配1.2.4驱动版本，建议更新至1.2.23及以上驱动版本。

  - RGA2 Device Driver
    - 支持兼容模式运行，API版本1.3.2以后新增接口无法使用，最佳兼容适配驱动版本为v2.1.0。

  - RGA Device Driver
    - 支持兼容模式运行，API版本1.3.2以后新增接口无法使用。

- 可通过以下方式更新驱动：

  - 同步SDK

    - RGA multicore Device Driver

      支持搭载RGA2/RGA3的芯片。

      ```
      <kernel_path>/driver/video/rockchip/rga3
      ```

    - RGA2 Device Driver

      搭载RGA2 的芯片支持 RGA2 Device Driver 和 RGA multicore Device Driver，部分早期发布固件均为 RGA2 Device Driver，较新的发布固件均为 RGA multicore Device Driver ，可选择更新为 RGA multicore Device Driver 或保持使用 RGA2 Device Driver

      RGA2 Device Driver路径：

      ```
      <kernel_path>/driver/video/rockchip/rga2
      ```

    - RGA Device Driver

      搭载RGA1的芯片仅支持 RGA Device Driver。

      ```
      <kernel_path>/driver/video/rockchip/rga3
      ```

  - 百度网盘

    可通过以下链接选择对应版本驱动源码更新至SDK对应目录下。

    https://eyun.baidu.com/s/3dGhufEL


### 适用芯片平台

Rockchip RK3128 | RK3126c | RK3288 | RK3288w | RV1108 | RK3368 | RK3326 | RK3228 | RK3228H | RK3326 | RK1808 | RV1126 | RV1109 | RK3399 | RK3399pro | RK3566 | RK3568 | RK3588 | RK3326S | RV1106 | RV1103 | RK3528 | RK3562

>  本仓库预编译文件只支持以下芯片平台，其他芯片平台可以使用SDK中源码进行编译。

Rockchip RK1808 | RV1126 | RV1109 | RK3399 | RK3399pro | RK3566 | RK3568 | RK3588 | RV1106 | RV1103 | RK3528 | RK3562

### 目录说明

**libs**：预编译的librga库

 - AndroidNdk
   - arm64-v8a： android-ndk-r16b编译，适用于64位Android系统，须匹配对应libc++_shared.so
   - armeabi-v7a： android-ndk-r16b编译，适用于32位Android系统，须匹配对应libc++_shared.so
 - Linux
   - gcc-aarch64： GCC-9.3编译，适用于64位Linux系统（适用于RK3588、RK3566、RK3568等芯片平台）
   - gcc-armhf： GCC-8.3编译，适用于32位Linux系统（适用于RK3588、RK3566、RK3568、RV1109、RV1126等芯片平台）
   - gcc-uclib-armhf：GCC-rockchip830-uclibc编译，适用于特定的使用uclibc的32位Linux系统（适用于RV1103、RV1106芯片平台）

**include**：相关头文件

**docs**：API说明文档、FAQ

**samples**：使用例程

 - sample_file： 示例图片

**tools**：适用工具

- bin： 预编译的可执行demo

### 使用说明

* **头文件引用**

  * C++调用im2d api

    im2d.hpp

  * C调用im2d api

    im2d.h

* **库文件**

  librga.so

  librga.a

* librga应用开发接口说明参考以下文件：

  [IM2D API说明文档【中文】](docs/Rockchip_Developer_Guide_RGA_CN.md)

  [IM2D API说明文档【英文】](docs/Rockchip_Developer_Guide_RGA_EN.md)

* RGA模块FAQ文档：

  [RGA_FAQ【中文】](docs/Rockchip_FAQ_RGA_CN.md)
  
  [RGA_FAQ【英文】](docs/Rockchip_FAQ_RGA_EN.md)

