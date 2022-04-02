// Fill out your copyright notice in the Description page of Project Settings.


#include "LDPlayerCharacterBase.h"

#include "LDLog.h"

// Sets default values
ALDPlayerCharacterBase::ALDCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(SpringArmComponentName);
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 450;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(CameraComponentName);
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void ALDCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogLD, Warning, TEXT("Test player character BeginPlay"));
	
}

// Called every frame
void ALDCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ALDCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

