// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GrabComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYVRPROJECT_API UGrabComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UGrabComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetupPlayerInputComponent(class UEnhancedInputComponent* enhancedInputComponent, TArray<class UInputAction*> inputs);


private:
	class AVR_Player* player;
	class APickUpActor* currentObject;
	FVector prevLoc;
	FVector deltaLoc;
	FQuat prevQuat;
	FQuat deltaQuat;

	void GrabObject();
	void ReleaseObject();
};
