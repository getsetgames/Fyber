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

#include "SdkboxFyberFunctions.generated.h"

UCLASS(NotBlueprintable)
class USdkboxFyberFunctions
    : public UObject 
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, meta = (Keywords = "SDKBOX Fyber"), Category = "SDKBOX")
	static void FyberInitialize(const FString &appID, const FString &securityToken);

	UFUNCTION(BlueprintCallable, meta = (Keywords = "SDKBOX Fyber"), Category = "SDKBOX")
	static void FyberShutdown();

    /**
     * Presents the Fyber Mobile OfferWall as a child view controller of your own view controller.
     */
	UFUNCTION(BlueprintCallable, meta = (Keywords = "SDKBOX Fyber"), Category = "SDKBOX")
    static void FyberShowOfferWall();

    /**
     * Request the server for rewarded video availability.
     */
	UFUNCTION(BlueprintCallable, meta = (Keywords = "SDKBOX Fyber"), Category = "SDKBOX")
    static void FyberRequestRewardedVideo(const FString& placementId);

    /**
     * Show an available rewarded video.
     */
	UFUNCTION(BlueprintCallable, meta = (Keywords = "SDKBOX Fyber"), Category = "SDKBOX")
    static void FyberShowRewardedVideo();

    /**
     * Check if interstitial ads are available
     */
	UFUNCTION(BlueprintCallable, meta = (Keywords = "SDKBOX Fyber"), Category = "SDKBOX")
    static void FyberRequestInterstitial();

    /**
     * Shows an interstitial ad. Check first that one is ready to be shown with requestInterstitial.
     */
	UFUNCTION(BlueprintCallable, meta = (Keywords = "SDKBOX Fyber"), Category = "SDKBOX")
    static void FyberShowInterstitial();

    /**
     * Fetches the amount of a given currency earned since the last time this method was
     * invoked for the current user ID / app ID combination.
     */
	UFUNCTION(BlueprintCallable, meta = (Keywords = "SDKBOX Fyber"), Category = "SDKBOX")
    static void FyberRequestDeltaOfCoins(const FString& currencyId = "");

protected:

	static FString _SettingsToJSONString();

protected:

};
