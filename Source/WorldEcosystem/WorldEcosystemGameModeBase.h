// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ecosistema.h"
#include "SimulationHUD.h"
#include "GameFramework/GameModeBase.h"
#include "WorldEcosystemGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class WORLDECOSYSTEM_API AWorldEcosystemGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

    AWorldEcosystemGameModeBase();

    AWorldEcosystemGameModeBase(const FObjectInitializer & ObjectInitializer);//creado para solucionar el error en esta clase con el macro generated body

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GeoVisualization", Meta = (BlueprintProtected = "true"))//significa que solo se puede cambiar en el constructor
    TSubclassOf<USimulationHUD> TypeHUDWidget;  

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeoVisualization")
    USimulationHUD * VisualizationHUDReference;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    AEcosistema * EcosistemaReference;

    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;
	
    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void CargarValoresDefault();
	
	
};
