//
//  MyTarget.h
//
//  Created by Vasiliy on 10.11.17.
//
//

#ifndef MyTarget_h
#define MyTarget_h

#include "base/ccConfig.h"
#include "jsapi.h"
#include "jsfriendapi.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>

void register_all_mytarget_framework(JSContext* cx, JS::HandleObject obj);

extern "C"
{
    void Java_org_cocos2dx_javascript_MyTargetPlugin_callbackResult(JNIEnv* env, jobject thiz, jint callbackId, jstring err, jstring result);
};

#endif /* MyTarget_h */
