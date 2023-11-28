

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <conio.h>

typedef int Tkey;

typedef struct _Wrkr
{
    int status;
    Tkey enrollment;
    char name[30];
    char LastName1[50];
    char LastName2[50];
    char sex[15];
    char JobPstion[30];
    char state[30];
    int age;
    Tkey cellphone;
} TWrkr;

typedef struct _index
{
    Tkey key;
    int indice;
} Tindice;

char *mayuscula(char cadena[]);
int validarNumeros(char mensaje[], int ri, int rf);
int random(int ri, int rf);
char *validarletras(char mensaje[], char cadena[]);
int contador(char cadena[]);
int validarnumeros(char mensaje[], int ri, int rf);

int valiEspacios(char cadena[]);
int valiAlfa(char cadena[]);
int valiCad(char cadena[]);

int numAleatorio(int ri, int rf);
int matriAlea(void);
int numTelAlea();

Tkey busqSeq(Tindice vect[], int n, Tkey num);
Tkey busqSeqOrd(Tindice vect[], int n, Tkey num);
Tkey busqBin(Tindice vect[], int n, Tkey num);
Tkey busqOpt(Tindice vect[], int n, Tkey num, int band);
Tkey busqSeqMat(int mat[][4], int m, int n, int num);

void imprVect(int vect[], int n);
void imprMat(int mat[][4], int m, int n);

bool ordBubble(Tindice vect[], int n);
bool ordBubbleMejorado(Tindice vect[], int n);
bool ordQuick(Tindice vect[], int n);
bool ordMerge(Tindice vect[], int n);
void mSort(Tindice vect[], Tindice temp[], int izq, int der);
void merge(Tindice vect[], Tindice temp[], int izq, int med, int der);
void qs(Tindice vect[], int limite_izq, int limite_der);
int ordOpt(Tindice vect[], int n, int ordenado);

void mayus(char cadena[]);
int largoCadena(char cadena[]);

bool valiMes(int mes, int anio);
bool esAnioBisiesto(int anio);
bool esFechaValida(int dia, int mes, int anio);

void genNomH(char cadena[]);
void genNomM(char cadena[]);
void genAp(char cadena[]);
void genPuesto(char cadena[]);
void genEdo(char estado[]);

char *mayuscula(char cadena[])
{
    int i, x;
    x = contador(cadena);

    for (i = 0; i < x; i++)
    {
        if (cadena[i] >= 'a' && cadena[i] <= 'z')
        {
            cadena[i] = cadena[i] - 32;
        }
    }
    return cadena;
}

int validarNumeros(char mensaje[], int ri, int rf)
{
    char entrada[100];
    int num;
    do
    {
        printf("%s", mensaje);
        fgets(entrada, sizeof(entrada), stdin);
        num = atoi(entrada);
        if (num < ri || num > rf)
        {
            printf("\nINGRESE EL NUMERO OTRA VEZ PORFAVOR\n");
        }
    } while (num < ri || num > rf);
    return num;
}

int random(int ri, int rf)
{
    int r;
    r = (rf - ri) + 1;
    return (rand() % r) + ri;
}

char *validarletras(char mensaje[], char cadena[])
{
    int x, i, salida;
    wchar_t letras;
    i = 0;
    salida = 0;
    printf("%s", mensaje);
    do
    {
        salida = 0;
        fflush(stdin);
        gets(cadena);
        x = contador(cadena);
        mayuscula(cadena);
        for (i = 0; i < x; i++)
        {
            letras = (wchar_t)cadena[i];
            if (!iswalpha(letras) && cadena[i] != ' ')
            {
                printf("CARACTERES INVALIDOS\n");
                salida = 1;
            }

            if (cadena[i] == ' ' && cadena[i + 1] == ' ')
            {
                printf("CARACTERES INVALIDOS\n");
                salida = 1;
                i = x;
            }
            if (cadena[i] >= '0' && cadena[i] <= '9')
            {
                printf("CARACTERES INVALIDOS\n");
                salida = 1;
                i = x;
            }
        }
        if (cadena[0] == ' ' || cadena[x - 1] == ' ')
        {
            printf("ESPACIOS AL INICIO O FINAL\n");
            salida = 1;
            i = x;
        }
    } while (salida == 1);
    return cadena;
}

