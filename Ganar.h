#pragma once
#include "juego.h"

namespace trabajofinal {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Ganar
	/// </summary>
	public ref class Ganar : public System::Windows::Forms::Form
	{CJuego^ resultado;
		Graphics^ graficador;
		BufferedGraphics^ buffer;
	public:
		
		Ganar(void)
		{
			InitializeComponent();
			this->graficador = this->CreateGraphics();
			this->buffer = BufferedGraphicsManager::Current->Allocate(this->graficador,
				this->ClientRectangle);
			this->resultado = gcnew CJuego();
			PlaySound(TEXT("AUDIOS\\win.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~Ganar()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ btncerrar;
	private: System::Windows::Forms::Timer^ tim_ganar;

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
			this->btncerrar = (gcnew System::Windows::Forms::Button());
			this->tim_ganar = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// btncerrar
			// 
			this->btncerrar->Location = System::Drawing::Point(868, 460);
			this->btncerrar->Name = L"btncerrar";
			this->btncerrar->Size = System::Drawing::Size(92, 31);
			this->btncerrar->TabIndex = 0;
			this->btncerrar->Text = L"Cerrar";
			this->btncerrar->UseVisualStyleBackColor = true;
			this->btncerrar->Click += gcnew System::EventHandler(this, &Ganar::btncerrar_Click);
			// 
			// tim_ganar
			// 
			this->tim_ganar->Enabled = true;
			this->tim_ganar->Tick += gcnew System::EventHandler(this, &Ganar::tganar);
			// 
			// Ganar
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(972, 503);
			this->Controls->Add(this->btncerrar);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"Ganar";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Ganar";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void btncerrar_Click(System::Object^ sender, System::EventArgs^ e) {
		tim_ganar->Enabled = false;
		PlaySound(NULL, NULL, 0);
		delete resultado;
		this->Close();
	}
	private: System::Void tganar(System::Object^ sender, System::EventArgs^ e) {
		resultado->ganar(this->buffer->Graphics);
		this->buffer->Render();
	}
	};
}
