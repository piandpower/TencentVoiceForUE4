// Fill out your copyright notice in the Description page of Project Settings.

#include "VoiceClient.h"

UVoiceClient* UVoiceClient::VoiceClient = nullptr;

UVoiceClient::UVoiceClient()
{
	m_voiceengine = gcloud_voice::GetVoiceEngine();
}

UVoiceClient::~UVoiceClient()
{

}

void UVoiceClient::Tick(float DeltaTime)
{
	m_voiceengine->Poll();
}

FORCEINLINE bool UVoiceClient::IsTickable() const
{
	return true;
}

FORCEINLINE TStatId UVoiceClient::GetStatId() const
{
	return TStatId();
}

UVoiceClient * UVoiceClient::GetVoiceClient()
{
	if (nullptr == VoiceClient)
	{
		VoiceClient = NewObject<UVoiceClient>();
		VoiceClient->AddToRoot();
	}
	return VoiceClient;
}

bool UVoiceClient::SetAppInfo(const FString& appID, const FString& appKey, int32 RoleID)
{
	if ((nullptr == m_voiceengine)
		&& (gcloud_voice::GCLOUD_VOICE_SUCC != m_voiceengine->SetAppInfo(TCHAR_TO_ANSI(*appID), TCHAR_TO_ANSI(*appKey), (char*)&RoleID)))
	{
		return false;
	}
	return true;
}

void UVoiceClient::InitEngine()
{
	m_voiceengine->Init();
	m_voiceengine->SetMode(gcloud_voice::IGCloudVoiceEngine::RealTime);
	m_voiceengine->SetServerInfo("udp://cn.voice.gcloudcs.com:10001");
}
