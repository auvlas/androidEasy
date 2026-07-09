#ifndef __JNI__GENERAL__H__
#define __JNI__GENERAL__H__

#include <jni.h>
#include "cell/cell.h"

void * getPtr(JNIEnv *env, jobject obj);

void setPtr(JNIEnv *env, jobject obj, void * ptr);


#endif
