#include <jni.h>
#include "cell/cell.h"

void * getPtr(JNIEnv *env, jobject obj) {
    jclass cls = (*env)->GetObjectClass(env, obj);
    jfieldID fid = (*env)->GetFieldID(env, cls, "m_nativePtr", "J");
    return (void *)(*env)->GetLongField(env, obj, fid);
}

void setPtr(JNIEnv *env, jobject obj, void * ptr) {
    jclass cls = (*env)->GetObjectClass(env, obj);
    jfieldID fid = (*env)->GetFieldID(env, cls, "m_nativePtr", "J");
    return (*env)->SetLongField(env, obj, fid, (jlong)ptr);
}