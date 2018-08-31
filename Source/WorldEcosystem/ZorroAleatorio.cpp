// Fill out your copyright notice in the Description page of Project Settings.

#include "ZorroAleatorio.h"

void AZorroAleatorio::DeterminarAccion() {
    if (bMuriendo) {
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
    }
}



