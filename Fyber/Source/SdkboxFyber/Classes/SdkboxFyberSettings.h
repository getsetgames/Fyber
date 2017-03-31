/****************************************************************************
 Copyright (c) 2015- SDKBOX Inc.
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

#include "UObject/Object.h"
#include "UObject/ScriptMacros.h"
#include "SdkboxFyberSettings.generated.h"

UCLASS(config = Engine, defaultconfig)
class USdkboxFyberSettings : public UObject
{
	GENERATED_BODY()

public:

	USdkboxFyberSettings(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(Config, EditAnywhere, Category=General, meta=(DisplayName="Debug Enable"))
	bool DebugEnable;

	UPROPERTY(Config, EditAnywhere, Category=IOS, meta=(DisplayName="App ID iOS"))
	FString AppIDiOS;

	UPROPERTY(Config, EditAnywhere, Category=IOS, meta=(DisplayName="Token iOS"))
	FString TokeniOS;

	UPROPERTY(Config, EditAnywhere, Category=Android, meta=(DisplayName="App ID Android"))
	FString AppIDAndroid;

	UPROPERTY(Config, EditAnywhere, Category=Android, meta=(DisplayName="Token Android"))
	FString TokenAndroid;

	UPROPERTY(Config, EditAnywhere, Category=General, meta=(DisplayName="Disable Video Pre-Caching"))
	bool DisableVideoPreCaching;

	UPROPERTY(Config, EditAnywhere, Category=General, meta=(DisplayName="Toast Messages"))
	bool ToastMessages;

	UPROPERTY(Config, EditAnywhere, Category=General, meta=(DisplayName="Video Close Button Delay Length"))
	int VideoCloseButtonDelayLength;

	UPROPERTY(Config, EditAnywhere, Category=General, meta=(DisplayName="Disable sound when watching video"))
	bool DisableSoundWhenWatchingVideo;
    
    UPROPERTY(Config, EditAnywhere, Category=Android, meta=(DisplayName="Run garbage collection on callbacks"))
    bool GarbageCollectOnCallbacksAndroid;    
};
