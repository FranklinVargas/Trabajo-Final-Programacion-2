#pragma once
#include "Jugar_laberinto.h"
#include "Info.h"

namespace trabajofinal {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de menu
	/// </summary>
	public ref class menu : public System::Windows::Forms::Form
	{
		Jugar_laberinto^ nombre;
		Info^ informar;
	public:
		menu(void)
		{
			InitializeComponent();
			PlaySound(TEXT("AUDIOS\\menu.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~menu()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Button^ btnjugar;
	private: System::Windows::Forms::Button^ btninfo;
	private: System::Windows::Forms::Button^ btncerrar;
	protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(menu::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->btnjugar = (gcnew System::Windows::Forms::Button());
			this->btninfo = (gcnew System::Windows::Forms::Button());
			this->btncerrar = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(990, 550);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// btnjugar
			// 
			this->btnjugar->Font = (gcnew System::Drawing::Font(L"ROG Fonts", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnjugar->Location = System::Drawing::Point(420, 146);
			this->btnjugar->Name = L"btnjugar";
			this->btnjugar->Size = System::Drawing::Size(144, 35);
			this->btnjugar->TabIndex = 1;
			this->btnjugar->Text = L"Jugar";
			this->btnjugar->UseVisualStyleBackColor = true;
			this->btnjugar->Click += gcnew System::EventHandler(this, &menu::btnjugar_Click);
			// 
			// btninfo
			// 
			this->btninfo->Font = (gcnew System::Drawing::Font(L"ROG Fonts", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btninfo->Location = System::Drawing::Point(363, 206);
			this->btninfo->Name = L"btninfo";
			this->btninfo->Size = System::Drawing::Size(252, 38);
			this->btninfo->TabIndex = 2;
			this->btninfo->Text = L"Informacion";
			this->btninfo->UseVisualStyleBackColor = true;
			this->btninfo->Click += gcnew System::EventHandler(this, &menu::btninfo_Click);
			// 
			// btncerrar
			// 
			this->btncerrar->Font = (gcnew System::Drawing::Font(L"ROG Fonts", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btncerrar->Location = System::Drawing::Point(407, 269);
			this->btncerrar->Name = L"btncerrar";
			this->btncerrar->Size = System::Drawing::Size(173, 40);
			this->btncerrar->TabIndex = 3;
			this->btncerrar->Text = L"Cerrar";
			this->btncerrar->UseVisualStyleBackColor = true;
			this->btncerrar->Click += gcnew System::EventHandler(this, &menu::btncerrar_Click);
			// 
			// menu
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(990, 550);
			this->Controls->Add(this->btncerrar);
			this->Controls->Add(this->btninfo);
			this->Controls->Add(this->btnjugar);
			this->Controls->Add(this->pictureBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"menu";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"menu";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void btncerrar_Click(System::Object^ sender, System::EventArgs^ e) {
		PlaySound(NULL, NULL, 0);
		this->Close();
	}
private: System::Void btnjugar_Click(System::Object^ sender, System::EventArgs^ e) {
	nombre = gcnew Jugar_laberinto();
	nombre->ShowDialog();

}
private: System::Void btninfo_Click(System::Object^ sender, System::EventArgs^ e) {
	this->informar = gcnew Info();
	this->informar->ShowDialog();
}
};
}
