// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetPointerComp.h"
#include "VR_Player.h"
#include "EnhancedInputComponent.h"
#include "Components/WidgetInteractionComponent.h"


// Sets default values for this component's properties
UWidgetPointerComp::UWidgetPointerComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UWidgetPointerComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Player = GetOwner<AVR_Player>();	
}


// Called every frame
void UWidgetPointerComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWidgetPointerComp::SetupPlayerInputComponent(UEnhancedInputComponent* enhancedInputComponent, TArray<UInputAction*> inputs)
{
	enhancedInputComponent->BindAction(inputs[6], ETriggerEvent::Started, this, &UWidgetPointerComp::MouseLeftClick);
	enhancedInputComponent->BindAction(inputs[6], ETriggerEvent::Completed, this, &UWidgetPointerComp::MouseLeftRelease);
	
}

void UWidgetPointerComp::MouseLeftClick(const FInputActionValue& value)
{
	// ������ ���� ���ͷ��� �����Ϳ� ���콺 ���� Ŭ�� ȿ���� �ο��Ѵ�. 
	// value�� �Ⱦ��� �̺�Ʈ�� ���� ����
	Player->RightPointer->PressPointerKey(EKeys::LeftMouseButton); // �� �̺�Ʈ�� ����Ǹ� LeftMouseButton�� ���� �Ͱ� ���� ȿ���� �ְڴ�.(�̷������� Ű ȿ�� �ο� ����)
}

void UWidgetPointerComp::MouseLeftRelease(const FInputActionValue& value)
{
	Player->RightPointer->ReleasePointerKey(EKeys::LeftMouseButton); // �� �̺�Ʈ�� ����Ǹ� LeftMouseButton�� ���� �Ͱ� ���� ȿ���� �ְڴ�.(�̷������� Ű ȿ�� �ο� ����)
}