int contador(char cadena[])
{
    int i;
    i = 0;
    while (cadena[i] != 0)
    {
        i++;
    }
    return i;
}

int validarnumeros(char mensaje[], int ri, int rf)
{
    char menu[100];
    int num, salida = 0, con, i;
    do
    {
        printf("%s", mensaje);
        fflush(stdin);
        gets(menu);
        con = contador(menu);
        for (i = 0; i < con; i++)
        {
            if (menu[i] >= '0' && menu[i] <= '9')
            {
                salida = 1;
                break;
            }
            else
            {
                salida = 0;
                break;
            }
        }
        num = atoi(menu);
        if (num < ri || num > rf)
        {
            printf("INGRESE EL NUMERO OTRA VEZ PORFAVOR\n");
        }
    } while (num < ri || num > rf || salida == 0);
    return num;
}

// Valida que una cadena no inicie o termine con espacios, o contenga dobles espacios.
int valiEspacios(char cadena[])
{
    int i = 0;

    // Inicia con espacio
    if (cadena[0] == ' ') // no puede iniciar con espacios
    {
        return 0;
    }

    // Termina con espacio
    if (cadena[largoCadena(cadena)] == ' ')
    {
        return 0;
    }

    // 2 espacios seguidos
    while (cadena[i] != '\0')
    {
        if (cadena[i] == ' ')
        {
            if (cadena[i + 1] == ' ')
            {
                return 0;
            }
        }
        i++;
    }

    return 1;
}

// Valida que la cadena solo tenga caracteres alfabeticos
int valiAlfa(char cadena[])
{
    int i = 0;

    while (cadena[i] != '\0')
    {
        if (cadena[i] != ' ' && cadena[i] != ',')
        {
            if (cadena[i] < 'A' || cadena[i] > 'Z')
            {
                return 0;
            }
        }

        i++;
    }

    return 1;
}

// Valida que no haya caracteres especiales en una cadena.
int valiCad(char cadena[])
{
    mayus(cadena);

    if (valiAlfa(cadena) == 0)
    {
        return 0;
    }

    if (valiEspacios(cadena) == 0)
    {
        return 0;
    }

    return 1;
}

/********* LLENADO ALEATORIO *********/

// Genera un numero aleatorio en un rango de numeros enteros.
int numAleatorio(int ri, int rf)
{
    int rango = (rf - ri + 1);

    return rand() % rango + ri;
}

int matriAlea(void)
{
    int matri, mid, low;
    mid = rand() % 100 * 1000;
    low = rand() % 1000;

    matri = 300000 + mid + low;

    return matri;
}

int numTelAlea()
{
    int numeroTelefono, mid, low;
    mid = rand() % 100 * 1000;
    low = rand() % 1000;

    numeroTelefono = 1000000 + mid + low;

    return numeroTelefono;
}

/********* BUSQUEDA *********/

// Busca un valor en un arreglo NO ORDENADO de forma secuencial.
Tkey busqSeq(Tindice vect[], int n, Tkey num)
{
    Tkey i;

    for (i = 0; i < n; i++)
    {
        if (vect[i].key == num)
        {
            return i; // Retorna índice
        }
    }

    return -1; // No se encontró
}

// Busca un valor en un arreglo ORDENADO de forma secuencial.
Tkey busqSeqOrd(Tindice vect[], int n, Tkey num)
{
    Tkey i = 0;

    while (i < n)
    {
        if (num >= vect[i].key)
        {
            if (vect[i].key == num)
            {
                return i; // Retorna índice
            }
        }
        else
        {
            return -1; // No se encontró
        }
    }

    return -1; // No se encontró
}

Tkey busqBin(Tindice vect[], int n, Tkey num)
{
    Tkey med;
    int ri = 0;
    int rf = n;

    while (ri <= rf)
    {
        med = ri + (rf - ri) / 2;

        if (vect[med].key == num)
        {
            return med;
        }
        else
        {
            if (num < vect[med].key)
            {
                rf = med - 1;
            }
            else
            {
                ri = med + 1;
            }
        }
    }

    return -1;
}

Tkey busqOpt(Tindice vect[], int n, Tkey num, int band)
{
    Tkey i;

    if (band == 1)
    {
        i = busqBin(vect, n, num);
    }
    else
    {
        i = busqSeq(vect, n, num);
    }

    return i;
}

