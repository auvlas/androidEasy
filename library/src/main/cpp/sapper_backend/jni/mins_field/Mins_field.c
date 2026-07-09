#include <jni.h>
#include "Mins_field.h"
#include "mins_field/mins_field.h"
#include "general/General.h"

JNIEXPORT void JNICALL Java_com_example_sapper_MinsField_init
        (JNIEnv *env, jobject obj, jlong rows, jlong cols, jlong mins) {
    setPtr(env, obj, (void *)init_mins_field((size_t)rows, (size_t)cols, (size_t)mins));
}

JNIEXPORT jlong JNICALL Java_com_example_sapper_MinsField_getCountMins
        (JNIEnv *env, jobject obj) {
    return (jlong) get_count_mins_mins_field(getPtr(env, obj));
}

JNIEXPORT jbyte JNICALL Java_com_example_sapper_MinsField_getCountMinsNear
        (JNIEnv *env, jobject obj, jlong row, jlong col) {
    return (jbyte) get_count_mins_cell_mins_field(getPtr(env, obj), (size_t)row, (size_t)col);
}

JNIEXPORT jboolean JNICALL Java_com_example_sapper_MinsField_isMin
        (JNIEnv *env, jobject obj, jlong row, jlong col) {
    return (jboolean) is_min_cell_mins_field(getPtr(env, obj), (size_t)row, (size_t)col);
}

JNIEXPORT void JNICALL Java_com_example_sapper_MinsField_upFlag
        (JNIEnv *env, jobject obj, jlong row, jlong col) {
    up_flag_cell_mins_field(getPtr(env, obj), (size_t)row, (size_t)col);
}

JNIEXPORT void JNICALL Java_com_example_sapper_MinsField_downFlag
        (JNIEnv *env, jobject obj, jlong row, jlong col) {
    down_flag_cell_mins_field(getPtr(env, obj), (size_t) row, (size_t) col);
}

JNIEXPORT jboolean JNICALL Java_com_example_sapper_MinsField_isFlag
        (JNIEnv *env, jobject obj, jlong row, jlong col) {
    return (jboolean) is_flag_cell_mins_field(getPtr(env, obj), (size_t)row, (size_t)col);
}

JNIEXPORT jlong JNICALL Java_com_example_sapper_MinsField_getCountRows
        (JNIEnv *env, jobject obj) {
    return (jlong)get_rows_mins_field(getPtr(env, obj));
}

JNIEXPORT jlong JNICALL Java_com_example_sapper_MinsField_getCountCols
        (JNIEnv *env, jobject obj) {
    return (jlong)get_columns_mins_field(getPtr(env, obj));
}

JNIEXPORT jboolean JNICALL Java_com_example_sapper_MinsField_isLive
        (JNIEnv *env, jobject obj) {
    return (jboolean) get_is_live_mins_field(getPtr(env, obj));
}

JNIEXPORT jboolean JNICALL Java_com_example_sapper_MinsField_isVictory
        (JNIEnv *env, jobject obj) {
    return (jboolean) is_victory_mins_field(getPtr(env, obj));
}

JNIEXPORT jlong JNICALL Java_com_example_sapper_MinsField_getCountEmpty
        (JNIEnv *env, jobject obj) {
    return (jlong) get_count_empty_mins_field(getPtr(env, obj));
}

JNIEXPORT jlong JNICALL Java_com_example_sapper_MinsField_getCountEmptyOpen
        (JNIEnv *env, jobject obj) {
    return (jlong) get_count_empty_open_mins_field(getPtr(env, obj));
}

JNIEXPORT jlong JNICALL Java_com_example_sapper_MinsField_getCountEmptyClose
        (JNIEnv *env, jobject obj) {
    return (jlong) get_count_empty_close_mins_field(getPtr(env, obj));
}

JNIEXPORT jbyte JNICALL Java_com_example_sapper_MinsField_getPercentVictory
        (JNIEnv *env, jobject obj) {
    return (jlong) get_percent_victory_mins_field(getPtr(env, obj));
}

JNIEXPORT jboolean JNICALL Java_com_example_sapper_MinsField_open
        (JNIEnv *env, jobject obj, jlong row, jlong col) {
    return (jboolean) open_cell_mins_field(getPtr(env, obj), row, col);
}

JNIEXPORT jboolean JNICALL Java_com_example_sapper_MinsField_isOpen
        (JNIEnv *env, jobject obj, jlong row, jlong col) {
    return (jboolean) is_open_cell_mins_field(getPtr(env, obj), row, col);
}

JNIEXPORT void JNICALL Java_com_example_sapper_MinsField_destroy
        (JNIEnv *env, jobject obj) {
    destroy_mins_field(getPtr(env, obj));
}