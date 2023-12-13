#include <jni.h>
#include <string>
#include <android/bitmap.h>
#include <android/log.h>
#include <cstdio>

#define LOG_TAG "libass_jni"


extern "C" JNIEXPORT jstring

JNICALL
Java_com_example_myapplication_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {

    std::string hello = "Hello from C+++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT int JNICALL
Java_com_example_myapplication_MainActivity_createTestBitmap(JNIEnv *env, jobject thiz,
                                                             jobject bitmap) {
    AndroidBitmapInfo info;
    void* pixels;
    int ret = AndroidBitmap_getInfo(env, bitmap, &info);

    if (ret) {
        __android_log_print(ANDROID_LOG_ERROR, "TEST", "Couldn't fetch info from AndroidBitmap_getInfo\n");
        return ret;
    }

    if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "The bitmap isn't Bitmap.Config.ARGB_8888\n");
        return -1;
    }

    ret = AndroidBitmap_lockPixels(env, bitmap, &pixels);
    if (ret) {
        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Couldn't lock the bitmap pixel via AndroidBitmap_lockPixels\n");
        return ret;
    }

    uint32_t* pixels_int = (uint32_t *) pixels;
    pixels_int[0] = 255 << 16;

    for (int y = 0; y < info.height; y++) {
        for (int x = 0; x < info.width; x++) {
            int A = 255;
            int R = 255;
            int G = 0;
            int B = 0;
            pixels_int[x] = (R & 0xff) << 24 | (G & 0xff) << 16 | (B & 0xff) << 8 | (A & 0xff);

        }
        pixels_int += info.width;
    }

    ret = AndroidBitmap_unlockPixels(env, bitmap);
    if (ret) {
        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Couldn't unlock the bitmap pixel via AndroidBitmap_unlockPixels\n");
        return -1;
    }

    return 0;
}