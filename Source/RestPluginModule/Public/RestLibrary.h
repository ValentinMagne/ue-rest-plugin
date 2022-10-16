#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Http.h"
#include "HttpModule.h"
#include "RestLibrary.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(RestLibrary, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRequestComplete, FString, response);

UCLASS(BlueprintType, Blueprintable)
class RESTPLUGINMODULE_API URestLibrary : public UObject
{
	GENERATED_UCLASS_BODY()

public:	
	URestLibrary();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Execute Sample function", Keywords = "HttpBlueprintPlugin sample test testing"), Category = "RestPlugin")
	float RestPluginSampleFunction(float Param);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Send Get Request", Keywords = "Http Get Request"), Category = "RestPlugin")
	void ProcessRequestGet(FString URL);

	void OnResponseGetReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UPROPERTY(BlueprintAssignable, Category = "RestPlugin")
	FOnRequestComplete onRequestComplete;

};
