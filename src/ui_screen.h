#ifndef SCREEN_H
#define SCREEN_H

enum Screen_Type {
  START_SCREEN,
  CREATE_PROGRAM_SCREEN,
  RUN_PROGRAM_SCREEN,
};

class Screen {
  public:
    virtual void drawScreenToBuffer() = 0;
    virtual void up() = 0;
    virtual void down() = 0;
    virtual void left() = 0;
    virtual void right() = 0;
    virtual void select() = 0;
    virtual void back() = 0;
};

#endif