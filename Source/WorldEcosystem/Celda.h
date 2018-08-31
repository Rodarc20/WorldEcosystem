// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Celda.generated.h"


UENUM(BlueprintType)
enum class EDireccion : uint8 {
    EArriba UMETA(DisplayName = "Arriba"),
    EAbajo UMETA(DisplayName = "Abajo"),
    EIzquierda UMETA(DisplayName = "Izquierda"),
    EDerecha UMETA(DisplayName = "Derecha"),
    ENinguno UMETA(DisplayName = "Ninguno")
};


UCLASS()
class WORLDECOSYSTEM_API ACelda : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACelda();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    UStaticMeshComponent * Mesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    UBoxComponent * Trigger;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    ACelda * CeldaArriba;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    ACelda * CeldaAbajo;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    ACelda * CeldaIzquierda;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    ACelda * CeldaDerecha;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    bool bPastoCreandose;//este bool es para la reserva de pasto, al momento de crear, por quepodria crear dos pastos en la fase de reporudcion, cada uno por alguna celda adjacente con pasto

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    bool HayPasto();
};
