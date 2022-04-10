// Fill out your copyright notice in the Description page of Project Settings.


#include "ADynamicDayNight.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/DirectionalLight.h"

#include "LDLog.h"

#define NIGHT_START_ANGLE 182
#define NIGHT_END_ANGLE 161
#define DAY_START_ANGLE 346
#define DAY_END_ANGLE 8

PRAGMA_DISABLE_OPTIMIZATION

AADynamicDayNight::AADynamicDayNight()
{

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> EditorSphereMesh(TEXT("/Engine/EditorMeshes/EditorSphere"));

	DayIndicator = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DayIndicator"));
	DayIndicator->SetupAttachment(RootComponent);
	DayIndicator->SetMobility(EComponentMobility::Movable);
	DayIndicator->SetStaticMesh(EditorSphereMesh.Object);

	NightIndicator = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NightIndicator"));
	NightIndicator->SetupAttachment(RootComponent);
	NightIndicator->SetMobility(EComponentMobility::Movable);
	NightIndicator->SetStaticMesh(EditorSphereMesh.Object);

	bAllowTickBeforeBeginPlay = true;
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AADynamicDayNight::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (SunLight)
	{
		const float NightStart = NightIndicator->GetComponentLocation().X;
		const float DayStart = DayIndicator->GetComponentLocation().X;
		const float Distance = DayStart - NightStart;

		float PlayerDistance = (DayStart - NightStart) * 0.5f;
		if (TargetPlayer)
		{
			PlayerDistance = TargetPlayer->GetActorLocation().X - NightStart;
		}
		if (PlayerDistance < 0)
		{
			// TODO: danger!
			PlayerDistance = 0;
		}
		else if (PlayerDistance > Distance)
		{
			// TODO: danger!
			PlayerDistance = Distance;
		}

		const float NewSunAngle = FMath::Lerp(NIGHT_START_ANGLE, DAY_START_ANGLE, PlayerDistance / Distance);
		SunLight->SetActorRotation(FRotator(NewSunAngle, 0, 0));
	}
}

bool AADynamicDayNight::ShouldTickIfViewportsOnly() const
{
	if (const UWorld* World = GetWorld())
	{
		switch (World->WorldType)
		{
		case EWorldType::Editor:
			return true;
		default:
			return false;
		}
	}
	return false;
}
PRAGMA_ENABLE_OPTIMIZATION