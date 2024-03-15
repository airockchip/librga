# 更新日志

## 1.10.1 （2024-03-06）

该版本RGA驱动建议更新至1.3.0及以上版本，最低支持1.2.4。

### 新增

- 新增支持芯片RK3576。
- 新增支持格式A8、Y8、YUV444_SP定义。
- 新增支持配置压缩模式RKFBC64x4、AFBC32x8 split mode。
- 新增支持配置TILE4x4模式。
- 新增支持配置缩放插值算法。
- 新增imsetAlphaBit()，支持配置ARGB5551/ABGR5551 alpha映射。

### 优化

- 优化示例代码CMake编译配置。

### 变更

- 源码更新包由原百度网盘迁移至联想网盘。
- 最低要求的CMake版本由原3.5更改为3.12。
- imresize() interpolation参数支持配置。
- RGA2不支持RGBA5551/BGRA5551/RGBA4444/BGRA4444格式。

### 修复

- 修复ARGB5551/ABGR5551/ARGB4444/ABGR4444格式内存排列错误的问题。
- 修复旧接口RkRgaIsReady()返回值异常的错误。

## 1.10.0_[9] （2023-12-11）

该版本RGA驱动建议更新至1.3.0及以上版本，最低支持1.2.4。

### 新增

- 增加关于性能影响的Q&A。
- rgaImDemo支持更多功能
  - 支持RV1106直接运行。
  - 增加更多blend模式。
  - 颜色填充支持自定义颜色。

### 变更

- 旧接口（RockchipRga API、C_API）维持原有功能，不支持globalAlpha功能。

### 修复

- 修复RK1808无法获取硬件信息的错误。
- 更正rga_req结构体错误的预留内存大小。
- 修正示例代码中一些退出流程。
- 修复示例代码中GraphicBuffer无法分配内存的问题。

- 修复importbuffer API返回值非预期。
- 修复调用旧接口导致fd 0被异常关闭的问题。
- 修复旧接口配置blend模式失效的问题。

## 1.10.0 （2023-09-12）

该版本RGA驱动建议更新至1.3.0及以上版本，最低支持1.2.4。

### 新增

- 支持更多Porter-Duff混合模型，src-in/dst-in/src-out/dst-out/src-atop/dst-atop/xor。（驱动须更新至1.3.0）
- 新增配置单独通道透明度API imsetOpacity()。
- 新增配置单独通道色域空间API imsetColorSpace()。
- 新增配置全局alpha示例代码。
- 支持GKI。（驱动须更新至1.3.0）

### 优化

- 补充FAQ中对于常见RGA2 不支持大于4G内存空间问题的Q&A。

### 变更

- samples/padding_demo使用dma32分配内存。
- 配置色域转换方式更改为通过imsetColorSpace()配置对应通道的色域空间。

### 修复

- RGA2可以支持 RGB2YUV模式下BT 709 limit range。（驱动须更新至1.3.0）
- 修复一些条件下调用task API参数会丢失的异常。
- 修复部分示例代码的笔误。

### 移除

- 移除对SDK环境变量ANDROID_12的依赖。

## 1.9.3 （2023-06-28）

该版本RGA驱动建议更新至1.2.27及以上版本，最低支持1.2.4。

### 优化

- 补充对samples目录下示例代码功能说明。
- 增加RK_FORMAT_XX格式的描述。

### 修复

- 修复FBC输入对实宽、实高的过度约束。（驱动须更新至1.2.27）
- 修复示例代码中部分笔误。



## 1.9.2 （2023-04-13）

该版本RGA驱动建议更新至1.2.25及以上版本，最低支持1.2.4。

### 新增

- 补全对FBC/TILE8×8 限制的检查。
- 增加FBC/Tile8×8的示例代码。
- 增加在不支持UV均值下采样的芯片上针对YUV422->YUV420场景下采样方法的示例代码。

### 优化

- 移除对libdrm.so的依赖，避免受libdrm版本影响导致编译失败。

### 修复

- 修复immakeBorder()配置top/bottom/left/right为0时输出画面异常。
- 修复部分fill/color_palette模式无法返回release_fence fd的问题。



## 1.9.1 （2023-02-06）

