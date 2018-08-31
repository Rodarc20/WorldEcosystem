// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Celda.h"
#include "Conejo.h"
#include "Zorro.generated.h"

UENUM(BlueprintType)
enum class EAccionZorro: uint8 {
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
struct FAccionZorroStruct {
    GENERATED_BODY()

    UPROPERTY()
    EAccionZorro Accion;

    UPROPERTY()
    AActor * ObjetivoAccion;
    
};

UCLASS()
class WORLDECOSYSTEM_API AZorro : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZorro();

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
    AConejo * ConejoComida;

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
    EAccionZorro AccionActual;

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    virtual void DeterminarAccion();//quiza deberia retornar la accion

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void EjecutarAccion();

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void IntervaloIteracion();

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    bool HayConejoDisponible();

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void Comer();

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void Morir();

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void Reproducir();

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void Mover(EAccionZorro Movimiento);
};
