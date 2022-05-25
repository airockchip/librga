# 更新日志

## 1.3.2 （2022-05-25）

特殊发布版本，适用于无法获取驱动版本号的RGA驱动。

### 新增

- 支持Android 12

## 1.3.1 （2021-11-05）

### 新增

- 支持ARGB4444/5551/8888、XRGB8888格式。（该功能有对应kernel提交）

### 优化

- 支持SDK通过CMAKE编译librga。

### 修复

- 修复部分已知问题。
- 修复搭载RGA1的平台调用librga时出现内核报错的问题。
- 解决BGR565、BGRA4444、BGRA5551格式转换颜色异常的问题。
- 修复IM2D API中设置globalAlpha后导致混合效果异常的问题。
- 修复部分crop场景imcheck无法正确校验的问题。
- 解决rgaImDemo fill模式异常报错的问题。

## 1.3.0 （2021-08-05）

### 新增

- 完善三通道模式src1通道参数校验。
- 增加usage —— IM_ASYNC

### 变更

- 更正IM_SYNC语意，原语意为 “标识本次RGA操作需要同步” ，与同步模式存在歧义，修改如下：

  传参 sync = 1 为同步模式， usage配置IM_SYNC；

  传参 sync = 0 为异步模式， usage配置IM_ASYNC。

### 修复

- 解决三通道模式Alpha叠加场景中复合旋转显示异常的问题。

## 1.2.6 （2021-08-02）

### 新增

- 支持BGR565、BGRA5551、BGRA4444格式。（该功能有对应kernel提交）

### 优化

- 优化部分内部逻辑。

### 修复

- 更正引用rga.h时可能会出现的编译报错。
- 更正docs/RGA_API_Instruction.md中部分芯片型号的硬件支持信息。
- 避免RockchipRga单例被异常销毁后可能引发的错误。

### 移除

- 部分功能中无用的日志打印。

## 1.2.5 （2021-07-08）

### 新增

- docs/RGA_FAQ.md。
- 三通道模式混合支持配置每条通道的CSC。

### 变更

- RGA硬件版本规则更改。
- docs/README.md重命名为docs/RGA_API_Instruction.md。

### 优化

- RGA硬件版本信息管理。
- RGA硬件功能校验。
- 更加完善明了的报错信息。

### 修复

- IMStrError() 线程安全。
- 修正RGA API开发指南中关于图像合成的错误描述。

## 1.2.4 （2021-06-01）

### 新增

- 405（src over）/504（dst over）两种预乘Alpha的混合模式。
- im2d api支持配置src/src1/dst图层自身的色域空间。

## 1.2.3 （2021-05-31）

### 新增

- 支持full csc模式。

### 变更

- 更正debian版本号。

## 1.2.2 （2021-04-26）

### 新增

- im2d api文档中增加版本号管理介绍。
- src支持直接读取256阶灰度图，并对灰度图进行缩放、裁剪等功能。（该功能有对应kernel提交）

### 修复

- im2d api中CSC模式错误的定义。
- 使用meson编译无法向下兼容的问题。

### 移除

- 一些无用打印。
- 对于旋转模式不合理的校验。



## 1.2.0 (2021-04-26)

### 新增

* im2d api支持ROP。
* sample目录下增加示例图片。
* 支持Gralloc4.0。
* rgaImDemo的循环选项和打印预期选项。
* color key功能。
* color fill支持YUV格式。
* 对RGA1的校验。
* 多种方式查询librga版本号。
* CHANGLOG.md。

### 变更

* 部分定义的索引值。
* 更新im2d api说明文档。
* 使用Apache-2.0 license。
* imresize()使用系数进行缩放时使用向下对齐。
* 取消全局初始化。
* librga版本号的管理。

### 优化

* 整合不同版本Android平台源码。
* 兼容Android、Linux平台。
* C_API的易用性。
* librga图像格式与Android平台图像格式兼容。
* imStrError()内存使用上的风险。
* 兼容两种同步/异步的配置方法。
* rgaSlt demo中支持配置虚拟地址和fd。
* rgaSlt demo返回报错值。
* 获取硬件支持信息的逻辑。
* imcheck()校验功能的可扩展性。
* rotate功能与mirror功能可以同时配置。
* nn_quantize功能与Alpha混合功能可以同时配置。

### 修复

* 修复一些已知错误。
* 在一些旧版本的Android的编译问题。
* C_API向下兼容问题。
* YUV对齐width stride只支持4对齐问题。
* A+B->C模式color space异常的问题。

### 移除

* 一些无效的定义。
* 对libhardware的依赖。
* makefile编译。
* librga初始化的打印。
* C_API对RGA模块的初始化。



## 1.1.1 (2020-11-12)

### 新增

* color palette功能。
* 支持A+B->C模式进行Alpha混合。
* src、dst、dst over Alpha混合模式。
* 输入格式YUYV422，输出格式YUYV422/420支。
* 输出格式Y400、Y4、Y1。
* wrapbuffer_handle api。
* meson支持编译im2d demo。

### 变更

* license变更。

### 优化

* librga版本管理机制。
* Android NDK编译。

### 修复

* 虚拟地址调用RGA结果输出黑线的问题（cache）。

* 修复一些已知错误。



## 1.0.3 (2020-09-18)

### 新增

* 在原本librga的代码基础上封装im2d api。
* 增加meson、cmake的编译支持。

### 变更

* 修改C_API的实现逻辑。

### 优化

* 整合源代码，使Linux和Android共用同一套源码。



## 1.0.0 （2020-06-03）

### 新增

* 移植librga到Android Q。