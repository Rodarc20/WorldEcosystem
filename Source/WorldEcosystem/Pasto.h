// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Celda.h"
#include "Pasto.generated.h"

UENUM(BlueprintType)
enum class EAccionPasto: uint8 {
    EEsperar UMETA(DisplayName = "Esperar"),
    EReproducir UMETA(DisplayName = "Reproducir"),
    EMorir UMETA(DisplayName = "Morir")
};

USTRUCT()
struct FAccionPastoStruct {
    GENERATED_BODY()

    UPROPERTY()
    EAccionPasto Accion;

    UPROPERTY()
    AActor * ObjetivoAccion;
    
};

UCLASS()
class WORLDECOSYSTEM_API APasto : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APasto();

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
    ACelda * CeldaActual;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    bool bMuriendo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    bool bReproduciendo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    bool bSiendoComido;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    int IteracionesReproduccion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    int IteracionesReproduccionActual;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    EAccionPasto AccionActual;

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void DeterminarAccion();

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void EjecutarAccion();

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void IntervaloIteracion();

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void Morir();

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void Reproducir();

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void CambiarPosicionMesh();
};

//la reproduccion del pasto tiene un comportameinto particular
//cuando llega el momento de la reoduccion si alguna de las celdas esta vacia, la lleno, y tambien, en mi celda, aumento el pasto en una,
//debo cuidar no reproducir dos celdas pasto en una sola vecina
