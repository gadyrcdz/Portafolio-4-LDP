#include <iostream>
#include <list>
#include <string>

class Patogeno {
public:
    std::string nombre;
    
    Patogeno(std::string n) {
        nombre = n;
    }
};

class Vacuna {
public:
    std::string pais;
    std::string nombre;
    int dosisApli;
    Patogeno* patogeno;  // Puntero al patógeno que combate

    Vacuna(std::string p, std::string n, int d) {
        pais = p;
        nombre = n;
        dosisApli = d;
        patogeno = nullptr;  // Inicialmente no tiene patógeno asociado
    }
};

class SistemaVacunas {
private:
    std::list<Vacuna> vacunas;
    std::list<Patogeno> patogenos;

public:
    void agregarVacuna(const std::string& pais, const std::string& nombre, int dosisApli) {
        Vacuna nuevaVacuna(pais, nombre, dosisApli);
        vacunas.push_back(nuevaVacuna);
        std::cout << "Vacuna agregada: " << nombre << " en " << pais << " con " << dosisApli << " dosis aplicadas.\n";
    }

    void agregarPatogeno(const std::string& nombre) {
        // Verificar si el patógeno ya existe
        for (const auto& patogeno : patogenos) {
            if (patogeno.nombre == nombre) {
                std::cout << "El patógeno ya existe en el sistema.\n";
                return;
            }
        }
        
        Patogeno nuevoPatogeno(nombre);
        patogenos.push_back(nuevoPatogeno);
        std::cout << "Patógeno agregado: " << nombre << "\n";
    }

    void asociarPatogenoVacuna(const std::string& nombreVacuna, const std::string& nombrePatogeno) {
        // Buscar el patógeno
        Patogeno* patogenoEncontrado = nullptr;
        for (auto& patogeno : patogenos) {
            if (patogeno.nombre == nombrePatogeno) {
                patogenoEncontrado = &patogeno;
                break;
            }
        }

        if (!patogenoEncontrado) {
            std::cout << "Patógeno no encontrado.\n";
            return;
        }

        // Asociar el patógeno a la vacuna
        bool vacunaEncontrada = false;
        for (auto& vacuna : vacunas) {
            if (vacuna.nombre == nombreVacuna) {
                vacuna.patogeno = patogenoEncontrado;
                vacunaEncontrada = true;
                std::cout << "Patógeno " << nombrePatogeno << " asociado a la vacuna " << nombreVacuna << "\n";
            }
        }

        if (!vacunaEncontrada) {
            std::cout << "Vacuna no encontrada.\n";
        }
    }

    void mostrarPatogenosYPaises() {
        // Lista para almacenar los patógenos únicos
        std::list<std::string> patogenosUnicos;
        
        // Obtener lista de patógenos únicos
        for (const auto& vacuna : vacunas) {
            if (vacuna.patogeno != nullptr) {
                bool existe = false;
                for (const auto& nombrePatogeno : patogenosUnicos) {
                    if (nombrePatogeno == vacuna.patogeno->nombre) {
                        existe = true;
                        break;
                    }
                }
                if (!existe) {
                    patogenosUnicos.push_back(vacuna.patogeno->nombre);
                }
            }
        }

        // Para cada patógeno, buscar los países que tienen vacuna
        std::cout << "\nPatógenos y países con vacunas disponibles:\n";
        for (const auto& nombrePatogeno : patogenosUnicos) {
            std::cout << "Patógeno: " << nombrePatogeno << "\n";
            std::cout << "Países con vacuna: ";
            
            // Lista temporal para almacenar países únicos para este patógeno
            std::list<std::string> paisesUnicos;
            
            // Buscar todos los países que tienen vacuna para este patógeno
            for (const auto& vacuna : vacunas) {
                if (vacuna.patogeno && vacuna.patogeno->nombre == nombrePatogeno) {
                    // Verificar si el país ya está en la lista
                    bool paisExiste = false;
                    for (const auto& pais : paisesUnicos) {
                        if (pais == vacuna.pais) {
                            paisExiste = true;
                            break;
                        }
                    }
                    if (!paisExiste) {
                        paisesUnicos.push_back(vacuna.pais);
                    }
                }
            }
            
            // Mostrar los países
            for (const auto& pais : paisesUnicos) {
                std::cout << pais << " ";
            }
            std::cout << "\n";
        }
    }

