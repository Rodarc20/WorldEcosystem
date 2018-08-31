// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Zorro.h"
#include "ZorroProbabilistico.generated.h"

/**
 * 
 */
UCLASS()
class WORLDECOSYSTEM_API AZorroProbabilistico : public AZorro
{
	GENERATED_BODY()
	
public:
    void DeterminarAccion() override;
	
	
	
};
