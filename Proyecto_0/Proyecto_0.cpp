// Clase principal del programa.
// Muestra estado de colas.
// Crea y atiende tiquetes.
// Administra tipos de usuario, areas y servicios.
// Muestra estadisticas.
// Y sale del programa (xd).
//Creadores: Jose Alberto Bulgarelli e Ignacio Castillo.

// Los comentarios con espacio al inicio son de Jose, los que empiezan inmediatamente despues del // son de Ignacio

#include <iostream>
#include <stdexcept>
#include <string>
#include "PriorityQueue.h"
#include "HeapPriorityQueue.h"
#include "Pair.h"
#include "LinkedStack.h"
#include "List.h"
#include "LinkedList.h"
#include "Area.h"
#include "Servicio.h"
#include "Usuario.h"
#include "Ventanilla.h"

using std::cout;
using std::endl;
using std::cin;
using std::getline;
using std::runtime_error;
using std::string;
using std::to_string;
using std::stoi;

bool revisarOpcion(string opcion, int cantidadOpciones) {
    for (int i = 1; i <= cantidadOpciones; i++)
        if (opcion == to_string(i))
            return true;
    return false;
}

template<typename E>
bool revisarRepetido(string opcion, List<E>* lista) {
    lista->goToStart();
    for (int i = 0; i < lista->getSize(); i++) {
        if (lista->trueGetElement(i).getDescripcion() == opcion) {
            lista->goToStart();
            return true;
        }
    }
    lista->goToStart();
    return false;
}

string getlinePeroNoTeDejaPonerVacio() {
    string input;
    getline(cin, input);
    cout << endl << "_________________\n" << endl << endl;
    if (input == "") {
        return " ";
    }
    return input;
}

int comprobarIndice(string eleccion, int cantidadOpciones) {  // Repeti esto dos veces entonces, wabam, funcion
    int indice = 0;            // Revisa que una entrada 1. Sean numeros y 2. Este en el rango de  opciones aceptadas
    if (eleccion == "") {
        eleccion = " ";
    }
    while (indice <= 0 || indice > cantidadOpciones) {
        for (int i = 0; i < eleccion.length(); i++) {
            if (!isdigit(eleccion[i])) {
                i = -1;
                cout << "Escriba una opcion valida: ";
                eleccion = getlinePeroNoTeDejaPonerVacio();
            }
        }
        indice = stoi(eleccion);
        if (indice > cantidadOpciones || indice <= 0) {
            cout << "Escriba una opcion valida: ";
            eleccion = getlinePeroNoTeDejaPonerVacio();
        }
    }
    return indice - 1;
}

string sacaMete(List<string>* lista1, List<string>* lista2) {  // Si se uso este?
    string s = lista1->remove();                               //No
    lista2->append(s);
    return s;
}

void sacaMeteVoid(List<string>* lista1, List<string>* lista2) { // Y este?
    string s = lista1->remove();                                //Tampoco
    lista2->append(s);
}

void printUsuarios(LinkedList<string>* usuarios) {  // Si se usan!! En este!!
    List<string>* temp = new LinkedList<string>();  //Y este no se usa
    string nombre;
    int contador = usuarios->getSize();
    for (int i = 0; i < contador; i++) {
        nombre = sacaMete(usuarios, temp);
        cout << nombre << endl;
    }
    contador = temp->getSize();
    for (int i = 0; i < contador; i++)
        sacaMeteVoid(temp, usuarios);
    delete temp;
}