    void ordenarPorDosis() {
        for (auto it = vacunas.begin(); it != vacunas.end(); ++it) {
            for (auto jt = std::next(it); jt != vacunas.end(); ++jt) {
                if (jt->dosisApli > it->dosisApli) {
                    std::swap(*it, *jt);
                }
            }
        }
    }

    void contarPaisesPorVacuna() {
        std::list<std::string> nombresVacunas;

        for (const auto& vacuna : vacunas) {
            bool existe = false;
            for (const auto& nombre : nombresVacunas) {
                if (nombre == vacuna.nombre) {
                    existe = true;
                    break;
                }
            }
            if (!existe) {
                nombresVacunas.push_back(vacuna.nombre);
            }
        }

        for (const auto& nombreVacuna : nombresVacunas) {
            int contador = 0;
            for (const auto& vacuna : vacunas) {
                if (vacuna.nombre == nombreVacuna) {
                    contador++;
                }
            }
            std::cout << "Vacuna: " << nombreVacuna << ", Países: " << contador << "\n";
        }
    }

    void mostrarEstadisticas() {
        if (vacunas.empty()) {
            std::cout << "No hay datos de vacunas.\n";
            return;
        }

        ordenarPorDosis();
        std::cout << "País con más dosis aplicadas: " << vacunas.front().pais 
                  << " (" << vacunas.front().dosisApli << " dosis)\n";
        
        contarPaisesPorVacuna();
        mostrarPatogenosYPaises();
        
        std::cout << "Primera vacuna registrada: " << vacunas.front().nombre 
                  << " en " << vacunas.front().pais << "\n";
        std::cout << "Última vacuna registrada: " << vacunas.back().nombre 
                  << " en " << vacunas.back().pais << "\n";
    }
};

class Menu {
private:
    SistemaVacunas sistema;

public:
    void mostrarMenu() {
        int opcion;
        do {
            std::cout << "\n----- Menú Principal -----\n";
            std::cout << "1. Agregar Vacuna\n";
            std::cout << "2. Agregar Patógeno\n";
            std::cout << "3. Asociar Patógeno a Vacuna\n";
            std::cout << "4. Mostrar Estadísticas\n";
            std::cout << "5. Salir\n";
            std::cout << "Seleccione una opción: ";
            std::cin >> opcion;

            switch (opcion) {
                case 1:
                    agregarVacuna();
                    break;
                case 2:
                    agregarPatogeno();
                    break;
                case 3:
                    asociarPatogenoVacuna();
                    break;
                case 4:
                    sistema.mostrarEstadisticas();
                    break;
                case 5:
                    std::cout << "Saliendo...\n";
                    break;
                default:
                    std::cout << "Opción no válida. Intente de nuevo.\n";
            }
        } while (opcion != 5);
    }

    void agregarVacuna() {
        std::string pais, nombre;
        int dosis;
        std::cout << "Ingrese el país: ";
        std::cin >> pais;
        std::cout << "Ingrese el nombre de la vacuna: ";
        std::cin >> nombre;
        std::cout << "Ingrese la cantidad de dosis aplicadas: ";
        std::cin >> dosis;

        sistema.agregarVacuna(pais, nombre, dosis);
    }

    void agregarPatogeno() {
        std::string nombre;
        std::cout << "Ingrese el nombre del patógeno: ";
        std::cin >> nombre;
        sistema.agregarPatogeno(nombre);
    }

    void asociarPatogenoVacuna() {
        std::string nombreVacuna, nombrePatogeno;
        std::cout << "Ingrese el nombre de la vacuna: ";
        std::cin >> nombreVacuna;
        std::cout << "Ingrese el nombre del patógeno: ";
        std::cin >> nombrePatogeno;
        sistema.asociarPatogenoVacuna(nombreVacuna, nombrePatogeno);
    }
};

int main() {
    Menu menu;
    menu.mostrarMenu();
    return 0;
}