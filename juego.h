#pragma once

#include <Windows.h>
#include <MMSystem.h>
#include <fstream>
#include <time.h>
using namespace std;
using namespace System;
using namespace System::Drawing;
using namespace System::Collections::Generic;
#define SUELO 0
#define MURO 1

const short lado = 30;
enum Direccion { ABAJO, IZQUIERDA, DERECHA, ARRIBA };

ref class CGrafico abstract {
protected:
	System::Drawing::Rectangle area_dibujo;
	Bitmap^ imagen;
public:
	CGrafico(System::Drawing::Rectangle area_dibujo)
		: area_dibujo(area_dibujo) {}
	~CGrafico() { delete this->imagen; }
	virtual void dibujar(Graphics^ graficador) abstract;
	void hacer_transparente() {
		Color fondo = this->imagen->GetPixel(0, 0);
		this->imagen->MakeTransparent(fondo);
	}
};
ref class CImagen : public CGrafico
{
public:
	CImagen(String^ ruta, System::Drawing::Rectangle area_dibujo) :
		CGrafico(area_dibujo) {
		this->imagen = gcnew Bitmap(ruta);
		this->area_dibujo = area_dibujo;
	}
	CImagen(Bitmap^ imagen, System::Drawing::Rectangle area_dibujo):
		CGrafico(area_dibujo){
		this->imagen = imagen;
		this->area_dibujo = area_dibujo;
	}
	 void dibujar(Graphics^ graficador) override{
		graficador->DrawImage(this->imagen, this->area_dibujo);
	}
	Point get_ubicacion() {
		return Point(this->area_dibujo.X + this->area_dibujo.Width / 2,
			this->area_dibujo.Y + this->area_dibujo.Height / 2);
	}
	
};

ref class CEscenario {
	Bitmap^ piso, ^ muro;
	const short n_columnas = 33;
	const short n_filas = 17;
	short** mapa;
	Random^ r;
	short general;
public:
	CEscenario() {
		r = gcnew Random;
		general = short(r->Next(1, 4));
		if (general == 1) {
			this->piso = gcnew Bitmap("FONDOS\\texturas2.jpg");
			this->muro = gcnew Bitmap("FONDOS\\texturas.jpg");
		}
		else if (general== 2) {
		this->piso = gcnew Bitmap("FONDOS\\textura.jpg");
		this->muro = gcnew Bitmap("FONDOS\\textura2.jpg");
		}
		else if (general == 3) {
			this->piso = gcnew Bitmap("FONDOS\\textu2.jpg");
			this->muro = gcnew Bitmap("FONDOS\\textu.jpg");
		}
		
		this->cargar_mapa(general);
	}
	~CEscenario() {
		delete this->piso, this->muro;
		for (short f = 0; f < this->n_filas; ++f)
			delete[] this->mapa[f];
		delete[] this->mapa;
	}
	void dibujar(Graphics^ graficador) {
		for (short f = 0; f < this->n_filas; ++f) {
			for (short c = 0; c < this->n_columnas; ++c) {
				System::Drawing::Rectangle area = System::Drawing::Rectangle(c * lado, f * lado, lado, lado);
				graficador->DrawImage(this->seleccionar_imagen(this->mapa[f][c]), area);
			}
		}
	}
	System::Drawing::Size get_dimensiones() {
		return System::Drawing::Size(this->n_columnas * lado, this->n_filas * lado);
	}

	bool es_camino(System::Drawing::Rectangle area_jugador, Direccion direccion) {
		short x1, y1, x2, y2;
		short x_jug = area_jugador.X, y_jug = area_jugador.Y;
		switch (direccion)
		{
		case DERECHA:	x1 = x2 = (area_jugador.X + lado - 1 + 5) / lado;
			y1 = (area_jugador.Y) / lado;
			y2 = (area_jugador.Y + lado - 1) / lado; break;
		case IZQUIERDA: x1 = x2 = (area_jugador.X - 5) / lado;
			y1 = (area_jugador.Y) / lado;
			y2 = (area_jugador.Y + lado - 1) / lado; break;
		case ABAJO: y1 = y2 = (area_jugador.Y + lado - 1 + 5) / lado;
			x1 = (area_jugador.X) / lado;
			x2 = (area_jugador.X + lado - 1) / lado; break;
		case ARRIBA: y1 = y2 = (area_jugador.Y - 5) / lado;
			x1 = (area_jugador.X) / lado;
			x2 = (area_jugador.X + lado - 1) / lado; break;
		}

		System::Drawing::Rectangle cuadro1 = System::Drawing::Rectangle(x1 * lado, y1 * lado, lado, lado);
		System::Drawing::Rectangle cuadro2 = System::Drawing::Rectangle(x2 * lado, y2 * lado, lado, lado);

		return (this->mapa[y1][x1] == SUELO && this->mapa[y2][x2] == SUELO);
	}
	bool es_piso(System::Drawing::Rectangle un_area) { 
		short x1, y1;
		x1 = (un_area.X ) / lado;
		y1 = (un_area.Y )/lado;
		return (this->mapa[y1][x1] == SUELO);
	}
	short get_tipo_mapa() { return this->general; }
private:
	bool cargar_mapa(short n) {
		ifstream archivo;
		if (n == 1) { archivo.open("FONDOS\\mapa.txt"); }
		else if (n == 2) { archivo.open("FONDOS\\mapa2.txt"); }
		else if (n == 3) { archivo.open("FONDOS\\mapa3.txt"); }

		if (archivo.is_open()) {
			this->mapa = new short* [this->n_filas];
			for (short f = 0; f < this->n_filas; ++f) {
				this->mapa[f] = new short[this->n_columnas];
				for (short c = 0; c < this->n_columnas; ++c) {
					archivo >> this->mapa[f][c];
				}
			}
			archivo.close();
			return true;
		}
		else return false;
	}
	Bitmap^ seleccionar_imagen(short id) {
		switch (id) {
		case 0: return this->piso;
		case 1: return this->muro;
		}
	}
};

