# MCFMOD
Cocos Creator version: 2.4.6 \
FMOD version: 2.02.05

#
## 接入Android
1. 复制文件\
将`fmod_android`、`media`、`mostar_fmod.cpp`复制到`proj.android-studio/jni`目录下。
2. 编辑`proj.android-studio/jni/CocosAndroid.mk`文件。

   1). 在`LOCAL_PATH := $(call my-dir)`下插入以下代码:

    ```
    include $(CLEAR_VARS)
    LOCAL_MODULE := fmod
    LOCAL_SRC_FILES := fmod_android/core/lib/$(TARGET_ARCH_ABI)/libfmod.so
    LOCAL_EXPORT_C_INCLUDES := fmod_android/inc
    include $(PREBUILT_SHARED_LIBRARY)

    include $(CLEAR_VARS)
    LOCAL_MODULE := fmodstudio
    LOCAL_SRC_FILES := fmod_android/studio/lib/$(TARGET_ARCH_ABI)/libfmodstudio.so
    LOCAL_EXPORT_C_INCLUDES := fmod_android/inc
    include $(PREBUILT_SHARED_LIBRARY)
    ```

   2). 将`LOCAL_SRC_FILES := ...`改为以下代码:

    ```
    LOCAL_SRC_FILES := hellojavascript/main.cpp \
				   ../../Classes/AppDelegate.cpp \
				   ../../Classes/jsb_module_register.cpp \
				   mostar_fmod.cpp \
    ```

    3). 在`LOCAL_STATIC_LIBRARIES := cocos2dx_static`下增加以下代码:
    ```
    LOCAL_SHARED_LIBRARIES := fmod fmodstudio
    ```
    示例图：\
    ![CocosCocosAndroid](https://raw.githubusercontent.com/MostarChow/MCFMOD/main/README/CocosAndroid.png)


3. 编辑`proj.android-studio/app/build.gradle`文件。

   1). 找到`sourceSets.main`插入`assets.srcDirs = ['res', '../jni/media']`\
   如以下代码:

   ```
   sourceSets.main {
        java.srcDirs "../src", "src"
        res.srcDirs "../res", 'res'
        jniLibs.srcDirs "../libs", 'libs'
        manifest.srcFile "AndroidManifest.xml"
        assets.srcDirs = ['res', '../jni/media']
    }
   ```
   示例图：\
   ![build_2](https://raw.githubusercontent.com/MostarChow/MCFMOD/main/README/build_2.png)
   

    2). 找到`dependencies`插入`implementation fileTree(dir: '../jni/fmod_android/core/lib/fmod.jar', include: ['*.jar'])`\
    如以下代码:
    ```
    dependencies {
        implementation fileTree(dir: '../libs', include: ['*.jar','*.aar'])
        implementation fileTree(dir: 'libs', include: ['*.jar','*.aar'])
        implementation fileTree(dir: "/Users/mostar/Developer/cocos2d-x/cocos/platform/android/java/libs", include: ['*.jar'])
        implementation project(':libcocos2dx')
        implementation fileTree(dir: '../jni/fmod_android/core/lib/fmod.jar', include: ['*.jar'])
    }
    ```
    示例图：\
   ![build_1](https://raw.githubusercontent.com/MostarChow/MCFMOD/main/README/build_1.png)

4. 编辑`proj.android-studio/app/src/org/cocos2dx/javascript/AppActivity.java`文件。

   1). 在`public class AppActivity extends Cocos2dxActivity {` 下插入以下代码:
   ```
   public static native void loadBank();
   public static native void playEvent(String path);
   public static native void stopEvent(String path);
   
   static
   {
    System.loadLibrary("fmod");
    System.loadLibrary("fmodstudio");
   }
   ```

#
## 接入iOS
1. 复制文件\
将`fmod_ios`、`media`复制到`proj.ios_mac`目录下。

2. 打开`*.xcodeproj`文件并打开`Build Settings`页。

3. 找到`Search Paths`下的`Header Search Paths`并加入以下代码：
   ```
   $(SRCROOT)/fmod_ios/header
   ```
4. 找到`Search Paths`下的`Library Search Paths`并加入以下代码:
   ```
   $(SRCROOT)/fmod_ios/lib/Release
   ```
5. 打开`Build Phases`下的`Link Binary With Libraries`。

6. 打开`proj.ios_mac/fmod_ios/lib/Release`将所有文件拖动到`Link Binary With Libraries`中。
   
   示例图：\
   ![ios_1](https://raw.githubusercontent.com/MostarChow/MCFMOD/main/README/ios_1.png)

7. 打开`proj.ios_mac/fmod_ios/MCFMOD`将所有文件拖动到`*.xcodeproj/Classes/ios`下。
   
   示例图：\
   ![ios_2](https://raw.githubusercontent.com/MostarChow/MCFMOD/main/README/ios_2.png)

8. 打开`*.xcodeproj/Classes/ios/AppController.mm`并引入`mostar_fmod_ios.hpp`。
   ```
   #import "mostar_fmod_ios.hpp"
   ```