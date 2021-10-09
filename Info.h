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
	/// Resumen de Info
	/// </summary>
	public ref class Info : public System::Windows::Forms::Form
	{
		short info;
		Cinfo^ resultado;
		Graphics^ graficador;
	private: System::Windows::Forms::Button^ btnizquierda;
	private: System::Windows::Forms::Button^ btnderecha;
	private: System::Windows::Forms::Button^ btnregresar;
	private: System::Windows::Forms::Timer^ tim_info;

		   BufferedGraphics^ buffer;
	public:
		Info(void)
		{

			InitializeComponent();
			info = 1;
			this->graficador = this->CreateGraphics();
			this->buffer = BufferedGraphicsManager::Current->Allocate(this->graficador, this->ClientRectangle);

			resultado = gcnew Cinfo();
			resultado->instruccione(info);
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~Info()
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Info::typeid));
			this->btnizquierda = (gcnew System::Windows::Forms::Button());
			this->btnderecha = (gcnew System::Windows::Forms::Button());
			this->btnregresar = (gcnew System::Windows::Forms::Button());
			this->tim_info = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// btnizquierda
			// 
			this->btnizquierda->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnizquierda.Image")));
			this->btnizquierda->Location = System::Drawing::Point(12, 190);
			this->btnizquierda->Name = L"btnizquierda";
			this->btnizquierda->Size = System::Drawing::Size(211, 250);
			this->btnizquierda->TabIndex = 0;
			this->btnizquierda->UseVisualStyleBackColor = true;
			this->btnizquierda->Click += gcnew System::EventHandler(this, &Info::btnizquierda_Click);
			// 
			// btnderecha
			// 
			this->btnderecha->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnderecha.Image")));
			this->btnderecha->Location = System::Drawing::Point(767, 190);
			this->btnderecha->Name = L"btnderecha";
			this->btnderecha->Size = System::Drawing::Size(211, 250);
			this->btnderecha->TabIndex = 1;
			this->btnderecha->UseVisualStyleBackColor = true;
			this->btnderecha->Click += gcnew System::EventHandler(this, &Info::btnderecha_Click);
			// 
			// btnregresar
			// 
			this->btnregresar->Font = (gcnew System::Drawing::Font(L"ROG Fonts", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnregresar->ForeColor = System::Drawing::SystemColors::Control;
			this->btnregresar->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnregresar.Image")));
			this->btnregresar->ImageAlign = System::Drawing::ContentAlignment::TopCenter;
			this->btnregresar->Location = System::Drawing::Point(789, 1);
			this->btnregresar->Name = L"btnregresar";
			this->btnregresar->Size = System::Drawing::Size(182, 52);
			this->btnregresar->TabIndex = 2;
			this->btnregresar->Text = L"Regresar";
			this->btnregresar->UseVisualStyleBackColor = true;
			this->btnregresar->Click += gcnew System::EventHandler(this, &Info::btnregresar_Click);
			// 
			// tim_info
			// 
			this->tim_info->Enabled = true;
			this->tim_info->Tick += gcnew System::EventHandler(this, &Info::tinfo);
			// 
			// Info
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(990, 550);
			this->Controls->Add(this->btnregresar);
			this->Controls->Add(this->btnderecha);
			this->Controls->Add(this->btnizquierda);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"Info";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Info";
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void btnregresar_Click(System::Object^ sender, System::EventArgs^ e) {
		delete this->resultado;
		tim_info->Enabled = false;
		this->Close();
	}
	private: System::Void tinfo(System::Object^ sender, System::EventArgs^ e) {
		resultado->instruccionnnn(this->buffer->Graphics);
		this->buffer->Render();
	}

	private: System::Void btnizquierda_Click(System::Object^ sender, System::EventArgs^ e) {
		info--;
		if (info < 1) { info = 4; }
		resultado->instruccione( info);
	}
	private: System::Void btnderecha_Click(System::Object^ sender, System::EventArgs^ e) {
		info++;
		if (info > 4) { info = 1; }
		resultado->instruccione(info);
	}
	};
}
