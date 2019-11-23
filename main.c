#include <raylib.h>
#include <stdlib.h> 
//Codigo realizado por la estudiante Lucia Monge, editado por Edgar Gonzales
//Con referencias de la pagina oficial de Raylib

//Se inicializan las funciones de las pantallas para uno y dos jugadores

int displayP1(void);
int displayP2(void);

//Rectangulo para verificar colision
Rectangle temp;

//Metodo principal de la aplicacion, genera el menu de inicio en donde se pide
//uno o dos personajes
int main(void){

    const int screenWidth = 1200;
    const int screenHeight = 900;

    //inicializacion de la ventana de menu
    InitWindow(screenWidth, screenHeight, "iCE Climbers Menu");
    //carga de imagenes
    Image iceC = LoadImage("img/iceC.png"); 
    //la imagen se hace textura para poder pintarla
    Texture2D texture = LoadTextureFromImage(iceC);

    Image HM = LoadImage("img/HM.png"); 
    Texture2D textureH = LoadTextureFromImage(HM);     
    
    //Vector de posicion para el martillo
    Vector2 HMPosition = { 200, 500 };
    UnloadImage(iceC);
    UnloadImage(HM);
    SetTargetFPS(60);                  

    while (!WindowShouldClose()){
        //Se inicia el dibujo
        BeginDrawing();
          
            ClearBackground((Color){0,0,0,0});
            DrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2 - 200, WHITE);
            DrawText("1 Player Game", 300, 500, 100, DARKGRAY);
            DrawText("2 Player Game", 300, 700, 100, DARKGRAY);
            //para seleccionar uno o dos personajes se debe presionar ambas teclas a la vez
            if (IsKeyDown(KEY_UP) && IsKeyUp(KEY_DOWN))
                DrawTexture(textureH,HMPosition.x, HMPosition.y, WHITE);
     
            
            if (IsKeyDown(KEY_DOWN) && IsKeyUp(KEY_UP))
                DrawTexture(textureH,HMPosition.x, HMPosition.y+200, WHITE);
            
            if (IsKeyDown(KEY_ENTER) && IsKeyDown(KEY_UP)){
                CloseWindow(); 
                displayP1();                
            }
            
            if (IsKeyDown(KEY_ENTER) && IsKeyDown(KEY_DOWN)){
                CloseWindow(); 
                displayP2();                
            }
        EndDrawing();
        
    }
    CloseWindow();      
    return 0;
}
//estructura para manejar los datos de un piso
struct piso{
    Image p;
    Vector2 pisoPos;
    int coli [24];
    int pintar [24];
    int yColi;
    int yPintar;    
};

