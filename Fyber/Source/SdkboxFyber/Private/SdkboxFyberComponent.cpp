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

USdkboxFyberComponent::FInterstitialDelegate     USdkboxFyberComponent::OnInterstitialReceiveOffersDelegate;
USdkboxFyberComponent::FInterstitialEnumDelegate USdkboxFyberComponent::OnInterstitialChangeStatusDelegate;
USdkboxFyberComponent::FVirtualCurrencyConnectorFailedDelegate  USdkboxFyberComponent::OnVirtualCurrencyConnectorFailedDelegate;
USdkboxFyberComponent::FVirtualCurrencyConnectorSuccessDelegate USdkboxFyberComponent::OnVirtualCurrencyConnectorSuccessDelegate;
USdkboxFyberComponent::FRewardedVideoDelegate                   USdkboxFyberComponent::OnBrandEngageClientReceiveOffersDelegate;
USdkboxFyberComponent::FRewardedVideoEnumDelegate               USdkboxFyberComponent::OnBrandEngageClientChangeStatusDelegate;
USdkboxFyberComponent::FOfferWallEnumDelegate                   USdkboxFyberComponent::OnOfferWallFinishDelegate;

USdkboxFyberComponent::USdkboxFyberComponent(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void USdkboxFyberComponent::OnRegister()
{
	Super::OnRegister();

    USdkboxFyberComponent::OnInterstitialReceiveOffersDelegate.AddUObject(this, &USdkboxFyberComponent::OnInterstitialReceiveOffersDelegate_Handler);
    USdkboxFyberComponent::OnInterstitialChangeStatusDelegate.AddUObject(this, &USdkboxFyberComponent::OnInterstitialChangeStatusDelegate_Handler);
	USdkboxFyberComponent::OnVirtualCurrencyConnectorFailedDelegate.AddUObject(this, &USdkboxFyberComponent::OnVirtualCurrencyConnectorFailedDelegate_Handler);
	USdkboxFyberComponent::OnVirtualCurrencyConnectorSuccessDelegate.AddUObject(this, &USdkboxFyberComponent::OnVirtualCurrencyConnectorSuccessDelegate_Handler);
    USdkboxFyberComponent::OnBrandEngageClientReceiveOffersDelegate.AddUObject(this, &USdkboxFyberComponent::OnBrandEngageClientReceiveOffersDelegate_Handler);
	USdkboxFyberComponent::OnBrandEngageClientChangeStatusDelegate.AddUObject(this, &USdkboxFyberComponent::OnBrandEngageClientChangeStatusDelegate_Handler);
	USdkboxFyberComponent::OnOfferWallFinishDelegate.AddUObject(this, &USdkboxFyberComponent::OnOfferWallFinishDelegate_Handler);
}

void USdkboxFyberComponent::OnUnregister()
{
	Super::OnUnregister();

    USdkboxFyberComponent::OnInterstitialReceiveOffersDelegate.RemoveAll(this);
    USdkboxFyberComponent::OnInterstitialChangeStatusDelegate.RemoveAll(this);
	USdkboxFyberComponent::OnVirtualCurrencyConnectorFailedDelegate.RemoveAll(this);
	USdkboxFyberComponent::OnVirtualCurrencyConnectorSuccessDelegate.RemoveAll(this);
    USdkboxFyberComponent::OnBrandEngageClientReceiveOffersDelegate.RemoveAll(this);
	USdkboxFyberComponent::OnBrandEngageClientChangeStatusDelegate.RemoveAll(this);
	USdkboxFyberComponent::OnOfferWallFinishDelegate.RemoveAll(this);
}

