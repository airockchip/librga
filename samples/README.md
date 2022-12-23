# librga IM2D API 示例代码说明

​	该目录下为librga IM2D API示例代码，包含常见的图像缩放、裁剪、旋转、Blit、alpha混合等操作的示例代码。

## 目录说明

├── **im2d_api_demo**：IM2D API快速演示DEMO<br/>
├── **im2d_slt**：slt测试工具<br/>
├── **allocator_demo**：内存分配器相关示例代码<br/>
├── **alpha_demo**：alpha混合、叠加相关示例代码<br/>
├── **async_demo**：异步模式相关示例代码<br/>
├── **config_demo**：线程全局配置相关示例代码<br/>
├── **copy_demo**：图像搬运、拷贝相关示例代码<br/>
├── **crop_demo**：图像裁剪、拼接相关示例代码<br/>
├── **cvtcolor_demo**：图像格式转换、色域转换相关示例代码<br/>
├── **fill_demo**：图像填充、画框相关示例代码<br/>
├── **mosaic_demo**：马赛克遮盖相关示例代码<br/>
├── **padding_demo**：padding相关示例代码<br/>
├── **resize_demo**：图像缩放相关示例代码<br/>
├── **rop_demo**：ROP运算相关示例代码<br/>
├── **transform_demo**：图像变换相关示例代码<br/>
├── **utils**：示例代码中使用的第三方引用、通用工具代码<br/>
└── **sample_file**：演示代码使用图像数据文件<br/>

## 编译说明

​	本仓库示例代码支持CMAKE编译，可以通过修改toolchain_*.cmake文件以及编译脚本实现快速编译。

### 工具链修改

- **Android NDK（build for android）**

​	参考librga源码目录下**toolchains/toolchain_android_ndk.cmake**写法，修改NDK路径、Android版本信息等。

| 工具链选项                          | 描述                                         |
| ----------------------------------- | -------------------------------------------- |
| CMAKE_ANDROID_NDK                   | NDK编译包路径                                |
| CMAKE_SYSTEM_NAME                   | 平台名，默认为Android                        |
| CMAKE_SYSTEM_VERSION                | Android版本                                  |
| CMAKE_ANDROID_ARCH_ABI              | 处理器版本                                   |
| CMAKE_ANDROID_NDK_TOOLCHAIN_VERSION | 工具链选择（clang/gcc）                      |
| CMAKE_ANDROID_STL_TYPE              | NDK C++库的链接方式（c++_static/c++_shared） |

- **Linux（buildroot/debian）**

​	参考librga源码目录下**toolchains/toolchain_linux.cmake**写法，修改工具链路径、名称。

| 工具链选项     | 描述       |
| -------------- | ---------- |
| TOOLCHAIN_HOME | 工具链目录 |
| TOOLCHAIN_NAME | 工具链名称 |

### 编译脚本修改

​	修改samples目录或需要编译的示例代码目录下**cmake_*.sh**，指定toolchain路径。

| 编译选项       | 描述                                                         |
| -------------- | ------------------------------------------------------------ |
| TOOLCHAIN_PATH | toolchain的绝对路径，即《工具链修改》小节中修改后的toolchain_*.cmake文件的绝对路径 |
| LIBRGA_PATH    | 需要链接的librga.so的绝对路径，默认为librga cmake编译时的默认打包路径 |
| BUILD_DIR      | 编译生成文件存放的相对路径                                   |

### 执行编译脚本

- **Android NDK（build for android）**

```bash
$ chmod +x ./cmake_android.sh
$ ./cmake_android.sh
```

- **Linux（buildroot/debian）**

```bash
$ chmod +x ./cmake_linux.sh
$ ./cmake_linux.sh
```

