// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Ecosistema.h"
#include "SimulationHUD.generated.h"

/**
 * 
 */
UCLASS()
class WORLDECOSYSTEM_API USimulationHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
    USimulationHUD(const FObjectInitializer & ObjectInitializer);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    AEcosistema * EcosistemaReference;
	
	
	
};
