// Fill out your copyright notice in the Description page of Project Settings.


#include "CarControllerComponent.h"
#include "VR_Player.h"
#include "EnhancedInputComponent.h"
#include "VRHandAnimInstance.h"
#include "MotionControllerComponent.h"
#include "Components/TextRenderComponent.h"
#include "MyCarActor.h"

// Sets default values for this component's properties
UCarControllerComponent::UCarControllerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCarControllerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Player = GetOwner<AVR_Player>();
	
}


// Called every frame
void UCarControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	// 양손의 그립 버튼을 둘 다 눌렀을 때
	if (bIsLeftGrip && bIsRightGrip) {
		//각도 계산하는 함수
		float degree = GetControllerAngle(Player->leftController->GetComponentLocation(), Player->rightController->GetComponentLocation(), Player->GetActorRightVector());

		Player->leftLog->SetText(FText::FromString(FString::Printf(TEXT("Angle : %d"),(int32)degree)));

		Player->MyFirstCar->RotateCar(degree);
	}
}

void UCarControllerComponent::SetupPlayerInputComponent(UEnhancedInputComponent* EnhancedInputComponent, TArray<class UInputAction*> inputs)
{
	EnhancedInputComponent->BindAction(inputs[3], ETriggerEvent::Started, this, &UCarControllerComponent::GripLeftOn);
	EnhancedInputComponent->BindAction(inputs[3], ETriggerEvent::Completed, this, &UCarControllerComponent::GripLeftOff);
	EnhancedInputComponent->BindAction(inputs[7], ETriggerEvent::Started, this, &UCarControllerComponent::GripRightOn);
	EnhancedInputComponent->BindAction(inputs[7], ETriggerEvent::Completed, this, &UCarControllerComponent::GripRightOff);

}

void UCarControllerComponent::aaaa(const FInputActionValue& value)
{
}

// 기준벡터와 양손벡터와의 각도 차이(핸들의 기울기)를 계산해서 반환하는 함수
float UCarControllerComponent::GetControllerAngle(FVector leftControllerLoc, FVector rightControllerLoc, FVector baseDirection)
{
	// hand 내적 base =  cos세타 
	// 단 길이는 모두 1이어야한다
	// 외적으로 방향성 알 수 있음

	// 양손벡터 구하기
	FVector handVector = (rightControllerLoc - leftControllerLoc).GetSafeNormal();

	// 기준벡터 구하기
	FVector baseVector = baseDirection.GetSafeNormal();

	// 내적
	float dotResult = FVector::DotProduct(handVector, baseVector);

	// 기준벡터와 양손벡터 사이의 각도 구하기
	//cos 의 아크cos이라서 세타만 남는다.
	float Degree = FMath::RadiansToDegrees(FMath::Acos(dotResult));
	//float Degree = FMath::Acos(dotResult);
	//UE_LOG(LogTemp, Warning, TEXT("Calc Angle: %.1f",degree));

	// 위쪽 벡터와 내적한 결과가 양수면 오른손이 위로 올라간 벡터, 음수면 오른손이 아래로 내려간 벡터
	if (FVector::DotProduct(Player->GetActorUpVector(), handVector) > 0) {
		Degree*= -1.0f;
	}

	return Degree;
}

void UCarControllerComponent::GripLeftOn()
{
	bIsLeftGrip = true;
}

void UCarControllerComponent::GripLeftOff()
{
	bIsLeftGrip = false;
}

void UCarControllerComponent::GripRightOn()
{

	bIsRightGrip = true;
}

void UCarControllerComponent::GripRightOff()
{
	bIsRightGrip = false;
}