int main() {
    try {
        string opcionPrincipal = "0", opcionSecundaria = "0";
        List<Usuario>* listaUsuarios = new LinkedList<Usuario>();
        List<string>* codigoUsuarios = new LinkedList<string>();
        List<Area>* areas = new LinkedList<Area>();
        PriorityQueue<string>* tiposUsuario = new HeapPriorityQueue<string>();
        List<Servicio>* servicios = new LinkedList<Servicio>();
        int consecutivoTiquetes = 100;
        // Elegir una opcion:
        while (opcionPrincipal != "6") {
            cout << "Escoja una opcion:" << endl;
            cout << "\t1. Ver estado de las colas." << endl;
            cout << "\t2. Crear tiquete." << endl;
            cout << "\t3. Atender tiquete." << endl;
            cout << "\t4. Administracion." << endl;
            cout << "\t5. Estadisticas del sistema." << endl;
            cout << "\t6. Salir del sistema." << endl;
            cout << "Opcion: ";
            opcionPrincipal = getlinePeroNoTeDejaPonerVacio();
            while (!revisarOpcion(opcionPrincipal, 6)) {
                cout << "Escriba una opcion valida: ";
                opcionPrincipal = getlinePeroNoTeDejaPonerVacio();
            }
            // 1. Ver estado de las colas
            // Mostrar areas existentes, cantidad de ventanillas en cada area y codigos de los tiquetes presentes en las diferentes colas
            // Cada ventanilla muestra el ultimo tiquete atendido
            if (opcionPrincipal == "1") {
                cout << "Areas existentes:" << endl;
                if (areas->isEmpty()) {
                    cout << "\tNo hay areas definidas." << endl << endl;
                }
                areas->goToStart();
                for (int i = 0; i < areas->getSize(); i++) {
                    Area a = areas->getElement();
                    cout << a << endl;

                    cout << "\tServicios del area y sus tiquetes en cola:" << endl;
                    a.servicios->goToStart();  // Innecesario?
                    if (a.servicios->isEmpty()) {
                        cout << "\t\tEl area no tiene servicios." << endl;
                    }
                    else {
                        for (int j = 0; j < a.servicios->getSize(); j++) {
                            Servicio s = a.servicios->getElement();
                            cout << "\t\t" << s << "." << endl;
                            a.servicios->next();
                        }
                        cout << endl << "\tTiquetes en cola de " << a << ": ";
                        if (a.tiquetes->isEmpty()) {
                            cout << "\t\tEl area " << a << " no tiene tiquetes en cola." << endl;
                        }
                        else {
                            a.tiquetes->print(); // A probar
                            cout << endl;
                        }
                    }
                    cout << "\tVentanillas del area y sus ultimos atendidos:" << endl;
                    a.ventanillas->goToStart();
                    for (int j = 0; j < a.ventanillas->getSize(); j++) {
                        Ventanilla v = a.ventanillas->getElement();
                        cout << "\t\t" << v << ": ";
                        if (v.ultimoAtendido != "N")
                            cout << v.ultimoAtendido << "." << endl;
                        else
                            cout << "No hay un ultimo atendido." << endl;
                        a.ventanillas->next();
                    }
                    areas->next();
                    a.servicios->goToStart();
                    a.ventanillas->goToStart();
                    cout << endl;
                }
                areas->goToStart();
            }

            // 2. Crear tiquete
            if (opcionPrincipal == "2") {
                opcionSecundaria = "1";
                while (opcionSecundaria == "1") {
                    cout << "Escoja una opcion:" << endl;
                    cout << "\t1. Seleccionar usuario y servicio." << endl;
                    cout << "\t2. Regresar." << endl;
                    cout << "Opcion: ";
                    opcionSecundaria = getlinePeroNoTeDejaPonerVacio();
                    while (!revisarOpcion(opcionSecundaria, 2)) {
                        cout << "Escriba una opcion valida: ";
                        opcionSecundaria = getlinePeroNoTeDejaPonerVacio();
                    }

                    // 1. Seleccionar tipo de cliente y servicio
                    if (opcionSecundaria == "1") {
                        if (tiposUsuario->isEmpty()) {
                            cout << "No hay tipos de usuario definidos." << endl;
                        }
                        else {
                            string usuarioTiquete, servicioTiquete;
                            // Las palabras del profesor Aviles resuenan en tu cabeza: "El usuario no tiene porque recordar algo que ya no se observa en pantalla" (muestra la lista de opciones antes de pedir elegir una)
                            for (int i = 0; i < listaUsuarios->getSize(); i++) {
                                cout << "\t" << i + 1 << ". " << listaUsuarios->trueGetElement(i).getDescripcion() << endl;
                            }
                            cout << "Elija el tipo de usuario: "; // Tmb hacer que aca escribas el numero de la opcion, no el nombre (siento que es mas comodo pero realmente no afecta en mucho)
                            usuarioTiquete = getlinePeroNoTeDejaPonerVacio();
                            int indiceEleccion = comprobarIndice(usuarioTiquete, listaUsuarios->getSize());
                            Usuario usuarioTiqueteAgarrar = listaUsuarios->trueGetElement(indiceEleccion);
                            if (servicios->isEmpty()) {
                                cout << "No hay servicios definidos." << endl;
                            }
                            else {
                                for (int i = 0; i < servicios->getSize(); i++) {
                                    cout << "\t" << i + 1 << ". " << servicios->trueGetElement(i).descripcion << endl;
                                }
                                cout << "Elija el servicio: ";
                                servicioTiquete = getlinePeroNoTeDejaPonerVacio();
                                indiceEleccion = comprobarIndice(servicioTiquete, servicios->getSize());
                                Servicio servicioTiqueteAgarrar = servicios->trueGetElement(indiceEleccion);
                                string actual = servicioTiqueteAgarrar.getAreaDescripcion();
                                Area objetivo;
                                areas->goToStart();
                                for (int i = 0; i < areas->getSize(); i++) {
                                    if (areas->getElement().getDescripcion() == actual) {
                                        objetivo = areas->getElement();
                                        break;
                                    }
                                    areas->next();
                                }
                                Tiquete winningTicket = Tiquete(objetivo.getCodigo() + to_string(consecutivoTiquetes));
                                objetivo.agregarTiquete(winningTicket, usuarioTiqueteAgarrar.getPrioridad() * 10 + servicioTiqueteAgarrar.getPrioridad());
                                areas->setElement(objetivo);
                                usuarioTiqueteAgarrar.agregarTiquete();
                                listaUsuarios->setElement(usuarioTiqueteAgarrar); // Those who spaguetti
                                // cout << usuarioTiqueteAgarrar.getCantidadTiquetes() << "!!!!!!!!!!!!!!!!!" << endl;
                                servicioTiqueteAgarrar.agregarTiquete();
                                servicios->setElement(servicioTiqueteAgarrar);
                                consecutivoTiquetes += 1;
                            }
                        }
                    }
                }
                // 2. Regresar
            }

            // 3. Atender Tiquete
            if (opcionPrincipal == "3") {
                if (areas->isEmpty()) {
                    cout << "No hay areas en donde atender tiquetes." << endl;
                }
                else {
                    string areaAtender, ventanillaAtender;
                    int posicionArea;
                    for (int i = 0; i < areas->getSize(); i++) {
                        cout << "\t" << i + 1 << ". " << areas->trueGetElement(i).descripcion << endl;
                    }
                    areas->goToStart(); // Redundante ahora que lo pienso, por el goToPos de mas adelante
                    cout << "Elija el area a atender: ";
                    areaAtender = getlinePeroNoTeDejaPonerVacio();
                    int indiceEleccion = comprobarIndice(areaAtender, areas->getSize());
                    areas->goToPos(indiceEleccion);
                    if (areas->getElement().getCantidadVentanillas() == 0)
                        cout << "No hay ventanillas en esta area." << endl;
                    else if (areas->getElement().getCantidadTiquetes() == 0)
                        cout << "No hay tiquetes en esta area." << endl;
                    else {
                        Area areaActual = areas->getElement();
                        cout << "Elija la ventanilla a atender: " << endl;
                        areaActual.mostrarVentanillas();
                        ventanillaAtender = getlinePeroNoTeDejaPonerVacio();
                        if (!areaActual.ventanillaExiste(ventanillaAtender))
                            cout << "La ventanilla no existe." << endl;  // Algo aqui salio mal
                        else {
                            //Atiende el tiquete quitandolo del heap al que pertenece.
                            int posicionVentanilla = areaActual.posicionVentanilla(ventanillaAtender);
                            areaActual.getVentanilla(posicionVentanilla).agregarAtendido();
                            areaActual.atenderTiquete(ventanillaAtender);
                            areas->setElement(areaActual);
                        }
                    }
                }
            }

            // 4. Administracion
            while (opcionPrincipal == "4") {
                cout << "Escoja una opcion:" << endl;
                cout << "\t1. Tipos de usuario." << endl;
                cout << "\t2. Areas" << endl;
                cout << "\t3. Servicios disponibles." << endl;
                cout << "\t4. Limpiar colas y estadisticas." << endl;
                cout << "\t5. Regresar." << endl;
                cout << "Opcion: ";
                opcionSecundaria = getlinePeroNoTeDejaPonerVacio();
                while (!revisarOpcion(opcionSecundaria, 5)) {
                    cout << "Escriba una opcion valida: ";
                    opcionSecundaria = getlinePeroNoTeDejaPonerVacio();
                }

                // 1. Tipos de usuario
                while (opcionSecundaria == "1") {
                    cout << "Escoja una opcion:" << endl;
                    cout << "\t1. Agregar." << endl;
                    cout << "\t2. Eliminar." << endl;
                    cout << "\t3. Regresar." << endl;
                    cout << "Opcion: ";
                    opcionSecundaria = getlinePeroNoTeDejaPonerVacio();
                    while (!revisarOpcion(opcionSecundaria, 3)) {
                        cout << "Escriba una opcion valida: ";
                        opcionSecundaria = getlinePeroNoTeDejaPonerVacio();
                    }

                    // 1. Agregar
                    if (opcionSecundaria == "1") {
                        string nuevoTipo;
                        string nuevaPrioridad;
                        cout << "Elija un nombre para el tipo de usuario: ";
                        nuevoTipo = getlinePeroNoTeDejaPonerVacio();
                        while (revisarRepetido(nuevoTipo, listaUsuarios)) {
                            cout << "Ese tipo de usuario ya existe. " << endl << endl << "Elija un nombre para el tipo de usuario: ";
                            nuevoTipo = getlinePeroNoTeDejaPonerVacio();
                        }
                        cout << "Elija una prioridad para " << nuevoTipo << ": ";
                        nuevaPrioridad = getlinePeroNoTeDejaPonerVacio();
                        for (int i = 0; i < nuevaPrioridad.length(); i++) {  // Aca revisa elemento por elemento que si sean numeros, sino hace q escribas la opcion de nuevo
                            if (!isdigit(nuevaPrioridad[i])) {
                                i = 0;
                                cout << "Escriba una prioridad valida: ";
                                nuevaPrioridad = getlinePeroNoTeDejaPonerVacio();
                            }
                        }
                        tiposUsuario->insert(nuevoTipo, stoi(nuevaPrioridad)); // Se inserta el nuevo tipo de usuario con el nombre y prioridad que elija el usuario
                        listaUsuarios->append(Usuario(nuevoTipo, stoi(nuevaPrioridad)));
                        opcionSecundaria = "1";
                    }

                    // 2. Eliminar
                    else if (opcionSecundaria == "2") {  // La lista de tipos esta ordenada por orden de entrada entonces el usuario te va a dar ese numerito, luego del numerito vez el nomble porque en la otra si esta ordenado bien, y ese nombre lo buscas UNO POR UNO en el heap y lo borras
                        if (listaUsuarios->isEmpty()) {  // Gracias a dios nunca hice esa locura de ahi arriba
                            cout << "No hay tipos de usuario." << endl;
                        }
                        else {
                            int indiceBorrar = 0;       // Big brain time
                            for (int i = 0; i < listaUsuarios->getSize(); i++) {
                                cout << "\t" << i + 1 << ". " << listaUsuarios->trueGetElement(i).getDescripcion() << endl;
                            }
                            cout << "Elija una opcion a eliminar: ";
                            opcionSecundaria = getlinePeroNoTeDejaPonerVacio();
                            indiceBorrar = comprobarIndice(opcionSecundaria, listaUsuarios->getSize());
                            string hayQueBorrar = listaUsuarios->trueRemove(indiceBorrar).getDescripcion();  // Eso ya no puede ser un string si tipo de usuario se hace su propia clase
                            string buscandoANemo = "Es imposible que pongas un tipo de usuario que sea ASI de forma que NUNCA va a fallar esto, osea tiene quwe hitear todos los caracteres INCLUSO los typos, mira pongo cosas aleatorias para que de FIJO no lo pegues, SJKHSFUISGFYUIHWJFASHGFJHSAVDIBJFKHAHOIFW, wabam"; // Innecesario btw
                            for (int i = 0; buscandoANemo != hayQueBorrar; i++) {
                                if (tiposUsuario->getElement(i) == hayQueBorrar) {
                                    buscandoANemo = tiposUsuario->remove(i);
                                }
                            }
                        }
                        opcionSecundaria = "1";
                    }

                    // 3. Regresar
                    else if (opcionSecundaria == "3") {
                        opcionSecundaria = "0";
                    }
                }

                // 2. Areas
                while (opcionSecundaria == "2") {
                    cout << "Escoja una opcion:" << endl;
                    cout << "\t1. Agregar." << endl;
                    cout << "\t2. Modificar cantidad de ventanillas." << endl;
                    cout << "\t3. Eliminar." << endl;
                    cout << "\t4. Regresar." << endl;
                    cout << "Opcion: ";
                    opcionSecundaria = getlinePeroNoTeDejaPonerVacio();
                    while (!revisarOpcion(opcionSecundaria, 4)) {
                        cout << "Escriba una opcion valida: ";
                        opcionSecundaria = getlinePeroNoTeDejaPonerVacio();
                    }

                    // 1. Agregar
                    if (opcionSecundaria == "1") {  // El area debe tener descripcion, codigo y cantidad de ventanillas
                        string newAreaDesc;
                        char newAreaCode;
                        string newAreaWindCount; // Asi bien gringo
                        cout << "Elija el nombre del area: ";
                        newAreaDesc = getlinePeroNoTeDejaPonerVacio();
                        while (revisarRepetido(newAreaDesc, areas)) {
                            cout << "Ese area ya existe. " << endl << endl << "Elija el nombre del area: ";
                            newAreaDesc = getlinePeroNoTeDejaPonerVacio();
                        }
                        cout << "Cantidad de ventanillas en el area: ";
                        newAreaWindCount = getlinePeroNoTeDejaPonerVacio();
                        for (int i = 0; i < newAreaWindCount.length(); i++) {
                            if (!isdigit(newAreaWindCount[i])) {
                                i = -1;
                                cout << "Escriba una cantidad valida: ";
                                newAreaWindCount = getlinePeroNoTeDejaPonerVacio();
                            }
                        }
                        newAreaCode = newAreaDesc[0]; //bleh   // EL MISMO MALDITO ERROR, TODOS LOS CAMINOS LLEVAN AL BLEH   // Veces que esta linea da problemas count: |||
                        string ayudamePorfavor = "";
                        string imSoDoneWithThis = newAreaCode + ayudamePorfavor; // Estas son las dos mejores lineas de codigo que he escrito en toda mi carrera
                        areas->append(Area(newAreaDesc, imSoDoneWithThis, stoi(newAreaWindCount)));
                        opcionSecundaria = "2";
                    }

                    // 2. Modificar cantidad de ventanillas
                    else if (opcionSecundaria == "2") {
                        if (areas->isEmpty()) {
                            cout << "No hay areas definidas." << endl;
                        }
                        else {
                            int indiceEleccion; // A falta de mejores nombres
                            string areaNewWindCount;
                            for (int i = 0; i < areas->getSize(); i++) {
                                cout << "\t" << i + 1 << ". " << areas->trueGetElement(i).descripcion << endl;
                            }
                            cout << "Elija el area a modificar: ";
                            opcionSecundaria = getlinePeroNoTeDejaPonerVacio();
                            indiceEleccion = comprobarIndice(opcionSecundaria, areas->getSize());
                            cout << "Cantidad de ventanillas en " << areas->trueGetElement(indiceEleccion).descripcion << ": " << areas->trueGetElement(indiceEleccion).getCantidadVentanillas() << endl;
                            cout << "Cantidad nueva de ventanillas: ";
                            opcionSecundaria = getlinePeroNoTeDejaPonerVacio();
                            for (int i = 0; i < opcionSecundaria.length(); i++) {
                                if (!isdigit(opcionSecundaria[i])) {
                                    i = -1;
                                    cout << "Escriba una opcion valida: ";
                                    opcionSecundaria = getlinePeroNoTeDejaPonerVacio();
                                }
                            }
                            Area imSoFrickinScared = areas->trueGetElement(indiceEleccion);
                            imSoFrickinScared.cambiarCantidadVentanillas(stoi(opcionSecundaria));
                            areas->setElement(imSoFrickinScared);
                        }
                        opcionSecundaria = "2";
                    }

                    // 3. Eliminar
                    else if (opcionSecundaria == "3") {
                        if (areas->isEmpty()) {
                            cout << "No se han creado areas." << endl;
                        }
                        else {
                            for (int i = 0; i < areas->getSize(); i++) {
                                cout << "\t" << i + 1 << ". " << areas->trueGetElement(i).descripcion << endl;
                            }
                            cout << "Elija el area a eliminar: ";
                            opcionSecundaria = getlinePeroNoTeDejaPonerVacio();
                            int indiceBorrar = comprobarIndice(opcionSecundaria, areas->getSize());
                            List<Servicio>* serviciosAreaBorrarDe = areas->trueGetElement(indiceBorrar).getServicios();
                            for (serviciosAreaBorrarDe->goToStart(); !serviciosAreaBorrarDe->atEnd(); serviciosAreaBorrarDe->next()) {
                                for (servicios->goToStart(); !servicios->atEnd(); servicios->next()) {
                                    if (servicios->getElement().getDescripcion() == serviciosAreaBorrarDe->getElement().getDescripcion()) {
                                        servicios->remove();
                                        break;
                                    }
                                }
                            }
                            areas->trueRemove(indiceBorrar);
                            servicios->goToStart();
                            areas->goToStart();
                        }
                        opcionSecundaria = "2";
                    }

                    // 4. Regresar
                    else if (opcionSecundaria == "4") {
                        opcionSecundaria = "0";
                    }
                }

                // 3. Servicios disponibles
                while (opcionSecundaria == "3") {
                    cout << "Escoja una opcion:" << endl;
                    cout << "\t1. Agregar." << endl;
                    cout << "\t2. Eliminar." << endl;
                    cout << "\t3. Reordenar." << endl;
                    cout << "\t4. Regresar." << endl;
                    cout << "Opcion: ";
                    opcionSecundaria = getlinePeroNoTeDejaPonerVacio();
                    while (!revisarOpcion(opcionSecundaria, 4)) {
                        cout << "Escriba una opcion valida: ";
                        opcionSecundaria = getlinePeroNoTeDejaPonerVacio();
                    }

                    // 1. Agregar
                    if (opcionSecundaria == "1") {
                        if (areas->isEmpty()) {
                            cout << "No se puede agregar un servicio sin haber definido al menos un area." << endl << endl;
                        }
                        else {
                            string newSerDesc;
                            Area newSerArea;                // Ser = Servicio
                            cout << "Elija un nombre para el servicio: ";
                            newSerDesc = getlinePeroNoTeDejaPonerVacio();
                            while (revisarRepetido(newSerDesc, servicios)) {
                                cout << "Ese servicio ya existe. " << endl << endl << "Elija un nombre para el servicio: ";
                                newSerDesc = getlinePeroNoTeDejaPonerVacio();
                            }
                            for (int i = 0; i < areas->getSize(); i++) {
                                cout << "\t" << i + 1 << ". " << areas->trueGetElement(i).descripcion << endl;
                            }
                            cout << "Elija a que area pertenece el servicio: ";
                            opcionSecundaria = getlinePeroNoTeDejaPonerVacio();
                            int opcionSecundariaPeroConDistintoNombre = comprobarIndice(opcionSecundaria, areas->getSize());
                            newSerArea = areas->trueGetElement(opcionSecundariaPeroConDistintoNombre);
                            string variableQueNoHaceNada = "*No hace nada*";
                            cout << "Elija la prioridad de " << newSerDesc << ": ";
                            opcionSecundaria = getlinePeroNoTeDejaPonerVacio();
                            for (int i = 0; i < opcionSecundaria.length(); i++) {
                                if (!isdigit(opcionSecundaria[i])) {
                                    i = -1;
                                    cout << "Escriba una opcion valida: ";
                                    opcionSecundaria = getlinePeroNoTeDejaPonerVacio();
                                }
                            }
                            Servicio newSer = Servicio(newSerDesc, stoi(opcionSecundaria), newSerArea.getDescripcion());
                            servicios->append(newSer);
                            newSerArea.servicios->append(servicios->trueGetElement(servicios->getSize() - 1)); // Ojito, podria echar error por (bullshit motivo)
                            areas->setElement(newSerArea);                                                     // Jose del futuro no esta siendo capaz de identificar el (bullshit motivo), recordarme poner comentarios mas detallados en el futuro
                        }                                                                                      // Jose del futuro del futuro si logro identificar (bullshit motivo), no aprendere nada de esta experiencia 
                        opcionSecundaria = "3";                                                                
                    }

                    // 2. Eliminar
                    else if (opcionSecundaria == "2") {  // Hay q quitar el servicio de la lista de servicios y del area donde esta
                        if (servicios->isEmpty()) {
                            cout << "No hay ningun servicio." << endl << endl;
                        }
                        else {
                            for (int i = 0; i < servicios->getSize(); i++) {
                                cout << "\t" << i + 1 << ". " << servicios->trueGetElement(i).descripcion << endl;
                            }
                            cout << endl << "Elija el servicio a eliminar: ";
                            opcionSecundaria = getlinePeroNoTeDejaPonerVacio();
                            int indiceBorrar = comprobarIndice(opcionSecundaria, servicios->getSize());
                            Servicio serBorrar = servicios->trueRemove(indiceBorrar);
                            Servicio buscandoANemo;
                            for (int i = 0; buscandoANemo.getDescripcion() != serBorrar.getDescripcion(); i++) {  // ?
                                for (int b = 0; b < areas->trueGetElement(i).getCantidadServicios() && buscandoANemo.getDescripcion() != serBorrar.getDescripcion(); b++) {
                                    if (areas->trueGetElement(i).getServicio(b).getDescripcion() == serBorrar.getDescripcion()) {
                                        buscandoANemo = areas->trueGetElement(i).getServicios()->trueRemove(b);
                                    }  // No se que cojones estaba yo pensando cuando escribi toda esta bullshit, unos dias despues estoy completamente confundido pero confio en cualquiera haya sido la vision que tuve en su momento
                                }      //Yo tampoco tengo ni idea de que dice ahi
                            }          // SI SIRVE (gracias, Jose lucido de aquel dia, por escribir esta parte que ni el Jose actual logra entender)
                            areas->goToStart();
                            servicios->goToStart();
                            // Gracias por todo Nemo
                            //y virgulilla
                        }
                        opcionSecundaria = "3";
                    }

                    // 3. Reordenar
                    else if (opcionSecundaria == "3") {
                        if (servicios->getSize() == 0) {
                            cout << "No hay servicios para reordenar." << endl << endl;
                        }
                        else {
                            for (int i = 0; i < servicios->getSize(); i++) {
                                cout << "\t" << i + 1 << ". " << servicios->trueGetElement(i).descripcion << endl;
                            }
                            servicios->goToStart();
                            string pos1, pos2;
                            cout << endl << "Escriba la primera posicion (1-" << servicios->getSize() << "): ";
                            pos1 = getlinePeroNoTeDejaPonerVacio();
                            while (!revisarOpcion(pos1, servicios->getSize())) {
                                cout << "Escriba una opcion valida: ";
                                pos1 = getlinePeroNoTeDejaPonerVacio();
                            }
                            cout << "Escriba la segunda posicion (1-" << servicios->getSize() << "): ";
                            pos2 = getlinePeroNoTeDejaPonerVacio();
                            while (!revisarOpcion(pos1, servicios->getSize()) || pos1 == pos2) {
                                cout << "Escriba una opcion valida: ";
                                pos2 = getlinePeroNoTeDejaPonerVacio();
                            }
                            servicios->swap(stoi(pos1) - 1, stoi(pos2) - 1);
                        }
                        opcionSecundaria = "3";
                    }

                    // 4. Regresar
                    else if (opcionSecundaria == "4") {
                        opcionSecundaria = "0";
                    }
                }

                // 4. Limpiar colas y estadisticas
                if (opcionSecundaria == "4") {
                    areas->goToStart();
                    for (int i = 0; i < areas->getSize(); i++) {
                        Area actual = areas->getElement();
                        actual.tiquetes->clear();
                        actual.tiquetesAtendidos->clear();
                        actual.cantidadTiquetes = 0;
                        actual.cantidadTiquetesAtendidos = 0;
                        for (int i = 0; i < actual.ventanillas->getSize(); i++) {
                            if (actual.getVentanilla(i).getUltimoAtendido() != "N") {
                                Ventanilla v = actual.getVentanilla(i);
                                v.setUltimoAtendido("N");
                                v.setCantidadAtendidos(0);
                                actual.ventanillas->setElement(v);
                            }
                        }
                        areas->setElement(actual);
                        areas->next();
                    }
                    listaUsuarios->goToStart();
                    for (int i = 0; i < listaUsuarios->getSize(); i++) {
                        Usuario usuario = listaUsuarios->getElement();
                        usuario.setCantidadTiquetes(0);
                        listaUsuarios->setElement(usuario);
                        listaUsuarios->next();
                    }
                    servicios->goToStart();
                    for (int i = 0; i < servicios->getSize(); i++) {
                        Servicio servicio = servicios->getElement();
                        servicio.setCantidadTiquetes(0);
                        servicios->setElement(servicio);
                        servicios->next();
                    }
                    areas->goToStart();
                    listaUsuarios->goToStart();
                    servicios->goToStart();
                }

                // 5. Regresar
                if (opcionSecundaria == "5") {
                    opcionPrincipal = "0";
                }
            }

            // 5. Estadisticas del sistema
            if (opcionPrincipal == "5") {
                cout << "Tiempo promedio por cada area:" << endl;
                if (areas->isEmpty()) {
                    cout << "\t No hay areas." << endl;
                }
                else {
                    areas->goToStart();
                    for (int i = 0; i < areas->getSize(); i++) {
                        int tiempo = 0;
                        Area actual = areas->getElement();
                        actual.tiquetesAtendidos->goToStart();
                        for (int j = 0; j < actual.cantidadTiquetesAtendidos; j++) {
                            tiempo += actual.tiquetesAtendidos->getElement().getEspera();
                            actual.tiquetesAtendidos->next();
                        }
                        cout << "\tArea: " << actual.descripcion << "." << endl;
                        if (actual.getCantidadTiquetesAtendidos() == 0) {
                            cout << "\tNo hay tiquetes atendidos." << endl;
                        }
                        else if (tiempo == 0) {
                            cout << "\tNo hay tiempo de espera." << endl;
                        }
                        else {
                            cout << "\tTiempo promedio: " << tiempo / actual.getCantidadTiquetesAtendidos() << "." << endl;
                        }
                        areas->next();
                    }
                }
                cout << endl;
                cout << "Cantidad de tiquetes dispensados por area: " << endl;
                if (areas->isEmpty()) {
                    cout << "\t No hay areas." << endl;
                }
                else {
                    areas->goToStart(); 
                    for (int i = 0; i < areas->getSize(); i++) {   // Hacer que esto muestre la cantidad de tiquetes CREADOS por area
                        cout << "\tArea: " << areas->getElement().descripcion;
                        cout << "\tTiquetes " << areas->getElement().cantidadTiquetes << endl;
                        areas->next();
                    }
                    cout << endl;
                    cout << "Cantidad de tiquetes atendidos por ventanilla: " << endl;
                    areas->goToStart();
                    for (int i = 0; i < areas->getSize(); i++) {
                        Area actual = areas->getElement();
                        actual.ventanillas->goToStart();
                        cout << "\tArea: " << actual.descripcion << "." << endl;
                        for (int j = 0; j < actual.cantidadVentanillas; j++) {
                            Ventanilla ventanillaActual = actual.ventanillas->getElement();
                            cout << "\t\tVentanilla: " << ventanillaActual << "." << endl;
                            cout << "\t\tAtendidos: " << ventanillaActual.cantidadAtendidos << "." << endl;
                            actual.ventanillas->next();
                        }
                        areas->next();
                    }
                }
                cout << endl;
                cout << "Cantidad de tiquetes dispensados por servicio:" << endl;
                if (servicios->isEmpty()) {
                    cout << "\tNo hay servicios definidos." << endl;
                }
                else {
                    servicios->goToStart();
                    for (int i = 0; i < servicios->getSize(); i++) {
                        cout << "\tServicio: " << servicios->getElement().descripcion;
                        cout << "\tTiquetes " << servicios->getElement().cantidadTiquetes << endl;  // Si falla prueba a hacer gets de esto
                        servicios->next();
                    }
                }
                cout << endl;
                cout << "Cantidad de tiquetes dispensados por tipo de usuario: " << endl;
                if (tiposUsuario->isEmpty()) {
                    cout << "\tNo hay tipos de usuario definidos." << endl;
                }
                else {
                    listaUsuarios->goToStart();
                    for (int i = 0; i < listaUsuarios->getSize(); i++) {
                        cout << listaUsuarios->getElement().getDescripcion() << ": " << listaUsuarios->getElement().getCantidadTiquetes() << "." << endl;
                        listaUsuarios->next();
                    }
                }
                cout << endl;
            }

            // 6. Salir
            if (opcionPrincipal == "6") {
                delete listaUsuarios;
                delete codigoUsuarios;
                delete areas;
                delete tiposUsuario;
                delete servicios;
                break;
            }
            opcionPrincipal = "0";
            opcionSecundaria = "0";
        }
    }
    catch (const runtime_error& e) {
        cout << e.what() << endl;
    }
    return 0;
};

// Me voy a volar la cabeza
//Confirmo

// We are so fucking cooked

// We are so back

// We did it