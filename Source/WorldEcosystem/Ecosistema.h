// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Celda.h"
#include "Pasto.h"
#include "Conejo.h"
#include "Zorro.h"
#include "Engine/EngineTypes.h"
#include "Camera/CameraComponent.h"
#include "Ecosistema.generated.h"

UCLASS()
class WORLDECOSYSTEM_API AEcosistema : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEcosistema();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    UCameraComponent * Camara;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    int IteracionActual;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    float TiempoIteracion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    int LadoMundo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    float LadoCelda;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ecosistema")
    TArray<ACelda *> Celdas;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ecosistema")
    TArray<APasto *> Pastos;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ecosistema")
    TArray<AConejo *> Conejos;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ecosistema")
    TArray<AZorro *> Zorros;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    TSubclassOf<class ACelda> CeldaType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    TSubclassOf<class AConejo> ConejoType;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    TSubclassOf<class APasto> PastoType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    TSubclassOf<class AZorro> ZorroType;

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void MatarPasto(APasto * PastoMuriendo);

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void MatarConejo(AConejo * ConejoMuriendo);

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void MatarZorro(AZorro * ZorroMuriendo);

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    APasto * CrearPasto(ACelda * Celda);

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    AConejo * CrearConejo(ACelda * Celda);

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    AZorro * CrearZorro(ACelda * Celda);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    int NumeroConejosReproduccionConejo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    int NumeroIteracionesVidaConejo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    int NumeroIteracionesReproduccionConejo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    int NumeroZorrosReproduccionZorro;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    int NumeroIteracionesVidaZorro;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    int NumeroIteracionesReproduccionZorro;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    int NumeroIteracionesReproduccionPasto;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    int NumeroPastosIniciales;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    int NumeroConejosIniciales;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ecosistema")
    int NumeroZorrosIniciales;

    FTimerHandle TimerDeterminarAccion;

    FTimerHandle TimerEjecutarAccion;

    FTimerHandle TimerIntervalo;

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void IniciarSimulacion();

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void PausarSimulacion();

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void ContinuarSimulacion();

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void DetenerSimulacion();

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void DeterminarAcciones();

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void EjecutarAcciones();

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void Intervalos();

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void CrearMundo();

    UFUNCTION(BlueprintCallable, Category = "Ecosistema")
    void PoblarMundo();
};


//esta clase es la encargada de crear todo