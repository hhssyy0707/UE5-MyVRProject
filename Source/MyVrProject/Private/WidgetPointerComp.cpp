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
	// 오른손 위젯 인터렉션 포인터에 마우스 왼쪽 클릭 효과를 부여한다. 
	// value는 안쓰고 이벤트만 받을 거임
	Player->RightPointer->PressPointerKey(EKeys::LeftMouseButton); // 이 이벤트가 실행되면 LeftMouseButton를 누른 것과 같은 효과를 주겠다.(이런식으로 키 효과 부여 가능)
}

void UWidgetPointerComp::MouseLeftRelease(const FInputActionValue& value)
{
	Player->RightPointer->ReleasePointerKey(EKeys::LeftMouseButton); // 이 이벤트가 실행되면 LeftMouseButton를 누른 것과 같은 효과를 주겠다.(이런식으로 키 효과 부여 가능)
}

