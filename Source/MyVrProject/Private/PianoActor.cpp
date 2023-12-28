// Fill out your copyright notice in the Description page of Project Settings.


#include "PianoActor.h"
#include "Components/SceneComponent.h"
#include "Components/ChildActorComponent.h"
#include "KeyboardActor.h"

// Sets default values
APianoActor::APianoActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(RootComp);

	
	// 전체 키보드판 넓이
	float width = (5 * 8) + (3 * (8 - 1));
	// width 반으로 나오면 키보드의 중점이 나온다.
	FVector startLoc = FVector(0, width * 0.5f * -1, 0);


	//for (int32 i = 0; i < KeySounds.Num(); i++) {
	for (int32 i = 0; i < 8; i++) {

		// 키보드 이름 넣기
		FString ActorName = FString::Printf(TEXT("keyboard_%d"),i+1);
		UChildActorComponent* children = CreateDefaultSubobject<UChildActorComponent>(FName(*ActorName));
		children->SetupAttachment(RootComponent);

		// keyActor에 생성한 키보드를 하나씩 넣어준다
		KeyActors.Add(children);

		//키보드 형태로 넣고싶다, 캐스팅
		// 각각의 키보드 액터들마다 가지고 있는 keySound 변수에 음원 파일들을 넣어준다.
		if (children->GetChildActor() != nullptr) { // 에러 방지 , 음원 없을 때 오류 날 수 있다.
			Cast<AKeyboardActor>(children->GetChildActor())->keySound = KeySounds[i];
		}

		children->SetRelativeLocation(startLoc + FVector(0,8*i,0));

	}

}

// Called when the game starts or when spawned
void APianoActor::BeginPlay()
{
	Super::BeginPlay();
	for (int32 i = 0; i < KeySounds.Num(); i++) {

	//키보드 형태로 넣고싶다, 캐스팅
	// 각각의 키보드 액터들마다 가지고 있는 keySound 변수에 음원 파일들을 넣어준다.
	if (KeyActors[i]->GetChildActor() != nullptr) { // 에러 방지 , 음원 없을 때 오류 날 수 있다.
		Cast<AKeyboardActor>(KeyActors[i]->GetChildActor())->keySound = KeySounds[i];
	}
	}
}

// Called every frame
void APianoActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

