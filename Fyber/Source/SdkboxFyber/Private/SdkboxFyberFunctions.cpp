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
#include "AudioDevice.h"

#if PLATFORM_IOS
#include "IOSAppDelegate.h"
#import "FyberSDK.h"
#elif PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "AndroidApplication.h"
#endif

#if PLATFORM_IOS
@interface SdkboxFyberFunctionsDelegate : NSObject<FYBRewardedVideoControllerDelegate, FYBVirtualCurrencyClientDelegate, FYBCacheManagerDelegate>
{
}
@end

static SdkboxFyberFunctionsDelegate *sfd = nil;


@implementation SdkboxFyberFunctionsDelegate

+(void)load
{
    if (!sfd)
    {
        sfd = [[SdkboxFyberFunctionsDelegate alloc] init];
    }
}

-(void)rewardedVideoControllerDidReceiveVideo:(FYBRewardedVideoController *)rewardedVideoController
{
    UE_LOG(SDKBOX, Log, TEXT("did receive rewarded video"));
    
    USdkboxFyberComponent::OnBrandEngageClientReceiveOffersDelegate.Broadcast(true);
}

-(void)rewardedVideoController:(FYBRewardedVideoController *)rewardedVideoController didFailToReceiveVideoWithError:(NSError *)error
{
    UE_LOG(SDKBOX, Log, TEXT("did fail to receive rewarded video: error - %s"), *FString([error localizedDescription]));
    
    USdkboxFyberComponent::OnBrandEngageClientReceiveOffersDelegate.Broadcast(false);
}

-(void)rewardedVideoControllerDidStartVideo:(FYBRewardedVideoController *)rewardedVideoController
{
    UE_LOG(SDKBOX, Log, TEXT("started rewawarded video"));
    
    USdkboxFyberComponent::OnBrandEngageClientChangeStatusDelegate.Broadcast(EFyberRewardedVideoEnum::RWE_REWARDED_VIDEO_STARTED, "");
}

-(void)rewardedVideoController:(FYBRewardedVideoController *)rewardedVideoController didFailToStartVideoWithError:(NSError *)error
{
    UE_LOG(SDKBOX, Log, TEXT("failed to start rewarded video: error - %s"), *FString([error localizedDescription]));
    
    USdkboxFyberComponent::OnBrandEngageClientChangeStatusDelegate.Broadcast(EFyberRewardedVideoEnum::RWE_REWARDED_VIDEO_ERROR, "");
}

-(void)rewardedVideoController:(FYBRewardedVideoController *)rewardedVideoController didDismissVideoWithReason:(FYBRewardedVideoControllerDismissReason)reason
{
    switch (reason) {
        case FYBRewardedVideoControllerDismissReasonError:
            UE_LOG(SDKBOX, Log, TEXT("error dismissing video"));
            USdkboxFyberComponent::OnBrandEngageClientChangeStatusDelegate.Broadcast(EFyberRewardedVideoEnum::RWE_REWARDED_VIDEO_ERROR, "");
            break;
            
        case FYBRewardedVideoControllerDismissReasonUserEngaged:
            UE_LOG(SDKBOX, Log, TEXT("user engaged with video"));
            USdkboxFyberComponent::OnBrandEngageClientChangeStatusDelegate.Broadcast(EFyberRewardedVideoEnum::RWE_REWARDED_VIDEO_USER_ENGAGED, "");
            break;
            
        case FYBRewardedVideoControllerDismissReasonAborted:
            UE_LOG(SDKBOX, Log, TEXT("user aborted video"));
            USdkboxFyberComponent::OnBrandEngageClientChangeStatusDelegate.Broadcast(EFyberRewardedVideoEnum::RWE_REWARDED_VIDEO_ABORTED, "");
            break;
            
        default:
            UE_LOG(SDKBOX, Log, TEXT("rewarded video finished"));
            USdkboxFyberComponent::OnBrandEngageClientChangeStatusDelegate.Broadcast(EFyberRewardedVideoEnum::RWE_REWARDED_VIDEO_FINISHED, "");
            break;
    }
}

