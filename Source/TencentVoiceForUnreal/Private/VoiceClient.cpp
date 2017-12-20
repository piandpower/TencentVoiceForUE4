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

UVoiceClient * UVoiceClient::GetVoiceClient()
{
	if (nullptr == VoiceClient)
	{
		VoiceClient = NewObject<UVoiceClient>();
		VoiceClient->AddToRoot();
	}
	return VoiceClient;
}

bool UVoiceClient::SetAppInfo()
{
	if (nullptr == m_voiceengine)
	{
		return false;
	}
	m_voiceengine->SetAppInfo("932849489", "d94749efe9fce61333121de84123ef9b", "E81DCA1782C5CE8B0722A366D7ECB41F");
	UE_LOG(LogTemp, Error, TEXT("SetAppInfo Successed!"));
	return true;
}
