// Fill out your copyright notice in the Description page of Project Settings.

#include "Pasto.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"
#include "Engine/StaticMesh.h"
#include "Ecosistema.h"
#include "Engine/Engine.h"
#include "WorldEcosystemGameModeBase.h"


// Sets default values
APasto::APasto()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
    RootComponent = Trigger;
    //Zona->SetupAttachment(RootComponent);
    Trigger->InitBoxExtent(FVector(45.0f, 45.0f, 45.0f));
    //Trigger->OnComponentBeginOverlap.AddDynamic(this, &APasto::OnBeginOverlapZona);
    //Trigger->OnComponentEndOverlap.AddDynamic(this, &APasto::OnEndOverlapZona);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(RootComponent);
	Mesh->SetRelativeScale3D(FVector(0.20f));
    //Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, 10.2f));
    Mesh->SetRelativeLocation(FVector(FMath::RandRange(-35.0f, 35.0f), FMath::RandRange(-35.0f, 35.0f), 10.2f));
	//ArticulacionCuello->SetWorldScale3D(FVector(0.05f));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'"));//de usar este creo que debo crear un obtener un  material y ponerselo, este tiene el pivot en el centro de la esfera
    if (MeshAsset.Succeeded()) {
        Mesh->SetStaticMesh(MeshAsset.Object);
        static ConstructorHelpers::FObjectFinder<UMaterial> MeshMaterialAsset(TEXT("Material'/Game/WorldEcosystem/Materials/PastoMaterial.PastoMaterial'"));//de usar este creo que debo crear un obtener un  material y ponerselo, este tiene el pivot en el centro de la esfera
        if (MeshMaterialAsset.Succeeded()) {
            Mesh->SetMaterial(0, MeshMaterialAsset.Object);
			//ArticulacionMaterialDynamic = UMaterialInstanceDynamic::Create(CuelloMaterialAsset.Object, this);
        }
    }

}

// Called when the game starts or when spawned
void APasto::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APasto::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APasto::DeterminarAccion() {
    if (bMuriendo) {
        AccionActual = EAccionPasto::EMorir;
    }
    else if (bReproduciendo) {
        AccionActual = EAccionPasto::EReproducir;
    }
    else {
        AccionActual = EAccionPasto::EEsperar;
    }
}

void APasto::EjecutarAccion() {
    if (AccionActual == EAccionPasto::EMorir) {
        Morir();
    }
    else if (AccionActual == EAccionPasto::EReproducir) {
        Reproducir();
    }
    else {
        //nada
    }
}

void APasto::IntervaloIteracion() {
    IteracionesReproduccionActual++;
    if (IteracionesReproduccionActual == IteracionesReproduccion) {
        bReproduciendo = true;
        //resestablecer la repdorucion actual al ejecutar la accion
    }
}

void APasto::Morir() {
        //en teoria no muero solo, no tengo vida
}

void APasto::Reproducir() {
    AGameModeBase * GameMode = UGameplayStatics::GetGameMode(GetWorld());//el miso error de set material
    AWorldEcosystemGameModeBase * EcoGameMode = Cast<AWorldEcosystemGameModeBase>(GameMode);
    AEcosistema * Ecosistema;
    if (EcoGameMode) {
        Ecosistema = EcoGameMode->EcosistemaReference;
        if (Ecosistema) {
            Ecosistema->CrearPasto(CeldaActual);
            if (CeldaActual->CeldaArriba) {
                if (!CeldaActual->CeldaArriba->HayPasto()) {
                    Ecosistema->CrearPasto(CeldaActual->CeldaArriba);
                }
                if (CeldaActual->CeldaArriba->CeldaDerecha) {
                    if (!CeldaActual->CeldaArriba->CeldaDerecha->HayPasto()) {
                        Ecosistema->CrearPasto(CeldaActual->CeldaArriba->CeldaDerecha);
                    }
                }
                if (CeldaActual->CeldaArriba->CeldaIzquierda) {
                    if (!CeldaActual->CeldaArriba->CeldaIzquierda->HayPasto()) {
                        Ecosistema->CrearPasto(CeldaActual->CeldaArriba->CeldaIzquierda);
                    }
                }
            }
            if (CeldaActual->CeldaAbajo) {
                if (!CeldaActual->CeldaAbajo->HayPasto()) {
                    Ecosistema->CrearPasto(CeldaActual->CeldaAbajo);
                }
                if (CeldaActual->CeldaAbajo->CeldaDerecha) {
                    if (!CeldaActual->CeldaAbajo->CeldaDerecha->HayPasto()) {
                        Ecosistema->CrearPasto(CeldaActual->CeldaAbajo->CeldaDerecha);
                    }
                }
                if (CeldaActual->CeldaAbajo->CeldaIzquierda) {
                    if (!CeldaActual->CeldaAbajo->CeldaIzquierda->HayPasto()) {
                        Ecosistema->CrearPasto(CeldaActual->CeldaAbajo->CeldaIzquierda);
                    }
                }
            }
            if (CeldaActual->CeldaDerecha) {
                if (!CeldaActual->CeldaDerecha->HayPasto()) {
                    Ecosistema->CrearPasto(CeldaActual->CeldaDerecha);
                }
            }
            if (CeldaActual->CeldaIzquierda) {
                if (!CeldaActual->CeldaIzquierda->HayPasto()) {
                    Ecosistema->CrearPasto(CeldaActual->CeldaIzquierda);
                }
            }
            IteracionesReproduccionActual = 0;
            bReproduciendo = false;
        }
    }
}

void APasto::CambiarPosicionMesh() {
    //desde 35 a -35
    Mesh->SetRelativeLocation(FVector(FMath::RandRange(-35.0f, 35.0f), FMath::RandRange(-35.0f, 35.0f), 10.2f));
}