//pantalla del primer jugador
int displayP1(void){
    InitWindow(1200, 950, "iCE Climbers 1 Player");
    bool col = false;
    
    Image pd = LoadImage("img/PD.png");
    Image pi = LoadImage("img/PI.png");
    
    struct piso P1 = {LoadImage("img/P1.png"),{0,650}};  
    ImageResize(&(P1.p), 1200, 300);
    
    struct piso P2 = {LoadImage("img/P2.png"),{0,350},{80,118,156,194,232,270,308,346,384,422,460,498,536,574,612,650,688,726,764,802,840,878,916,954},
        {145,183,221,259,297,335,373,411,449,487,525,563,601,639,677,715,753,791,829,867,905,943,981,1019},630,590};  
    ImageResize(&(P2.p), 1200, 300);
    
    struct piso P3 = {LoadImage("img/P3.png"),{0,50},{125,163,201,239,277,315,353,391,429,467,505,543,581,619,657,695,733,771,809,847,885,923,961,999},
        {190,228,266,304,342,380,418,456,494,532,570,608,646,684,722,760,798,836,874,912,950,988,1026,1064},330,300};  
    ImageResize(&(P3.p), 1200, 300);
    
    ImageResize(&pd, 110, 120);
    
    Vector2 p1Position = { 550, 750 };
    
    Texture2D texp = LoadTextureFromImage(P1.p);
    Texture2D texp2 = LoadTextureFromImage(P2.p);
    Texture2D texp3 = LoadTextureFromImage(P3.p);
    Texture2D texpd = LoadTextureFromImage(pd);
    Texture2D texpi = LoadTextureFromImage(pi);
    
    
    UnloadImage(pd);
    UnloadImage(pi);
    UnloadImage(P1.p);
    UnloadImage(P2.p);
    UnloadImage(P3.p);
    
    SetTargetFPS(60);
    
    while (!WindowShouldClose()){
        //manejo del personaje con flechas
        if (IsKeyPressed(KEY_RIGHT)) p1Position.x += 25.0f;
        if (IsKeyPressed(KEY_LEFT)) p1Position.x -= 25.0f;
        if (IsKeyPressed(KEY_UP)) p1Position.y -= 25.0f;
        if (IsKeyPressed(KEY_DOWN)) p1Position.y += 25.0f;
        //se dibuja al personaje y los pisos
        BeginDrawing();     
           ClearBackground((Color){0,0,0,0});
           DrawTexture(texp,P1.pisoPos.x,P1.pisoPos.y,WHITE);
           DrawTexture(texp2,P2.pisoPos.x,P2.pisoPos.y,WHITE);
           DrawTexture(texp3,P3.pisoPos.x,P3.pisoPos.y,WHITE);
           DrawTexture(texpd, p1Position.x, p1Position.y , WHITE);
           //logica de colision
           for (int i; i < 25; i++){
            Vector2 point = {P2.coli[i],P2.yColi};
            Vector2 center = {p1Position.x,p1Position.y};
            col = CheckCollisionPointCircle(point,center,10.0);
            if (col){
                Rectangle temp = {5,5,P2.pintar[i],P2.yPintar};
                DrawRectangleRec(temp,WHITE);
                
            }
        }
          
        EndDrawing();
            
    }
}

//pantalla de dos jugadores
int displayP2(void){
    InitWindow(1200, 900, "iCE Climbers 2 Players");
    InitWindow(1200, 900, "iCE Climbers 1 Player");
    
    Image pd = LoadImage("img/PD.png");
    Image pi = LoadImage("img/PI.png");
    Vector2 p1Position = { 550, 670 };
    
    Texture2D texpd = LoadTextureFromImage(pd);
    Texture2D texpi = LoadTextureFromImage(pi);
    
    UnloadImage(pd);
    UnloadImage(pi);
    
    Image nd = LoadImage("img/ND.png");
    Image ni = LoadImage("img/NI.png");
    Vector2 p2Position = { 350, 670 };
    
    Texture2D texnd = LoadTextureFromImage(nd);
    Texture2D texni = LoadTextureFromImage(ni);
    
    UnloadImage(nd);
    UnloadImage(ni);
    //manejo de los personajes con flechas y con las letras w,a,s,d.d
    while (!WindowShouldClose()){
        if (IsKeyPressed(KEY_RIGHT)) p1Position.x += 25.0f;
        if (IsKeyPressed(KEY_LEFT)) p1Position.x -= 25.0f;
        if (IsKeyPressed(KEY_UP)) p1Position.y -= 25.0f;
        if (IsKeyPressed(KEY_DOWN)) p1Position.y += 25.0f;
        
        if (IsKeyPressed(KEY_D)) p2Position.x += 25.0f;
        if (IsKeyPressed(KEY_A)) p2Position.x -= 25.0f;
        if (IsKeyPressed(KEY_W)) p2Position.y -= 25.0f;
        if (IsKeyPressed(KEY_S)) p2Position.y += 25.0f;
        
        BeginDrawing();
           ClearBackground((Color){0,0,0,0});
           DrawTexture(texpd, p1Position.x, p1Position.y, WHITE);
           DrawTexture(texnd, p2Position.x, p2Position.y, WHITE);
        EndDrawing();
            
    }
}