#include "raylib.h"
struct Player {
    Rectangle rect;
    Vector2 speed;
    Color color;
};
struct Bullets{
	Rectangle rect;
	Vector2 speed; 
	Color color;
	bool active;
};
int main(){
 const int windowWidth{500};
 const int windowHeight{500};
 int num_bullets{50};
InitWindow(windowWidth,windowHeight,"My Window");
InitAudioDevice(); 
Player player;
player.rect.height= 50;
player.rect.width = 50;
player.color = RED;
player.rect.x = windowWidth/2;
player.rect.y = windowHeight-player.rect.height;
player.speed.x = 10;
player.speed.y = 0;

Bullets bullet[num_bullets];
for (int i = 0; i<num_bullets; i++){
bullet[i].rect.height= 10;
bullet[i].rect.width = 10;
bullet[i].color = GREEN;
bullet[i].rect.x = (windowWidth/2)+(player.rect.width/2)-(bullet[i].rect.width/2);
bullet[i].rect.y = (windowHeight-player.rect.height)-(bullet[i].rect.height);
bullet[i].speed.x = 50;
bullet[i].speed.y = -10;
bullet[i].active = false;}
int shootRate = 0;


Music music = LoadMusicStream("resources/sound.wav"); 
Sound sound = LoadSound("resources/pickUp.wav");
PlayMusicStream(music);

SetTargetFPS(60);  
	while(!WindowShouldClose()){

UpdateMusicStream(music); 

BeginDrawing();
DrawRectangleRec(player.rect,player.color);
    for (int i = 0; i < num_bullets; i++)
    {
        if (bullet[i].active)
            DrawRectangleRec(bullet[i].rect, bullet[i].color);
    }

    if (IsKeyDown(KEY_SPACE))
    {
        shootRate += 5;
        for (int i = 0; i <num_bullets; i++)
        {
            if (!bullet[i].active && shootRate % 40 == 0)
            {
				PlaySound(sound);
                bullet[i].rect.x = player.rect.x;
                bullet[i].rect.y = player.rect.y + player.rect.height / 4;
                bullet[i].active = true;
				break;
            }
        }
    }


    for (int i = 0; i < num_bullets; i++)
    {
        if (bullet[i].active)
        {
           
            bullet[i].rect.y += bullet[i].speed.y;

            if (bullet[i].rect.y <= 0) 
            {
                bullet[i].active = false;
                shootRate = 0;
            }
        }
    }


if(IsKeyPressed(KEY_A)&&player.rect.x>windowWidth-player.rect.width){
player.speed.x = -10;
}
if(IsKeyPressed(KEY_D)&&player.rect.x<0){
player.speed.x = 10;
}
player.rect.x += player.speed.x;
if(player.rect.x<0||player.rect.x>windowWidth-player.rect.width)
{player.speed.x = 0;}

ClearBackground(WHITE); 
EndDrawing();
}	
CloseAudioDevice(); 
CloseWindow();
}