// Fill out your copyright notice in the Description page of Project Settings.


#include "RestLibrary.h"

DEFINE_LOG_CATEGORY(RestLibrary);

// Sets default values
URestLibrary::URestLibrary(const FObjectInitializer& init)
	:Super(init)
{

}

float URestLibrary::RestPluginSampleFunction(float Param)
{
	return Param * 3;
}

void URestLibrary::ProcessRequestGet(FString URL)
{
	UE_LOG(RestLibrary, Log, TEXT("Process GET request for : %s"), *URL);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

	HttpRequest->OnProcessRequestComplete().BindUObject(this, &URestLibrary::OnResponseGetReceived);

	HttpRequest->SetURL(URL);

	HttpRequest->SetVerb("Get");

	HttpRequest->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");

	HttpRequest->ProcessRequest();
}

void URestLibrary::OnResponseGetReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UE_LOG(RestLibrary, Log, TEXT("GET RESPONSE : %s"), *Response->GetContentAsString());

		// TODO http://www.orfeasel.com/parsing-json-files/ or use JSON parser plugin (from IWAGD) ? 

		GLog->Log(TEXT("END REQUEST"));
		FString JSONString = Response->GetContentAsString();
		onRequestComplete.Broadcast(JSONString);
	}
}