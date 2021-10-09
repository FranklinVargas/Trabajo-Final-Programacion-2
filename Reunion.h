#pragma once
#include "paralainfo.h"
namespace trabajofinal {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Reunion
	/// </summary>
	public ref class Reunion : public System::Windows::Forms::Form
	{
		short a;
		Cinfo^ resultado;
		Graphics^ graficador;
	private: System::Windows::Forms::Timer^ tim_reunion;
		   BufferedGraphics^ buffer;

	public:
		Reunion(void)
		{
			InitializeComponent();
			this->a = 1;
			this->graficador = this->CreateGraphics();
			this->buffer = BufferedGraphicsManager::Current->Allocate(this->graficador,
				this->ClientRectangle);
			resultado = gcnew Cinfo();
			PlaySound(TEXT("AUDIOS\\reunion.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
			resultado->dialogos(1);
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~Reunion()
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
			this->tim_reunion = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// tim_reunion
			// 
			this->tim_reunion->Enabled = true;
			this->tim_reunion->Tick += gcnew System::EventHandler(this, &Reunion::treunion);
			// 
			// Reunion
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(972, 503);
			this->Name = L"Reunion";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Reunion";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Reunion::Reunion_KeyDown);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void treunion(System::Object^ sender, System::EventArgs^ e) {
		resultado->dialogossss(this->buffer->Graphics);
		this->buffer->Render();
	}
	private: System::Void Reunion_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::Space)
		{
			a++;
			resultado->dialogos(a);
			if (a == 5) {
				tim_reunion->Enabled = false;
				delete resultado;
				PlaySound(TEXT("AUDIOS\\fondom.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
				this->Close();
			}
		}
	}

	};
}
