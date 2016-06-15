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

USdkboxFyberListener* USdkboxFyberFunctions::_FyberListener = nullptr;

void USdkboxFyberFunctions::FyberInitialize()
{
#if PLATFORM_IOS || PLATFORM_ANDROID
    sdkbox::PluginFyber::init("123", TCHAR_TO_ANSI(*_SettingsToJSONString()));
    if (!_FyberListener)
    {
        _FyberListener = NewObject<USdkboxFyberListener>(USdkboxFyberListener::StaticClass());
        sdkbox::PluginFyber::setListener(_FyberListener);
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
	sdkbox::PluginFyber::showOfferWall();
#endif
}

void USdkboxFyberFunctions::FyberRequestRewardedVideo(const FString& placementId)
{
#if PLATFORM_IOS || PLATFORM_ANDROID
	sdkbox::PluginFyber::requestRewardedVideo(TCHAR_TO_ANSI(*placementId));
#endif
}

void USdkboxFyberFunctions::FyberShowRewardedVideo()
{
#if PLATFORM_IOS || PLATFORM_ANDROID
	sdkbox::PluginFyber::showRewardedVideo();
#endif
}

void USdkboxFyberFunctions::FyberRequestInterstitial()
{
#if PLATFORM_IOS || PLATFORM_ANDROID
	sdkbox::PluginFyber::requestInterstitial();
#endif
}

void USdkboxFyberFunctions::FyberShowInterstitial()
{
#if PLATFORM_IOS || PLATFORM_ANDROID
	sdkbox::PluginFyber::showInterstitial();
#endif
}

void USdkboxFyberFunctions::FyberRequestDeltaOfCoins(const FString& currencyId)
{
#if PLATFORM_IOS || PLATFORM_ANDROID
	sdkbox::PluginFyber::requestDeltaOfCoins(TCHAR_TO_ANSI(*currencyId));
#endif
}

//
// Protected Methods
//

FString USdkboxFyberFunctions::_SettingsToJSONString()
{
#if PLATFORM_IOS || PLATFORM_ANDROID
	const USdkboxFyberSettings* settings = GetDefault<USdkboxFyberSettings>();

    TSharedPtr<FJsonObject> jo    =  MakeShareable(new FJsonObject);
    TSharedPtr<FJsonObject> ios[] = {MakeShareable(new FJsonObject), MakeShareable(new FJsonObject)};
    TSharedPtr<FJsonObject> drd[] = {MakeShareable(new FJsonObject), MakeShareable(new FJsonObject)};

    jo->SetObjectField("ios", ios[0]);
    ios[0]->SetObjectField("Fyber", ios[1]);

    jo->SetObjectField("android", drd[0]);
    drd[0]->SetObjectField("Fyber", drd[1]);

    ios[1]->SetBoolField("debug", settings->DebugEnable);
    ios[1]->SetBoolField("toast", settings->ToastMessages);
    ios[1]->SetStringField("appid", settings->AppIDiOS);
    ios[1]->SetStringField("token", settings->TokeniOS);

    drd[1]->SetBoolField("debug", settings->DebugEnable);
    drd[1]->SetBoolField("toast", settings->ToastMessages);
    drd[1]->SetStringField("appid", settings->AppIDAndroid);
    drd[1]->SetStringField("token", settings->TokenAndroid);

    FString OutputString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
    FJsonSerializer::Serialize(jo.ToSharedRef(), Writer);

    return OutputString;
#else
    return "";
#endif
}

