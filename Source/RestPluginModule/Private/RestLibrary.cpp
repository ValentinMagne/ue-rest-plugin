#include "RestLibrary.h"

DEFINE_LOG_CATEGORY(RestLibrary);

URestLibrary::URestLibrary(const FObjectInitializer& init)
	:Super(init)
{

}

float URestLibrary::RestPluginSampleFunction(float Param)
{
	return Param * 100;
}

void URestLibrary::ProcessRequestGet(FString URL)
{
	UE_LOG(RestLibrary, Log, TEXT("Process GET request for : %s"), *URL);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

	HttpRequest->OnProcessRequestComplete().BindUObject(this, &URestLibrary::OnResponseReceived);

	HttpRequest->SetURL(URL);

	HttpRequest->SetVerb("Get");

	HttpRequest->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");

	HttpRequest->ProcessRequest();
}

void URestLibrary::ProcessRequestPost(FString URL, FString body)
{
	UE_LOG(RestLibrary, Log, TEXT("Process POST request for : %s"), *URL);
	UE_LOG(RestLibrary, Log, TEXT("Process POST request with body : %s"), *body);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

	HttpRequest->OnProcessRequestComplete().BindUObject(this, &URestLibrary::OnResponseReceived);

	HttpRequest->SetURL(URL);

	HttpRequest->SetVerb("Post");

	HttpRequest->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");

	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	HttpRequest->SetContentAsString(body);

	HttpRequest->ProcessRequest();
}

void URestLibrary::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UE_LOG(RestLibrary, Log, TEXT("GET RESPONSE : %s"), *Response->GetContentAsString());
		GLog->Log(TEXT("END REQUEST"));
		FString JSONString = Response->GetContentAsString();
		onRequestComplete.Broadcast(JSONString);
	}
}
