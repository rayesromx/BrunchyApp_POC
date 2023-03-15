
#include <windows.h>
#include <string>
#include "resource.h"

using namespace std;

//HWND - HANDLER WINDOW - MANEJADOR DE VENTANA - REFERENCIA A DIALOGO O COMPONENTE/CONTROL

//INT_PTR CALLBACK fn
//(
//	HWND hDialgoActual, //referencia al dialogo que se esta siendo desplegado/llamado
//	UINT uMensaje,			//mensaje o evento de interaccion en Windows
//	WPARAM wParam,			//contienen informacion adicional del mensaje
//	LPARAM lParam				//contienen informacion adicional del mensaje
//)
//{
//
//	return FALSE;
//}

//los callbacks son las funciones que definen el comportamiento de un dialogo

HINSTANCE IdentificadorAppGlobal;
string usuarioEnSesion;

INT_PTR CALLBACK fnDlgPantallaPrincipal
(
	HWND hDialgoActual, //referencia al dialogo que se esta siendo desplegado/llamado
	UINT uMensaje,			//mensaje o evento de interaccion en Windows
	WPARAM wParam,			//contienen informacion adicional del mensaje
	LPARAM lParam				//contienen informacion adicional del mensaje
)
{
	switch (uMensaje)
	{
	case WM_INITDIALOG:
	{
		string saludo = "Bienvenido, " + usuarioEnSesion;
		SetDlgItemTextA(hDialgoActual, LBL_SALUDO, saludo.c_str());
	}
	break;
	case WM_CLOSE:
	{
		int respuesta = MessageBoxA(
			hDialgoActual,
			"Este es un mensaje",
			"Este un titulo",
			MB_ICONHAND | MB_OKCANCEL
		);

		if (respuesta == IDOK)
		{
			PostQuitMessage(0); // funcion que finaliza con la aplicacion
		}
		else
		{

		}

	}
	break;

	}


	return FALSE;
}

bool prendido = false;

