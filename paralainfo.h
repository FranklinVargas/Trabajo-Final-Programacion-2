#pragma once
#include "Juego.h"

ref class Cinfo {
	List <CImagen^>^ Fondo_instruccion;
	List<CAnimacion^>^ muestra;
	CImagen^ Fondooficial;
	CAnimacion^ muestraoficial;
public:
	Cinfo() {
		this->Fondo_instruccion = gcnew List<CImagen^>;
		this->Fondo_instruccion->Add(gcnew CImagen("FONDOS\\Fondoaasasins.jpg", System::Drawing::Rectangle(-25, -75, 800, 500)));
		this->Fondo_instruccion->Add(gcnew CImagen("FONDOS\\AliadosFondo.jpg", System::Drawing::Rectangle(-25, -75, 800, 500)));
		this->Fondo_instruccion->Add(gcnew CImagen("FONDOS\\FondoPortal.jpg", System::Drawing::Rectangle(-25, -75, 800, 500)));
		//imagenes conversacion
		this->Fondo_instruccion->Add(gcnew CImagen("FONDOS\\dialogo1.jpg", System::Drawing::Rectangle(-25, -75, 800, 500)));
		this->Fondo_instruccion->Add(gcnew CImagen("FONDOS\\dialogo2.jpg", System::Drawing::Rectangle(-25, -75, 800, 500)));
		this->Fondo_instruccion->Add(gcnew CImagen("FONDOS\\dialogo3.jpg", System::Drawing::Rectangle(-25, -75, 800, 500)));
		this->Fondo_instruccion->Add(gcnew CImagen("FONDOS\\dialogo4.jpg", System::Drawing::Rectangle(-25, -75, 800, 500)));
		this->Fondo_instruccion->Add(gcnew CImagen("FONDOS\\dialogo5.jpg", System::Drawing::Rectangle(-25, -75, 800, 500)));
		this->Fondo_instruccion->Add(gcnew CImagen("FONDOS\\CorruptFondo.jpg", System::Drawing::Rectangle(-25, -75, 800, 500)));


		this->muestra = gcnew List<CAnimacion^>;
		this->muestra->Add(gcnew CAnimacion("FONDOS\\Assassins.png", System::Drawing::Rectangle(350, 100, 50, 50), 4, 4, 16));
		this->muestra->Add(gcnew CAnimacion("FONDOS\\aliado2.png", System::Drawing::Rectangle(350, 100, 50, 50), 4, 4, 16));
		this->muestra->Add(gcnew CAnimacion("FONDOS\\portal.png", System::Drawing::Rectangle(350, 100, 50, 50), 3, 3, 9));
		this->muestra->Add(gcnew CAnimacion("FONDOS\\Corrupts.png", System::Drawing::Rectangle(350, 100, 50, 50), 4, 4, 16));

	}
	~Cinfo() {

		for (short i = 0; i < Fondo_instruccion->Count; i++)
		{delete Fondo_instruccion[i];}
		for (short i = 0; i < muestra->Count; i++)
		{delete muestra[i];}
		delete this->Fondo_instruccion, this->muestra;		
		delete this->Fondooficial, this->muestraoficial;
	}


	void dialogos(short a) {

		switch (a)
		{
		case 1:
			Fondooficial = Fondo_instruccion[3];
			break;
		case 2:
			Fondooficial = Fondo_instruccion[4];
			break;
		case 3:
			Fondooficial = Fondo_instruccion[5];
			break;
		case 4:
			Fondooficial = Fondo_instruccion[6];
			break;
		case 5:
			Fondooficial = Fondo_instruccion[7];
			break;
		}
	}
	void instruccione(short a) {
		switch (a)
		{
		case 1:
			Fondooficial = Fondo_instruccion[0];
			muestraoficial = muestra[0];
			break;
		case 2:
			Fondooficial = Fondo_instruccion[1];
			muestraoficial = muestra[1];
			break;
		case 3:
			Fondooficial = Fondo_instruccion[2];
			muestraoficial = muestra[2];
			break;
		case 4:
			Fondooficial = Fondo_instruccion[8];
			muestraoficial = muestra[3];
			break;
		default:
			break;
		}
	}

	void instruccionnnn( Graphics^ graficador) {
		this->Fondooficial->dibujar(graficador);
		this->muestraoficial->dibujar(graficador);
	}
	void dialogossss(Graphics^ graficador) {
		this->Fondooficial->dibujar(graficador);
	}


};