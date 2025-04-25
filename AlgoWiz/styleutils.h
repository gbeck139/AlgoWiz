#ifndef STYLEUTILS_H
#define STYLEUTILS_H
#include <QString>

inline const QString &gameButtonStyle() {
    static const QString s = R"(
    QPushButton {
      background: rgba(255,165,0,0.15);
      border: 2px solid #FFA500;
      border-radius: 8px;
      color: #ffffff;
      font: 700 18px 'Trebuchet MS';
      padding: 8px 16px;
    }
    QPushButton:hover {
      background: #FFA500;
      color: #000000;
    }
    QPushButton:pressed {
      background: #FF7B00;
      color: #000000;
    }
  )";
    return s;
}


#endif // STYLEUTILS_H
