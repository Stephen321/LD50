// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"

#include "ADynamicDayNight.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class LD50_API AADynamicDayNight : public AActor
{
	GENERATED_BODY()
public:
	AADynamicDayNight();

public:
	virtual void Tick(float DeltaSeconds) override;
	virtual bool ShouldTickIfViewportsOnly() const override;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = LD)
	TObjectPtr<class UStaticMeshComponent> DayIndicator;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = LD)
	TObjectPtr<class UStaticMeshComponent> NightIndicator;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = LD)
	TObjectPtr<class ADirectionalLight> SunLight;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = LD)
	TObjectPtr<AActor> TargetPlayer;

private:
};
