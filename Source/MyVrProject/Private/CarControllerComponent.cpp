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

	// ����� �׸� ��ư�� �� �� ������ ��
	if (bIsLeftGrip && bIsRightGrip) {
		//���� ����ϴ� �Լ�
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

// ���غ��Ϳ� ��պ��Ϳ��� ���� ����(�ڵ��� ����)�� ����ؼ� ��ȯ�ϴ� �Լ�
float UCarControllerComponent::GetControllerAngle(FVector leftControllerLoc, FVector rightControllerLoc, FVector baseDirection)
{
	// hand ���� base =  cos��Ÿ 
	// �� ���̴� ��� 1�̾���Ѵ�
	// �������� ���⼺ �� �� ����

	// ��պ��� ���ϱ�
	FVector handVector = (rightControllerLoc - leftControllerLoc).GetSafeNormal();

	// ���غ��� ���ϱ�
	FVector baseVector = baseDirection.GetSafeNormal();

	// ����
	float dotResult = FVector::DotProduct(handVector, baseVector);

	// ���غ��Ϳ� ��պ��� ������ ���� ���ϱ�
	//cos �� ��ũcos�̶� ��Ÿ�� ���´�.
	float Degree = FMath::RadiansToDegrees(FMath::Acos(dotResult));
	//float Degree = FMath::Acos(dotResult);
	//UE_LOG(LogTemp, Warning, TEXT("Calc Angle: %.1f",degree));

	// ���� ���Ϳ� ������ ����� ����� �������� ���� �ö� ����, ������ �������� �Ʒ��� ������ ����
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

