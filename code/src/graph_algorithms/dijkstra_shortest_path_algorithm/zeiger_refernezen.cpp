int* pi; //Zeiger auf int
char** pcc; //Zeiger auf Zeiger auf char
int* ap[15]; //Array von 15 Zeigern auf int
int (*fp)(char*); //Zeiger auf eine Funktion, die einen char* als Argument 
                  //übernimmt und einen int zurückgibt

int* f(char*); //Funktion die einen char* als Argument übernimmt und einen 
               //Zeiger auf int zurück gibt