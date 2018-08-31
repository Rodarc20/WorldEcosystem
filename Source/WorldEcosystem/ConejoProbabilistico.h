// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Conejo.h"
#include "ConejoProbabilistico.generated.h"

/**
 * 
 */
UCLASS()
class WORLDECOSYSTEM_API AConejoProbabilistico : public AConejo
{
	GENERATED_BODY()
	
public:
    void DeterminarAccion() override;
	
	
	
};
