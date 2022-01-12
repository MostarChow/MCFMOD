# MCFMOD
封装FMOD

#
## 接入Android
1. 复制文件\
将`fmod_android`、`media`、`mostar_fmod.cpp`复制到`proj.android-studio/jni`目录下。
2. 编辑`proj.android-studio/jni/CocosAndroid.mk`文件。\

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

3. 编辑`proj.android-studio/app/build.gradle`文件。\

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
