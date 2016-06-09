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

class USdkboxFyberListener;

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
    DECLARE_MULTICAST_DELEGATE_OneParam(FIntDelegate, int32);
    DECLARE_MULTICAST_DELEGATE_OneParam(FBoolDelegate, bool);
   	DECLARE_MULTICAST_DELEGATE_OneParam(FStringDelegate, const FString&);
    DECLARE_MULTICAST_DELEGATE_TwoParams(FIntStringDelegate, int32, const FString&);
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FVirtualCurrencyConnectorFailedDelegate, int32, const FString&, const FString&);
	DECLARE_MULTICAST_DELEGATE_FourParams(FVirtualCurrencyConnectorSuccessDelegate, float, const FString&, const FString&, const FString&);

	static FVirtualCurrencyConnectorFailedDelegate  OnVirtualCurrencyConnectorFailedDelegate;
	static FVirtualCurrencyConnectorSuccessDelegate OnVirtualCurrencyConnectorSuccessDelegate;
	static FBoolDelegate                            OnCanShowInterstitialDelegate;
	static FVoidDelegate                            OnInterstitialDidShowDelegate;
	static FStringDelegate                          OnInterstitialDismissDelegate;
	static FVoidDelegate                            OnInterstitialFailedDelegate;
	static FBoolDelegate                            OnBrandEngageClientReceiveOffersDelegate;
	static FIntStringDelegate                       OnBrandEngageClientChangeStatusDelegate;
	static FIntDelegate                             OnOfferWallFinishDelegate;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDynVoidDelegate);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDynIntDelegate, int32, Status);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDynBoolDelegate, bool, Yes);
   	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDynStringDelegate, const FString&, Message);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDynIntStringDelegate, int32, Status, const FString&, Message);
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
	FDynBoolDelegate                                OnBrandEngageClientReceiveOffers;

    UPROPERTY(BlueprintAssignable)
	FDynIntStringDelegate                           OnBrandEngageClientChangeStatus;

    UPROPERTY(BlueprintAssignable)
	FDynIntDelegate                                 OnOfferWallFinish;

protected:

	void OnVirtualCurrencyConnectorFailedDelegate_Handler(int32 error, const FString& errorCode, const FString& message) {OnVirtualCurrencyConnectorFailed.Broadcast(error, errorCode, message);}
	void OnVirtualCurrencyConnectorSuccessDelegate_Handler(float deltaOfCoins, const FString& currencyId, const FString& currencyName, const FString& transactionId) {OnVirtualCurrencyConnectorSuccess.Broadcast(deltaOfCoins, currencyId, currencyName, transactionId);}
	void OnCanShowInterstitialDelegate_Handler(bool canShowInterstitial) {OnCanShowInterstitial.Broadcast(canShowInterstitial);};
	void OnInterstitialDidShowDelegate_Handler() {OnInterstitialDidShow.Broadcast();};
	void OnInterstitialDismissDelegate_Handler(const FString& reason) {OnInterstitialDismiss.Broadcast(reason);};
	void OnInterstitialFailedDelegate_Handler() {OnInterstitialFailed.Broadcast();};
	void OnBrandEngageClientReceiveOffersDelegate_Handler(bool areOffersAvailable) {OnBrandEngageClientReceiveOffers.Broadcast(areOffersAvailable);};
	void OnBrandEngageClientChangeStatusDelegate_Handler(int32 status, const FString& message) {OnBrandEngageClientChangeStatus.Broadcast(status, message);};
	void OnOfferWallFinishDelegate_Handler(int32 status) {OnOfferWallFinish.Broadcast(status);};
};