ref class CSprite : public CGrafico {
protected:
	short n_fil;
	short n_col;
	short indice;
	short direccion;
public:
	CSprite(String^ ruta, System::Drawing::Rectangle area_dibujo, short n_fil, short n_col)
		: CGrafico(area_dibujo), n_col(n_col), n_fil(n_fil), indice(0) {
		this->imagen = gcnew Bitmap(ruta);
		this->hacer_transparente();
	}
	
	void dibujar(Graphics^ graficador) override {
		graficador->DrawImage(this->imagen, this->area_dibujo, this->obtener_recorte(), GraphicsUnit::Pixel);
		++this->indice %= this->n_col;
	}
	System::Drawing::Rectangle posicion() {
		return this->area_dibujo;
	}
protected:
	System::Drawing::Rectangle obtener_recorte() {
		short ancho = this->imagen->Width / this->n_col;
		short alto = this->imagen->Height / this->n_fil;
		short x = this->indice * ancho;
		short y = this->direccion * alto;
		return System::Drawing::Rectangle(x, y, ancho, alto);
	}
};
ref class CAnimacion : public CSprite
{
protected:
	short n_subimagenes;
public:
	CAnimacion(String^ ruta, System::Drawing::Rectangle area_dibujo, short n_f, short n_c, short n_subi) :CSprite(ruta, area_dibujo, n_f, n_c)
	{
		this->n_subimagenes = n_subi;
		this->indice = 0;
		this->hacer_transparente();
	}
	void dibujar(Graphics^ graficador)override
	{
		System::Drawing::Rectangle area_recorte = recorte_animado();
		graficador->DrawImage(this->imagen, this->area_dibujo, area_recorte, GraphicsUnit::Pixel);
		if (++this->indice == this->n_subimagenes) { indice = 0; }
	}

	virtual System::Drawing::Rectangle recorte_animado()
	{
		short ancho_subimagen = this->imagen->Width / this->n_col;
		short alto_subimagen = this->imagen->Height / this->n_fil;
		short x = this->indice % this->n_col * ancho_subimagen;
		short y = this->indice / this->n_col * alto_subimagen;
		return System::Drawing::Rectangle(x, y, ancho_subimagen, alto_subimagen);
	}

	System::Drawing::Rectangle posicion() {
		return this->area_dibujo;
	}

};

