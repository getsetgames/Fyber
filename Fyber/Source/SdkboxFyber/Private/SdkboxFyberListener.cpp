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

USdkboxFyberListener::USdkboxFyberListener(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
    , _previousVolume(-1)
{}

void USdkboxFyberListener::onVirtualCurrencyConnectorFailed(int error, const std::string& errorCode, const std::string& errorMsg)
{
	USdkboxFyberComponent::OnVirtualCurrencyConnectorFailedDelegate.Broadcast(error, errorCode.c_str(), errorMsg.c_str());
}

void USdkboxFyberListener::onVirtualCurrencyConnectorSuccess(double deltaOfCoins, const std::string& currencyId, const std::string& currencyName, const std::string& transactionId)
{
	USdkboxFyberComponent::OnVirtualCurrencyConnectorSuccessDelegate.Broadcast(deltaOfCoins, currencyId.c_str(), currencyName.c_str(), transactionId.c_str());
}

void USdkboxFyberListener::onCanShowInterstitial(bool canShowInterstitial)
{
	USdkboxFyberComponent::OnCanShowInterstitialDelegate.Broadcast(canShowInterstitial);
}

void USdkboxFyberListener::onInterstitialDidShow()
{
	USdkboxFyberComponent::OnInterstitialDidShowDelegate.Broadcast();
}

void USdkboxFyberListener::onInterstitialDismiss(const std::string& reason)
{
	USdkboxFyberComponent::OnInterstitialDismissDelegate.Broadcast(reason.c_str());
}

void USdkboxFyberListener::onInterstitialFailed()
{
	USdkboxFyberComponent::OnInterstitialFailedDelegate.Broadcast();
}

void USdkboxFyberListener::onBrandEngageClientReceiveOffers(bool areOffersAvailable)
{
	USdkboxFyberComponent::OnBrandEngageClientReceiveOffersDelegate.Broadcast(areOffersAvailable);
}

void USdkboxFyberListener::onBrandEngageClientChangeStatus(int status, const std::string& msg)
{
	//UE_LOG(SDKBOX, Warning, TEXT("onBrandEngageClientChangeStatus: %d %s"), status, msg.c_str());

	USdkboxFyberComponent::OnBrandEngageClientChangeStatusDelegate.Broadcast(EFyberRewardedVideoEnum(status), msg.c_str());
	switch (status)
	{
	case sdkbox::FYB_REWARDED_VIDEO_STARTED:
		_pushVolumeChange();
		break;
	case sdkbox::FYB_REWARDED_VIDEO_FINISHED:
	case sdkbox::FYB_REWARDED_VIDEO_ABORTED:
	case sdkbox::FYB_REWARDED_VIDEO_ERROR:
	default:
		_popVolumeChange();
	}
}

void USdkboxFyberListener::onOfferWallFinish(int status)
{
	USdkboxFyberComponent::OnOfferWallFinishDelegate.Broadcast(EFyberOfferWallEnum(status));
}

//
// Protected Methods
//

void USdkboxFyberListener::_pushVolumeChange()
{
	const USdkboxFyberSettings* settings = GetDefault<USdkboxFyberSettings>();
	if (settings && settings->DisableSoundWhenWatchingVideo && 0 > _previousVolume)
		_previousVolume = _setMasterVolume(0);
}

void USdkboxFyberListener::_popVolumeChange()
{
	const USdkboxFyberSettings* settings = GetDefault<USdkboxFyberSettings>();
	if (settings && settings->DisableSoundWhenWatchingVideo && 0 <= _previousVolume)
		_previousVolume = _setMasterVolume(_previousVolume);
}

float USdkboxFyberListener::_setMasterVolume(float Volume)
{
	FAudioDevice* AudioDevice = GEngine->GetMainAudioDevice();
	if (!AudioDevice)
		return -1;

	float previousVolume = -1;
	for (auto i = AudioDevice->SoundClasses.CreateIterator(); i; ++i)
	{
		USoundClass* SoundClass = i.Key();
		FString SoundClassName;

		// Test if the Split function works then, if the name was the right one
		if (SoundClass->GetFullName().Split(L".", nullptr, &SoundClassName, ESearchCase::CaseSensitive) && SoundClassName.Equals("Master"))
		{
			previousVolume = SoundClass->Properties.Volume;
			SoundClass->Properties.Volume = Volume;
			break;
		}
	}

	//UE_LOG(SDKBOX, Warning, TEXT("previousVolume: %.02f"), previousVolume);

	return previousVolume;
}
