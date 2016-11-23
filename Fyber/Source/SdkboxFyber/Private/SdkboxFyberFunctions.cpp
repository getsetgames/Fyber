/****************************************************************************
 Copyright (c) 2015 SDKBOX Inc.
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "SdkboxFyberPrivatePCH.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "AndroidApplication.h"
#endif


void USdkboxFyberFunctions::FyberInitialize(const FString &appID, const FString &securityToken)
{
#if PLATFORM_IOS || PLATFORM_ANDROID
    //sdkbox::PluginFyber::init("123", TCHAR_TO_ANSI(*_SettingsToJSONString()));
    
    
    // public void AndroidThunkJava_FyberInit(java.lang.String, java.lang.String);
    // descriptor: (Ljava/lang/String;Ljava/lang/String;)V
    
//    if (!_FyberListener)
//    {
//        _FyberListener = NewObject<USdkboxFyberListener>(USdkboxFyberListener::StaticClass());
//        sdkbox::PluginFyber::setListener(_FyberListener);
//    }
#endif

#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        static jmethodID Method = FJavaWrapper::FindMethod(Env,
                                                           FJavaWrapper::GameActivityClassID,
                                                           "AndroidThunkJava_FyberInit",
                                                           "(Ljava/lang/String;Ljava/lang/String;)V",
                                                           false);
        

        jstring jAppID         = Env->NewStringUTF(TCHAR_TO_UTF8(*appID));
        jstring jSecurityToken = Env->NewStringUTF(TCHAR_TO_UTF8(*securityToken));
        
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, jAppID, jSecurityToken);
        
        Env->DeleteLocalRef(jAppID);
        Env->DeleteLocalRef(jSecurityToken);
    }
#endif
    
    
}

void USdkboxFyberFunctions::FyberShutdown()
{
#if PLATFORM_IOS || PLATFORM_ANDROID
    if (_FyberListener && _FyberListener->IsValidLowLevel())
    {
        _FyberListener->ConditionalBeginDestroy();
        _FyberListener = nullptr;
    }
#endif
}

void USdkboxFyberFunctions::FyberShowOfferWall()
{
#if PLATFORM_IOS || PLATFORM_ANDROID
	//sdkbox::PluginFyber::showOfferWall();
#endif
}

void USdkboxFyberFunctions::FyberRequestRewardedVideo(const FString& placementId)
{
#if PLATFORM_IOS || PLATFORM_ANDROID
	//sdkbox::PluginFyber::requestRewardedVideo(TCHAR_TO_ANSI(*placementId));
#endif
    
//AndroidThunkJava_FyberRequestVideo
    
    
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        static jmethodID Method = FJavaWrapper::FindMethod(Env,
                                                           FJavaWrapper::GameActivityClassID,
                                                           "AndroidThunkJava_FyberRequestVideo",
                                                           "(Ljava/lang/String;)V",
                                                           false);
        
        jstring jPlacementId = Env->NewStringUTF(TCHAR_TO_UTF8(*placementId));

        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, jPlacementId);
        
        Env->DeleteLocalRef(jPlacementId);
    }
#endif
    
}

void USdkboxFyberFunctions::FyberShowRewardedVideo()
{
#if PLATFORM_IOS || PLATFORM_ANDROID
	//sdkbox::PluginFyber::showRewardedVideo();
#endif
}

void USdkboxFyberFunctions::FyberRequestInterstitial()
{
#if PLATFORM_IOS || PLATFORM_ANDROID
	//sdkbox::PluginFyber::requestInterstitial();
#endif
}

void USdkboxFyberFunctions::FyberShowInterstitial()
{
#if PLATFORM_IOS || PLATFORM_ANDROID
	//sdkbox::PluginFyber::showInterstitial();
#endif
}

void USdkboxFyberFunctions::FyberRequestDeltaOfCoins(const FString& currencyId)
{
#if PLATFORM_IOS || PLATFORM_ANDROID
	//sdkbox::PluginFyber::requestDeltaOfCoins(TCHAR_TO_ANSI(*currencyId));
#endif
}

{


}

