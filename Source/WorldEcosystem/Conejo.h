// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Celda.h"
#include "Pasto.h"
#include "Conejo.generated.h"

UENUM(BlueprintType)
enum class EAccionConejo: uint8 {
    EMoverArriba UMETA(DisplayName = "Mover Arriba"),
    EMoverAbajo UMETA(DisplayName = "Mover Abajo"),
    EMoverIzquierda UMETA(DisplayName = "Mover Izquierda"),
    EMoverDerecha UMETA(DisplayName = "Mover Derecha"),
    EEsperar UMETA(DisplayName = "Esperar"),
    EComer UMETA(DisplayName = "Comer"),
    EReproducir UMETA(DisplayName = "Reproducir"),
    EMorir UMETA(DisplayName = "Morir")
};

USTRUCT()
struct FAccionConejoStruct {
    GENERATED_BODY()

    UPROPERTY()
    EAccionConejo Accion;

    UPROPERTY()
    AActor * ObjetivoAccion;
    
};


UCLASS()
class WORLDECOSYSTEM_API AConejo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConejo();

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

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    ACelda * CeldaActual;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    APasto * PastoComida;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    bool bMuriendo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    bool bReproduciendo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    bool bSiendoComido;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    int VidaMaxima;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    int VidaActual;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    int NumeroReproduccion;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    int IteracionesReproduccion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    int IteracionesReproduccionActual;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    EAccionConejo AccionActual;

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void DeterminarAccion();

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void EjecutarAccion();

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void IntervaloIteracion();

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    bool HayPastoDisponible();

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void Comer();

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void Morir();

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void Reproducir();

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void Mover(EAccionConejo Movimiento);
};