INT_PTR CALLBACK fnDlgInicioSesion
(
	HWND hDialgoActual, //referencia al dialogo que se esta siendo desplegado/llamado
	UINT uMensaje,			//mensaje o evento de interaccion en Windows
	WPARAM wParam,			//contienen informacion adicional del mensaje
	LPARAM lParam				//contienen informacion adicional del mensaje
)
{
	
	switch (uMensaje)
	{
	case WM_INITDIALOG: //este evento o mensaje se dispara antes de que se muestre el dialogo
	{
		SetDlgItemTextA(hDialgoActual, LBL_ERRORUSUARIO,"");
		SetDlgItemTextA(hDialgoActual, LBL_ERRORCONTRASENA, "");
	}
	break;
	case WM_CLOSE:
	{
		int respuesta = MessageBoxA(
			hDialgoActual,
			"Estas seguro que deseas cerrar el programa??",
			"Estas por cerrar la aplicacion",
			MB_ICONHAND | MB_OKCANCEL
		);

		if (respuesta == IDOK)
		{
			PostQuitMessage(0); // funcion que finaliza con la aplicacion
		}
		else
		{

		}
	}
	break;
	case WM_COMMAND: // evento que se dispara cuando se interactua con el dialogo
	{
		switch (LOWORD(wParam)) // sirve para saber con que componente/control se esta interactuando
		{
		case BTN_INICIARSESION:
		{
			SetDlgItemTextA(hDialgoActual, LBL_ERRORUSUARIO, "");
			SetDlgItemTextA(hDialgoActual, LBL_ERRORCONTRASENA, "");

			char usuario[100], contrasena[50];

			GetDlgItemTextA( // Get Dialog Item text +> obtener el texto de un componente
				hDialgoActual,
				TXT_USUARIO,
				usuario,
				100
			);

			GetDlgItemTextA(hDialgoActual,TXT_CONTRASENA,contrasena,50);


			string usStr(usuario);
			string usContra(contrasena);


			if (usStr == "")
			{
				SetDlgItemTextA(hDialgoActual, LBL_ERRORUSUARIO, "El usuario es requerido");
			}

			if (usContra == "")
			{
				SetDlgItemTextA(hDialgoActual, LBL_ERRORCONTRASENA, "La contrasena es requerida");
			}

			if (usContra != "" && usContra.length() < 3)
			{
				SetDlgItemTextA(hDialgoActual, LBL_ERRORCONTRASENA, "La contrasena debe tener mas de 3 caracteres");
			}
			


			if (usStr == "ray" && usContra == "123")
			{
				string mensaje = "El usuario " + usStr + " ha iniciado sesion";
				MessageBoxA(
					hDialgoActual,
					mensaje.c_str(),
					"Sesion iniciada",
					MB_OK | MB_ICONINFORMATION
				);

				usuarioEnSesion.append(usStr);

				HWND hDlg = CreateDialogW(
					IdentificadorAppGlobal,										//Identificador de la aplicacion 
					MAKEINTRESOURCE(DLG_PANTALLAPRINCIPAL), //Id del dialogo
					NULL,															// HWND de Referencia a la ventana padre
					fnDlgPantallaPrincipal
				);


				ShowWindow(hDlg, SW_SHOW);
				DestroyWindow(hDialgoActual);

			}
			else

			{
				MessageBoxA(
					hDialgoActual,
					"Credenciales invalidas",
					"Error al iniciar sesion",
					MB_OK | MB_ICONERROR
				);
			}

			
		}
		break;
		case BTN_SALIR:
		{
			PostQuitMessage(0);
		}
		break;
		case BTN_PRUEBA:
		{
			HWND hControl = GetDlgItem(hDialgoActual, BTN_INICIARSESION); // Get Dialog Item => regresa la referencia de un componente/control dentro de un dialogo
			if (prendido)
			{
				ShowWindow(hControl, SW_HIDE);
				SetDlgItemTextA( // Set Dialog Item Text => Establecer texto
					hDialgoActual, // handler del dialogo que se esta ejecutando o actual
					BTN_PRUEBA,
					"_(uwu)/"
				);

			}
			else
			{
				ShowWindow(hControl, SW_SHOW);
				SetDlgItemTextA( // Set Dialog Item Text => Establecer texto
					hDialgoActual, // handler del dialogo que se esta ejecutando o actual
					BTN_PRUEBA, // id del componente que se va a modificar
					"_(o n O)_" // texto a usar
				);
			}
			prendido = !prendido;

			SetDlgItemTextA(
				hDialgoActual, TXT_USUARIO,"ingresa tu usuario"
			);

			//ingresa tu usuario
			SetDlgItemTextA(hDialgoActual, LBL_ERRORUSUARIO, "el nombre de usario es requerido");
		}
		break;
		}
	}
	break;
	}
	return FALSE;
}

int WINAPI wWinMain(
	HINSTANCE hIdentificador,     // Identificador de la aplicacion 
	HINSTANCE hPrevInstance, // Identificador de la aplicacion previa
	PWSTR pCmdLine,					 // argumentos de la linea de comandos
	int nCmdShow)						 // un valor que indica como se va a desplegar la pantalla
{
	IdentificadorAppGlobal = hIdentificador;

	HWND hDlgInicioSesion = CreateDialogW(
		hIdentificador,										//Identificador de la aplicacion 
		MAKEINTRESOURCE(DLG_INICIOSESION), //Id del dialogo
		NULL,															// HWND de Referencia a la ventana padre
		fnDlgInicioSesion
	);

	ShowWindow(hDlgInicioSesion, SW_SHOW);


	// Run the message loop.
	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg); // traduce los eventos del teclado
		DispatchMessage(&msg);			 // despacha los mensajes a los callback de los dialogos
	}

	return 0;
}
