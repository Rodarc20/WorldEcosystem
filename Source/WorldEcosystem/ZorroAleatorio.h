// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Zorro.h"
#include "ZorroAleatorio.generated.h"

/**
 * 
 */
UCLASS()
class WORLDECOSYSTEM_API AZorroAleatorio : public AZorro
{
	GENERATED_BODY()
	
public:
    void DeterminarAccion() override;
	
	
	
};
