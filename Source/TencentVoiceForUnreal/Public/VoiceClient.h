// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GCloudVoice.h"
#include "VoiceClient.generated.h"

/**
 * 
 */
UCLASS()
class TENCENTVOICEFORUNREAL_API UVoiceClient : public UObject
{
	GENERATED_BODY()

public:
	UVoiceClient();
	~UVoiceClient();

public:
	UFUNCTION(BlueprintPure, Category = "Voice Plug-in")
		// Get or New a voice client instance(if not exist),singleton object
		static UVoiceClient* GetVoiceClient();

	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		// Set VoiceEngine AppInfo.successed return true,otherwise return false
		bool SetAppInfo();

private:
	static UVoiceClient* VoiceClient;
	class gcloud_voice::IGCloudVoiceEngine* m_voiceengine;
};
