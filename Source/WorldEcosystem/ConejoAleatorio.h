// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Conejo.h"
#include "ConejoAleatorio.generated.h"

/**
 * 
 */
UCLASS()
class WORLDECOSYSTEM_API AConejoAleatorio : public AConejo
{
	GENERATED_BODY()
	
public:
    void DeterminarAccion() override;
	
	
};
