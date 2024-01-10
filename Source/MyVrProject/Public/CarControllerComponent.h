// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputActionValue.h"
#include "CarControllerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYVRPROJECT_API UCarControllerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCarControllerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetupPlayerInputComponent(class UEnhancedInputComponent* EnhancedInputComponent, TArray<class UInputAction*> inputs);
	void aaaa(const FInputActionValue& value);
	float GetControllerAngle(FVector leftControllerLoc, FVector rightControllerLoc, FVector baseDirection);
	void GripLeftOn();
	void GripLeftOff();
	void GripRightOn();
	void GripRightOff();

private:
	class AVR_Player* Player;
	bool bIsLeftGrip = false; // 경우의 수가 2개 이상인 경우에는 enum으로 이하면 bool 변수 사용
	bool bIsRightGrip = false;

};
