#ifndef __JNI__MINS_FIELD__H__
#define __JNI__MINS_FIELD__H__

#include <jni.h>

JNIEXPORT void JNICALL Java_com_example_sapper_MinsField_init
        (JNIEnv *env, jobject obj, jlong rows, jlong cols, jlong mins);

JNIEXPORT jlong JNICALL Java_com_example_sapper_MinsField_getCountMins
        (JNIEnv *env, jobject obj);

JNIEXPORT jbyte JNICALL Java_com_example_sapper_MinsField_getCountMinsNear
        (JNIEnv *env, jobject obj, jlong row, jlong col);

JNIEXPORT jboolean JNICALL Java_com_example_sapper_MinsField_isMin
        (JNIEnv *env, jobject obj, jlong row, jlong col);

JNIEXPORT void JNICALL Java_com_example_sapper_MinsField_upFlag
        (JNIEnv *env, jobject obj, jlong row, jlong col);

JNIEXPORT void JNICALL Java_com_example_sapper_MinsField_downFlag
        (JNIEnv *env, jobject obj, jlong row, jlong col);

JNIEXPORT jboolean JNICALL Java_com_example_sapper_MinsField_isFlag
        (JNIEnv *env, jobject obj, jlong row, jlong col);

JNIEXPORT jlong JNICALL Java_com_example_sapper_MinsField_getCountRows
        (JNIEnv *env, jobject obj);

JNIEXPORT jlong JNICALL Java_com_example_sapper_MinsField_getCountCols
        (JNIEnv *env, jobject obj);

JNIEXPORT jboolean JNICALL Java_com_example_sapper_MinsField_isLive
        (JNIEnv *env, jobject obj);

JNIEXPORT jboolean JNICALL Java_com_example_sapper_MinsField_isVictory
        (JNIEnv *env, jobject obj);

JNIEXPORT jboolean JNICALL Java_com_example_sapper_MinsField_open
        (JNIEnv *env, jobject obj, jlong row, jlong col);

JNIEXPORT jboolean JNICALL Java_com_example_sapper_MinsField_isOpen
        (JNIEnv *env, jobject obj, jlong row, jlong col);

JNIEXPORT void JNICALL Java_com_example_sapper_MinsField_destroy
        (JNIEnv *env, jobject obj);


#endif