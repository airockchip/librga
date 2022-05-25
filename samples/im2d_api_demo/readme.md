# IM2D API 示例

## 编译说明

* **Android Source Project**

配置好Android源码编译环境后，在示例代码目录下执行**mm**进行编译。根据不同的Android版本将自动选择Android.mk或Android.bp作为编译脚本。

* **Android NDK (build for android)**

修改librga源码根目录下的文件**cmake-android.sh**。执行以下操作完成编译：

```bash
$ chmod +x ./cmake-android.sh
$ ./cmake-android.sh
```

​    **[编译选项]**

1. 指定ANDROID_NDK_HOME为NDK开发包的路径
2. 指定CMAKE_ANDROID为android SDK包中cmake可执行文件的路径
3. 根据需要选择不同架构，设置-DANDROID_ABI等于armeabi-v7a或arm64-v8a
4. 根据需要选择不同的android平台版本，设置-DANDROID_PLATFORM
4. 指定LIBRGA_PATH为librga.so的绝对路径

* **Cmake (buildroot/debian)**

修改librga源码根目录下的**buildroot.cmake**文件。执行以下脚本完成编译:

```bash
$ chmod +x ./cmake-android.sh
$ ./cmake-linux.sh
```

​    **[编译选项]**

1. 指定TOOLCHAIN_HOME为交叉编译工具的路径
2. 指定CMAKE_C_COMPILER为gcc编译命令的路径
3. 指定CMAKE_CXX_COMPILER为g++编译命令的路径
4. 指定LIBRGA_PATH为librga.so的绝对路径

### 使用说明


见docs目录下《Rockchip_Developer_Guide_RGA_CN.md》——测试用例及调试方法 章节。