ref class CJugador : public CSprite {
	short vida;
public:
	CJugador()
		: CSprite("SPRITE\\aliado.png", System::Drawing::Rectangle(lado, lado*15, lado, lado), 4, 4) {
		this-> vida = 10;
	}

	void mover(Direccion direccion, CEscenario^ escenario) {
		this->direccion = (short)direccion;
		if (escenario->es_camino(this->area_dibujo, direccion)) {
			switch (direccion) {
			case ARRIBA: this->area_dibujo.Y -= 5; break;
			case ABAJO: this->area_dibujo.Y += 5; break;
			case DERECHA: this->area_dibujo.X += 5; break;
			case IZQUIERDA: this->area_dibujo.X -= 5; break;
			}
		}
	}

	short getx() { return this->area_dibujo.X; }
	short gety() { return this->area_dibujo.Y; }
	void setx(short x) { this->area_dibujo.X=x; }
	void sety(short y) { this->area_dibujo.Y=y; }
	short get_vida() {return vida;}
	void perder_vida() { this->vida-=1; }
	//analizar
	bool hay_colision(System::Drawing::Rectangle otro) {
		if (this->area_dibujo.IntersectsWith(otro)) return true;
		else return false;
	}
	void muerte() {
	
	}
};

ref class CCorrutps : public CSprite {
	CAnimacion^ explosion;
	Random^ r;
	short countm;
	short countm2;
public:
	CCorrutps(System::Drawing::Rectangle area_dibujo)
		:CSprite("SPRITE\\Corrupts.png", area_dibujo, 4, 4) {
		this->area_dibujo = area_dibujo;
		r = gcnew Random; countm = 0; countm2 = 0;
	}
	CAnimacion^ explosion_kamikaze() {
		return this->explosion = gcnew CAnimacion("SPRITE\\explot.png", this->area_dibujo, 4, 4, 16);
	}
	void perseguir(short x, short y, CEscenario^ escenario) {

		short distanciax = x - area_dibujo.X; if (distanciax < 1) { distanciax = distanciax * -1; }
		short distanciay = y - area_dibujo.Y; if (distanciay < 1) { distanciay = distanciay * -1; }

		if (escenario->es_camino(area_dibujo, ARRIBA) == true&&(x==area_dibujo.X)) {
			if (distanciay != 0)this->area_dibujo.Y -= 5;
		}

		else if (escenario->es_camino(area_dibujo, ABAJO) == true&&(x==area_dibujo.X)) {
			if (distanciay != 0)this->area_dibujo.Y += 5;
		}

		else if (escenario->es_camino(area_dibujo, IZQUIERDA)== true&& (y == area_dibujo.Y)) {
			if (distanciax != 0)this->area_dibujo.X -= 5;
		}

		else if (escenario->es_camino(area_dibujo, DERECHA) == true&&(y == area_dibujo.Y)) {
			if (distanciax != 0)this->area_dibujo.X += 5;
		}
	}
	bool cercania(short x, short y) {
		if ((x - area_dibujo.X <= lado * 2 && x - area_dibujo.X >= lado * -2) && y == area_dibujo.Y ||
			(y - area_dibujo.Y <= lado * 2 && y - area_dibujo.Y >= lado * -2) && x == area_dibujo.X) return true;
		else return false;
	}
	void mover(CEscenario^ escenario) {
		short n = r->Next(1, 3);
		switch (n)
		{
		case 1: moverforma1(escenario);
			break;
		case 2:	moverforma2(escenario);
			break;
		}
	}
private:
	void moverforma1(CEscenario^ escenario) {
		if (this->countm == 0) {
			if (escenario->es_camino(area_dibujo, DERECHA) == true) { area_dibujo.X += 5; }
			if (escenario->es_camino(area_dibujo, DERECHA) == false)  this->countm = 1; 
		}
		if (this->countm == 1) {
			if (escenario->es_camino(area_dibujo, IZQUIERDA) == true) { area_dibujo.X -= 5; }
			if (escenario->es_camino(area_dibujo, IZQUIERDA) == false) this->countm = 0;
		}
	}
	void moverforma2(CEscenario^ escenario) {
		if (this->countm2 == 0) {
			if (escenario->es_camino(area_dibujo, ARRIBA) == true) { area_dibujo.Y -= 5; }
			if (escenario->es_camino(area_dibujo, ARRIBA) == false) this->countm2 = 1;
		}
		if (this->countm2 == 1) {
			if (escenario->es_camino(area_dibujo, ABAJO) == true) { area_dibujo.Y += 5; }
			if (escenario->es_camino(area_dibujo, ABAJO) == false) this->countm2 = 0;
		}
	}
};
ref class CAliados : public CSprite {
	CAnimacion^ pelea;
	Random^ r;
	short countm;
	short countm2;
public:
	CAliados(System::Drawing::Rectangle area_dibujo)
		:CSprite("SPRITE\\aliado2.png", area_dibujo, 4, 4) {
		this->area_dibujo = area_dibujo;
		r = gcnew Random; countm = 0; countm2 = 0;
	}
	CAnimacion^ animacion_pelea() {
		return this->pelea = gcnew CAnimacion("SPRITE\\pelea.png", this->area_dibujo, 1, 4, 4);
	}
	void mover(CEscenario^ escenario) {
		short n = r->Next(1, 3);
		switch (n)
		{
		case 1: moverforma1(escenario);
			break;
		case 2:	moverforma2(escenario);
			break;
		}
	}
	bool colision(System::Drawing::Rectangle otro) {
		if (this->area_dibujo.IntersectsWith(otro)) return true;
		else return false;
	}
private:
	void moverforma1(CEscenario^ escenario) {
		if (this->countm == 0) {
			if (escenario->es_camino(area_dibujo, DERECHA) == true) { area_dibujo.X += 5; }
			if (escenario->es_camino(area_dibujo, DERECHA) == false)  this->countm = 1; 
		}
		if (this->countm == 1) {
			if (escenario->es_camino(area_dibujo, IZQUIERDA) == true) { area_dibujo.X -= 5; }
			if (escenario->es_camino(area_dibujo, IZQUIERDA) == false) this->countm = 0;
		}
	}
	void moverforma2(CEscenario^ escenario) {
		if (this->countm2 == 0) {
			if (escenario->es_camino(area_dibujo, ARRIBA) == true) { area_dibujo.Y -= 5; }
			if (escenario->es_camino(area_dibujo, ARRIBA) == false) this->countm2 = 1;
		}
		if (this->countm2 == 1) {
			if (escenario->es_camino(area_dibujo, ABAJO) == true) { area_dibujo.Y += 5; }
			if (escenario->es_camino(area_dibujo, ABAJO) == false) this->countm2 = 0;
		}
	}
};

