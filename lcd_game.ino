#include <LCD_I2C.h>
#include <EEPROM.h>

#include <vector>

// LCD
#define LCD_ADDRESS 0x27
#define HEIGHT 2
#define WIDTH 16

//joystick
#define joyX A1
#define joyY A0
#define joyBtn A2

// game settings
#define FPS 6

// flowers
#define TULIP_LEFT 1 
uint8_t tupli_left[8] =
{
  B00110,
  B01001,
  B11101,
  B11101,
  B10101,
  B00001,
  B00010,
  B00100
};
#define TULIP_RIGHT 2
uint8_t tupli_right[8] =
{
  B01100,
  B10010,
  B10111,
  B10111,
  B10101,
  B10000,
  B01000,
  B00100
};
#define GARLIC 3
uint8_t garlic[8] =
{
  B01110,
  B10001,
  B10101,
  B01110,
  B00100,
  B00100,
  B10101,
  B01110
};
#define FLOWER_R 4
uint8_t flower_r[] = {
  B00000,
  B01010,
  B01110,
  B01110,
  B00100,
  B00101,
  B00110,
  B00100
};
#define FLOWER_L 5
uint8_t flower_l[] = {
  B00000,
  B01010,
  B01110,
  B01110,
  B00100,
  B01100,
  B00110,
  B00100
};
#define BERRY 6
uint8_t berry[] = {
  B00000,
  B00000,
  B00000,
  B00100,
  B00100,
  B01110,
  B10111,
  B01110
};
#define POPPY 7
byte poppy[] = {
  B00000,
  B00100,
  B01010,
  B00100,
  B00100,
  B00100,
  B00110,
  B00010
};
#define UNKNOWN_FLOWER 8
byte unknown_flower[] = {
  B01110,
  B10001,
  B01110,
  B00100,
  B00100,
  B00110,
  B00100,
  B00100
};


#define FLOWERS_TYPE_COUNT 8
byte FLOWERS[FLOWERS_TYPE_COUNT]= {TULIP_LEFT, TULIP_RIGHT, GARLIC, FLOWER_R, FLOWER_L, BERRY, POPPY, UNKNOWN_FLOWER};

// map
#define PLAYER_START_X 13
#define PLAYER_START_Y 13

#define MAP_WIDTH 27
#define MAP_HEIGHT 27

