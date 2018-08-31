// Fill out your copyright notice in the Description page of Project Settings.

#include "Zorro.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"
#include "Engine/StaticMesh.h"
#include "Conejo.h"
#include "Ecosistema.h"
#include "Engine/Engine.h"
#include "WorldEcosystemGameModeBase.h"


// Sets default values
AZorro::AZorro()
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
    Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, 10.0f));
    Mesh->SetRelativeLocation(FVector(FMath::RandRange(-35.0f, 35.0f), FMath::RandRange(-35.0f, 35.0f), 10.0f));
	//ArticulacionCuello->SetWorldScale3D(FVector(0.05f));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));//de usar este creo que debo crear un obtener un  material y ponerselo, este tiene el pivot en el centro de la esfera
    if (MeshAsset.Succeeded()) {
        Mesh->SetStaticMesh(MeshAsset.Object);
        static ConstructorHelpers::FObjectFinder<UMaterial> MeshMaterialAsset(TEXT("Material'/Game/WorldEcosystem/Materials/ZorroMaterial.ZorroMaterial'"));//de usar este creo que debo crear un obtener un  material y ponerselo, este tiene el pivot en el centro de la esfera
        if (MeshMaterialAsset.Succeeded()) {
            Mesh->SetMaterial(0, MeshMaterialAsset.Object);
			//ArticulacionMaterialDynamic = UMaterialInstanceDynamic::Create(CuelloMaterialAsset.Object, this);
        }
    }

}

// Called when the game starts or when spawned
void AZorro::BeginPlay() {
	Super::BeginPlay();
	
}

// Called every frame
void AZorro::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AZorro::DeterminarAccion() {
    /*if (bMuriendo) {
        AccionActual = EAccionZorro::EMorir;
        return;
    }
    if (bReproduciendo) {
        AccionActual = EAccionZorro::EReproducir;
        return;
    }
    //TArray<FAccionConejoStruct> ListaAccionesStructTurno;
    TArray<EAccionZorro> ListaAccionesTurno;
    if (HayConejoDisponible()) {
        ListaAccionesTurno.Add(EAccionZorro::EComer);
    }
    if (CeldaActual) {
        if (CeldaActual->CeldaArriba) {
            ListaAccionesTurno.Add(EAccionZorro::EMoverArriba);
        }
        if (CeldaActual->CeldaAbajo) {
            ListaAccionesTurno.Add(EAccionZorro::EMoverAbajo);
        }
        if (CeldaActual->CeldaDerecha) {
            ListaAccionesTurno.Add(EAccionZorro::EMoverDerecha);
        }
        if (CeldaActual->CeldaIzquierda) {
            ListaAccionesTurno.Add(EAccionZorro::EMoverIzquierda);
        }
    }
    ListaAccionesTurno.Add(EAccionZorro::EEsperar);

    int IdAccion = FMath::RandRange(0, ListaAccionesTurno.Num()-1);
    AccionActual = ListaAccionesTurno[IdAccion];

    if (AccionActual == EAccionZorro::EComer) {
        ConejoComida->bSiendoComido = true;
        //esto es para reservar el pasto que comere, para que cuando evalue otros conejos, no tomen en cuestan este pasto que ya escogi
    }*/
}

void AZorro::EjecutarAccion() {
    if (AccionActual == EAccionZorro::EMorir) {
        Morir();
    }
    else if (AccionActual == EAccionZorro::EReproducir) {
        Reproducir();
    }
    else if (AccionActual == EAccionZorro::EComer) {
        Comer();
    }
    else {
        Mover(AccionActual);
    }
}

void AZorro::IntervaloIteracion() {
    VidaActual--;
    if (!VidaActual) {
        bMuriendo = true;
        //tal vez aqui deba matar al individuo
    }
    IteracionesReproduccionActual++;
    if (IteracionesReproduccionActual == IteracionesReproduccion) {
        bReproduciendo = true;
        //resestablecer la repdorucion actual al ejecutar la accion
    }
}

bool AZorro::HayConejoDisponible() {
    //esta funcion verfica que haya pasto dispoinible para comer, tengo que verificar que ese pasto no este reservado, que baya a ser comido
    TArray<AActor *> ActorsInCelda;
    Trigger->GetOverlappingActors(ActorsInCelda);//le pasamos el array donde se guardaran

    // para cada actor encontrado
    for (int i = 0; i < ActorsInCelda.Num(); ++i) {
        //casteamos el actor a un pickup, esto para quedarno socn tosdos lo pickups que podriian se clases c++ o blueprints,
        AConejo * const ConejoActor = Cast<AConejo>(ActorsInCelda[i]);//por estos usos de pickup es que hemos incluido Pickup.h
        //si el casteo es exitoso y el pickup es valido y esta activo 
        if (ConejoActor && !ConejoActor->bSiendoComido && !ConejoActor->bMuriendo && !ConejoActor->IsPendingKill()) {//se comprueba que no se haya ordenado la destruccion de ese pickup, por que aveces pasa eso
            //entonces llamamos a la funcoin del pickup WasCollected();
            ConejoComida = ConejoActor;
            return true;
        }
    }
    return false;
}