Tkey busqSeqMat(int mat[][4], int m, int n, int num)
{
    Tkey i, j;

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (mat[i][j] == num)
            {
                return i; // Retorna índice
            }
        }
    }

    return -1; 
}


void imprVect(int vect[], int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        printf("[%3d]\n", vect[i]);
    }
}

void imprMat(int mat[][4], int m, int n)
{
    int i, j;

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("[%2d]", mat[i][j]);
        }
        printf("\n");
    }
}

bool ordBubble(Tindice vect[], int n)
{
    int i, j;
    Tindice temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (vect[j].key <= vect[i].key)
            {
                temp = vect[i];
                vect[i] = vect[j];
                vect[j] = temp;
            }
        }
    }

    return true;
}

bool ordBubbleMejorado(Tindice vect[], int n)
{
    int i, j;
    Tindice temp;
    bool swap = true;

    for (i = 0; i < n - 1 && swap; i++)
    {
        swap = false;

        for (j = n - 1; j > i; j--)
        {
            if (vect[j].key <= vect[j - 1].key)
            {
                temp = vect[j];
                vect[j] = vect[j - 1];
                vect[j - 1] = temp;
                swap = true;
            }
        }
    }

    return true;
}

bool ordMerge(Tindice vect[], int n)
{
    Tindice temp[n];

    mSort(vect, temp, 0, n - 1);

    return true;
}

void mSort(Tindice vect[], Tindice temp[], int izq, int der)
{
    int med;

    if (izq < der)
    {
        med = (izq + der) / 2;
        mSort(vect, temp, izq, med);
        mSort(vect, temp, med + 1, der);
        merge(vect, temp, izq, med + 1, der);
    }
}

void merge(Tindice vect[], Tindice temp[], int izq, int med, int der)
{
    int i, izq_fin, num_elem, temp_pos;

    izq_fin = med - 1;
    temp_pos = izq;
    num_elem = der - izq + 1;

    while ((izq <= izq_fin) && (med <= der))
    {
        if (vect[izq].key <= vect[med].key)
        {
            temp[temp_pos].key = vect[izq].key;
            temp[temp_pos].indice = vect[izq].indice;
            temp_pos++;
            izq++;
        }
        else
        {
            temp[temp_pos].key = vect[med].key;
            temp[temp_pos].indice = vect[med].indice;
            temp_pos++;
            med++;
        }
    }

    while (izq <= izq_fin)
    {
        temp[temp_pos].key = vect[izq].key;
        temp[temp_pos].indice = vect[izq].indice;
        temp_pos++;
        izq++;
    }

    while (med <= der)
    {
        temp[temp_pos].key = vect[med].key;
        temp[temp_pos].indice = vect[med].indice;
        temp_pos++;
        med++;
    }

    for (i = 0; i <= num_elem; i++)
    {
        vect[der].key = temp[der].key;
        vect[der].indice = temp[der].indice;
        der--;
    }
}

bool ordQuick(Tindice vect[], int n)
{
    qs(vect, 0, n - 1);

    return true;
}

void qs(Tindice vect[], int limite_izq, int limite_der)
{
    int izq, der, pivote;
    Tindice temp;

    izq = limite_izq;
    der = limite_der;
    pivote = vect[(izq + der) / 2].key;

    do
    {
        while (vect[izq].key < pivote && izq < limite_der)
        {
            izq++;
        }

        while (pivote < vect[der].key && der > limite_izq)
        {
            der--;
        }

        if (izq <= der)
        {
            temp = vect[izq];
            vect[izq] = vect[der];
            vect[der] = temp;
            izq++;
            der--;
        }
    } while (izq <= der);

    if (limite_izq < der)
    {
        qs(vect, limite_izq, der);
    }

    if (limite_der > izq)
    {
        qs(vect, izq, limite_der);
    }
}

int ordOpt(Tindice vect[], int n, int ordenado)
{
    int i;

    if (ordenado == 0)
    {
        if (n <= 1000)
        {
            i = ordQuick(vect, n);
            printf("Ordenado usando Quick Sort\n");
        }
        else
        {
            i = ordMerge(vect, n);
            printf("Ordenado usando Merge Sort\n");
        }
    }
    else
    {
        if (ordenado == 2)
        {
            i = ordBubbleMejorado(vect, n);
            printf("Ordenado usando Bubble Sort Mejorado\n");
        }
    }

    return 1;
}


