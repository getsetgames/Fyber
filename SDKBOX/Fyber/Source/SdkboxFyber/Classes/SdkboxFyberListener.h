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

#include "PluginFyber.h"
#include "SdkboxFyberListener.generated.h"

// UE4 HeaderTool fails to parse the namespace properly, so...
struct UListener : public sdkbox::FyberListener {};

UCLASS(NotBlueprintable)
class USdkboxFyberListener
    : public UObject
    , public UListener
{
	GENERATED_BODY()
    
public:

    USdkboxFyberListener(const FObjectInitializer& ObjectInitializer);

    void onVirtualCurrencyConnectorFailed (int error, // deprecated filed, always: 0
                                           const std::string& errorCode, // deprecated filed, always: ""
                                           const std::string& errorMsg);

	void onVirtualCurrencyConnectorSuccess(double deltaOfCoins,
                                           const std::string& currencyId,
                                           const std::string& currencyName,
                                           const std::string& transactionId);

    // Interstitial
    void onCanShowInterstitial(bool canShowInterstitial);
    void onInterstitialDidShow();
    void onInterstitialDismiss(const std::string& reason);
    void onInterstitialFailed();

    // Rewarded Video
	void onBrandEngageClientReceiveOffers(bool areOffersAvailable);
    void onBrandEngageClientChangeStatus(int status, const std::string& msg);

    // Offer Wall
    void onOfferWallFinish(int status);

protected:

	void _pushVolumeChange();
	void _popVolumeChange();
    float _setMasterVolume(float Volume);

protected:

	float _previousVolume;
};