const byte lvl_map[MAP_HEIGHT][MAP_WIDTH] PROGMEM = {
  {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
  {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
  {1, 0, 1, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 0, 1, 0, 1},
  {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
  {1, 0, 1, 0, 3, 3, 1, 0, 3, 3, 1, 0, 3, 3, 3, 0, 1, 3, 1, 0, 1, 0, 1, 1, 1, 0, 1},
  {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
  {1, 0, 1, 0, 3, 3, 3, 0, 3, 3, 3, 0, 3, 0, 1, 0, 3, 3, 1, 0, 3, 3, 3, 3, 1, 0, 1},
  {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 3, 3, 1, 3, 3, 0, 1, 0, 1, 0, 1, 3, 1, 0, 3, 3, 1, 0, 3, 3, 3, 3, 1},
  {1, 0, 3, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 1, 0, 3, 3, 3, 0, 1, 0, 1, 1, 0, 3, 3, 0, 3, 3, 3, 3, 3, 0, 3, 3, 3, 0, 1},
  {1, 0, 1, 0, 0, 0, 1, 0, 1, 3, 1, 0, 0, 0, 1, 3, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1},
  {0, 0, 1, 0, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 3, 1, 0, 0},
  {3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 3, 3, 3, 3, 0, 0, 1, 0, 0, 0, 0, 0, 3},
  {1, 3, 3, 0, 3, 0, 3, 0, 3, 1, 1, 3, 0, 3, 1, 1, 1, 1, 3, 0, 1, 3, 3, 0, 3, 0, 1},
  {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1},
  {1, 3, 3, 0, 1, 0, 1, 0, 3, 3, 3, 0, 3, 3, 1, 1, 1, 1, 1, 0, 3, 3, 3, 0, 1, 3, 1},
  {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 3, 0, 1, 0, 1, 0, 3, 0, 1, 0, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1},
  {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 3, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 3, 3, 1, 0, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 1},
  {1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
  {1, 0, 3, 0, 1, 0, 1, 0, 1, 3, 1, 3, 1, 3, 3, 0, 1, 0, 3, 3, 1, 0, 3, 3, 3, 3, 1},
  {1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
  {1, 0, 1, 0, 1, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 0, 1, 0, 3, 3, 3, 3, 3, 3, 3, 0, 1},
  {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 3, 1, 3, 3, 3, 1, 3, 3, 3, 3, 3, 0, 3, 1, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1},
};

// other
#define ASCII_SPACE 32
#define SEED_PIN A4
#define BUSH_TOP 9
byte bush_top[] = {
  B00000,
  B10101,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

IntervalTimer timer;

void wait_until_released() {
  delay(400);
}

LCD_I2C lcd(LCD_ADDRESS);

class Joy {
  public:
  int p0;
  int p1;
  int p2;
  Joy(int pin0, int pin1, int pin2) {
    p0 = pin0;
    p1 = pin1;
    p2 = pin2;
  }

  bool pressed() {
    return moveX() || moveY() || pressedBtn();
  }

  int moveX() {
    int val = analogRead(p0);
    if (val < 300) {
      return 1;
    } else if (val > 700) {
      return -1;
    }

    return 0;
  }

  int moveY() {
    int val = analogRead(p1);
    if (val < 300) {
      return -1;
    } else if (val > 700) {
      return 1;
    }

    return 0;
  }

  bool pressedBtn() {
    return analogRead(p2) <= 10;
  }
};
Joy joy(joyX, joyY, joyBtn);

class Menu {

  public:
  int opts_count;
  int m_length;
  int m_pos = 0;
  int m_cursor_pos = 0;
  int start_, end_;

  //    Menu(String options[], const int options_count, const int menu_length=1, const LCD_I2C& display_) {
  Menu(String options[],
    const int options_count,
      const int menu_length,
        const Joy & joy_) {
    opts = options;
    opts_count = options_count;
    m_length = menu_length;
    //      lcd(display_);     

    start_ = 0;
    end_ = menu_length - 1;
  }

  int i = 0;

  void change_option(int inc) {

  int old_pos = m_cursor_pos;
  m_cursor_pos = max(min(m_length - 1, m_cursor_pos + inc), 0);
  m_pos = max(min(opts_count - 1, m_pos + inc), 0);
  bool cursor_chaneged = old_pos != m_cursor_pos;

  if (!cursor_chaneged) {
    if (inc > 0) {
      if (end_ + 1 <= opts_count - 1) {

        ++start_;
        ++end_;
      }
    } else if (inc < 0) {
      if (start_ - 1 >= 0) {
        --start_;
        --end_;

      }
    }
  }
}

  void print() {

  lcd.clear();
  for (int i = 0; i < m_length; i++) {
    lcd.setCursor(0, i);

    String s = opts[i + start_], o;
    if (m_cursor_pos == i) {
      o = ">" + s + "<";
    } else {
      o = " " + s;
    }
    lcd.print(o);
  }
}

  int select() {
  bool selected;
  int change_opt;

  do {
    change_opt = joy.moveY();
    selected = joy.pressedBtn() || (joy.moveY() == 1);
  } while (!(change_opt || selected));

  if (change_opt) {
    wait_until_released();
    selected = 0;
    change_option(-change_opt);
    return -1;
  }

  return m_pos;
}

  private:
  String * opts;
};

String options[4] = {
  "     GRAJ     ",
  "    WYNIKI    ",
  "   JAK GRAC   ",
  "    O GRZE    "
};
int max_option = 4;
Menu menu(options, max_option, 2, joy);

void lcd_setup() {

  lcd.begin();
  
  lcd.createChar(TULIP_LEFT, tupli_left);
  lcd.createChar(TULIP_RIGHT, tupli_right);
  lcd.createChar(GARLIC, garlic);
  lcd.createChar(FLOWER_R, flower_r);
  lcd.createChar(FLOWER_L, flower_l);
  lcd.createChar(BERRY, berry);
  lcd.createChar(POPPY, poppy);
  lcd.createChar(UNKNOWN_FLOWER, unknown_flower);

  lcd.createChar(BUSH_TOP, bush_top);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.noAutoscroll();
  lcd.noBlink();
  lcd.noCursor();

  lcd.backlight();
}

void welcome_screen() {

  String s1 = "Flower";
  String s2 = "Picker";
  int s1_offset = 4;
  int s2_offset = 6;

  int s1_curr_offset = -s1.length();
  int s2_curr_offset = 16;

  byte top[WIDTH];
  byte bottom[WIDTH];

  while (s1_curr_offset < 17 && s2_curr_offset + s2.length() >= 0) {
    //for (int i=-max(s1.length(), s2.length()); i < 16; i++){

    for (int j = 0; j < WIDTH; j++) {
        top[j] = ASCII_SPACE;
        bottom[j] = ASCII_SPACE;
   }

    for (unsigned int j = 0; j < s1.length(); j++) {
      if (s1_curr_offset + j >= 0 && s1_curr_offset + j < 16) {
        top[s1_curr_offset + j] = s1[j];
      }
    }

    for (unsigned int j = 0; j < s2.length(); j++) {
      if (s2_curr_offset + j >= 0 && s2_curr_offset + j < 16) {
        bottom[s2_curr_offset + j] = s2[j];
      }
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    print_array(top, WIDTH);
    lcd.setCursor(0, 1);
    print_array(bottom, WIDTH);
    if (s1_curr_offset == s1_offset) {
      for (int k=0; k<3; k++){
        lcd.noBacklight();
        delay(250);
        lcd.backlight();
        delay(250);
      }
    } else {
      delay(100);
    }

    s1_curr_offset++;
    s2_curr_offset--;

  }
}

void display_menu() {
  int option = -1;
  while (option == -1) {
    menu.print();
    option = menu.select();
  }

  switch (option) {
  case 0: {
    play_game();
    break;
  }
  case 1: {
    list_records();
    break;
  }
  case 2: {
    how_to_play();
    break;
  }
  case 3: {
    about_page();
    break;
  }
  }
}

class Flower {
  
  public:

  byte x;
  byte y;
  uint8_t type;

  Flower(byte x_, byte y_){
    x = x_;
    y = y_;  
    int rnd = random(0, FLOWERS_TYPE_COUNT);
    type = FLOWERS[rnd];
  }
};


class Game {
  public:
  int score;
  byte ending;
  int ticks_left;
  int pos_x;
  int pos_y;

  int start_x;
  int start_y;

  int facing_x;
  int facing_y;

  bool running;
  std::vector<Flower> flowers;
  byte flowers_count;
  int state;
  
  Game(int x, int y) {

    start_x = x;
    start_y = y;
    reset();
    }
    
  void reset(){

    pos_x = start_x;
    pos_y = start_y;

    ticks_left = 20 * FPS;
    running = true;

    facing_x = (pos_x - MAP_WIDTH >= 0) - (pos_x - MAP_WIDTH <= 0);
    facing_y = (pos_y - MAP_HEIGHT >= 0) - (pos_y - MAP_HEIGHT <= 0);
    if (!facing_x) {
      facing_x = random(2) ? 1: -1;
    }
    if (!facing_y) {
      facing_x = random(2) ? 1: -1;
    }
    state = 0;
 
    float flower_desity = 1. / 8 / 8;
    flowers_count = max(1, ceil(MAP_WIDTH * MAP_HEIGHT * flower_desity));

    flowers.clear();
    for (int i = 0; i < flowers_count; i++){
      
      byte x, y;
      bool valid = false;
      while (!valid){
        x = random(0, MAP_WIDTH);
        y = random(0, MAP_HEIGHT);

        if (lvl_map[y][x] % 2){
          continue;
        }

        if (x == pos_x){
          continue;
        }

        if (y == pos_y){
          continue;
        }

        for (auto const& flower: flowers){
          if (x == flower.x && y == flower.x){
            continue;
          }
        }
        valid = true;
      }

      Flower flower(x,y);
      flowers.push_back(flower);
      } 
    }

  int is_flower(int x, int y){
    int idx=0;
    for(auto const& flower: flowers){
      if (flower.x == x && flower.y == y){
        return idx;
      }
      idx++;
    }
    return -1;
  }

  void move(int x, int y) {
    int tmp_x, tmp_y;
    tmp_x = (pos_x + x + MAP_WIDTH) % MAP_WIDTH;
    tmp_y = (pos_y + y + MAP_HEIGHT) % MAP_HEIGHT;

    if (pos_x == tmp_x && pos_y == tmp_y){
      state = 0;
    }
    else {
      state += facing_x;
    }
    
    if (lvl_map[tmp_y][tmp_x] % 2 == 0){ // can acess tile
      if (tmp_x - pos_x) {
        facing_x = ((tmp_x - pos_x) > 0) - ((tmp_x - pos_x) < 0);
      }
      if (tmp_y - pos_y) {
        facing_y = ((tmp_y - pos_y) > 0) - ((tmp_y - pos_y) < 0);
      }
      pos_x = tmp_x;
      pos_y = tmp_y;
    }

    int flower_idx = is_flower(pos_x, pos_y);
    if (flower_idx != -1){
      score += 10;
      ticks_left += 5 * FPS;    
      flowers.erase(flowers.begin() + flower_idx, flowers.begin() + flower_idx + 1);
    }

    // endings
    // not flowers left ending
    if (!flowers.size()){
      score += ticks_left / FPS;
      running = false;
      ending = 1;
    }

    // max score ending
    score = max(0, min(score, 255));
    if (score == 255){
      running = false;
      ending = 2;
    }

    // not time left ending
    --ticks_left;
    if (ticks_left <= 0){
      running = false;
      ticks_left = 0;
      ending = 3;
    }

    draw();
}
  
  void draw(){    
    int min_x, min_y;

    if (pos_x < WIDTH / 2){
      min_x = 0;
    }
    else if (MAP_WIDTH - pos_x < WIDTH / 2){
      min_x = MAP_WIDTH - WIDTH;
    }
    else {
      min_x = pos_x - WIDTH / 2;
    }
    
    //  need fix for bigger screens ?
    if (facing_y < 0){
      min_y = pos_y - 1;
    }
    else if (facing_y > 0) {
      min_y = pos_y;
    } 
    if (pos_y == 0) {
      min_y = 0;
    }
    if (pos_y == MAP_HEIGHT - 1){
      min_y = MAP_HEIGHT - 2;
    }

    int player_x;
    if (pos_x < WIDTH / 2){
      player_x = pos_x;
    }
    else if (MAP_WIDTH - pos_x < WIDTH / 2){
      player_x = WIDTH - (MAP_WIDTH - pos_x);
    }
    else {
      player_x = WIDTH / 2;
    }

    int player_y;
    if (facing_y > 0){
      player_y = 0;
      if (pos_y == MAP_HEIGHT - 1){
        player_y = 1;
      }
      }
    else if (facing_y < 0){
      player_y = 1;
    }
    if (pos_y == 0){
      player_y = 0;
    }
    if (pos_y == MAP_HEIGHT - 1){
      player_y = 1;
    }

    // draw map
    byte map_pice[WIDTH];
    for (byte j=0; j < HEIGHT; j++){
      lcd.setCursor(0,j);

      for (byte i=0; i < WIDTH; i++){
        map_pice[i] = get_char(lvl_map[min_y+j][min_x+i]);
      }

      print_array(map_pice, WIDTH);
    }

    // draw flowers
    for(auto const& flower: flowers) {
      if ((flower.x >= min_x && flower.x < min_x + WIDTH)  && (flower.y >= min_y && flower.y < min_y + HEIGHT)){
        lcd.setCursor(flower.x - min_x, flower.y - min_y);
        lcd.write(flower.type);
      }
    }
    // draw player
    byte stay_right[] = {
      B00110,
      B00110,
      B00000,
      B01110,
      B11111,
      B01110,
      B01010,
      B01010
    };
    
    byte stay_left[] = {
      B01100,
      B01100,
      B00000,
      B01110,
      B11111,
      B01110,
      B01010,
      B01010
    };
    
    byte run_right_1[] = {
      B00110,
      B00110,
      B10000,
      B01110,
      B01111,
      B01110,
      B01010,
      B10010
    };
    
    byte run_right_2[] = {
      B00110,
      B00110,
      B00000,
      B11111,
      B01110,
      B01111,
      B10000,
      B00000
    };
    
    byte run_right_3[] = {
      B00110,
      B00110,
      B00001,
      B01110,
      B11110,
      B01110,
      B01001,
      B00100
    };
    
    byte run_right_4[] = {
      B00110,
      B00110,
      B00000,
      B01110,
      B11111,
      B01110,
      B01010,
      B01010
    };
    
    byte run_left_1[] = {
      B01100,
      B01100,
      B00001,
      B01110,
      B11110,
      B01110,
      B01010,
      B01001
    };
    
    byte run_left_2[] = {
      B01100,
      B01100,
      B00000,
      B11111,
      B01110,
      B01111,
      B10000,
      B00001
    };
    
    byte run_left_3[] = {
      B01100,
      B01100,
      B10000,
      B01110,
      B01111,
      B01110,
      B01001,
      B00100
    };

    byte run_left_4[8] = {
      B01100,
      B01100,
      B00000,
      B01110,
      B11111,
      B01110,
      B01010,
      B01010
    };

    byte character[8];
    if (state > 0 ){
      int i = abs((state % 4));
      if (i==0){
        memcpy(character, run_right_1, 8);
      }
      else if (i==1){
        memcpy(character, run_right_2, 8);
      }
      else if (i==2){
        memcpy(character, run_right_3, 8);
      }
      else if (i==3){
        memcpy(character, run_right_4, 8);
      }
    }
    else if(state < 0){
      int i = abs((state % 4));
      if (i==0){
        memcpy(character, run_left_1, 8);
      }
      else if (i==1){
        memcpy(character, run_left_2, 8);
      }
      else if (i==2){
        memcpy(character, run_left_3, 8);
      }
      else if (i==3){
        memcpy(character, run_left_4, 8);
      }
    }
    else {
      if (facing_x > 0 ){
        memcpy(character, stay_right, 8);
      }else {
        memcpy(character, stay_left, 8);
      }
    }

    lcd.createChar(0, character);    
    lcd.setCursor(player_x, player_y);
    lcd.write(0);
    }

  private:
  byte get_char(byte c){
    switch (c){
      case 0:
        return ASCII_SPACE;
      case 1:
        return 255;
      case 3:
        return BUSH_TOP;
      default :
        return 88; // ASCII 'X' code
    }
  }
};

Game game(PLAYER_START_X, PLAYER_START_Y);

void game_action(){
  
  int x = - joy.moveX();
  int y = - joy.moveY();
  game.move(x,y);
}

void play_game() { 
  //counting
  lcd.clear();
  for (int i = 0; i < 17; i++) {
    lcd.setCursor(i, 0);
    lcd.write(255);
    delay(50);
    lcd.setCursor(i, 1);
    lcd.write(255);
  }

  for (int j = 3; j > 0; j--) {
    for (int i = 0; i < 17; i++) {
      lcd.setCursor(i - 1, j % 2 == 0);
      lcd.write(255);
      lcd.setCursor(i, j % 2 == 0);
      lcd.print(j);
      delay(1000 / 16);
    }
  }

  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("GO!");
  delay(1000);

  game.reset();
  timer.begin(game_action, 1000000/FPS);
  while(game.running){
    delay(10); // do not remove this, otherwise game won't stop after dead ¯\_(ツ)_/¯
  }
  
  timer.end();
  wait_until_released();
  if (game.ending == 1){
    lcd.setCursor(4, 0);
    lcd.print("TIME'S UP");
    lcd.setCursor(7, 1);
    lcd.print(game.score);
  }
  else if (game.ending == 2){
    lcd.setCursor(4, 0);
    lcd.print("MAX SCORE");
  }
  else if (game.ending == 3){
    lcd.setCursor(4, 0);
    lcd.print("GAME OVER");
    lcd.setCursor(7, 1);
    lcd.print(game.score);
    
  }

  // save score
  if (game.score) {
    byte scores[20];
    int idx =-1;
    for (int i = 0; i < 20; i++){
      byte score = EEPROM.read(i);
      scores[i] = score;
      if (score < game.score && idx != -1){
        idx = i;
      }
    }

    if (idx != -1) {
      for (int i = 19; i > idx; i--){
        EEPROM.write(i+1, scores[i]);
      }
      EEPROM.write(idx, game.score);
    }
  }

  delay(3000);
}

void list_records() {
  lcd.clear();
  wait_until_released();
  int scores_len = 0;
  String records[20];
  for (int i = 0; i < 20; i++) {
    char c[14];
    byte score = EEPROM.read(i);

    if (score > 0) {
      scores_len++;
    }

    if (i < 9) {
      sprintf(c, " TOP %d   %4d ", i + 1, score);
    } else {
      sprintf(c, " TOP %d  %4d ", i + 1, score);
    }

    String s(c);
    records[i] = s;
  }
  Menu records_menu(records, scores_len, 2, joy);

  int option = -1;
  while (option == -1) {
    records_menu.print();
    option = records_menu.select();
  }
  wait_until_released();
}

class Credists {
  public:
  int i = 0;
  String strs[10] = {
    "                ",
    "                ",
    "     Cezary     ",
    "    Paziewski   ",
    "     projekt    ",
    "  zaliczeniowy  ",
    "       na       ",
    "  programowanie ",
    "mikrokontrolerow",
    "    2020/2021   "
  };

  int s1, s2;
  Credits() {
    clear();
  };
  void inc() {
    s1 = s2;
    s2 = ++s2 % s_size;
  }
  void clear() {
    s1 = 0;
    s2 = 1;
  }

  void print() {
    String str1 = strs[s1];
    String str2 = strs[s2];
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(str1);
    lcd.setCursor(0, 1);
    lcd.print(str2);
    inc();
  };
  private:
    int s_size = sizeof(strs) / sizeof(strs[0]);
};

Credists credits;

void print_creds() {
  credits.print();
}

void about_page() {
  credits.clear();
  timer.begin(print_creds, 500000);
  wait_until_released();

  while (true) {
    if (joy.pressed()) {
      timer.end();
      wait_until_released();
      break;
    }
  }
}

void print_array(const byte arr[],
  const unsigned int arr_size) {
  for (unsigned int i = 0; i < arr_size; i++) {
    lcd.write(arr[i]);
  }
}

class How_to {
  public:
  int i = 0;
  String strs[11] = {
    "     Zbieraj    ",
    "     kwiatki    ",
    "        i       ",
    "     zdobywaj   ",
    "     punkty.    ",
    "     Zbierz     ",
    "    wszystkie   ",
    "      zanim     ",
    "     skonczy    ",
    "       sie      ",
    "      czas.     ",
  };

  int s1, s2, flowers;
  How_to() {
    clear();
  };
  void inc() {
    s1 = s2;
    if (s2 == 10){
      flowers = true;
    }
    s2 = ++s2 % s_size;
  }
  void clear() {
    s1 = 0;
    s2 = 1;
    flowers = true;
  }

  void print() {
    lcd.clear();
    if (flowers){
      flowers = false;
      for (int j = 0; j < HEIGHT; j++){
        lcd.setCursor(0, j);
        for (int i = 0; i < WIDTH; i++){
          lcd.write(random(1, 9));
        }
      }
      return;
    }
    
    String str1 = strs[s1];
    String str2 = strs[s2];
    lcd.setCursor(0, 0);
    lcd.print(str1);
    lcd.setCursor(0, 1);
    lcd.print(str2);
    inc();
  };
  private:
    int s_size = sizeof(strs) / sizeof(strs[0]);
};

How_to how_to;

void print_how_to(){
  how_to.print();
}

void how_to_play(){
  how_to.clear();
  timer.begin(print_how_to, 500000);
  wait_until_released();

  while (true) {
    if (joy.pressed()) {
      timer.end();
      wait_until_released();
      break;
    }
  }
}

void setup() {
  randomSeed(analogRead(SEED_PIN));
  lcd_setup();
  welcome_screen();
}

void loop() {
  display_menu();
}
