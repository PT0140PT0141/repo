#if !defined(__KEYBOARD_H__)
#define __KEYBOARD_H__

namespace raspberryUtil {

  namespace keyboard {

    class keyboard {
      
    public:
      keyboard() { };
      ~keyboard() { };

      static int kbhit();
      
    }; // End of class keyboard

  } // End of namespace keyboard

} // End of namespace raspberryUtil

#endif // __KEYBOARD_H__