ref class CAssasins : public CSprite {
	CAnimacion^ explosion;
	Random^ r;
	short countm;
	short countm2;
public:
	CAssasins(System::Drawing::Rectangle area_dibujo)
		:CSprite("SPRITE\\Assassins.png", area_dibujo, 4, 4) {
		this->area_dibujo = area_dibujo;
		r = gcnew Random; countm = 0; countm2 = 0;
	}
	CAnimacion^ explosion_kamikaze() {
		return this->explosion = gcnew CAnimacion("SPRITE\\explot.png", this->area_dibujo, 4, 4, 16);
	}
	void mover(CEscenario^ escenario) {
		short n = r->Next(1, 3);
		switch (n)
		{
		case 1: moverforma1(escenario);
			break;
		case 2:	moverforma2(escenario);
			break;
		}
	}
	bool colision(System::Drawing::Rectangle otro) {
		if (this->area_dibujo.IntersectsWith(otro)) return true;
		else return false;
	}
	void perseguir(short x, short y, CEscenario^ escenario) {

		short distanciax = x - area_dibujo.X; if (distanciax < 1) { distanciax = distanciax * -1; }
		short distanciay = y - area_dibujo.Y; if (distanciay < 1) { distanciay = distanciay * -1; }
		System::Drawing::Rectangle areaaux, aux2, aux3, aux4;
		areaaux = area_dibujo; aux2 = area_dibujo; aux3 = area_dibujo; aux4 = area_dibujo;
		areaaux.Y -= lado; aux2.Y += lado; aux3.X -= lado; aux4.X += lado;

		if ((escenario->es_camino(area_dibujo, ARRIBA) == true)&& (escenario->es_camino(areaaux, ARRIBA) == true)&& (x == area_dibujo.X)) {
			if (distanciay != 0)this->area_dibujo.Y -= 10;
		}

		else if ((escenario->es_camino(area_dibujo, ABAJO) == true) && (escenario->es_camino(aux2, ABAJO) == true) && (x == area_dibujo.X)) {
			if (distanciay != 0)this->area_dibujo.Y += 10;
		}

		else if ((escenario->es_camino(area_dibujo, IZQUIERDA) == true) && (escenario->es_camino(aux3, IZQUIERDA) == true) && (y == area_dibujo.Y)) {
			if (distanciax != 0)this->area_dibujo.X -= 10;
		}

		else if ((escenario->es_camino(area_dibujo, DERECHA) == true)&& (escenario->es_camino(aux4, DERECHA) == true) && (y == area_dibujo.Y)) {
			if (distanciax != 0)this->area_dibujo.X += 10;
		}
	}
	bool cercania(short x, short y) {
		if ((x - area_dibujo.X <= lado * 4 && x - area_dibujo.X >= lado * -4) && y == area_dibujo.Y ||
			(y - area_dibujo.Y <= lado * 4 && y - area_dibujo.Y >= lado * -4) && x == area_dibujo.X) return true;
		else return false;
	}
private:
	void moverforma1(CEscenario^ escenario) {
		if (this->countm == 0) {
			if (escenario->es_camino(area_dibujo, DERECHA) == true) { area_dibujo.X += 10; }
			if (escenario->es_camino(area_dibujo, DERECHA) == false)  this->countm = 1;
		}
		if (this->countm == 1) {
			if (escenario->es_camino(area_dibujo, IZQUIERDA) == true) { area_dibujo.X -= 10; }
			if (escenario->es_camino(area_dibujo, IZQUIERDA) == false) this->countm = 0;
		}
	}
	void moverforma2(CEscenario^ escenario) {
		if (this->countm2 == 0) {
			if (escenario->es_camino(area_dibujo, ARRIBA) == true) { area_dibujo.Y -= 10; }
			if (escenario->es_camino(area_dibujo, ARRIBA) == false) this->countm2 = 1;
		}
		if (this->countm2 == 1) {
			if (escenario->es_camino(area_dibujo, ABAJO) == true) { area_dibujo.Y += 10; }
			if (escenario->es_camino(area_dibujo, ABAJO) == false) this->countm2 = 0;
		}
	}

};



