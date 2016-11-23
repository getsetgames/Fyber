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

#if PLATFORM_IOS
@interface SdkboxFyberFunctionsDelegate : NSObject<FYBRewardedVideoControllerDelegate, FYBVirtualCurrencyClientDelegate, FYBCacheManagerDelegate>
{
    
}
@end

static SdkboxFyberFunctionsDelegate *sfd = [[SdkboxFyberFunctionsDelegate alloc] init];


@implementation SdkboxFyberFunctionsDelegate

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
    USdkboxFyberFunctions::PushVolumeChange();
}

-(void)rewardedVideoController:(FYBRewardedVideoController *)rewardedVideoController didFailToStartVideoWithError:(NSError *)error
{
    UE_LOG(SDKBOX, Log, TEXT("failed to start rewarded video: error - %s"), *FString([error localizedDescription]));
    
    USdkboxFyberComponent::OnBrandEngageClientChangeStatusDelegate.Broadcast(EFyberRewardedVideoEnum::RWE_REWARDED_VIDEO_ERROR, "");
    USdkboxFyberFunctions::PopVolumeChange();
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
   UE_LOG(SDKBOX, Log, TEXT("completing pre-caching result: %d"), videosAvailable);
}

@end

#endif

void USdkboxFyberFunctions::FyberInitialize(const FString &appID, const FString &securityToken)
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

