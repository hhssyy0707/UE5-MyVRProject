// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputActionValue.h"
#include "VRHandAnimComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYVRPROJECT_API UVRHandAnimComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVRHandAnimComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupPlayerInputComponent(class UEnhancedInputComponent* EnhancedInputComponent, TArray<class UInputAction*> inputs);
		
	void InputIndexTriggerValue_Left(const FInputActionValue& value);
	void InputGripValue_Left(const FInputActionValue& value);
	void InputIndexTriggerTouch_Left(const FInputActionValue& value);
	void InputThumbstickTouch_Left(const FInputActionValue& value);

	void InputIndexTriggerValue_Right(const FInputActionValue& value);
	void InputGripValue_Right(const FInputActionValue& value);
	void InputIndexTriggerTouch_Right(const FInputActionValue& value);
	void InputThumbstickTouch_Right(const FInputActionValue& value);

private:
	class AVR_Player* Player;
	class UVRHandAnimInstance* handAnim_Left;
	class UVRHandAnimInstance* handAnim_Right;
};
