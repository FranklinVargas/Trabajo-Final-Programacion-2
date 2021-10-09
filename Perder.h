#pragma once
#include "juego.h";
namespace trabajofinal {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Perder
	/// </summary>
	public ref class Perder : public System::Windows::Forms::Form
	{
		CJuego^ resultado;
		Graphics^ graficador;
		BufferedGraphics^ buffer;
	private: System::Windows::Forms::Timer^ tim_perder;

	private: System::Windows::Forms::Button^ btnsalir;

	public:
		Perder(void)
		{
			InitializeComponent();
			this->graficador = this->CreateGraphics();
			this->buffer = BufferedGraphicsManager::Current->Allocate(this->graficador,
				this->ClientRectangle);
			this->resultado = gcnew CJuego();
			PlaySound(TEXT("AUDIOS\\lost.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~Perder()
		{
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
			this->tim_perder = (gcnew System::Windows::Forms::Timer(this->components));
			this->btnsalir = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// tim_perder
			// 
			this->tim_perder->Enabled = true;
			this->tim_perder->Tick += gcnew System::EventHandler(this, &Perder::tperder);
			// 
			// btnsalir
			// 
			this->btnsalir->Location = System::Drawing::Point(870, 493);
			this->btnsalir->Name = L"btnsalir";
			this->btnsalir->Size = System::Drawing::Size(93, 34);
			this->btnsalir->TabIndex = 0;
			this->btnsalir->Text = L"Salir";
			this->btnsalir->UseVisualStyleBackColor = true;
			this->btnsalir->Click += gcnew System::EventHandler(this, &Perder::btnsalir_Click);
			// 
			// Perder
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(990, 550);
			this->Controls->Add(this->btnsalir);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"Perder";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Perder";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void btnsalir_Click(System::Object^ sender, System::EventArgs^ e) {
		tim_perder->Enabled = false;
		PlaySound(NULL, NULL, 0);
		delete resultado;
		this->Close();
	}
	private: System::Void tperder(System::Object^ sender, System::EventArgs^ e) {
		resultado->perder(this->buffer->Graphics);
		this->buffer->Render();

	}
	};
}