void AZorro::Comer() {
    AGameModeBase * GameMode = UGameplayStatics::GetGameMode(GetWorld());//el miso error de set material
    AWorldEcosystemGameModeBase * EcoGameMode = Cast<AWorldEcosystemGameModeBase>(GameMode);
    AEcosistema * Ecosistema;
    if (EcoGameMode) {
        Ecosistema = EcoGameMode->EcosistemaReference;
        if (Ecosistema) {
            Ecosistema->MatarConejo(ConejoComida);
            VidaActual = VidaMaxima;
        }
    }
}

void AZorro::Morir() {
    AGameModeBase * GameMode = UGameplayStatics::GetGameMode(GetWorld());//el miso error de set material
    AWorldEcosystemGameModeBase * EcoGameMode = Cast<AWorldEcosystemGameModeBase>(GameMode);
    AEcosistema * Ecosistema;

    UE_LOG(LogClass, Log, TEXT("Zorro muriendo."));
    if (EcoGameMode) {
        Ecosistema = EcoGameMode->EcosistemaReference;
        if (Ecosistema) {
            Ecosistema->MatarZorro(this);
        }
    }
}

void AZorro::Reproducir() {
    AGameModeBase * GameMode = UGameplayStatics::GetGameMode(GetWorld());//el miso error de set material
    AWorldEcosystemGameModeBase * EcoGameMode = Cast<AWorldEcosystemGameModeBase>(GameMode);
    AEcosistema * Ecosistema;
    if (EcoGameMode) {
        Ecosistema = EcoGameMode->EcosistemaReference;
        if (Ecosistema) {
            TArray<ACelda *> Celdas;
            if (CeldaActual->CeldaArriba) {
                Celdas.Add(CeldaActual->CeldaArriba);
                if (CeldaActual->CeldaArriba->CeldaDerecha) {
                    Celdas.Add(CeldaActual->CeldaArriba->CeldaDerecha);
                }
                if (CeldaActual->CeldaArriba->CeldaIzquierda) {
                    Celdas.Add(CeldaActual->CeldaArriba->CeldaIzquierda);
                }
            }
            if (CeldaActual->CeldaAbajo) {
                Celdas.Add(CeldaActual->CeldaAbajo);
                if (CeldaActual->CeldaAbajo->CeldaDerecha) {
                    Celdas.Add(CeldaActual->CeldaAbajo->CeldaDerecha);
                }
                if (CeldaActual->CeldaAbajo->CeldaIzquierda) {
                    Celdas.Add(CeldaActual->CeldaAbajo->CeldaIzquierda);
                }
            }
            if (CeldaActual->CeldaDerecha) {
                Celdas.Add(CeldaActual->CeldaDerecha);
            }
            if (CeldaActual->CeldaIzquierda) {
                Celdas.Add(CeldaActual->CeldaIzquierda);
            }
            for (int i = 0; i < NumeroReproduccion; i++) {
                int IdCelda = FMath::RandRange(0, Celdas.Num()-1);
                Ecosistema->CrearZorro(Celdas[IdCelda]);
            }
            IteracionesReproduccionActual = 0;
            bReproduciendo = false;
        }
    }
}

void AZorro::Mover(EAccionZorro Movimiento) {
    if (Movimiento == EAccionZorro::EMoverArriba) {
        CeldaActual = CeldaActual->CeldaArriba;
        SetActorLocation(CeldaActual->GetActorLocation());
    }
    else if (Movimiento == EAccionZorro::EMoverAbajo) {
        CeldaActual = CeldaActual->CeldaAbajo;
        SetActorLocation(CeldaActual->GetActorLocation());
    }
    else if (Movimiento == EAccionZorro::EMoverDerecha) {
        CeldaActual = CeldaActual->CeldaDerecha;
        SetActorLocation(CeldaActual->GetActorLocation());
    }
    else if (Movimiento == EAccionZorro::EMoverIzquierda) {
        CeldaActual = CeldaActual->CeldaIzquierda;
        SetActorLocation(CeldaActual->GetActorLocation());
    }
    else if (Movimiento == EAccionZorro::EEsperar) {
        //no hacer nada
    }
}

