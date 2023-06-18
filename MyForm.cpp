extern std::string NOKA_P = "ERROR NOT FOUND KEY ERROR";
typedef unsigned char byte;

const hasp_feature_t feature = HASP_DEFAULT_FID;
hasp_handle_t handle = HASP_INVALID_HANDLE_VALUE;
hasp_status_t status;
hasp_status_t crypt;


unsigned char vendor_code[] =
"AzIceaqfA1hX5wS+M8cGnYh5ceevUnOZIzJBbXFD6dgf3tBkb9cvUF/Tkd/iKu2fsg9wAysYKw7RMAsV"
"vIp4KcXle/v1RaXrLVnNBJ2H2DmrbUMOZbQUFXe698qmJsqNpLXRA367xpZ54i8kC5DTXwDhfxWTOZrB"
"rh5sRKHcoVLumztIQjgWh37AzmSd1bLOfUGI0xjAL9zJWO3fRaeB0NS2KlmoKaVT5Y04zZEc06waU2r6"
"AU2Dc4uipJqJmObqKM+tfNKAS0rZr5IudRiC7pUwnmtaHRe5fgSI8M7yvypvm+13Wm4Gwd4VnYiZvSxf"
"8ImN3ZOG9wEzfyMIlH2+rKPUVHI+igsqla0Wd9m7ZUR9vFotj1uYV0OzG7hX0+huN2E/IdgLDjbiapj1"
"e2fKHrMmGFaIvI6xzzJIQJF9GiRZ7+0jNFLKSyzX/K3JAyFrIPObfwM+y+zAgE1sWcZ1YnuBhICyRHBh"
"aJDKIZL8MywrEfB2yF+R3k9wFG1oN48gSLyfrfEKuB/qgNp+BeTruWUk0AwRE9XVMUuRbjpxa4YA67SK"
"unFEgFGgUfHBeHJTivvUl0u4Dki1UKAT973P+nXy2O0u239If/kRpNUVhMg8kpk7s8i6Arp7l/705/bL"
"Cx4kN5hHHSXIqkiG9tHdeNV8VYo5+72hgaCx3/uVoVLmtvxbOIvo120uTJbuLVTvT8KtsOlb3DxwUrwL"
"zaEMoAQAFk6Q9bNipHxfkRQER4kR7IYTMzSoW5mxh3H9O8Ge5BqVeYMEW36q9wnOYfxOLNw6yQMf8f9s"
"JN4KhZty02xm707S7VEfJJ1KNq7b5pP/3RjE0IKtB2gE6vAPRvRLzEohu0m7q1aUp8wAvSiqjZy7FLaT"
"tLEApXYvLvz6PEJdj4TegCZugj7c8bIOEqLXmloZ6EgVnjQ7/ttys7VFITB3mazzFiyQuKf4J6+b/a/Y";

std::vector<unsigned int> h = { 0x6A09E667, 0xBB67AE85, 0x3C6EF372, 0xA54FF53A, 0x510E527F, 0x9B05688C, 0x1F83D9AB, 0x5BE0CD19 }; // 1-ая инициализация переменных


[STAThread]
int main(array<String^>^ arg) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
	status = hasp_login(feature, vendor_code, &handle);
    Project1::MyForm form; //WinFormsTest - имя вашего проекта
    Application::Run(% form);
}

System::Void Project1::MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e) {



	std::ofstream out_file;
	std::vector<unsigned int> W_first;
	std::vector<unsigned int> W;
	std::vector<unsigned int> HASH;
	unsigned char HASH_cry[16];
	String^ HASH_out;
	String^ HASH_out_out_FILE;
	std::string HASH_out_file;
	std::stringstream sstream;
	String^ mesen = textBox1->Text;
	if (mesen == "") {
		MessageBox::Show("Пустая строка", "Предупреждение", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	}
	else if ((mesen[0] == ' ')) {
		MessageBox::Show("Слово не должно начинаться с пробела", "Предупреждение", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		textBox1->Text = "";
	}
	else
	{
		if (status != HASP_STATUS_OK)
		{
			switch (status)
			{
			case HASP_FEATURE_NOT_FOUND:
				MessageBox::Show("Вставьте ключ.", "Предупреждение", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			case HASP_HASP_NOT_FOUND:
				MessageBox::Show("Ключ не найден!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			case HASP_OLD_DRIVER:
				MessageBox::Show("Драйвер устарел.", "Предупреждение", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
			case HASP_NO_DRIVER:
				MessageBox::Show("Драйвер не найден!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			case HASP_INV_VCODE:
				MessageBox::Show("Ключ не верен!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			default:
				break;
			}
		}
		else {
			std::string mes = marshal_as<std::string>(mesen);
			W_first = Message_change(mes);
			W = Generation_of_words(W_first);
			HASH = Count_HASH(h, W);
			if (HASH.size() == 1) //==
				textBox2->Text = marshal_as<String^>(NOKA_P);
			else {
				for (int i = 0; i < 16; i++) {
					if (i < 8) {
						HASH_cry[i] = (unsigned char)HASH[i];
						HASH_out = HASH_out + (HASH[i].ToString("x"));
					}
					else {
						HASH_cry[i] = (unsigned char)0;
					}
				}
				crypt = hasp_encrypt(handle, &HASH_cry, 16);
				for (int i = 0; i < 8; i++) {
					HASH_out_out_FILE = HASH_out_out_FILE + (HASH_cry[i].ToString("x"));
				}
				if (!Noka(status, feature, vendor_code)) //! поставить
					MessageBox::Show("Ключ не найден!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
				else {
					textBox2->Text = HASH_out;
					HASH_out_file = marshal_as<std::string>(HASH_out_out_FILE);
					if (file_go) {          // поток для записи
						out_file.open("D:\\MY_FILE.txt", std::ios::app);
						out_file <<"Начальное слово: "<<"\"" << mes << "\"" << " Ее шфир: " << HASH_out_file << std::endl;
						out_file.close();
						if (crypt != HASP_STATUS_OK) {
							switch (crypt)
							{
							case HASP_FEATURE_NOT_FOUND:
								MessageBox::Show("HASP_FEATURE_NOT_FOUND", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
							case HASP_INV_HND:
								MessageBox::Show("HASP_INV_HND", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
							case HASP_TOO_SHORT:
								MessageBox::Show("HASP_TOO_SHORT", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
							case HASP_ENC_NOT_SUPP:
								MessageBox::Show("HASP_ENC_NOT_SUPP", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
							}
						}
						else {
							MessageBox::Show("Файл зашифрован", "", MessageBoxButtons::OK, MessageBoxIcon::Information);
						}
						MessageBox::Show("Хеш успешно записан в файл (D:\\MY_FILE.txt).", "", MessageBoxButtons::OK, MessageBoxIcon::Information);
					}
				}
			}
		}
	}
}


System::Void Project1::MyForm::textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
    textBox2->ReadOnly = true;
}

System::Void Project1::MyForm::checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (file_go)
		file_go = false;
	else
		file_go = true;
}