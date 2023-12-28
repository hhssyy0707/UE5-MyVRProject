// Fill out your copyright notice in the Description page of Project Settings.


#include "VRHandAnimComponent.h"
#include "EnhancedInputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "VRHandAnimInstance.h"
#include "VR_Player.h"

// Sets default values for this component's properties
UVRHandAnimComponent::UVRHandAnimComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UVRHandAnimComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Player = GetOwner<AVR_Player>();

	if (Player != nullptr) {
		handAnim_Left = Cast<UVRHandAnimInstance>(Player->leftHand->GetAnimInstance());

		if (handAnim_Left) {
			handAnim_Left->bMirror_cpp = true;
		}

		handAnim_Right = Cast<UVRHandAnimInstance>(Player->rightHand->GetAnimInstance());
		if (handAnim_Right) {
			handAnim_Right->bMirror_cpp = false;

		}
	}
}


// Called every frame
void UVRHandAnimComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...


}

void UVRHandAnimComponent::SetupPlayerInputComponent(UEnhancedInputComponent* EnhancedInputComponent, TArray<class UInputAction*> inputs)
{

	EnhancedInputComponent->BindAction(inputs[2], ETriggerEvent::Triggered, this, &UVRHandAnimComponent::InputIndexTriggerValue_Left);
	EnhancedInputComponent->BindAction(inputs[2], ETriggerEvent::Completed, this, &UVRHandAnimComponent::InputIndexTriggerValue_Left);
	EnhancedInputComponent->BindAction(inputs[3], ETriggerEvent::Triggered, this, &UVRHandAnimComponent::InputGripValue_Left);
	EnhancedInputComponent->BindAction(inputs[3], ETriggerEvent::Completed, this, &UVRHandAnimComponent::InputGripValue_Left);
	EnhancedInputComponent->BindAction(inputs[4], ETriggerEvent::Triggered, this, &UVRHandAnimComponent::InputIndexTriggerTouch_Left);
	EnhancedInputComponent->BindAction(inputs[4], ETriggerEvent::Completed, this, &UVRHandAnimComponent::InputIndexTriggerTouch_Left);
	EnhancedInputComponent->BindAction(inputs[5], ETriggerEvent::Triggered, this, &UVRHandAnimComponent::InputThumbstickTouch_Left);
	EnhancedInputComponent->BindAction(inputs[5], ETriggerEvent::Completed, this, &UVRHandAnimComponent::InputThumbstickTouch_Left);
	EnhancedInputComponent->BindAction(inputs[6], ETriggerEvent::Triggered, this, &UVRHandAnimComponent::InputIndexTriggerValue_Right);
	EnhancedInputComponent->BindAction(inputs[6], ETriggerEvent::Completed, this, &UVRHandAnimComponent::InputIndexTriggerValue_Right);
	EnhancedInputComponent->BindAction(inputs[7], ETriggerEvent::Triggered, this, &UVRHandAnimComponent::InputGripValue_Right);
	EnhancedInputComponent->BindAction(inputs[7], ETriggerEvent::Completed, this, &UVRHandAnimComponent::InputGripValue_Right);
	EnhancedInputComponent->BindAction(inputs[8], ETriggerEvent::Triggered, this, &UVRHandAnimComponent::InputIndexTriggerTouch_Right);
	EnhancedInputComponent->BindAction(inputs[8], ETriggerEvent::Completed, this, &UVRHandAnimComponent::InputIndexTriggerTouch_Right);
	EnhancedInputComponent->BindAction(inputs[9], ETriggerEvent::Triggered, this, &UVRHandAnimComponent::InputThumbstickTouch_Right);
	EnhancedInputComponent->BindAction(inputs[9], ETriggerEvent::Completed, this, &UVRHandAnimComponent::InputThumbstickTouch_Right);
}

void UVRHandAnimComponent::InputIndexTriggerValue_Left(const FInputActionValue& value)
{
	if (handAnim_Left != nullptr) {
		handAnim_Left->PoseAlphaIndexCurl_cpp = value.Get<float>();
	}
}

void UVRHandAnimComponent::InputGripValue_Left(const FInputActionValue& value)
{
	if (handAnim_Left != nullptr) {
		handAnim_Left->PoseAlphaGrasp_cpp = value.Get<float>();
	}
}

void UVRHandAnimComponent::InputIndexTriggerTouch_Left(const FInputActionValue& value)
{
	if (handAnim_Left != nullptr) {
		handAnim_Left->PoseAlphaPoint_cpp = value.Get<bool>();
	}
}

void UVRHandAnimComponent::InputThumbstickTouch_Left(const FInputActionValue& value)
{
	if (handAnim_Left != nullptr) {
		handAnim_Left->PoseAlphaThumbUp_cpp = value.Get<bool>();
	}
}

void UVRHandAnimComponent::InputIndexTriggerValue_Right(const FInputActionValue& value)
{
	if (handAnim_Right != nullptr) {
		handAnim_Right->PoseAlphaIndexCurl_cpp = value.Get<float>();
	}
}

void UVRHandAnimComponent::InputGripValue_Right(const FInputActionValue& value)
{
	if (handAnim_Right != nullptr) {
		handAnim_Right->PoseAlphaGrasp_cpp = value.Get<float>();
	}
}

void UVRHandAnimComponent::InputIndexTriggerTouch_Right(const FInputActionValue& value)
{
	if (handAnim_Right != nullptr) {
		handAnim_Right->PoseAlphaPoint_cpp = value.Get<bool>();
	}
}

void UVRHandAnimComponent::InputThumbstickTouch_Right(const FInputActionValue& value)
{
	if (handAnim_Right != nullptr) {
		handAnim_Right->PoseAlphaThumbUp_cpp = value.Get<bool>();
	}
}

