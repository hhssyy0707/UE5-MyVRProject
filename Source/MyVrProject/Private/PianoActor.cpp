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

	
	// ��ü Ű������ ����
	float width = (5 * 8) + (3 * (8 - 1));
	// width ������ ������ Ű������ ������ ���´�.
	FVector startLoc = FVector(0, width * 0.5f * -1, 0);


	//for (int32 i = 0; i < KeySounds.Num(); i++) {
	for (int32 i = 0; i < 8; i++) {

		// Ű���� �̸� �ֱ�
		FString ActorName = FString::Printf(TEXT("keyboard_%d"),i+1);
		UChildActorComponent* children = CreateDefaultSubobject<UChildActorComponent>(FName(*ActorName));
		children->SetupAttachment(RootComponent);

		// keyActor�� ������ Ű���带 �ϳ��� �־��ش�
		KeyActors.Add(children);

		//Ű���� ���·� �ְ�ʹ�, ĳ����
		// ������ Ű���� ���͵鸶�� ������ �ִ� keySound ������ ���� ���ϵ��� �־��ش�.
		if (children->GetChildActor() != nullptr) { // ���� ���� , ���� ���� �� ���� �� �� �ִ�.
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

	//Ű���� ���·� �ְ�ʹ�, ĳ����
	// ������ Ű���� ���͵鸶�� ������ �ִ� keySound ������ ���� ���ϵ��� �־��ش�.
	if (KeyActors[i]->GetChildActor() != nullptr) { // ���� ���� , ���� ���� �� ���� �� �� �ִ�.
		Cast<AKeyboardActor>(KeyActors[i]->GetChildActor())->keySound = KeySounds[i];
	}
	}
}

// Called every frame
void APianoActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

