#pragma once
#include "juego.h"
#include "Perder.h"
#include "Ganar.h"
#include "Reunion.h"
namespace trabajofinal {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Jugar_laberinto
	/// </summary>
	public ref class Jugar_laberinto : public System::Windows::Forms::Form
	{
		Perder^ result;
		Ganar^ result2;
		Reunion^ part;
		BufferedGraphics^ buffer; CJuego^ juego; Graphics^ graficador;
	private: System::Windows::Forms::Timer^ tim_animador;

	public:
		Jugar_laberinto(void)
		{
			InitializeComponent();
			this->graficador = this->CreateGraphics();
			this->juego = gcnew CJuego;
			this->ClientSize = this->juego->get_dimensiones();
			this->buffer = BufferedGraphicsManager::Current->Allocate(this->CreateGraphics(), this->ClientRectangle);
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~Jugar_laberinto()
		{
			delete this->juego;
			if (components)
			{
				delete components;
			}
		}
	private: System::ComponentModel::IContainer^ components;
	protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->tim_animador = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// tim_animador
			// 
			this->tim_animador->Enabled = true;
			this->tim_animador->Tick += gcnew System::EventHandler(this, &Jugar_laberinto::animar);
			// 
			// Jugar_laberinto
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(282, 253);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"Jugar_laberinto";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Jugar_laberinto";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Jugar_laberinto::cerrando);
			this->Load += gcnew System::EventHandler(this, &Jugar_laberinto::animar);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Jugar_laberinto::interactuar);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void animar(System::Object^ sender, System::EventArgs^ e) {
		this->juego->jugar(this->buffer->Graphics);
		this->buffer->Render();
		if (juego->perdiendo()||juego->pasotiempo()) {
			this->Close();
			result = gcnew Perder();
			result->ShowDialog();
		}
		if (juego->ganando()) {
			this->Close();
			result2 = gcnew Ganar();
			result2->ShowDialog();
		}
		if (juego->negociando()) {
			part = gcnew Reunion();
			part->ShowDialog();
			juego->agregarass();
		}
	}
	private: System::Void interactuar(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode) {
		case Keys::Up: this->juego->interactuar(ARRIBA); break;
		case Keys::Down: this->juego->interactuar(ABAJO); break;
		case Keys::Left: this->juego->interactuar(IZQUIERDA); break;
		case Keys::Right: this->juego->interactuar(DERECHA); break;
		}
	}
	private: System::Void cerrando(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
		this->tim_animador->Enabled = false;
		delete this->juego;
	}
	};
}