该版本RGA驱动建议更新至1.2.24及以上版本，最低支持1.2.4。

### 新增

- 新增支持芯片RK3562。
- 增加TILE8x8、FBC示例代码。

### 优化

- 编译阶段无需依赖libdrm.so。
- 完善TILE8x8、FBC的参数限制。

### 修复

- 修复TILE8x8格式运行异常问题。（驱动须更新至1.2.24）
- 修复 imcheckHeader() 在编译C程序时的报错。
- 修复meson无法编译librga。



## 1.9.0 （2022-12-20）

该版本RGA驱动建议更新至1.2.22及以上版本，最低支持1.2.4。

### 新增

- 新增支持芯片RK3528。

- 适配Android 12 gralloc 0.3
- 新增头文件校验接口。
- 新增批处理接口（im2d_task.h）。
- 新增数组模式接口。
- 新增padding接口。
- 支持通过Android属性/环境变量动态的开启/关闭 librga 运行日志。
- 增加对drm_fourcc格式支持。
- 增加示例代码单独编译说明。
- 增加多种常见场景示例代码。
  - allocator_demo
  - alpha_demo
  - async_demo
  - config_demo
  - copy_demo
  - crop_demo
  - cvtcolor_demo
  - fill_demo
  - mosaic_demo
  - resize_demo
  - rop_demo
  - transform_demo
  - padding_demo

### 优化

- 兼容rga2 driver、multi_rga driver。
- 优化librga与驱动之间版本校验机制。
- 优化头文件结构。
- 头文件添加更多描述信息。
- 优化cmake编译脚本。

### 修复

- 修复RGA3 dst-over模式对YUV格式处理异常问题。



## 1.8.1 （2022-06-20）

### 修复

- 更正wrapbuffer_handle宏函数与C++函数定义不同的问题，更正后与宏函数传参相同。。
- 修复部分编译warning。



## 1.8.0 （2022-05-25）

该版本RGA驱动须更新至1.2.6。

### 新增

- 新增支持芯片RK3326S、RV1106、RV1103。
- 增加英文说明文档。
- 增加马赛克、OSD接口（部分芯片支持）。
- 支持Rockit-ko在内核的调用。
- 新增importbuffer接口支持使用buffer_size作为传参（RGA驱动1.2.9及以上版本支持）。
- 增加默认编译静态库、动态库。

### 优化

- 针对部分接口的异常返回，增加更多的报错信息。

### 修复

- 更正文档中部分描述。
- 修复部分格式无法importbuffer的问题。

## 1.7.2 （2022-01-20）

该版本RGA驱动须更新至1.2.6。

### 新增

- Android/Linux平台支持异步模式。
- 支持多硬件约束条件融合校验。
- 增加librga对驱动版本校验功能。
- 支持查询RGA负载。
- 针对外部buffer增加import/release接口。

### 优化

- 优化cmake编译脚本。
- 异步模式支持查询指定任务完成情况。

### 变更

- C++接口实现与C实现隔离。
- librga支持12及以前的Android版本。

### 修复

- 修复软件信号导致异常退出的问题。

### 移除

- 弃用genversion.sh

## 1.6.0 (2021-11-23)

### 新增

- 支持RGA3硬件。
- 增加任务核心指定、优先级配置。
- 异步模式引入fence机制。
- utils支持AFBC图像的读写。
- 3588 RGA支持ROP功能。
- CMAKE编译支持C接口。

### 变更

- 驱动支持变更为 multi_rga。
- improcess增加传参：input_fence_fd、output_fence_fd、im_opt_t结构体。
- imsync增加传参：release_fence_fd。
- im2d_api 中 color/colorkey/nn/rop 模式将通过 im_opt_t 结构体进行配置。
- Linux平台暂时不支持Async模式。
- 头文件的数据类型与驱动重新对齐。（头文件存在修改）

### 修复

- 改正部分错误的格式命名。
- 更正YUYV420的像素大小。
- 修改宏函数内临时变量名称，避免非预期错误。

## 1.4.0 （2021-11-10）

### 新增

- 支持Android 12编译。

### 变更

- RockchipRga接口demo目录变更：

  librga/sample/ -> librga/sample/legacy/。

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