void mayus(char cadena[])
{
    int i;

    for (i = 0; cadena[i] != '\0'; i++)
    {
        char caracter = cadena[i];

        if (caracter >= 'a' && caracter <= 'z')
        {
            caracter -= 32; // Convertir a mayúscula (ASCII)
        }

        cadena[i] = caracter;
    }
}

int largoCadena(char cadena[])
{
    int i;

    for (i = 0; cadena[i] != '\0'; i++)
        ;

    return i - 1;
}

bool valiMes(int mes, int anio)
{
    if (anio == 2023)
    {
        if (mes > 10)
        {
            return false;
        }
    }

    return true;
}

bool esAnioBisiesto(int anio)
{
    if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0))
    {
        return true;
    }

    return false;
}

bool esFechaValida(int dia, int mes, int anio)
{
    if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
    {
        if (dia > 30)
        {
            return false; // Abril, junio, septiembre y noviembre tienen hasta 30 días.
        }
    }
    else if (mes == 2)
    {
        if (dia > 29)
        {
            return false; 
        }

        if (dia == 29 && !esAnioBisiesto(anio))
        {
            return false; 
        }
    }

    return true;
}



void genNomH(char cadena[])
{
    char nombresH[][10] = {"JUAN", "PEDRO", "CARLOS", "LUIS", "JAVIER", "ANDRES", "ALEJANDRO", "MIGUEL", "JOSE", "ADAN", "JORGE", "GABRIEL", "ROBERTO", "DAVID", "FERNANDO", "RAUL", "EDUARDO", "SERGIO", "ANTONIO", "FRANCISCO"};
    strcpy(cadena, nombresH[rand() % 20]);
}

void genNomM(char cadena[])
{
    char nombresM[][10] = {"DANIELA", "LAURA", "ANA", "CARMEN", "SOFIA", "ISABEL", "MARTA", "PAULA", "ELENA", "PATRICIA", "LUCIA", "CLARA", "ROSA", "BEATRIZ", "CAROLINA", "JULIA", "TERESA", "SARA", "IRENE", "ADRIANA"};
    strcpy(cadena, nombresM[rand() % 20]);
}

void genAp(char cadena[])
{
    char apellidos[][11] = {"BARRIOS", "RODRIGUEZ", "LOPEZ", "PEREZ", "MARTINEZ", "SANCHEZ", "FERNANDEZ", "GONZALEZ", "RAMIREZ", "TORRES", "MARTIN", "JIMENEZ", "RUIZ", "DIAZ", "SOTO", "GOMEZ", "LOZANO", "CASTRO", "HERRERA", "GARCIA","SUAREZ", "VILLEGAS", "GUERRERO", "PALACIOS", "FARIAS", "AVILA", "MOLINA", "SALAZAR", "DELGADO", "SANCHEZ", "FLORES", "MORALES", "ROMERO", "OROZCO", "RIVERA", "CASTILLO", "CHAVEZ", "SUAREZ", "VILLEGAS", "GUERRERO"};
    strcpy(cadena, apellidos[rand() % 40]);
}

void genPuesto(char cadena[])
{
    char puestos[][30] = {"DevSoft", "IngRed", "AnlDatos", "DisGraf", "EspRRHH", "GteProj", "ConsFin", "MedGen", "Enferm", "Abogado", "AnMktDg", "EspSeg", "IngCivil", "Contado", "ProfPrim", "ChefEje", "TecSup", "DisUX", "AsistAdm", "AnlVent", "InvCien", "AnlSist", "PsOrg", "EspLog", "IngElec", "EdCont", "Arquitect", "AsServ", "Traduct", "EspERen", "RepVInt", "TrabSoc"};

    strcpy(cadena, puestos[numAleatorio(0, 31)]);
}

void genEdo(char estado[])
{
    char estados[][3] = {"AS", "BC", "BS", "CC", "CL", "CM", "CS", "CH", "DF", "DG", "GT", "GR", "HG", "JC", "MC", "MN", "MS", "NT", "NL", "OC", "PL", "QT", "QR", "SP", "SL", "SR", "TC", "TS", "TL", "VZ", "YN", "ZS", "NE"};
    int num = numAleatorio(0, 32);

    strcpy(estado, estados[num]);
}