ref class CJuego {
	//objetos clave
	CJugador^ principal;
	List<CCorrutps^>^ corrupto;
	List<CAliados^>^ aliado;
	List<CAssasins^>^ assasin;
	CEscenario^ escenario;
	//añadidos
	CAnimacion^ portal;
	CAnimacion^ explosion;
	CAnimacion^ explosion2;
	CAnimacion^ flag;
	CAnimacion^ Lose;
	CAnimacion^ Win;
	int tiempo;
	//verificadores extra
	bool existeportal;
	bool creacionportal;
	bool indicador_explosion;
	bool creacionassasins;
public:
	CJuego() {
		PlaySound(TEXT("AUDIOS\\fondom.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
		Lose = gcnew CAnimacion("FONDOS\\over.png", System::Drawing::Rectangle(-75, -25, 900, 500), 3, 4, 12);
		Win = gcnew CAnimacion("FONDOS\\win.png", System::Drawing::Rectangle(-75, -25, 850, 450), 3, 1, 3);
		this->principal = gcnew CJugador;
		this->escenario = gcnew CEscenario;
		crear_bandera(this->escenario->get_tipo_mapa());
		crear_corruptos(this->escenario);
		crear_aliados(this->escenario);
		//0 sera tomado como NO y 1 como SI
		this->existeportal = 0;
		this->creacionportal = 0;
		this->creacionassasins = 0;
		
	}
	~CJuego() {
		PlaySound(TEXT("AUDIOS\\menu.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
		delete this->escenario;
		delete this->principal;
		for (short i = 0; i < this->corrupto->Count; ++i) {
			delete this->corrupto[i];
		}
		delete this->corrupto;
		for (short i = 0; i < this->aliado->Count; ++i) {
			delete this->aliado[i];
		}
		delete this->aliado;
		delete this->portal, this->explosion, this->explosion2, this->flag;
		delete this->Win; delete this->Lose;
	}
	void jugar(Graphics^ graficador) {
		short corrupcount=this->corrupto->Count; 
		short aliadocount=this->aliado->Count;

		this->escenario->dibujar(graficador);
		this->principal->dibujar(graficador);
		this->flag->dibujar(graficador);
		graficador->DrawString("Tiempo: " + (clock() / 1000), gcnew Font("Comic Sans MS", 12), Brushes::Black, 30, 5);
		graficador->DrawString("Vidas: " + this->principal->get_vida(), gcnew Font("Comic Sans MS", 12), Brushes::Black, 200, 5);
		for (short i = 0; i < this->corrupto->Count; ++i) {
			this->corrupto[i]->dibujar(graficador);
			this->corrupto[i]->mover(this->escenario);
		}
		for (short i = 0; i < this->aliado->Count; ++i) {
			this->aliado[i]->dibujar(graficador);
			this->aliado[i]->mover(this->escenario);
		}
		//choque con los enemigos
		for (short i = 0; i < this->corrupto->Count; ++i) {
			if (this->principal->hay_colision(this->corrupto[i]->posicion())) {
				this->explosion = this->corrupto[i]->explosion_kamikaze();
				//se repite el dibujo de la explosion, por que al graficarlo solo una vez, casi no se nota
				for (short i = 0; i < 5; i++)
				{
					this->explosion->dibujar(graficador);
				}
				this->principal->perder_vida(); this->corrupto->RemoveAt(i);
			}
		}

		if (this->creacionassasins == 1) {

			for (short i = 0; i < this->assasin->Count; ++i) {
				this->assasin[i]->dibujar(graficador);
				this->assasin[i]->mover(this->escenario);

				if (this->principal->hay_colision(this->assasin[i]->posicion())) {
					this->explosion = this->assasin[i]->explosion_kamikaze();
					//se repite el dibujo de la explosion, por que al graficarlo solo una vez, casi no se nota
					for (short i = 0; i < 5; i++)
					{
						this->explosion->dibujar(graficador);
					}
					this->principal->perder_vida(); this->assasin->RemoveAt(i);
				}
				//choque entre aliados asesinos
				for (short k = 0; k < this->aliado->Count; ++k) {
					if (this->aliado[k]->colision(this->assasin[i]->posicion())) {
						this->explosion2 = this->aliado[k]->animacion_pelea();
						//se repite el dibujo de la pelea, por que al graficarlo solo una vez, casi no se nota
						for (short a = 0; a < 10; a++)
						{
							this->explosion2->dibujar(graficador);
						}
						this->aliado->RemoveAt(k); break;
					}
				}
			}
		
		}
		//choque con aliados
		for (short i = 0; i < this->corrupto->Count; ++i) {
			for (short k = 0; k < this->aliado->Count; ++k) {
				if (this->aliado[k]->colision(this->corrupto[i]->posicion())) {
					this->explosion2 = this->aliado[k]->animacion_pelea();
					//se repite el dibujo de la pelea, por que al graficarlo solo una vez, casi no se nota
					for (short a = 0; a < 10; a++)
					{this->explosion2->dibujar(graficador);	}
					this->corrupto->RemoveAt(i); this->aliado->RemoveAt(k); break;
				}
			}
		}

		//ayuda al jugador - recordar que solo se brindará esto una vez
		if (this->creacionportal == 0) {
			if (principal->get_vida() == 1) {
				crear_portal(this->principal->getx(), this->principal->gety(), this->escenario);
				this->creacionportal = 1; this->existeportal = 1;
			}
		}
		if (this->existeportal == 1) { this->portal->dibujar(graficador); }
		//fin de la ayuda
		//asesinos
	}
	void interactuar(Direccion direccion) {
		this->principal->mover(direccion, this->escenario);

		for (short i = 0; i < this->corrupto->Count; ++i) {
			//si esta cerca de un enemigo
			if(this->corrupto[i]->cercania(this->principal->getx(),this->principal->gety())){ //si se cumpe, lo sigue
				this->corrupto[i]->perseguir(this->principal->getx(), this->principal->gety(), this->escenario);}
		}
		if (creacionassasins == 1) {
			for (short i = 0; i < this->assasin->Count; ++i) {
				//si esta cerca de un enemigo
				if (this->assasin[i]->cercania(this->principal->getx(), this->principal->gety())) { //si se cumpe, lo sigue
					this->assasin[i]->perseguir(this->principal->getx(), this->principal->gety(), this->escenario);
				}
			}
		}

		//si existe el portal se ejecuta
		if (existeportal == 1) {
			if (this->principal->hay_colision(portal->posicion()) == true) {
				teletransportar(this->principal, this->escenario); this->existeportal = 0;
				delete this->portal;
			}
		}


	}
	System::Drawing::Size get_dimensiones() {
		return this->escenario->get_dimensiones();
	}
	bool perdiendo() { 
		if (this->principal->get_vida() == 0) return true;
		else return false;
	}
	bool ganando() {
		if (this->principal->hay_colision(this->flag->posicion())) return true;
		else return false;
	}
	bool negociando() {
		if (clock() >100000&& clock()<100200) return true;
		else return false;
	}
	bool pasotiempo() {
		if (clock() > 200000 && clock() < 200200) return true;
		else return false;
	}
	void perder(Graphics^ graficador) {
		Lose->dibujar(graficador);
	}
	void ganar(Graphics^ graficador) {
		Win->dibujar(graficador);
	}
	void agregarass() {
		crearasesinos(); this->creacionassasins = 1;
	}
private:
	void crear_portal(short x, short y, CEscenario^ escenario) {
		System::Drawing::Rectangle ubicacionportal = System::Drawing::Rectangle(x, y, 30, 30);
		
		if (escenario->es_camino(ubicacionportal, DERECHA)&& escenario->es_camino(System::Drawing::Rectangle(x - lado, y, 30, 30), DERECHA)) {
			this->portal = gcnew CAnimacion("FONDOS\\portal.png", System::Drawing::Rectangle(x + (lado*2), y, 30, 30), 3, 3, 9);
		}
		else if (escenario->es_camino(ubicacionportal, IZQUIERDA) && escenario->es_camino(System::Drawing::Rectangle(x - lado, y, 30, 30), IZQUIERDA)) {
			this->portal = gcnew CAnimacion("FONDOS\\portal.png", System::Drawing::Rectangle(x - (lado * 2), y, 30, 30), 3, 3, 9);
		}
		else if (escenario->es_camino(ubicacionportal, ARRIBA) && escenario->es_camino(System::Drawing::Rectangle(x, y - lado, 30, 30), ARRIBA)) {
			this->portal = gcnew CAnimacion("FONDOS\\portal.png", System::Drawing::Rectangle(x, y - (lado * 2), 30, 30), 3, 3, 9);
		}
		else if (escenario->es_camino(ubicacionportal, ABAJO) && escenario->es_camino(System::Drawing::Rectangle(x, y + lado, 30, 30), ABAJO)) {
			this->portal = gcnew CAnimacion("FONDOS\\portal.png", System::Drawing::Rectangle(x, y + (lado * 2), 30, 30), 3, 3, 9);
		}
	}

	void teletransportar(CJugador^ jugador, CEscenario^ escenario) {
		short n = escenario->get_tipo_mapa();
		switch (n)
		{
		case 1:
			jugador->setx(lado * 5); jugador->sety(lado * 15);
			break;
		case 2:
			jugador->setx(lado); jugador->sety(lado);
			break;
		case 3:
			jugador->setx(lado * 11); jugador->sety(lado * 6);
			break;
		}
	}
	void crear_bandera(short n_mapa) {
		switch (n_mapa)
		{
		case 1: this->flag = gcnew CAnimacion("SPRITE\\flag.png", System::Drawing::Rectangle(lado*31,lado, 30, 30), 2, 3, 6); break;
		case 2: this->flag = gcnew CAnimacion("SPRITE\\flag.png", System::Drawing::Rectangle(lado*17, lado*7, 30, 30), 2, 3, 6); break;
		case 3: this->flag = gcnew CAnimacion("SPRITE\\flag.png", System::Drawing::Rectangle(lado*24, lado*15, 30, 30), 2, 3, 6); break;
		}
	}
	void crear_corruptos(CEscenario^ escenario) {
		short dx, dy;
		Random^ xy;
		xy = gcnew Random;
		this->corrupto = gcnew List<CCorrutps^>;
		do {
			dx = xy->Next(1, 32) * lado; dy = xy->Next(1, 16) * lado;

			if (escenario->es_piso(System::Drawing::Rectangle(dx, dy, lado, lado)))
				this->corrupto->Add(gcnew CCorrutps(System::Drawing::Rectangle(dx, dy, lado, lado)));
		} while (this->corrupto->Count < 10);
	}
	void crear_aliados(CEscenario^ escenario) {
		short dx, dy;
		Random^ xy;
		xy = gcnew Random;
		this->aliado = gcnew List<CAliados^>;
		do {
			dx = xy->Next(1, 32) * lado; dy = xy->Next(1, 16) * lado;

			if (escenario->es_piso(System::Drawing::Rectangle(dx, dy, lado, lado)))
				this->aliado->Add(gcnew CAliados(System::Drawing::Rectangle(dx, dy, lado, lado)));
		} while (this->aliado->Count < 5);
	}
	void crearasesinos() {
		short dx, dy;
		Random^ xy;
		xy = gcnew Random;
		this->assasin = gcnew List<CAssasins^>;
		do {
			dx = xy->Next(1, 32) * lado; dy = xy->Next(1, 16) * lado;

			if (escenario->es_piso(System::Drawing::Rectangle(dx, dy, lado, lado)))
				this->assasin->Add(gcnew CAssasins(System::Drawing::Rectangle(dx, dy, lado, lado)));
		} while (this->assasin->Count < 5);
	
	}
};