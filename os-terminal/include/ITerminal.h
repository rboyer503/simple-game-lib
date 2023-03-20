#ifndef ITERMINAL_H
#define ITERMINAL_H

#include <sstream>
#include <vector>


enum eTermMode
{
    TM_NORMAL,
    TM_GAME
};

enum eKBCode
{
    KB_NONE,
    KB_ESCAPE,
    KB_ENTER,
    KB_SPACE,
    KB_UP,
    KB_LEFT,
    KB_RIGHT,
    KB_DOWN,
    KB_A,
    KB_B,
    KB_C,
    KB_D,
    KB_E,
    KB_F,
    KB_G,
    KB_H,
    KB_I,
    KB_J,
    KB_K,
    KB_L,
    KB_M,
    KB_N,
    KB_O,
    KB_P,
    KB_Q,
    KB_R,
    KB_S,
    KB_T,
    KB_U,
    KB_V,
    KB_W,
    KB_X,
    KB_Y,
    KB_Z,
    KB_MAX
};

typedef std::vector<eKBCode> kb_codes_vec;


class ITerminal
{
protected:
    eTermMode term_mode_;

public:
    ITerminal() :
        term_mode_(TM_NORMAL)
    {}
    virtual ~ITerminal() {}

    eTermMode getMode() const {return term_mode_; }

    virtual bool initialize() = 0;
    virtual bool release() = 0;
    virtual bool setMode(eTermMode term_mode) = 0;
    virtual void clearScreen() const = 0;
    virtual void setCursorPos(int x, int y) const = 0;
    virtual void output(const std::ostringstream & oss, bool doFlush = true) const = 0;
    virtual void output(const std::string & str, bool doFlush = true) const = 0;
    virtual void doRefresh() const = 0;
    virtual bool pollKeys(kb_codes_vec & kb_codes) = 0;
};

#endif // ITERMINAL_H
