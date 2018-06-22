#include "inc/debug.h"

void dFlag()
{
	mvprintw(0,50,"Here!!!");
	refresh();
	getch();
}
//===================================================================


void DebugInt(int input)
{
	mvprintw(0,50,"%d", input);
	refresh();
	getch();
}
//===================================================================


void DebugLine(Line *line)
{
  mvprintw(0,0,"Line Debug:\n");
  printw("Angle: %d \t length: %d\n",line->angle, line->length);
  printw("Line Points:\n");
  for(uint8_t i = 0; i < line->length; i++)
  {
    printw("Index: %d \t X = %d \t Y = %d\n", i, LineGetPoint(i, line).x, LineGetPoint(i, line).y);
  }
  refresh();
  getch();
}
//===================================================================


void DebugEnemySightFullLines(const Enemy *enemy)
{
  Line *aux_line = NewLine();

  ShowPoint(&enemy->icon.point, "@");

  for(uint16_t i = 0; i < enemy->sight->full_lines->length; i++)
  {
    aux_line = VectorLineGetLine(i, enemy->sight->full_lines);
    ShowLine(aux_line, ".");
  }

  DestroyLine(aux_line);
}
//===================================================================


void DebugEnemySightInstantLines(const Enemy *enemy)
{
  ShowPoint(&enemy->icon.point, "@");

  if(!enemy->sight_active)
    return;

  Line *aux_line = NewLine();

  for(uint16_t i = 0; i < enemy->sight->instant_lines->length; i++)
  {
    aux_line = VectorLineGetLine(i, enemy->sight->instant_lines);
    ShowLine(aux_line, "x");
  }

  DestroyLine(aux_line);
}
//===================================================================


void DebugObjectsFromMap(Map *map) {
  printw("Hero position:\t\t(%d, %d)\n", map->object.hero.x, map->object.hero.y);
  for (int i = 0; i < map->object.enemy_free_index; ++i)
  {
    printw("Enemy position:\t\t(%d, %d)\n", map->object.enemy[i].x, map->object.enemy[i].y);
  }
  printw("Power Up position:\t(%d, %d)\n", map->object.power_up.x, map->object.power_up.y);
  for (int i = 0; i < map->object.hostage_free_index; ++i)
  {
    printw("Hostage position:\t(%d, %d)\n", map->object.hostage[i].x, map->object.hostage[i].y);
  }
  printw("Key position:\t\t(%d, %d)\n", map->object.key.x, map->object.key.y);
  printw("Exit position:\t\t(%d, %d)\n", map->object.exit.x, map->object.exit.y);
}
//===================================================================


void DebugPrintMap(Map *map)
{
  for(uint8_t i=0; i < MAX_HEIGHT; i++)
  {
    for(uint8_t j=0; j < MAX_LENGTH; j++)
    {
      mvprintw(i, j, "%c", map->matrix[i][j]);
    }
  }
}
//===================================================================
