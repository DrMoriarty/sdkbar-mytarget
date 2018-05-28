//
//  MyTarget.m
//
//  Created by Vasiliy on 10.11.17.
//
//

#include "MyTarget.h"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "scripting/js-bindings/manual/js_manual_conversions.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <sstream>
#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "utils/PluginUtils.h"

static void cpp_callbackResult(int callbackId, std::string errorStr, std::string resultStr);

static void printLog(const char* str) {
    CCLOG("%s", str);
}

static bool pluginMethod0(const char* method) {
    cocos2d::JniMethodInfo methodInfo;

    if (! cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/javascript/MyTargetPlugin", method, "()Z")) {
        return false;
    }
    bool res = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
    return res;
}

static bool pluginMethod1(const char* method, int param) {
    cocos2d::JniMethodInfo methodInfo;

    if (! cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/javascript/MyTargetPlugin", method, "(I)Z")) {
        return false;
    }
    bool res = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, param);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
    return true;
}

static bool pluginMethod1(const char* method, bool param) {
    cocos2d::JniMethodInfo methodInfo;

    if (! cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/javascript/MyTargetPlugin", method, "(Z)Z")) {
        return false;
    }
    bool res = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, param);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
    return true;
}

static bool pluginMethod2(const char* method, int param, int callbackId) {
    cocos2d::JniMethodInfo methodInfo;

    if (! cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/javascript/MyTargetPlugin", method, "(II)Z")) {
        return false;
    }
    bool res = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, param, callbackId);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
    return true;
}

static bool jsb_mytarget_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    printLog("jsb_mytarget_init");
    JSAutoRequest rq(cx);
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CCLOG("init, param count:%d.\n", argc);
    JS::CallReceiver rec = JS::CallReceiverFromVp(vp);
    bool ok = true;
    if(argc == 0) {
        if (pluginMethod0("init")) {
            rec.rval().set(JSVAL_TRUE);
        } else {
            rec.rval().set(JSVAL_FALSE);
        }
        return true;
    } else {
        JS_ReportError(cx, "Invalid number of arguments");
        return false;
    }
}

static bool jsb_mytarget_loadBanner(JSContext *cx, uint32_t argc, jsval *vp)
{
    printLog("jsb_mytarget_loadBanner");
    JSAutoRequest rq(cx);
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    CCLOG("init, param count:%d.\n", argc);
    JS::CallReceiver rec = JS::CallReceiverFromVp(vp);
    bool ok = true;
    if(argc == 3) {
        // param, callback, this
        CallbackFrame *loginCallback = new CallbackFrame(cx, obj, args.get(2), args.get(1));

        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *) & arg0);

        if (pluginMethod2("loadBanner", arg0, loginCallback->callbackId)) {
            rec.rval().set(JSVAL_TRUE);
        } else {
            rec.rval().set(JSVAL_FALSE);
        }
    } else {
        JS_ReportError(cx, "Invalid number of arguments");
        return false;
    }
    return true;
}

static bool jsb_mytarget_showBanner(JSContext *cx, uint32_t argc, jsval *vp)
{
    printLog("jsb_mytarget_showBanner");
    JSAutoRequest rq(cx);
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    JS::CallReceiver rec = JS::CallReceiverFromVp(vp);
    if(argc == 2) {
        CallbackFrame *cb = new CallbackFrame(cx, obj, args.get(1), args.get(0));
        if(pluginMethod1("showBanner", cb->callbackId)) {
            rec.rval().set(JSVAL_TRUE);
        } else {
            rec.rval().set(JSVAL_FALSE);
        }
        return true;
    } else {
        JS_ReportError(cx, "Invalid number of arguments");
        return false;
    }
}

static bool jsb_mytarget_removeBanner(JSContext *cx, uint32_t argc, jsval *vp)
{
    printLog("jsb_mytarget_removeBanner");
    JSAutoRequest rq(cx);
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    JS::CallReceiver rec = JS::CallReceiverFromVp(vp);
    if(argc == 2) {
        CallbackFrame *cb = new CallbackFrame(cx, obj, args.get(1), args.get(0));


        if (pluginMethod1("removeBanner", cb->callbackId)) {
            rec.rval().set(JSVAL_TRUE);
        } else {
            rec.rval().set(JSVAL_FALSE);
        }
        return true;
    } else {
        JS_ReportError(cx, "Invalid number of arguments");
        return false;
    }
}

static bool jsb_mytarget_loadFullScreen(JSContext *cx, uint32_t argc, jsval *vp)
{
    printLog("jsb_mytarget_loadFullScreen");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    JS::CallReceiver rec = JS::CallReceiverFromVp(vp);
    bool ok = true;
    if(argc == 3) {
        // params, callback function & this
        CallbackFrame *cb = new CallbackFrame(cx, obj, args.get(2), args.get(1));
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *) & arg0);

        if (pluginMethod2("loadFullScreen", arg0, cb->callbackId)) {
            rec.rval().set(JSVAL_TRUE);
        } else {
            rec.rval().set(JSVAL_FALSE);
        }
        return true;
    } else {
        JS_ReportError(cx, "Invalid number of arguments");
        return false;
    }
}

