## librga

RGA (Raster Graphic Acceleration Unit)是一个独立的2D硬件加速器，可用于加速点/线绘制，执行图像缩放、旋转、bitBlt、alpha混合等常见的2D图形操作。本仓库代码实现了RGA用户空间驱动，并提供了一系列2D图形操作API。

### 版本说明

**RGA API** 版本: 1.3.2

**RGA 驱动** 适配版本：

- 无法通过debug节点获取版本号的驱动版本。
- 开机日志打印版本号为 3.xx/4.xx 硬件版本号的驱动版本。
- 当使用版本号大于1.2版本的驱动版本时，请使用1.7.0及以上librga版本。

### 适用芯片平台

Rockchip RK3066 | RK3188 | RK2926 | RK2928 | RK3026 | RK3028 | RK3128 | Sofia3gr | RK3288 | RK3288w | RK3190 | RK1108 | RK3368 | RK3326 | RK3228 | RK3228H | RK3326 | RK1808 | RV1126 | RV1109 | RK3399 | RK3399pro | RK3566 | RK3568

>  本仓库预编译文件只支持以下芯片平台，其他芯片平台可以使用SDK中源码进行编译。

Rockchip RK1808 | RV1126 | RV1109 | RK3399 | RK3399pro | RK3566 | RK3568

### 目录说明

**libs**：预编译的librga库

 - AndroidNdk
   - arm64-v8a： android-ndk-r16b编译，适用于64位Android系统，须匹配对应libc++_shared.so
   - armeabi-v7a： android-ndk-r16b编译，适用于32位Android系统，须匹配对应libc++_shared.so
 - Linux
   - gcc-aarch64： GCC-9.3编译，适用于64位Linux系统（适用于RK3566、RK3568、RK3399等芯片平台）
   - gcc-armhf： GCC-8.3编译，适用于32位Linux系统（适用于RK3566、RK3568、RK3399、RV1109、RV1126等芯片平台）

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

* librga应用开发接口说明参考以下文件：

  [RGA_API_Instruction.md](docs/RGA_API_Instruction.md)

* RGA模块FAQ文档：

  [RGA_FAQ.md](docs/RGA_FAQ.md)

