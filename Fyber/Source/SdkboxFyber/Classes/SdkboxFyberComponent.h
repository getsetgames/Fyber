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

#pragma once

#include "SdkboxFyberComponent.generated.h"

UENUM(BlueprintType)
enum class EFyberInterstitialEnum : uint8
{
    ISE_INTERSTITIAL_PRESENTED    = 1 UMETA(DisplayName="InterstitialPresented"),
    ISE_INTERSTITIAL_DISMISSED    = 2 UMETA(DisplayName="InterstitialDismissed"),
    ISE_INTERSTITIAL_ERROR        = 3 UMETA(DisplayName="InterstitialError"),
    ISE_INTERSTITIAL_USER_ENGAGED = 4 UMETA(DisplayName="InterstitialUserEngaged")
};

UENUM(BlueprintType)
enum class EFyberOfferWallEnum : uint8
{
    OWE_OFFERWALL_PRESENTED = 1 UMETA(DisplayName="OfferWallPresented"),
	OWE_OFFERWALL_DISMISSED = 2 UMETA(DisplayName="OfferWallDismissed"),
	OWE_OFFERWALL_ERROR     = 3 UMETA(DisplayName="OfferWallError")
};

UENUM(BlueprintType)
enum class EFyberRewardedVideoEnum : uint8
{
    RWE_REWARDED_VIDEO_STARTED      = 1 UMETA(DisplayName="RewardedVideoStarted"),
    RWE_REWARDED_VIDEO_FINISHED     = 2 UMETA(DisplayName="RewardedVideoFinished"),
    RWE_REWARDED_VIDEO_ERROR        = 3 UMETA(DisplayName="RewardedVideoError"),
    RWE_REWARDED_VIDEO_ABORTED      = 4 UMETA(DisplayName="RewardedVideoAborted"),
    RWE_REWARDED_VIDEO_USER_ENGAGED = 5 UMETA(DisplayName="RewardedVideoUserEngaged")
};

UCLASS(ClassGroup=SDKBOX, HideCategories=(Activation, "Components|Activation", Collision), meta=(BlueprintSpawnableComponent))
class USdkboxFyberComponent
    : public UActorComponent
{
	GENERATED_BODY()
	
public:
            
    USdkboxFyberComponent(const FObjectInitializer& ObjectInitializer);
    
    void OnRegister() override;
    void OnUnregister() override;

    DECLARE_MULTICAST_DELEGATE(FVoidDelegate);
    DECLARE_MULTICAST_DELEGATE_OneParam(FOfferWallEnumDelegate, EFyberOfferWallEnum);
    DECLARE_MULTICAST_DELEGATE_OneParam(FBoolDelegate, bool);
   	DECLARE_MULTICAST_DELEGATE_OneParam(FStringDelegate, const FString&);
    DECLARE_MULTICAST_DELEGATE_TwoParams(FRewardedVideoDelegate, bool, const FString&);
    DECLARE_MULTICAST_DELEGATE_TwoParams(FRewardedVideoEnumDelegate, EFyberRewardedVideoEnum, const FString&);
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FVirtualCurrencyConnectorFailedDelegate, int32, const FString&, const FString&);
	DECLARE_MULTICAST_DELEGATE_FourParams(FVirtualCurrencyConnectorSuccessDelegate, float, const FString&, const FString&, const FString&);

	static FVirtualCurrencyConnectorFailedDelegate  OnVirtualCurrencyConnectorFailedDelegate;
	static FVirtualCurrencyConnectorSuccessDelegate OnVirtualCurrencyConnectorSuccessDelegate;
	static FBoolDelegate                            OnCanShowInterstitialDelegate;
	static FVoidDelegate                            OnInterstitialDidShowDelegate;
	static FStringDelegate                          OnInterstitialDismissDelegate;
	static FVoidDelegate                            OnInterstitialFailedDelegate;
	static FRewardedVideoDelegate                   OnBrandEngageClientReceiveOffersDelegate;
	static FRewardedVideoEnumDelegate               OnBrandEngageClientChangeStatusDelegate;
	static FOfferWallEnumDelegate                   OnOfferWallFinishDelegate;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDynVoidDelegate);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDynOfferWallEnumDelegate, EFyberOfferWallEnum, Status);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDynBoolDelegate, bool, Yes);
   	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDynStringDelegate, const FString&, Message);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDynRewardedVideoDelegate, bool, areOffersAvailable, const FString&, ResultMessage);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDynRewardedVideoEnumDelegate, EFyberRewardedVideoEnum, Status, const FString&, Message);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDynVirtualCurrencyConnectorFailedDelegate, int32, Error, const FString&, ErrorCode, const FString&, Message);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FDynVirtualCurrencyConnectorSuccessDelegate, float, DeltaOfCoins, const FString&, CurrencyId, const FString&, CurrencyName, const FString&, TransactionId);

    UPROPERTY(BlueprintAssignable)
	FDynVirtualCurrencyConnectorFailedDelegate      OnVirtualCurrencyConnectorFailed;

    UPROPERTY(BlueprintAssignable)
	FDynVirtualCurrencyConnectorSuccessDelegate     OnVirtualCurrencyConnectorSuccess;

    UPROPERTY(BlueprintAssignable)
	FDynBoolDelegate                                OnCanShowInterstitial;

    UPROPERTY(BlueprintAssignable)
	FDynVoidDelegate                                OnInterstitialDidShow;

    UPROPERTY(BlueprintAssignable)
	FDynStringDelegate                              OnInterstitialDismiss;

    UPROPERTY(BlueprintAssignable)
	FDynVoidDelegate                                OnInterstitialFailed;

    UPROPERTY(BlueprintAssignable)
    FDynRewardedVideoDelegate                       OnBrandEngageClientReceiveOffers;

    UPROPERTY(BlueprintAssignable)
	FDynRewardedVideoEnumDelegate                   OnBrandEngageClientChangeStatus;

    UPROPERTY(BlueprintAssignable)
	FDynOfferWallEnumDelegate                       OnOfferWallFinish;

protected:

	void OnVirtualCurrencyConnectorFailedDelegate_Handler(int32 error, const FString& errorCode, const FString& message) {OnVirtualCurrencyConnectorFailed.Broadcast(error, errorCode, message);}
	void OnVirtualCurrencyConnectorSuccessDelegate_Handler(float deltaOfCoins, const FString& currencyId, const FString& currencyName, const FString& transactionId) {OnVirtualCurrencyConnectorSuccess.Broadcast(deltaOfCoins, currencyId, currencyName, transactionId);}
	void OnCanShowInterstitialDelegate_Handler(bool canShowInterstitial) {OnCanShowInterstitial.Broadcast(canShowInterstitial);};
	void OnInterstitialDidShowDelegate_Handler() {OnInterstitialDidShow.Broadcast();};
	void OnInterstitialDismissDelegate_Handler(const FString& reason) {OnInterstitialDismiss.Broadcast(reason);};
	void OnInterstitialFailedDelegate_Handler() {OnInterstitialFailed.Broadcast();};
	void OnBrandEngageClientReceiveOffersDelegate_Handler(bool areOffersAvailable, const FString& message) {OnBrandEngageClientReceiveOffers.Broadcast(areOffersAvailable, message);};
	void OnBrandEngageClientChangeStatusDelegate_Handler(EFyberRewardedVideoEnum status, const FString& message) {OnBrandEngageClientChangeStatus.Broadcast(status, message);};
	void OnOfferWallFinishDelegate_Handler(EFyberOfferWallEnum status) {OnOfferWallFinish.Broadcast(status);};
};