// Virtual currency callbacks
//
-(void)virtualCurrencyClient:(FYBVirtualCurrencyClient *)client didReceiveResponse:(FYBVirtualCurrencyResponse *)response
{
    UE_LOG(SDKBOX, Log, TEXT("received virtual currency reward id:%s, currency name:%s, delta of coins:%f, transactionId:%s"),
           *FString(response.currencyId), *FString(response.currencyName), response.deltaOfCoins, *FString(response.latestTransactionId));
    
    USdkboxFyberComponent::OnVirtualCurrencyConnectorSuccessDelegate.Broadcast(response.deltaOfCoins,
                                                                               FString(response.currencyId),
                                                                               FString(response.currencyName),
                                                                               "");
}

-(void)virtualCurrencyClient:(FYBVirtualCurrencyClient *)client didFailWithError:(NSError *)error
{
    UE_LOG(SDKBOX, Log, TEXT("failed to get currency reward %s"), *FString([error description]));
    
    USdkboxFyberComponent::OnVirtualCurrencyConnectorFailedDelegate.Broadcast(1,
                                                                              FString([[NSNumber numberWithInteger:error.code] stringValue]),
                                                                              FString(error.localizedDescription));
}

// Cache manager callbacks
//
-(void)cacheManagerDidCompletePrecachingWithVideosAvailable:(BOOL)videosAvailable
{
   UE_LOG(SDKBOX, Log, TEXT("completed pre-caching result: %d"), videosAvailable);
}

@end

#elif PLATFORM_ANDROID