static bool jsb_mytarget_showFullScreen(JSContext *cx, uint32_t argc, jsval *vp)
{
    printLog("jsb_mytarget_showFullScreen");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    JS::CallReceiver rec = JS::CallReceiverFromVp(vp);
    if(argc == 2) {
        // callback, this
        CallbackFrame *cb = new CallbackFrame(cx, obj, args.get(1), args.get(0));
        if(pluginMethod1("showFullScreen", cb->callbackId)) {
            rec.rval().set(JSVAL_TRUE);
        } else {
            rec.rval().set(JSVAL_FALSE);
        }
        return true;
    } else {
        JS_ReportError(cx, "Invalid number of arguments");
        return false;
    }
}

static bool jsb_mytarget_setUserConsent(JSContext *cx, uint32_t argc, jsval *vp)
{
    printLog("jsb_mytarget_setUserConsent");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    JS::CallReceiver rec = JS::CallReceiverFromVp(vp);
    if(argc == 1) {
        // callback, this
        bool arg0 = false;
        //ok &= jsval_to_bool(cx, args.get(0), (bool *) &arg0);
        
        if(pluginMethod1("setUserConsent", JS::ToBoolean(args.get(0)))) {
            rec.rval().set(JSVAL_TRUE);
        } else {
            rec.rval().set(JSVAL_FALSE);
        }
        return true;
    } else {
        JS_ReportError(cx, "Invalid number of arguments");
        return false;
    }
}

static bool jsb_mytarget_setUserAgeRestricted(JSContext *cx, uint32_t argc, jsval *vp)
{
    printLog("jsb_mytarget_setUserAgeRestricted");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    JS::CallReceiver rec = JS::CallReceiverFromVp(vp);
    if(argc == 1) {
        // callback, this
        bool arg0 = false;
        //ok &= jsval_to_bool(cx, args.get(0), (bool *) &arg0);
        
        if(pluginMethod1("setUserAgeRestricted", JS::ToBoolean(args.get(0)))) {
            rec.rval().set(JSVAL_TRUE);
        } else {
            rec.rval().set(JSVAL_FALSE);
        }
        return true;
    } else {
        JS_ReportError(cx, "Invalid number of arguments");
        return false;
    }
}

void register_all_mytarget_framework(JSContext* cx, JS::HandleObject obj)
{
    printLog("register_all_mytarget_framework");
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "mytarget", &ns);

    JS_DefineFunction(cx, ns, "init", jsb_mytarget_init, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ns, "loadBanner", jsb_mytarget_loadBanner, 3, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ns, "showBanner", jsb_mytarget_showBanner, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ns, "removeBanner", jsb_mytarget_removeBanner, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ns, "loadFullScreen", jsb_mytarget_loadFullScreen, 3, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ns, "showFullScreen", jsb_mytarget_showFullScreen, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ns, "setUserConsent", jsb_mytarget_setUserConsent, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ns, "serUserAgeRestricted", jsb_mytarget_setUserAgeRestricted, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);

}

static void cpp_callbackResult(int callbackId, std::string errorStr, std::string resultStr)
{
    cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([callbackId, errorStr, resultStr] {
            CallbackFrame *cb = CallbackFrame::getById(callbackId);
            if(!cb) {
                printLog("callbackResult: callbackId not found!");
                return;
            }

            JSAutoRequest rq(cb->cx);
            JSAutoCompartment ac(cb->cx, cb->_ctxObject.ref());

            JS::AutoValueVector valArr(cb->cx);
            if(resultStr.size() > 0) {
                valArr.append(JSVAL_NULL);
                valArr.append(std_string_to_jsval(cb->cx, resultStr));
            } else {
                valArr.append(std_string_to_jsval(cb->cx, errorStr));
                valArr.append(JSVAL_NULL);
            };
            JS::HandleValueArray funcArgs = JS::HandleValueArray::fromMarkedLocation(2, valArr.begin());
            cb->call(funcArgs);
            printLog("requestResult finished");
            delete cb;
        });
}

void Java_org_cocos2dx_javascript_MyTargetPlugin_callbackResult(JNIEnv* env, jobject thiz, jint callbackId, jstring err, jstring result)
{
    printLog("Get requestResult");
    std::string s_err;
    std::string s_res;
    if(result != NULL) {
        const char* ch = env->GetStringUTFChars(result, NULL);
        s_res = ch;
        env->ReleaseStringUTFChars(result, ch);
    }
    if(err != NULL) {
        const char* ch = env->GetStringUTFChars(err, NULL);
        s_err = ch;
        env->ReleaseStringUTFChars(err, ch);
    }

    cpp_callbackResult(callbackId, s_err, s_res);
}