// Video request errors
//
extern "C" void Java_com_epicgames_ue4_GameActivity_nativeFyberOnAdAvailable(JNIEnv* jenv, jobject thiz)
{
    USdkboxFyberComponent::OnBrandEngageClientReceiveOffersDelegate.Broadcast(true);
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeFyberOnAdNotAvailable(JNIEnv* jenv, jobject thiz)
{
    USdkboxFyberComponent::OnBrandEngageClientReceiveOffersDelegate.Broadcast(false);
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeFyberOnRequestError(JNIEnv* jenv, jobject thiz, jstring errorMessage)
{
    const char* sErrorMessage = jenv->GetStringUTFChars(errorMessage, 0);
    
    USdkboxFyberComponent::OnBrandEngageClientChangeStatusDelegate.Broadcast(EFyberRewardedVideoEnum::RWE_REWARDED_VIDEO_ERROR,
                                                                             FString(UTF8_TO_TCHAR(sErrorMessage)));
    
    jenv->ReleaseStringUTFChars(errorMessage, sErrorMessage);
}

// Video playing callbacks
//
extern "C" void Java_com_epicgames_ue4_GameActivity_nativeFyberShowRewardedVideo(JNIEnv* jenv, jobject thiz, jboolean wasVideoStarted)
{
    if (wasVideoStarted)
    {
        USdkboxFyberComponent::OnBrandEngageClientChangeStatusDelegate.Broadcast(EFyberRewardedVideoEnum::RWE_REWARDED_VIDEO_STARTED, "");
    }
    else
    {
        USdkboxFyberComponent::OnBrandEngageClientChangeStatusDelegate.Broadcast(EFyberRewardedVideoEnum::RWE_REWARDED_VIDEO_ERROR, "");
    }
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeFyberRewardedVideoFinished(JNIEnv* jenv, jobject thiz)
{
    USdkboxFyberComponent::OnBrandEngageClientChangeStatusDelegate.Broadcast(EFyberRewardedVideoEnum::RWE_REWARDED_VIDEO_FINISHED, "");
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeFyberRewardedVideoAborted(JNIEnv* jenv, jobject thiz)
{
    USdkboxFyberComponent::OnBrandEngageClientChangeStatusDelegate.Broadcast(EFyberRewardedVideoEnum::RWE_REWARDED_VIDEO_ABORTED, "");
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeFyberRewardedVideoError(JNIEnv* jenv, jobject thiz)
{
    USdkboxFyberComponent::OnBrandEngageClientChangeStatusDelegate.Broadcast(EFyberRewardedVideoEnum::RWE_REWARDED_VIDEO_ERROR, "");
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeFyberRewardedVideoUserEngaged(JNIEnv* jenv, jobject thiz)
{
    USdkboxFyberComponent::OnBrandEngageClientChangeStatusDelegate.Broadcast(EFyberRewardedVideoEnum::RWE_REWARDED_VIDEO_USER_ENGAGED, "");
}

// Virtual currency reward callbacks
//
extern "C" void Java_com_epicgames_ue4_GameActivity_nativeFyberVirtualCurrencyRewardOnRequestError(JNIEnv* jenv, jobject thiz, jstring errorMessage)
{
    const char* sErrorMessage = jenv->GetStringUTFChars(errorMessage, 0);
    
    USdkboxFyberComponent::OnVirtualCurrencyConnectorFailedDelegate.Broadcast(1,
                                                                              FString(""),
                                                                              FString(UTF8_TO_TCHAR(sErrorMessage)));
    
    jenv->ReleaseStringUTFChars(errorMessage, sErrorMessage);
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeFyberVirtualCurrencyRewardOnError
(
    JNIEnv* jenv,
    jobject thiz,
    jstring errorCode,
    jstring errorType,
    jstring errorMessage
)
{
    const char* sErrorCode    = jenv->GetStringUTFChars(errorCode,    0);
    const char* sErrorType    = jenv->GetStringUTFChars(errorType,    0);
    const char* sErrorMessage = jenv->GetStringUTFChars(errorMessage, 0);
    
    USdkboxFyberComponent::OnVirtualCurrencyConnectorFailedDelegate.Broadcast(1,
                                                                              FString(UTF8_TO_TCHAR(sErrorCode)),
                                                                              FString(UTF8_TO_TCHAR(sErrorMessage)));
    
    jenv->ReleaseStringUTFChars(errorCode,    sErrorCode);
    jenv->ReleaseStringUTFChars(errorType,    sErrorType);
    jenv->ReleaseStringUTFChars(errorMessage, sErrorMessage);
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeFyberVirtualCurrencyRewardOnSuccess
(
    JNIEnv* jenv,
    jobject thiz,
    jstring currencyId,
    jstring currencyName,
    jdouble deltaOfCoins,
    jstring latestTransactionId)
{
    const char* sCurrencyId          = jenv->GetStringUTFChars(currencyId,          0);
    const char* sCurrencyName        = jenv->GetStringUTFChars(currencyName,        0);
    const char* sLatestTransactionId = jenv->GetStringUTFChars(latestTransactionId, 0);
    
    USdkboxFyberComponent::OnVirtualCurrencyConnectorSuccessDelegate.Broadcast(deltaOfCoins,
                                                                               FString(sCurrencyId),
                                                                               FString(sCurrencyName),
                                                                               FString(sLatestTransactionId));

    jenv->ReleaseStringUTFChars(currencyId,          sCurrencyId);
    jenv->ReleaseStringUTFChars(currencyName,        sCurrencyName);
    jenv->ReleaseStringUTFChars(latestTransactionId, sLatestTransactionId);
}

#endif

void USdkboxFyberFunctions::FyberInitialize(const FString &appID, const FString &securityToken)
{
    const USdkboxFyberSettings* settings = GetDefault<USdkboxFyberSettings>();
  
    FString sAppID;
    FString sToken;
    
 #if PLATFORM_IOS
    sAppID = settings->AppIDiOS;
    sToken = settings->TokeniOS;
    
    if (sAppID.Len() == 0)
    {
        UE_LOG(SDKBOX, Warning, TEXT("No iOS app ID specified"));
    }
    else
    {
        UE_LOG(SDKBOX, Log, TEXT("Found iOS app ID:%s"), *sAppID);
    }
    
    if (sToken.Len() == 0)
    {
        UE_LOG(SDKBOX, Warning, TEXT("No iOS security token specified"));
    }
    else
    {
        UE_LOG(SDKBOX, Log, TEXT("Found iOS security token:%s"), *sToken);
    }
    
    dispatch_async(dispatch_get_main_queue(), ^{
        
        @try
        {
            if (settings->DebugEnable)
            {
                [FyberSDK setLoggingLevel:FYBLogLevelDebug];
            }
            else
            {
                [FyberSDK setLoggingLevel:FYBLogLevelOff];
            }
            
            [FyberSDK cacheManager].delegate = sfd;
            
            [FyberSDK instance].shouldShowToastOnReward = settings->ToastMessages;

            FYBSDKOptions *options = [FYBSDKOptions optionsWithAppId:sAppID.GetNSString() securityToken:sToken.GetNSString()];
            options.startVideoPrecaching = !settings->DisableVideoPreCaching;
            
            [FyberSDK startWithOptions:options];
        }
        @catch(NSException *e)
        {
            UE_LOG(SDKBOX, Error, TEXT("Error starting Fyber SDK:%s"), *FString([e description]));
        }
    });
    
#elif PLATFORM_ANDROID
    sAppID = settings->AppIDAndroid;
    sToken = settings->TokenAndroid;

    if (sAppID.Len() == 0)
    {
        UE_LOG(SDKBOX, Warning, TEXT("No Android app ID specified"));
    }
    
    if (sToken.Len() == 0)
    {
        UE_LOG(SDKBOX, Warning, TEXT("No Android security token specified"));
    }
    
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        static jmethodID Method = FJavaWrapper::FindMethod(Env,
                                                           FJavaWrapper::GameActivityClassID,
                                                           "AndroidThunkJava_FyberInit",
                                                           "(Ljava/lang/String;Ljava/lang/String;)V",
                                                           false);
        
        jstring jAppID         = Env->NewStringUTF(TCHAR_TO_UTF8(*sAppID));
        jstring jSecurityToken = Env->NewStringUTF(TCHAR_TO_UTF8(*sToken));
        
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, jAppID, jSecurityToken);
        
        Env->DeleteLocalRef(jAppID);
        Env->DeleteLocalRef(jSecurityToken);
    }
#else
    UE_LOG(SDKBOX, Warning, TEXT("Cannot run Fyber on this platform"));
#endif
}

void USdkboxFyberFunctions::FyberShowOfferWall()
{
#if PLATFORM_IOS
#elif PLATFORM_ANDROID
#endif
}

void USdkboxFyberFunctions::FyberRequestRewardedVideo(const FString& placementId)
{
#if PLATFORM_IOS
    dispatch_async(dispatch_get_main_queue(), ^{
        FYBRewardedVideoController *rewardedVideoController   = [FyberSDK rewardedVideoController];
        rewardedVideoController.virtualCurrencyClientDelegate = sfd;
        rewardedVideoController.delegate                      = sfd;
        
        [rewardedVideoController requestVideo];
        
        UE_LOG(SDKBOX, Log, TEXT("requesting rewarded video..."));
    });
    
#elif PLATFORM_ANDROID
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
#else
    USdkboxFyberComponent::OnBrandEngageClientReceiveOffersDelegate.Broadcast(false);
#endif
}

void USdkboxFyberFunctions::FyberShowRewardedVideo()
{
#if PLATFORM_IOS
    dispatch_async(dispatch_get_main_queue(), ^{
        FYBRewardedVideoController *rewardedVideoController   = [FyberSDK rewardedVideoController];
        rewardedVideoController.virtualCurrencyClientDelegate = sfd;
        rewardedVideoController.delegate                      = sfd;
     
        [rewardedVideoController presentRewardedVideoFromViewController:(UIViewController *)[IOSAppDelegate GetDelegate].IOSController];
        
        UE_LOG(SDKBOX, Log, TEXT("showing rewarded video..."));
    });
        
#elif PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        static jmethodID Method = FJavaWrapper::FindMethod(Env,
                                                           FJavaWrapper::GameActivityClassID,
                                                           "AndroidThunkJava_FyberShowRewardedVideo",
                                                           "()V",
                                                           false);
        
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method);
    }
#else
    USdkboxFyberComponent::OnBrandEngageClientChangeStatusDelegate.Broadcast(EFyberRewardedVideoEnum::RWE_REWARDED_VIDEO_ERROR, "");
#endif
}

void USdkboxFyberFunctions::FyberRequestInterstitial()
{
#if PLATFORM_IOS
#elif PLATFORM_ANDROID
#else
#endif
}

void USdkboxFyberFunctions::FyberShowInterstitial()
{
#if PLATFORM_IOS
#elif PLATFORM_ANDROID
#else
#endif
}

void USdkboxFyberFunctions::FyberRequestDeltaOfCoins(const FString& currencyId)
{
#if PLATFORM_IOS
#elif PLATFORM_ANDROID
#else
#endif
}

